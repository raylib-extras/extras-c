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

#include <stdlib.h>
#include <stdbool.h>

#if defined(_WIN32)
#ifndef MAX_PATH
#define MAX_PATH 1025
#endif


void* LoadLibraryA(void* lpLibFileName);
void* LoadLibraryW(void* lpLibFileName);

#ifdef UNICODE
#define LoadLibrary  LoadLibraryW
#else
#define LoadLibrary  LoadLibraryA
#endif // !UNICODE

void* GetProcAddress(void* hModule, void* lpProcName);

void* GetCurrentProcess(void);
bool FreeLibrary(void* hLibModule);

int  WideCharToMultiByte(unsigned int cp, unsigned long flags, const unsigned short* widestr, int cchwide, char* str, int cbmb, const char* defchar, int* used_default);

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
        typedef unsigned long(*GetModuleFileNameFunc)(void*, void*, void*, unsigned long);
        GetModuleFileNameFunc getModuleFileNameExWPtr = NULL;
        void* lib = LoadLibrary(L"psapi.dll");
        if (lib == NULL)
        {
            appDir[0] = '\\';
        }
        else
        {
#if defined (UNICODE)
			getModuleFileNameExWPtr = (GetModuleFileNameFunc)GetProcAddress(lib, "GetModuleFileNameExW");
#else
			getModuleFileNameExWPtr = (GetModuleFileNameFunc)GetProcAddress(lib, "GetModuleFileNameExA");
#endif

            if (getModuleFileNameExWPtr == NULL)
            {
                appDir[0] = '\\';
            }
            else
            {
                int len = 0;
#if defined (UNICODE)
				unsigned short widePath[MAX_PATH];
				len = getModuleFileNameExWPtr(GetCurrentProcess(), NULL, widePath, MAX_PATH);

                len = WideCharToMultiByte(0, 0, widePath, len, appDir, MAX_PATH, NULL, NULL);
#else
				len = getModuleFileNameExWPtr(GetCurrentProcess(), NULL, appDir, MAX_PATH);
#endif
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
            int len = strlen(appDir);
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