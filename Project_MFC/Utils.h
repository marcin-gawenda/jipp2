#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <windows.h>
#include <string>

class Utils {
public:
    static COLORREF CStringToColorRef(const CString& str);
    static char* ColorRefToCharArray(const COLORREF& color);
    static CString ColorRefToCString(const COLORREF& color);
    static char* CStringToCharArray(const CString& str);
    static CString CharArrayToCString(const char* cString);
};

#endif // UTILS_H
