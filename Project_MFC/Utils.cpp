#include "pch.h"
#include "Utils.h"
#include <sstream>
#include <cstring> // For strlen
#ifdef UNICODE
#include <cwchar> // For mbstowcs
#endif


// Method to convert a string in the format "RGB(r, g, b)" to a COLORREF
COLORREF Utils::StringToColorRef(const std::string& str) {
    size_t pos1 = str.find('(');
    size_t pos2 = str.find(')');
    std::string numbers = str.substr(pos1 + 1, pos2 - pos1 - 1);
    std::stringstream ss(numbers);
    int r, g, b;
    char comma;
    ss >> r >> comma >> g >> comma >> b;
    return RGB(r, g, b);
}

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


std::string Utils::ColorRefToString(const COLORREF& color) {
    // Extract the red, green, and blue components
    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);
    //char strColor[20];
    //sprintf_s(strColor, sizeof(strColor), "RGB(%d,%d,%d)", red, green, blue);
    // Create a string stream
    std::stringstream ss;
    ss << "RGB(" << red << "," << green << "," << blue << ")";

    // Convert to std::string and return
    //const char* cstr = ss.str().c_str();
    return ss.str();
}

char* Utils::StringToCharArray(const std::string& str) {
    // Allocate memory for the char array
    char* cstr = new char[str.length() + 1];

    // Copy the contents of the string to the char array
    strcpy_s(cstr, sizeof(cstr), str.c_str());

    return cstr;
}


#include <afxstr.h> // For CString

char* Utils::CStringToCharArray(const CString& str)
{
    // Allocate a buffer to hold the string
    char* buffer = new char[str.GetLength() + 1];
    // Copy the CString contents to the buffer
    strcpy_s(buffer,sizeof(buffer), str);
    return buffer;
}

void FreeCharBuffer(char* buffer)
{
    delete[] buffer;
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
    CString str = Utils::CharArrayToCString(ca);
    return ca;
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
