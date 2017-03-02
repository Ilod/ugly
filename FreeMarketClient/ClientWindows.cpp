#include "Client.h"
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

namespace FreeMarket
{
    bool GameServer::StartLocalServer(const std::string& commandLine)
    {
        HANDLE clientIn, clientOut, serverIn, serverOut;
        SECURITY_ATTRIBUTES sa;
        ZeroMemory(&sa, sizeof(sa));
        sa.nLength = sizeof(sa);
        sa.bInheritHandle = TRUE;
        sa.lpSecurityDescriptor = NULL;

        if (!CreatePipe(&clientIn, &serverOut, &sa, 16384))
            return false;
        if (!CreatePipe(&serverIn, &clientOut, &sa, 16384))
            return false;
        if (!SetHandleInformation(clientIn , HANDLE_FLAG_INHERIT, 0))
            return false;
        if (!SetHandleInformation(clientOut, HANDLE_FLAG_INHERIT, 0))
            return false;
        
        if (_dup2(_open_osfhandle((intptr_t)clientIn , _O_RDONLY), _fileno(stdin )) != 0)
            return false;
        if (_dup2(_open_osfhandle((intptr_t)clientOut, _O_WRONLY), _fileno(stdout)) != 0)
            return false;

        STARTUPINFOA si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        si.hStdInput = serverIn;
        si.hStdOutput = serverOut;
        si.dwFlags |= STARTF_USESTDHANDLES;
        PROCESS_INFORMATION pi;
        ZeroMemory(&pi, sizeof(pi));
        
        if (!CreateProcessA(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
            return false;

        return true;
    }
}
