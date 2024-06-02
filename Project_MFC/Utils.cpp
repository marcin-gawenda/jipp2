#include "pch.h"
#include "Utils.h"
#include <sstream>
#include <cstring> // For strlen
#ifdef UNICODE
#include <cwchar> // For mbstowcs
#endif


COLORREF Utils::CStringToColorRef(const CString& cStr) {
    // Convert CString to std::string
    CT2CA pszConvertedAnsiString(cStr);
    std::string str(pszConvertedAnsiString);
    size_t pos1 = str.find('(');
    size_t pos2 = str.find(')');
    std::string numbers = str.substr(pos1 + 1, pos2 - pos1 - 1);
    std::stringstream ss(numbers);
    int r, g, b;
    char comma;
    ss >> r >> comma >> g >> comma >> b;
    return RGB(r, g, b);
}


char* Utils::CStringToCharArray(const CString& str)
{
    // Allocate a buffer to hold the string
    char* buffer = new char[str.GetLength() + 1];
    // Copy the CString contents to the buffer
    strcpy_s(buffer,sizeof(buffer), str);
    return buffer;
}


char* Utils::ColorRefToCharArray(const COLORREF& color) {
    // Extract the red, green, and blue components
    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);
    char strColor[20];
    sprintf_s(strColor, sizeof(strColor), "RGB(%d,%d,%d)", red, green, blue);
    return strColor;
}

CString Utils::ColorRefToCString(const COLORREF& color) {
    char* ca = Utils::ColorRefToCharArray(color);   
    return Utils::CharArrayToCString(ca);    
}


CString Utils::CharArrayToCString(const char* cString)
{
#ifdef UNICODE
    // Convert char* to wchar_t*
    size_t newSize = strlen(cString) + 1;
    wchar_t* wString = new wchar_t[newSize];
    mbstowcs(wString, cString, newSize);
    CString myCString(wString);
    delete[] wString;  // Clean up the allocated memory
    return myCString;
#else
    return CString(cString);
#endif
}
