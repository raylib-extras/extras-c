/**********************************************************************************************
*
*   raylibExtras * Utilities and Shared Components for Raylib
*
*   path_utils * functions to help manage paths on different OSs
*
*   LICENSE: MIT
*
*   Copyright (c) 2020 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#if defined(_WIN32)

#include <windows.h>
const char PathDelim = '\\';

#elif defined(__linux__)
#include <unistd.h>
const char PathDelim = '/';

#elif defined(__APPLE__)
#include <sys/syslimits.h>
const char PathDelim = '/';

#endif // OSs

char appDir[4096 + 1] = { 0 };

const char* rlGetApplicationBasePath()
{
    if (appDir[0] == 0)
    {
        appDir[0] = '/' ; // default for everyone to start out with

#if defined(_WIN32)
        typedef DWORD(WINAPI* GetModuleFileNameFunc)(HANDLE, HMODULE, LPSTR, DWORD);
        GetModuleFileNameFunc getModuleFileNameExWPtr = NULL;
        HMODULE lib = LoadLibrary(L"psapi.dll");
        if (lib == NULL)
        {
            appDir[0] = '\\';
        }
        else
        {
            getModuleFileNameExWPtr = (GetModuleFileNameFunc)GetProcAddress(lib, "GetModuleFileNameExA");

            if (getModuleFileNameExWPtr == NULL)
            {
                appDir[0] = '\\';
            }
            else
            {
                int len = getModuleFileNameExWPtr(GetCurrentProcess(), NULL, appDir, MAX_PATH);
                if (len > 0)
                {
                    for (int i = len; i >= 0; --i)
                    {
                        if (appDir[i] == '\\')
                        {
                            appDir[i + 1] = '\0';
                            i = -1;
                        }
                    }
                }
            }
            FreeLibrary(lib);
        }
#elif defined(__linux__)
        unsigned int size = sizeof(appDir);

        ssize_t len = readlink("/proc/self/exe", appDir, size);
        if (len > 0)
        {
            for (int i = len; i >= 0; --i)
            {
                if (appDir[i] == '/')
                {
                    appDir[i + 1] = '\0';
                    i = -1;
                }
            }
        }

#elif defined(__APPLE__)
        uint32_t size = sizeof(appDir);

        if (_NSGetExecutablePath(appDir, &size) == 0)
        {
            int len = strlne(appDir);
            for (int i = len; i >= 0; --i)
            {
                if (appDir[i] == '/')
                {
                    appDir[i + 1] = '\0';
                    i = -1;
                }
            }
        }
#endif
    }
    return appDir;
}