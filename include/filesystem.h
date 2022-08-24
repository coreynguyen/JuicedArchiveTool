/*	======================================================================

	Title:		Windows File System Helper Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		General helper class for accessing files on windows

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		wrote it!

	======================================================================	*/
#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <shlwapi.h>
#include <cmath>
#include <tchar.h>
#include "stringext.h"
#include "wstringext.h"
#include <shlobj.h>
#include <sstream>


namespace win {
	std::wstring openfilenameW(const wchar_t* filter, HWND owner, unsigned long flags);
	std::string openfilename(const char *filter, HWND owner);
	std::string savefilename(const char *filter, HWND owner);


	int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

	bool GetDir();


	size_t getFileSize (std::string fileName);
	size_t getFileSizeW(std::wstring fileName);
	bool doesFileExist (std::string fileName);
	bool doesFileExistW (std::wstring fileName);
	bool doesFolderExist (std::string dirName_in);
	bool doesFolderExistW (std::wstring dirName_in);
	bool makeDirW(std::wstring wsPath);
	bool copyFile (std::string existing_filename, std::string target_filename);
	bool copyFileW (std::wstring existing_filename, std::wstring target_filename);
	bool moveFileW (std::wstring existing_filename, std::wstring target_filename);
	void getFilesW (std::wstring* &dirFiles, unsigned long &numFiles, std::wstring pattern);
	std::string runningPath();
	std::wstring runningPathW();
	};


#endif // FILESYSTEM_H
