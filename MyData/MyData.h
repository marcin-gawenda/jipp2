// MyData.h : main header file for the MyData DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#ifdef MYDATA_EXPORTS
#define MYDATA_API __declspec(dllexport)
#else
#define MYDATA_API __declspec(dllimport)
#endif

#include "resource.h"		// main symbols


// CMyDataApp
// See MyData.cpp for the implementation of this class
//

class CMyDataApp : public CWinApp
{
public:
	CMyDataApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


#pragma pack(push, 1)
class CExcept1App;

class MYDATA_API MY_COORD {
public:
	double x;
	double y;
};

class MYDATA_API MY_POINT : virtual public MY_COORD
{
public:
	char* name = nullptr;
	int numb;
	COLORREF color;

	// RGB(200, 200, 200)
	// _color = 0x00000000
	MY_POINT() { x = 0; y = 0; name = nullptr, numb = 0; color = RGB(200, 200, 200); }	
	MY_POINT(double xx, double yy, char* _name = nullptr, int _numb = 0, COLORREF _color = RGB(200, 200, 200)) { x = xx; y = yy; name = _name; numb = _numb; color = _color; }
	~MY_POINT() {}
	//~MY_POINT() { if (name) { delete[] name; name = nullptr; } }
	void set(double xx, double yy, char* _name = nullptr, int _numb = 0, COLORREF _color = RGB(200, 200, 200)) { x = xx; y = yy; name = _name; numb = _numb; color = _color; }
	MY_POINT get() { return *this; }

	// is capable to compare MY_POINT to do std::string
	bool operator==(const CString& key) const {
		return CString(name) == key;
	}
};

class MYDATA_API MY_DATA : public MY_POINT
{
protected:
	MY_POINT* pTab;
	int capacity;
	int last;
public:
	CExcept1App* pExcept;
public:
	MY_DATA(int no_it);
	MY_DATA(const MY_DATA& ob);
	~MY_DATA() { Free(); }
	void Free() { if (pTab) delete[] pTab; pTab = NULL; }
	void Init(int no_it);
	void Push(const MY_POINT& tmp);
	int size() { return last; }
	void clear() { last = 0; }

	MY_POINT& operator [] (const int i)
	{
		return pTab[i];
	}

	void GetMaxMinCoords(double& max_x, double& min_x, double& max_y, double& min_y);

private:
	MY_POINT* allocTab(MY_POINT* pTab, int i);
};

#pragma pack(pop)
