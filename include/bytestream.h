/*	======================================================================

	Title:		I/O Helper Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		General Binary i/o helper class

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		wrote it!

	======================================================================	*/

#ifndef BYTESTREAM_H
#define BYTESTREAM_H

#include <iostream>
#include <string>
#include <windows.h>
#include <type_traits>

// For floating point types
template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* p = nullptr>
constexpr T modulo(const T x, const T y) {return (x < T() ? T(-1) : T(1)) * ((x < T() ? -x : x) - static_cast<long long int>((x/y < T() ? -x/y : x/y)) * (y < T() ? -y : y));}
// For non-floating point types
template<typename T>
using TypeToCast = typename std::conditional<std::is_floating_point<T>::value, int, T>::type;
template<typename T, typename std::enable_if<!std::is_floating_point<T>::value>::type* p = nullptr>
constexpr T modulo(const T x, const T y) {return (static_cast<TypeToCast<T>>(x) % static_cast<TypeToCast<T>>(y));}



class bytestream {
  public:
	std::wstring fpath;
	std::wstring fname;
	std::wstring fext;
	size_t pos;
	unsigned long size;
	char* stream;
	bool islilEndian;
	bytestream ();
	virtual ~bytestream ();
	size_t getFileSizeW(std::wstring fileName);
	bool doesFolderExistW (std::wstring dirName_in);
	bool doesFileExistW (std::wstring fileName);
	bool doesFileExist (std::string fileName);
	bool makeDirW(std::wstring wsPath);
	std::wstring getFilenamePathW (const std::wstring &str);
	std::wstring getFilenameFileW(const std::wstring &str);
	std::wstring getFilenameTypeW (std::wstring const &path );
	void setBigEndian ();
	void setLittleEndian ();
	void close ();
	bool openFile (std::string filename);
	bool openFileW (std::wstring filename);
	bool openResource (int resource_id, const char* resource_class);
	bool amendFile (std::wstring filename, size_t &offset);
	bool writeFile (std::string filename, size_t offset = 0, size_t wsize = 0, char* data = NULL);
	bool writeFileW (std::wstring filename, size_t offset = 0, size_t wsize = 0, char* data = NULL);
	bool createFile (unsigned long bufferSize);
	void resize (size_t newsize);
	size_t tell ();
	void seek (unsigned long offset = 0, char dir = 0);
	signed long unsigned_to_signed(unsigned long n, char nbits);
	int8_t readbyte ();
	int16_t readshort ();
	int32_t readlong ();
	int64_t readlonglong ();
	uint8_t readUbyte ();
	uint16_t readUshort ();
	uint32_t readUlong ();
	uint64_t readUlonglong ();
	std::string readline ();
	std::string readstring (int length = -1, unsigned char term = 0x00);
	float readfloat ();
	double readdouble ();
	void writebyte (unsigned char val);
	void writeshort (unsigned short val);
	void writelong (unsigned long val);
	void writefloat (float val);
	void writedouble (double val);
	void writestring (std::string str, signed long length = -1);
	};

#endif // BYTESTREAM_H
