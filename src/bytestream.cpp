//#include <iostream>
//#include <string>
#include <cstring>
//#include <cstddef>
//#include <windows.h>
//#include <shlwapi.h>
//#include <cmath>
//#include <tchar.h>
//#include <vector>
//#include <iomanip> // needed for setprecision
//#include <sstream>
//#include <fstream>
//#include <time.h>	// needed for get_part_date

#include <windows.h>
#include <math.h>       /* pow */
#include "bytestream.h"
#include "resource.h"




bytestream::bytestream () {
	pos = 0;
	size = 0;
	stream = NULL;
	islilEndian = true;
	}
bytestream::~bytestream () {
	if (stream != NULL) {delete[] stream;}
	pos = 0;
	size = 0;
	stream = NULL;
	islilEndian = true;
	}
size_t bytestream::getFileSizeW(std::wstring fileName) {
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesExW((wchar_t*)fileName.c_str(), GetFileExInfoStandard, &fad))
		return -1; // error condition, could call GetLastError to find out more
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return size.QuadPart;
	}
bool bytestream::doesFileExist (std::string fileName) {
	DWORD dwAttrib = GetFileAttributesA(fileName.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
bool bytestream::doesFileExistW (std::wstring fileName) {
	DWORD dwAttrib = GetFileAttributesW((wchar_t*)fileName.c_str());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
bool bytestream::doesFolderExistW (std::wstring dirName_in) {
	//DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	DWORD ftyp = GetFileAttributesW((wchar_t*)dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) {
		return false;  //something is wrong with your path!
		}
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
		return true;   // this is a directory!
		}
	return false;    // this is not a directory!
	}
bool bytestream::makeDirW(std::wstring wsPath) {
	// https://www.codeguru.com/cpp/w-p/files/article.php/c4439/CreatePath--Full-Path-Creation-wstring-version.htm
	unsigned long attr;
	size_t pos;
	bool result = false;
	std::wstring tmp;

	if (wsPath.length() > 0) {
		if (wsPath[wsPath.length() - 1] != '\\') {
			wsPath += L"\\";
			}
		// Look for existing object:
		attr = GetFileAttributesW(wsPath.c_str());
		if (attr == 0xFFFFFFFF) { // doesn't exist yet - create it!
			pos = wsPath.find_last_of(L"\\", wsPath.length() - 2);
			if (pos != std::wstring::npos) {
				// Create parent dirs:
				result = makeDirW(wsPath.substr(0, pos + 1));
				}
			// Create node:
			result = result && CreateDirectoryW(wsPath.c_str(), NULL);
			CreateDirectoryW(wsPath.c_str(), NULL);
			}
		else if (FILE_ATTRIBUTE_DIRECTORY != attr) {
			// object already exists, but is not a dir
			result = false;
			}
		}
	return result;
	}
std::wstring bytestream::getFilenamePathW (const std::wstring &str) {
	// getFilenamePath file   -- returns: "g:\subdir1\subdir2\"
	wchar_t found;
	std::wstring strt;
	found = str.find_last_of(L"/\\");
	if (found != std::wstring::npos) {
		strt = str.substr(0, found);
		return (strt + L"\\");
		}
	else {
		return L"";
		}
	}
std::wstring bytestream::getFilenameFileW(const std::wstring &str) {
	// getFilenameFile file   -- returns: "myImage"
	wchar_t found;
	std::wstring strt;
	found = str.find_last_of(L"/\\");
	if (found < str.size()) {
		strt = str.substr(found + 1, -1);
		found = strt.find(L".");
		if (found < strt.size()) {
			strt = strt.substr(0, found);
			}
		//return strt;
		}
	else {
		strt = str;
		//return str;
		}
	wchar_t lastdot = strt.find_last_of(L".");
	if (lastdot == std::string::npos) return strt;
	return strt.substr(0, lastdot);
	}
std::wstring bytestream::getFilenameTypeW (std::wstring const &path ) {
	// getFilenameType file -- returns: ".jpg"
	std::wstring ext;
	wchar_t dotIdx = path.find_last_of( L"." );
	if ( dotIdx != std::wstring::npos ) {
		wchar_t dirSepIdx = path.find_last_of( L"/\\" );
		if ( dotIdx > dirSepIdx + 1 ) {
			ext = path.substr( dotIdx );
			}
		}
	return ext;
	}
void bytestream::setBigEndian () {islilEndian = false;}
void bytestream::setLittleEndian () {islilEndian = true;}
void bytestream::close () {
	if (stream != NULL) {delete[] stream;}
	pos = 0;
	size = 0;
	stream = NULL;
	islilEndian = true;
	}
bool bytestream::openFile(std::string filename) {
	return openFileW(std::wstring(filename.begin(), filename.end()));
	}
bool bytestream::openFileW (std::wstring filename) {
	HANDLE hFile = CreateFileW(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
		);

	// check that file was opened successfully
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to Open File\n";
		return false;
		}

	// Clear old buffer
	close();

	// get / check file size is larger then 0
	size = GetFileSize(hFile, NULL);
	if (size == 0) {
		std::cout << "Failed to read file. File is Empty?\n";
		return false;
		}

	// size char for buffer
	stream = new char[size];

	// attempt to read file contents into memory
	unsigned long dwBytesRead = 0;
	if(ReadFile(hFile, stream, size, &dwBytesRead, NULL) == FALSE || dwBytesRead != size) {
		std::cout << "Failed to copy file into memory\n";
		CloseHandle(hFile);
		close();
		return false;
		}

	// close out handle :-)
	CloseHandle(hFile);

	// extract components of file path
	fpath = getFilenamePathW(filename);
	fname = getFilenameFileW(filename);
	fext = getFilenameTypeW(filename);

	return true;
	}

bool bytestream::openResource (int resource_id, const char* resource_class) {

	/*
	https://mklimenko.github.io/english/2018/06/23/embed-resources-msvc/
	https://stackoverflow.com/questions/16527973/load-resource-as-byte-array-programmaticaly-in-c

	usage:
	openResource(IDR_DATA1, "RCDATA");
	*/

	HRSRC hResource = FindResourceA(NULL, MAKEINTRESOURCEA(resource_id), resource_class);
	if (hResource == NULL) {
		std::cout << "failed To Find Resource" << std::endl;
		return false;
		}

	HGLOBAL hMemory = LoadResource(NULL, hResource);
	if (hMemory == NULL) {
		std::cout << "failed To Load Resource" << std::endl;
		return false;
		}

	DWORD dwSize = SizeofResource(NULL, hResource);
	LPVOID lpAddress = LockResource(hMemory);

	if (dwSize == 0) {
		std::cout << "file is empty" << std::endl;
		return false;
		}

	if (stream != NULL) {
		delete[] stream;
		}

	size = dwSize;
	stream = new char[dwSize];
	memcpy(stream, lpAddress, dwSize);
	return true;
	}

bool bytestream::amendFile (std::wstring filename, size_t &offset) {

	HANDLE hFile = CreateFileW(
		filename.c_str(),		// file to open
		GENERIC_READ,			// open for reading
		FILE_SHARE_READ,		// share for reading
		NULL,					// default security
		OPEN_EXISTING,			// existing file only
		FILE_ATTRIBUTE_NORMAL,	// normal file
		NULL					// no attr. template
		);

	// check that file was opened successfully
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Failed to Open File\n";
		return false;
		}
	//std::cout << offset << std::endl;
	// get / check file size is larger then 0
	size_t fsize = GetFileSize(hFile, NULL);
	if (fsize == 0 || offset + fsize > size) {
		std::cout << "Failed to read file. File is Empty?\n";
		return false;
		}

	// attempt to read file contents into memory
	unsigned long dwBytesRead = 0;
	if(ReadFile(hFile, &stream[offset], fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize) {
		std::cout << "Failed to copy file into memory\n";
		CloseHandle(hFile);
		return false;
		}

	offset += fsize;

	// close out handle :-)
	CloseHandle(hFile);

	return true;
	}
bool bytestream::writeFile (std::string filename, size_t offset, size_t wsize, char* data ) {
	//std::wcout << "filename:\t" << filename << std::endl;
	if (data == NULL) {
		if (wsize < 1) {wsize = size - offset;}
		if (offset + wsize > size) {wsize = size - offset;}
		}
	else if (wsize == 0) {
		return false;
		}

	unsigned long dwBytesWritten = 0;
	unsigned long dwPos = 0;

	//std::wcout << L"File: " << filename << std::endl;
	HANDLE hFile = CreateFileA(
		filename.c_str(),			// open One.txt
		GENERIC_WRITE,						// open for reading
		FILE_SHARE_READ,					// do not share
		NULL,								// no security
		CREATE_ALWAYS,							// existing file only
		FILE_ATTRIBUTE_NORMAL,				// normal file
		NULL								// no attr. template
		);

	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << L"failed to write file:\n\t" << filename << std::endl;
		return false;
		}

	dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
	LockFile(hFile, dwPos, 0, wsize, 0);
	if (data == NULL) {
		WriteFile(hFile, stream + offset, wsize, &dwBytesWritten, NULL);
		}
	else {
		WriteFile(hFile, data, wsize, &dwBytesWritten, NULL);
		}

	UnlockFile(hFile, dwPos, 0, wsize, 0);
	CloseHandle(hFile);
	return true;
	}
bool bytestream::writeFileW (std::wstring filename, size_t offset, size_t wsize, char* data ) {
	//std::wcout << "filename:\t" << filename << std::endl;
	if (data == NULL) {
		if (wsize < 1) {wsize = size - offset;}
		if (offset + wsize > size) {wsize = size - offset;}
		}
	else if (wsize == 0) {
		return false;
		}

	unsigned long dwBytesWritten = 0;
	unsigned long dwPos = 0;

	//std::wcout << L"File: " << filename << std::endl;

	HANDLE hFile = CreateFileW(
		filename.c_str(),			// open One.txt
		GENERIC_WRITE,						// open for reading
		FILE_SHARE_READ,					// do not share
		NULL,								// no security
		CREATE_ALWAYS,							// existing file only
		FILE_ATTRIBUTE_NORMAL,				// normal file
		NULL								// no attr. template
		);

	if (hFile == INVALID_HANDLE_VALUE) {
		std::wcout << L"failed to write file:\n\t" << filename << std::endl;
		return false;
		}

	dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
	LockFile(hFile, dwPos, 0, wsize, 0);
	if (data == NULL) {
		WriteFile(hFile, stream + offset, wsize, &dwBytesWritten, NULL);
		}
	else {
		WriteFile(hFile, data, wsize, &dwBytesWritten, NULL);
		}

	UnlockFile(hFile, dwPos, 0, wsize, 0);
	CloseHandle(hFile);
	return true;
	}
bool bytestream::createFile (unsigned long bufferSize) {
	if (bufferSize > 0) {
		close();
		size = bufferSize;
		stream = new char[bufferSize];
		return true;
		}
	return false;
	}
void bytestream::resize (size_t newsize) {
	if (newsize > size && stream != NULL) {
		delete[] stream;
		pos = 0;
		size = newsize;
		stream = new char[size];
		}
	else if (stream != NULL) {
		size = newsize;
		}
	else {
		size = newsize;
		stream = new char[size];
		}
	}
size_t bytestream::tell () {return pos;}
void bytestream::seek (unsigned long offset, char dir) {
	switch (dir) {
		case 0: pos = offset; break;	// abs
		case 1: pos += offset; break;	// rel
		case 2: pos -= offset; break;	// end
		}
	if (pos > size) {pos = size;}
	}
signed long bytestream::unsigned_to_signed (unsigned long n, char nbits) {	// unsigned_to_signed 0x80 8 = -128
	signed long result = n;
	if (n > pow(2, nbits) / 2) {
		result = n - pow(2, nbits);
		}
	return result;
	}
uint8_t bytestream::readUbyte () {
	uint8_t result = 0xFF;
	if (pos + 1 <= size) {
		result = (uint8_t)stream[pos];
		pos += 1;
		}
	return result;
	}
uint16_t bytestream::readUshort () {
	unsigned char byteOrder[] = {0, 1};
	if (!islilEndian) {byteOrder[0] = 1; byteOrder[1] = 0;}
	uint16_t result = 0xFFFF;
	if (pos + 2 <= size) {
		//result = (uint16_t)((uint8_t)stream[pos + byteOrder[0]] * 0x0001);
		//result += (uint16_t)((uint8_t)stream[pos + byteOrder[1]] * 0x0100);
		result = ((unsigned short)stream[pos + byteOrder[1]] << 8) | (unsigned char)stream[pos + byteOrder[0]];
		pos += 2;
		}
	return result;
	}
uint32_t bytestream::readUlong () {
	unsigned char byteOrder[] = {0, 1, 2, 3};
	if (!islilEndian) {
		byteOrder[0] = 3; byteOrder[1] = 2;
		byteOrder[2] = 1; byteOrder[3] = 0;
		}
	uint32_t result = 0xFFFFFFFF;
	if (pos + 4 <= size) {
		result = {
			(uint32_t)((uint8_t)stream[pos + byteOrder[0]] * 0x00000001) + \
			(uint32_t)((uint8_t)stream[pos + byteOrder[1]] * 0x00000100) + \
			(uint32_t)((uint8_t)stream[pos + byteOrder[2]] * 0x00010000) + \
			(uint32_t)((uint8_t)stream[pos + byteOrder[3]] * 0x01000000)
			};


/*
int a = int((unsigned char)(buffer[0]) << 24 |
            (unsigned char)(buffer[1]) << 16 |
            (unsigned char)(buffer[2]) << 8 |
            (unsigned char)(buffer[3]));

*/



		pos += 4;
		}
	return result;
	}
uint64_t bytestream::readUlonglong () {
	unsigned char byteOrder[] = {0, 1, 2, 3, 4, 5, 6, 7};
	if (!islilEndian) {
		byteOrder[0] = 7; byteOrder[1] = 6; byteOrder[2] = 5;
		byteOrder[3] = 4; byteOrder[4] = 3; byteOrder[5] = 2;
		byteOrder[6] = 1; byteOrder[7] = 0;
		}
	unsigned long long result = {
		((uint8_t)stream[pos + byteOrder[0]] * (unsigned long long)0x0000000000000001) + \
		((uint8_t)stream[pos + byteOrder[1]] * (unsigned long long)0x0000000000000100) + \
		((uint8_t)stream[pos + byteOrder[2]] * (unsigned long long)0x0000000000010000) + \
		((uint8_t)stream[pos + byteOrder[3]] * (unsigned long long)0x0000000001000000) + \
		((uint8_t)stream[pos + byteOrder[4]] * (unsigned long long)0x0000000100000000) + \
		((uint8_t)stream[pos + byteOrder[5]] * (unsigned long long)0x0000010000000000) + \
		((uint8_t)stream[pos + byteOrder[6]] * (unsigned long long)0x0001000000000000) + \
		((uint8_t)stream[pos + byteOrder[7]] * (unsigned long long)0x0100000000000000)
		};
	pos += 8;
	return result;
	}
int8_t bytestream::readbyte() {return (int8_t)unsigned_to_signed(readUbyte(), 8);}
int16_t bytestream::readshort() {return (int16_t)unsigned_to_signed(readUshort(), 16);}
int32_t bytestream::readlong() {return (int32_t)unsigned_to_signed(readUlong(), 32);}
int64_t bytestream::readlonglong() {return (int64_t)unsigned_to_signed(readUlonglong(), 64);}
std::string bytestream::readstring (int length, unsigned char term) {
	std::string result = "";
	unsigned char letter;
	bool isTerm = false;
	if (length < 0) {
		while (isTerm == false && pos < size) {
			if (pos < size) {
				letter = stream[pos];
				pos++;
				}
			else {
				isTerm = true;
				}
			if (letter == term) {isTerm = true;}
			if (isTerm == false) {result += letter;}
			}
		}
	else {
		if (length > 0 && (pos + length) <= size) {
			result.reserve(length);
			for (int i = 0; i < length; ++i) {
				letter = stream[pos];
				pos++;
				if (letter == 0) {isTerm = true;}
				if (isTerm == false) {result += letter;}
				}
			}
		}
	return result;
	}
std::string bytestream::readline () {
	uint32_t startpoint = pos;
	std::string line = "";
	while (pos < size && stream[pos] != 0x0A && stream[pos] != 0x0D) {
		pos++;
		}
	if (pos > startpoint) {
		line = std::string(&stream[startpoint], pos - startpoint);
		}
	while (pos < size && (stream[pos] == 0x0A || stream[pos] == 0x0D)) {
		pos++;
		}
	return line;
	}
float bytestream::readfloat () {
	float result = 0.0;
	unsigned long b = readUlong();
	memcpy(&result, &b, 4);
	return result;
	}
double bytestream::readdouble () {
	double result = 0.0;
	unsigned long long b = readUlonglong();
	memcpy(&result, &b, 8);
	return result;
	}
void bytestream::writebyte (unsigned char val) {
	stream[pos] = val;
	pos++;
	}
void bytestream::writeshort (unsigned short val) {
	if (!islilEndian) {
		stream[pos + 1] = val & 0x00FF;
		stream[pos + 0] = (val & 0xFF00) >> 8;
		}
	else {
		stream[pos + 1] = (val & 0xFF00) >> 8;
		stream[pos + 0] = val & 0x00FF;
		}
	pos+=2;
	}
void bytestream::writelong (unsigned long val) {
	if (!islilEndian) {
		stream[pos + 3] = val & 0x00FF;
		stream[pos + 2] = (val & 0xFF00) >> 0x08;
		stream[pos + 1] = (val & 0xFF0000) >> 0x10;
		stream[pos + 0] = (val & 0xFF000000) >> 0x18;
		}
	else {
		stream[pos + 3] = (val & 0xFF000000) >> 0x18;
		stream[pos + 2] = (val & 0xFF0000) >> 0x10;
		stream[pos + 1] = (val & 0xFF00) >> 0x08;
		stream[pos + 0] = val & 0x00FF;
		}
	pos+=4;
	}
//void bytestream::writefloat (float val) {
//	unsigned char* c = (unsigned char*) &val;
//	if (!islilEndian) {
//		stream[pos + 3] = c[0];
//		stream[pos + 2] = c[1];
//		stream[pos + 1] = c[2];
//		stream[pos + 0] = c[3];
//		}
//	else {
//		stream[pos + 3] = c[3];
//		stream[pos + 2] = c[2];
//		stream[pos + 1] = c[1];
//		stream[pos + 0] = c[0];
//		}
//	pos+=4;
//	}
void bytestream::writestring (std::string str, signed long length) {
	if (length > -1) {
		unsigned long len = length;
		for (unsigned long i = 0; i < len; i++) {
			if (i < str.size()) {
				writebyte(str[i]);
				}
			else {
				writebyte(0);
				}
			}
		}
	else {
		if (str.size() > 0) {
			for (unsigned long i = 0; i < str.size(); i++) {
				writebyte(str[i]);
				}
			}
		writebyte(0);
		}
	}
void bytestream::writefloat (float val) {
	unsigned char* c = (unsigned char*) &val;
	char order[4] = {0, 1, 2, 3};
	for (int i = 0; i < 4; i++) {
		stream[pos + order[i]] = c[i];
		}
	pos+=4;
	}
void bytestream::writedouble (double val) {
	unsigned char* c = (unsigned char*) &val;
	char order[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < 8; i++) {
		stream[pos + order[i]] = c[i];
		}
	pos+=8;
	}
