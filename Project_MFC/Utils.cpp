#include "pch.h"
#include "Utils.h"
#include <sstream>

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

char* Utils::ColorRefToCharArray(COLORREF color) {
    // Extract the red, green, and blue components
    int red = GetRValue(color);
    int green = GetGValue(color);
    int blue = GetBValue(color);
    char strColor[20];
    sprintf_s(strColor, sizeof(strColor), "RGB(%d,%d,%d)", red, green, blue);
    return strColor;
}

