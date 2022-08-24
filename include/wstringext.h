/*	======================================================================

	Title:		Wide String Helper Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		General wide string helper class

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		wrote it!

	======================================================================	*/

#ifndef WSTRINGEXT_H
#define WSTRINGEXT_H

#include <iostream>
#include <string>

#include <windows.h>
#include <shlwapi.h>

std::wstring toUpperW(const std::wstring &s);
std::wstring toLowerW(const std::wstring &s);
std::wstring getFilenamePathW (const std::wstring &str);
std::wstring openfilenameW(const wchar_t* filter, HWND owner, unsigned long flags);
std::wstring getFilenameFileW(const std::wstring &str);
std::wstring getFilenameTypeW (std::wstring const &path);
std::wstring string_to_wstring (std::string s);
std::wstring getSavePathW(std::wstring defaultPath = L"", const wchar_t* szCaption = L"Browse for folder...", unsigned int flags = BIF_USENEWUI, HWND hOwner = NULL);

#endif // WSTRINGEXT_H
