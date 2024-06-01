#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <windows.h>
#include <string>

class Utils {
public:
    static COLORREF StringToColorRef(const std::string& str);
    static std::string ColorRefToString(const COLORREF& color);
    static char* ColorRefToCharArray(COLORREF color);
    static char* StringToCharArray(const std::string& str);
};

#endif // UTILS_H
