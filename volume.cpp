#include "volume.h"

bool Volume::GetHandle()
{
    // "\\.\"是win32的设备名字空间 通过该前缀可绕过文件系统直接和物理设备交互
    QString FileName = "\\\\.\\";
    FileName += m_volume;
    FileName += ":";

    LPCWSTR lstrFileName = (const wchar_t*) FileName.utf16();
    hVol = CreateFile( lstrFileName,
                       GENERIC_READ | GENERIC_WRITE,
                       FILE_SHARE_READ | FILE_SHARE_WRITE,
                       nullptr,
                       OPEN_EXISTING,
                       FILE_ATTRIBUTE_READONLY,
                       nullptr);
    if (hVol != INVALID_HANDLE_VALUE) {
        qDebug() << "GetHandle OK" << endl;
        return true;
    } else {
        qDebug() << "GetHandle Failed: " << GetLastError() << endl;
        return false;
    }
}

bool Volume::CreateUSN()
{
    // 在目标卷上创建update sequence number(USN)更改日志流
    // 或修改现有的更改日志流
    created_usn_data.MaximumSize = 0;
    created_usn_data.AllocationDelta = 0;

    DWORD dwBytes;
    if (DeviceIoControl(hVol,
                        FSCTL_CREATE_USN_JOURNAL,
                        &created_usn_data,
                        sizeof(created_usn_data),
                        nullptr,
                        0,
                        &dwBytes,
                        nullptr)) {
        qDebug() << "CreateUSN ok" << endl;
        return true;
    } else {
        qDebug() << "Init USN falied: " << GetLastError() << endl;
        return false;
    }
}

bool Volume::GetUSNInfo()
{
    // 查询当前USN变更日志 记录和容量的信息
    DWORD dwBytes;
    if (DeviceIoControl(hVol,
                        FSCTL_QUERY_USN_JOURNAL,
                        nullptr,
                        0,
                        &JournalData,
                        sizeof(JournalData),
                        &dwBytes,
                        nullptr)) {
        qDebug() << "Query journal ok" << endl;
        return true;
    } else {
        qDebug() << "Query journal falied: " << GetLastError() << endl;
        return false;
    }
}

bool Volume::ReadUSNJournal() {
    const int BUF_LEN = 4096;
    CHAR Buffer[BUF_LEN];
    DWORD dwBytes, dwRetBytes;
    PUSN_RECORD UsnRecord;

    // NTFS文件系统包含一个名为master file的文件
    // 有关文件的所有信息（包括其大小、时间和日期戳、
    // 权限和数据内容）都存储在MFT条目中
    MFT_ENUM_DATA_V0 mft_data;
    mft_data.StartFileReferenceNumber = 0;
    mft_data.LowUsn = JournalData.FirstUsn;
    mft_data.HighUsn = JournalData.NextUsn;

    frnPfrnNameMap[0x5000000000005].FileName = QString{m_volume} + ":";
    frnPfrnNameMap[0x5000000000005].ParentFileReferenceNumber = 0;

    while (DeviceIoControl(hVol,
                           FSCTL_ENUM_USN_DATA,
                           &mft_data,
                           sizeof (mft_data),
                           Buffer,
                           BUF_LEN,
                           &dwBytes,
                           NULL)) {
        dwRetBytes = dwBytes - sizeof(USN);

        // 找到第一条USN记录
        UsnRecord = (PUSN_RECORD)(((PUCHAR)Buffer) + sizeof(USN));

        while (dwRetBytes > 0) {
            // 获取 ParentFileReferenceNumber FileReferenceNumber FileName FileNameLength
            /* FileReferenceNumber: 将日志记录与文件相关联的随机值
             * ParentFileReferenceNumber: 与此记录关联的文件或目录所在目录的序号
             */

            pfrn_name.FileName =  QString::fromWCharArray(UsnRecord->FileName, UsnRecord->FileNameLength/2);;
            pfrn_name.ParentFileReferenceNumber = UsnRecord->ParentFileReferenceNumber;
            frnPfrnNameMap[UsnRecord->FileReferenceNumber] = pfrn_name;

            DWORD record_len = UsnRecord->RecordLength;

            dwRetBytes -= record_len;
            // Find the next record
            UsnRecord = (PUSN_RECORD)(((PCHAR)UsnRecord) +
                                      record_len);
        }
        mft_data.StartFileReferenceNumber = *(USN*)&Buffer;
    }
    qDebug() << frnPfrnNameMap.size() << endl;
    return true;
}

bool Volume::DeleteUSN()
{
    DELETE_USN_JOURNAL_DATA DeleteData;
    DeleteData.UsnJournalID = JournalData.UsnJournalID;
    DeleteData.DeleteFlags = USN_DELETE_FLAG_DELETE;
    DWORD dwBytes;

    if ( DeviceIoControl(hVol,
        FSCTL_DELETE_USN_JOURNAL,
        &DeleteData,
        sizeof (DeleteData),
        NULL,
        0,
        &dwBytes,
        NULL)
        ) {
            CloseHandle(hVol);
            return true;
    } else {
        CloseHandle(hVol);
        return false;
    }
}

bool Volume::GetFilePathByFrn(DWORDLONG frn, QString& path)
{
    auto it = frnPfrnNameMap.find(frn);
    if (it != frnPfrnNameMap.end()) {
        if (it->second.ParentFileReferenceNumber != 0) {
            GetFilePathByFrn(it->second.ParentFileReferenceNumber, path);
        }
        path += it->second.FileName;
        path += '\\';
    }
    return true;
}
