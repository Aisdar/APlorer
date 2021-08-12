//#pragma execution_character_set("utf-8")
#include "ntfsdata.h"

NTFSData::NTFSData()
{

}

void NTFSData::initData(QStringList& fileName)
{
    GetVolumeVector();
    for (auto i : volume_vec) {
        i.InitVolumeInformation();
        for (auto j : i.fileNameVec) {
            fileName << j;
        }
    }
}

bool NTFSData::isNTFS(char c)
{
    char lpRootPathName[] = ("c:\\");
    lpRootPathName[0] = c;
    char lpVolumeNameBuffer[MAX_PATH];
    DWORD lpVolumeSerialNumber;
    DWORD lpMaximumComponentLength;
    DWORD lpFileSystemFlags;
    char lpFileSystemNameBuffer[MAX_PATH];

    if ( GetVolumeInformationA(
        lpRootPathName,
        lpVolumeNameBuffer,
        MAX_PATH,
        &lpVolumeSerialNumber,
        &lpMaximumComponentLength,
        &lpFileSystemFlags,
        lpFileSystemNameBuffer,
        MAX_PATH
        )) {
        if (!strcmp(lpFileSystemNameBuffer, "NTFS")) {
            return true;
        }
    }
    return false;
}

bool NTFSData::GetVolumeVector()
{
    for (int i = 0; i < 26; i++) {
        char vol = 'A' + i;
        if (isNTFS(vol)) {
            qDebug() << vol << "盘是NTFS格式. " << endl;
            volume_vec.push_back(Volume(vol));
        }
    }
    return true;
}
