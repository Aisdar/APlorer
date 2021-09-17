#include "CShell.h"
#include <QDebug>
#include <assert/advanced_assert.h>

<<<<<<< HEAD
#ifdef _WIN32
=======
>>>>>>> 11211436808d976b99da47c5654be94dca8d7116
#include <initguid.h>
#include <Shobjidl.h>
#include <ShlObj.h>
#include <windowsx.h>
#include <Windows.h>


// [!]
#pragma comment(lib, "user32.lib")

class CItemIdListReleaser {
public:
    explicit CItemIdListReleaser(ITEMIDLIST * idList) : _idList(idList) {}
    ~CItemIdListReleaser() { if (_idList) CoTaskMemFree(_idList); }
private:
    ITEMIDLIST * _idList;
};

class CComInterfaceReleaser {
public:
    explicit CComInterfaceReleaser(IUnknown * i) : _i(i) {}
    ~CComInterfaceReleaser() { if (_i) _i->Release(); }
private:
    IUnknown * _i;
};

class CItemIdArrayReleaser {
public:
    explicit CItemIdArrayReleaser(const std::vector<ITEMIDLIST*>& idArray) : _array(idArray) {}
    ~CItemIdArrayReleaser() {
        for (ITEMIDLIST* item: _array)
            CoTaskMemFree(item);
    }

    CItemIdArrayReleaser& operator=(const CItemIdArrayReleaser&) = delete;
private:
    const std::vector<ITEMIDLIST*>& _array;
};

bool prepareContextMenuForObjects(std::vector<std::wstring> objects, void * parentWindow, HMENU& hmenu, IContextMenu*& imenu)
{
    if (objects.empty())
        return false;

    std::vector<ITEMIDLIST*> ids;
    std::vector<LPCITEMIDLIST> relativeIds;
    IShellFolder * ifolder = 0;

    for (size_t i = 0, nItems = objects.size(); i < nItems; ++i)
    {
        auto& item = objects[i];
        std::replace(item.begin(), item.end(), '/', '\\');
        qDebug() << " -----> " << item;
        ids.emplace_back(nullptr);
        HRESULT result = SHParseDisplayName(item.c_str(), nullptr, &ids.back(), 0, nullptr); // TODO: avoid c_str() somehow?
        if (!SUCCEEDED(result) || !ids.back())
        {
            ids.pop_back();
            continue;
        }

        relativeIds.emplace_back(nullptr);
        result = SHBindToParent(ids.back(), IID_IShellFolder, (void**)&ifolder, &relativeIds.back());
        if (!SUCCEEDED(result) || !relativeIds.back())
            relativeIds.pop_back();
        else if (i < nItems - 1 && ifolder)
        {
            ifolder->Release();
            ifolder = nullptr;
        }
    }

    CItemIdArrayReleaser arrayReleaser(ids);

    assert_r(parentWindow);
    assert_and_return_message_r(ifolder, "Error getting ifolder", false);
    assert_and_return_message_r(!relativeIds.empty(), "RelativeIds is empty", false);
    imenu = 0;
    HRESULT result = ifolder->GetUIObjectOf((HWND)parentWindow, (UINT)relativeIds.size(), (const ITEMIDLIST **)relativeIds.data(), IID_IContextMenu, 0, (void**)&imenu);
    if (!SUCCEEDED(result) || !imenu)
        return false;

    hmenu = CreatePopupMenu();
    if (!hmenu)
        return false;

    return (SUCCEEDED(imenu->QueryContextMenu(hmenu, 0, 1, 0x7FFF, CMF_NORMAL)));
}

bool OsShell::openShellContextMenuForObjects(const std::vector<std::wstring>& objects, int xPos, int yPos, void * parentWindow)
{
    IContextMenu * imenu = 0;
    HMENU hMenu = NULL;
    if (!prepareContextMenuForObjects(objects, parentWindow, hMenu, imenu) || !hMenu || !imenu)
        return false;

    CComInterfaceReleaser menuReleaser(imenu);

    const int iCmd = TrackPopupMenuEx(hMenu, TPM_RETURNCMD, xPos, yPos, (HWND)parentWindow, NULL);
    if (iCmd > 0)
    {
        CMINVOKECOMMANDINFO info = { 0 };
        info.cbSize = sizeof(info);
        info.hwnd = (HWND)parentWindow;
        info.lpVerb  = MAKEINTRESOURCEA(iCmd - 1);
        info.nShow = SW_SHOWNORMAL;
        imenu->InvokeCommand((LPCMINVOKECOMMANDINFO)&info);
    }

    DestroyMenu(hMenu);

    return true;
}
