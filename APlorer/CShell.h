#ifndef CSHELL_H
#define CSHELL_H

#include <string>
#include <vector>

class QString;

namespace OsShell
{
    bool openShellContextMenuForObjects(const std::vector<std::wstring>& objects, int xPos, int yPos, void * parentWindow);
};

#endif // CSHELL_H
