#ifndef HELPER_H
#define HELPER_H

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

//#ifdef UNICODE
//	typedef WCHAR    TCHAR;
//#else
//	typedef char     TCHAR;
//#endif


#include <iostream>
#include <string>
#include <cstring>
#include <windows.h>
#include <shlwapi.h>
#include <cmath>
#include <tchar.h>
#include <vector>
#include <iomanip> // needed for setprecision
#include <sstream>
#include <fstream>
#include <time.h>	// needed for get_part_date
//#include <climits>

/*
	Set of common functions I often use, where functionality
	is similar to native maxscript functions to make it easier
	to port my maxscript's into native c++

	As I've adopted usage of unicode, alot more funcitons have
	made the switch to windows API ones.

	The following libraries may be required
		#include <windows.h>
		#include <direct.h>
		#include <dirent.h>
		#include <shlwapi.h>
		#include <stdio.h>
		#include <shellapi.h>

	Along with these linker flags
		-lwinmm
		-lshlwapi
		-lcomdlg32
		-lole32
	*/


// usage: swap_endian<uint32_t>(42).
// https://stackoverflow.com/a/4956493
//template <typename T>
//T swap_endian(T u)
//{
//    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");
//
//    union
//    {
//        T u;
//        unsigned char u8[sizeof(T)];
//    } source, dest;
//
//    source.u = u;
//
//    for (size_t k = 0; k < sizeof(T); k++)
//        dest.u8[k] = source.u8[sizeof(T) - k - 1];
//
//    return dest.u;
//}

enum seekType {set, end, cur};
enum signIs {Signed, Unsigned};

namespace myTypes {	// Data Types
	struct color {
		float r;
		float g;
		float b;
		float a;
		color (float c_r = 0.0, float c_g = 0.0, float c_b = 0.0, float c_a = 1.0) {
			r = c_r; g = c_g; b = c_b; a = c_a;
			}
		};
	struct p2 {
		float x;
		float y;
		p2 (float p_x = 0.0, float p_y = 0.0) {
			x = p_x; y = p_y;
			}
		float getDistance (p2 point) {
			return std::sqrt(pow(point.x - x, 2) + pow(point.y - y, 2) * 1.0);
			}
		};
	struct uv {
		float u;
		float v;
		uv (float p_u = 0.0, float p_v= 0.0) {
			u = p_u; v = p_v;
			}
		};
	struct p3 {
		float x;
		float y;
		float z;
		p3 (float p_x = 0.0, float p_y = 0.0, float p_z = 0.0) {
			x = p_x; y = p_y; z = p_z;
			}
		void normalize () {
			double div = std::sqrt((x * x) + (y * y) + (z * z));
			if (x == 0 && y == 0 && z == 0) {
				x = 1.0f; y = 0.0f; z = 0.0f;
				}
			else {
				x = x / div; y = y / div; z = z / div;
				}
			}
		p3 cross(p3 crossProd) {
			crossProd.x = crossProd.y * z - crossProd.z * y;
			crossProd.y = crossProd.z * x - crossProd.x * z;
			crossProd.z = crossProd.x * y - crossProd.y * x;
			return crossProd;
			}
		};
	struct p4 {
	public:
		float x;
		float y;
		float z;
		float w;
		p4 (float p_x = 0.0, float p_y = 0.0, float p_z = 0.0, float p_w = 0.0) {
			x = p_x;
			y = p_y;
			z = p_z;
			w = p_w;
			}
		float dot(p4& other) const {
			return x * other.x + y * other.y + z * other.z + w * other.w;
			};
		};
	struct weight4 {
		float w1;
		float w2;
		float w3;
		float w4;
		signed long b1;
		signed long b2;
		signed long b3;
		signed long b4;
		};
	class Vec4 {
	public:
		Vec4(float x, float y, float z, float w) :
			x(x), y(y), z(z), w(w) {}

		float dot(const Vec4& other) const {
			return x * other.x + y * other.y + z * other.z + w * other.w;
			};

		float x, y, z, w;
		};
	class Mat4x4 {
	public:
		float values[16];
		Mat4x4() {
			values[0] =  1.0;
			values[1] =  0.0;
			values[2] =  0.0;
			values[3] =  0.0;
			values[4] =  0.0;
			values[5] =  1.0;
			values[6] =  0.0;
			values[7] =  0.0;
			values[8] =  0.0;
			values[9] =  0.0;
			values[10] = 1.0;
			values[11] = 0.0;
			values[12] = 0.0;
			values[13] = 0.0;
			values[14] = 0.0;
			values[15] = 1.0;
			}
		Mat4x4(float v00, float v01, float v02, float v03,
				float v10, float v11, float v12, float v13,
				float v20, float v21, float v22, float v23,
				float v30, float v31, float v32, float v33) {
			values[0] =  v00;
			values[1] =  v01;
			values[2] =  v02;
			values[3] =  v03;
			values[4] =  v10;
			values[5] =  v11;
			values[6] =  v12;
			values[7] =  v13;
			values[8] =  v20;
			values[9] =  v21;
			values[10] = v22;
			values[11] = v23;
			values[12] = v30;
			values[13] = v31;
			values[14] = v32;
			values[15] = v33;
			}
		void identity() {
			values[0] =  1.0;
			values[1] =  0.0;
			values[2] =  0.0;
			values[3] =  0.0;
			values[4] =  0.0;
			values[5] =  1.0;
			values[6] =  0.0;
			values[7] =  0.0;
			values[8] =  0.0;
			values[9] =  0.0;
			values[10] = 1.0;
			values[11] = 0.0;
			values[12] = 0.0;
			values[13] = 0.0;
			values[14] = 0.0;
			values[15] = 1.0;
			}
		Vec4 row(const int row) const {
			return Vec4(
				values[row*4],
				values[row*4+1],
				values[row*4+2],
				values[row*4+3]
				);
			}
		Vec4 column(const int column) const {
			return Vec4(
				values[column],
				values[column + 4],
				values[column + 8],
				values[column + 12]
				);
			}
		Mat4x4 multiply(const Mat4x4& other) const {
			Mat4x4 result;
			for (int row = 0; row < 4; ++row) {
				for (int column = 0; column < 4; ++column) {
					result.values[row*4+column] = this->row(row).dot(other.column(column));
					}
				}
			return result;
			}
		void extractEulerAngleXYZ(float& rotXangle, float& rotYangle, float& rotZangle) const {
			rotXangle = atan2(-row(1).z, row(2).z);
			float cosYangle = sqrt(pow(row(0).x, 2) + pow(row(0).y, 2));
			rotYangle = atan2(row(0).z, cosYangle);
			float sinXangle = sin(rotXangle);
			float cosXangle = cos(rotXangle);
			rotZangle = atan2(cosXangle * row(1).x + sinXangle * row(2).x, cosXangle * row(1).y + sinXangle * row(2).y);
			}
		void eulerAsMatrix (double bank, double attitude, double heading) { // give in radians
			// https://stackoverflow.com/a/47283530
			float cosY = cos(heading);     // Yaw
			float sinY = sin(heading);

			float cosP = cos(attitude);     // Pitch
			float sinP = sin(attitude);

			float cosR = cos(bank);     // Roll
			float sinR = sin(bank);

			values[5] = cosY * cosR + sinY * sinP * sinR;
			values[9] = cosR * sinY * sinP - sinR * cosY;
			values[1] = cosP * sinY;

			values[6] = cosP * sinR;
			values[10] = cosR * cosP;
			values[2] = -sinP;

			values[4] = sinR * cosY * sinP - sinY * cosR;
			values[8] = sinY * sinR + cosR * cosY * sinP;
			values[0] = cosP * cosY;
			}
		};

	struct Box {
		p2 corner1;
		p2 corner2;
		p2 corner3;
		p2 corner4;
		};
	bool boxContainsPoint(p2 point, Box box){
		//	https://stackoverflow.com/a/33539450

		//Calculate distances from corner to corner
		float abL = box.corner1.getDistance(box.corner2);
		float bcL = box.corner2.getDistance(box.corner3);
		float cdL = box.corner3.getDistance(box.corner4);
		float daL = box.corner4.getDistance(box.corner1);

		//Calculate corner touch distance
		float apL = box.corner1.getDistance(point);
		float bpL = box.corner2.getDistance(point);
		float cpL = box.corner3.getDistance(point);
		float dpL = box.corner4.getDistance(point);

		//Here we calculate the touch area, using Heron's Formula
		float area1 = (abL + apL + bpL) / 2;
		float area2 = (bcL + bpL + cpL) / 2;
		float area3 = (cdL + cpL + dpL) / 2;
		float area4 = (daL + dpL + apL) / 2;
		float a1 = sqrtf(area1 * (area1 - abL)*(area1 - apL)*(area1 - bpL));
		float a2 = sqrtf(area2 * (area2 - bcL)*(area2 - bpL)*(area2 - cpL));
		float a3 = sqrtf(area3 * (area3 - cdL)*(area3 - cpL)*(area3 - dpL));
		float a4 = sqrtf(area4 * (area4 - daL)*(area4 - dpL)*(area4 - apL));

		//Calculate the rectangle area
		float A = std::roundf(abL*bcL);

		//Check to see if the point contains the polygon rect
		if(A == std::roundf(a1 + a2 + a3 + a4)) return true;
		return false;
		}
	}

namespace myMath {	// Math Operators
	myTypes::Mat4x4 transMatrix (float x = 0.0, float y = 0.0, float z = 0.0, float w = 1.0) {
		myTypes::Mat4x4 tfm(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, x, y, z, w);
		return tfm;
		}
	myTypes::Mat4x4 scaleMatrix (float x = 1.0, float y = 1.0, float z = 1.0, float w = 1.0) {
		myTypes::Mat4x4 tfm(x, 0.0, 0.0, 0.0, 0.0, y, 0.0, 0.0, 0.0, 0.0, z, 0.0, 0.0, 0.0, 0.0, w);
		return tfm;
		}
	float toRadians(float degrees) {
		return degrees * (M_PI / 180);
		}
	float toDegrees(float radians) {
		return radians * (180 / M_PI);
		}
	unsigned long roundToMultiple (unsigned long numToRound, unsigned long multiple) {
		unsigned long remainder = numToRound % multiple;
		if (remainder == 0) {
			return numToRound;
			}
		return (numToRound + multiple - remainder);
		}
	long floordiv (long num, long den) {
		if (0 < (num^den)) {
			return num/den;
			}
		else {
			ldiv_t res = ldiv(num,den);
			return (res.rem)? res.quot-1 : res.quot;
			}
		}
	unsigned int getByteAlignment (unsigned long position, unsigned long alignTo) {
		return (((alignTo - (position % alignTo)) % alignTo));// + alignTo;
		}
	}

namespace myHash {	// Hashing Functions
	namespace string {
		unsigned long SDBMHash_32(std::string str) {
			// https://www.partow.net/programming/hashfunctions/#SDBMHashFunction
			unsigned long hashid = 0;
			for (unsigned long i = 0; i < str.length(); i++) {
				hashid = ((int)str[i]) + (hashid << 6) + (hashid << 16) - hashid;
				}
			return hashid;
			}
		unsigned long DJB2Hash_32(std::string str) {
			// http://www.cse.yorku.ca/~oz/hash.html
			unsigned long hashid = 5381;
			for (unsigned long i = 0; i < str.length(); i++) {
				hashid = hashid * 33 + ((int)str[i]);
				}
			return hashid;
			}
		}
	}

namespace myBitWise {	// Bit Wise
	namespace bit {
		bool get (unsigned long val, unsigned char b) {
			return ((val & ( 1 << b )) >> b);
			}
		unsigned long set (unsigned long val, unsigned char b, bool state) {
			if (state) {
				val ^= ((val * 0 - 1) ^ val) & ((val * 0 + 1) << b);
				}
			else {
				val ^= ((val * 0) ^ val) & ((val * 0 + 1) << b);
				}
			return val;
			}
		unsigned long shift (unsigned long val, signed char b) {
			if (b < 0.0) {
				val = val >> -b;
				}
			else {
				val = val << b;
				}
			return val;
			}
		std::string IntAsString (double a) {
			std::string result = "";
			std::ostringstream temp;
			temp << a;
			if (temp.good ()) {
				result = temp.str();
				}
			return result;
			}
		std::string IntAsChar(int a) {
			std::ostringstream temp;
			temp << a;
			return temp.str();
			}
		unsigned char CharAsInt (char &chr) {
			return chr;
			}
		std::string IntAsHex(int number, int length = 2) {
			std::string s;
			std::ostringstream temp;
			temp << std::hex << number;
			s = temp.str();
			for (unsigned int i = 0; i < s.size(); ++i) {
				s[i] = (s[i] <= 'z' && s[i] >= 'a') ? s[i]-('a'-'A') : s[i];
				}
			s.insert(s.begin(), length - s.length(), '0');
			return ("0x" + s);
			}
		unsigned long StringAsInt (std::string s) {
			std::stringstream str(s);
			unsigned long num = 0;
			unsigned int i = 0;
			i = s.find("x",0);
			if (i <= s.size()) {
				str << std::hex << "00000000" << s.substr(i + 1,s.size()-(i+1));
				str >> num;
				}
			else {
				str >> num;
				}
			return num;
			}
		double StringAsFloat (std::string s) {
			std::istringstream str(s);
			double num;
			str >> num;
			return num;
			}
		myTypes::p3 StringAsP3 (std::string s) {
			myTypes::p3 result;
			result.x = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" ")));
			result.y = myBitWise::bit::StringAsFloat(s.substr(s.find(" ") + 1, s.find_last_of(" ") - s.find(" ") - 1));
			result.z = myBitWise::bit::StringAsFloat(s.substr(s.find_last_of(" ") + 1));
			return result;
			}
		myTypes::p4 StringAsP4 (std::string s) {
			myTypes::p4 result;
			result.x = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" ")));
			s = s.substr(s.find(" ") + 1);
			result.y = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" ")));
			s = s.substr(s.find(" ") + 1);
			result.z = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" ")));
			s = s.substr(s.find(" ") + 1);
			result.w = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" ")));
			return result;
			}
		myTypes::color StringAsColor (std::string s) {
			myTypes::color result;
			result.r = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" "))) / 255.0;
			s = s.substr(s.find(" ") + 1);
			result.b = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" "))) / 255.0;
			s = s.substr(s.find(" ") + 1);
			result.g = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" "))) / 255.0;
			s = s.substr(s.find(" ") + 1);
			result.a = myBitWise::bit::StringAsFloat(s.substr(0, s.find(" "))) / 255.0;
			return result;
			}
		}
	}

namespace myString {	// String Operations
	std::string getTimeStamp (const std::string &datepart) {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format
		strftime(buf, sizeof(buf), datepart.c_str(), &tstruct);
		return buf;
		}
	std::string toUpper(const std::string &s) {
		std::string ret(s.size(), char());
		for (unsigned int i = 0; i < s.size(); ++i) {
			ret[i] = (s[i] <= 'z' && s[i] >= 'a') ? s[i]-('a'-'A') : s[i];
			}
		return ret;
		}
	std::string toLower(const std::string &s) {
		std::string ret(s.size(), char());
		for (unsigned int i = 0; i < s.size(); ++i) {
			ret[i] = (s[i] <= 'Z' && s[i] >= 'A') ? s[i]-('A'-'a') : s[i];
			}
		return ret;
		}
	std::wstring toUpperW(const std::wstring &s) {
		std::wstring ret(s.size(), char());
		for (unsigned int i = 0; i < s.size(); ++i) {
			ret[i] = (s[i] <= L'z' && s[i] >= L'a') ? s[i]-(L'a'-L'A') : s[i];
			}
		return ret;
		}
	std::wstring toLowerW(const std::wstring &s) {
		std::wstring ret(s.size(), char());
		for (unsigned int i = 0; i < s.size(); ++i) {
			ret[i] = (s[i] <= L'Z' && s[i] >= L'A') ? s[i]-(L'A'-L'a') : s[i];
			}
		return ret;
		}
	std::string rtrim (std::string str) {
		if (str.size() > 0) {
			std::string blank(str.size(), ' ');
			if (str!=blank) {
				int start2 = 0, end2 = str.length() - 1;
				while(isspace(str[start2]) || isspace(str[end2])) {
					if(isspace(str[start2])) {start2++;}
					if(isspace(str[end2])) {end2--;}
					}
				str.erase(0,start2);
				str.erase((end2 - start2) + 1);
				}
			else {str = "UNKNOWN";}
			}
		return str;
		}
	std::string trim(const std::string &s) {
		std::string::const_iterator it = s.begin();
		while (it != s.end() && isspace(*it)) {it++;}
		std::string::const_reverse_iterator rit = s.rbegin();
		while (rit.base() != it && isspace(*rit)) {rit++;}
		return std::string(it, rit.base());
		}
	std::string Replace(std::string subject, const std::string& search, const std::string& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
			}
		return subject;
		}
	std::string padString (std::string str, unsigned int len, std::string pad, bool addToLeft = true) {
		std::string temp = str;
		std::string padding = "";
		if (temp.size() > len) {
			temp = temp.substr(0, len);
			}
		if ((len - temp.size()) > 0) {
			for (unsigned int i = 0; i < ((len - temp.size())); i++){
				padding += pad;
				}
			}
		if (addToLeft) {
			return (padding + temp);
			}
		else {
			return (temp + padding);
			}
		}
	std::string wstring_to_string (std::wstring ws) {
		// http://blog.mijalko.com/2008/06/convert-stdstring-to-stdwstring.html
		std::string s;
		return s.assign(ws.begin(), ws.end());
		}
	std::wstring string_to_wstring (std::string s) {
		// http://blog.mijalko.com/2008/06/convert-stdstring-to-stdwstring.html
		std::wstring ws;
		return ws.assign(s.begin(), s.end());
		}
	}

namespace myUTF {	// String Unicode Stuff
	int StringToWString(std::wstring &ws, const std::string &s) {
		std::wstring wsTmp(s.begin(), s.end());
		ws = wsTmp;
		return 0;
		}
	std::wstring shift_jis_to_utf_16(const std::string& str) {
		//https://qiita.com/yumetodo/items/453d14eff41b805d8fc4
		static_assert(sizeof(wchar_t) == 2, "this function is windows only");
		const int len = ::MultiByteToWideChar(932/*CP_ACP*/, 0, str.c_str(), -1, nullptr, 0);
		std::wstring re(len * 2 + 2, L'\0');
		if (!::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &re[0], len)) {
			const auto ec = ::GetLastError();
			switch (ec)
			{
			case ERROR_INSUFFICIENT_BUFFER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
			case ERROR_INVALID_FLAGS:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
			case ERROR_INVALID_PARAMETER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
			case ERROR_NO_UNICODE_TRANSLATION:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_NO_UNICODE_TRANSLATION"); break;
			default:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
				}
			}
		const std::size_t real_len = std::wcslen(re.c_str());
		re.resize(real_len);
		re.shrink_to_fit();
		return re;
		}
	std::string UTF8toSjis2(std::string srcUTF8){
		// http://sayahamitt.net/utf8%E3%81%AAstring%E5%85%A5%E3%82%8C%E3%81%9F%E3%82%89shiftjis%E3%81%AAstring%E5%87%BA%E3%81%A6%E3%81%8F%E3%82%8B%E9%96%A2%E6%95%B0%E4%BD%9C%E3%81%A3%E3%81%9F/
		int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(),srcUTF8.size() + 1, NULL, 0);
		wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
		MultiByteToWideChar(CP_UTF8, 0, srcUTF8.c_str(), srcUTF8.size() + 1,bufUnicode, lenghtUnicode);
		int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
		char* bufShiftJis = new char[lengthSJis];
		WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);
		std::string strSJis(bufShiftJis);
		delete bufUnicode;
		delete bufShiftJis;
		return strSJis;
		}
	std::string SjistoUTF82(std::string srcSjis){
		// http://sayahamitt.net/utf8%E3%81%AAstring%E5%85%A5%E3%82%8C%E3%81%9F%E3%82%89shiftjis%E3%81%AAstring%E5%87%BA%E3%81%A6%E3%81%8F%E3%82%8B%E9%96%A2%E6%95%B0%E4%BD%9C%E3%81%A3%E3%81%9F/
		int lenghtUnicode = MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, NULL, 0);
		wchar_t* bufUnicode = new wchar_t[lenghtUnicode];
		MultiByteToWideChar(CP_THREAD_ACP, 0, srcSjis.c_str(), srcSjis.size() + 1, bufUnicode, lenghtUnicode);
		int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);
		char* bufUTF8 = new char[lengthUTF8];
		WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUnicode + 1, bufUTF8, lengthUTF8, NULL, NULL);
		std::string strUTF8(bufUTF8);
		delete bufUnicode;
		delete bufUTF8;
		return strUTF8;
		}
//	std::string sjis2utf8(const std::string& sjis) {
//		//VC++ SJIS string ‚ð utf-8‚Ìstring‚É•ÏŠ·‚·‚é
//		std::string utf8_string;
//
//		//ˆê’USJIS‚©‚çutf-16‚Ö•ÏŠ·
//		LPCCH pSJIS = (LPCCH)sjis.c_str();
//		int utf16size = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, pSJIS, -1, 0, 0);
//		if (utf16size != 0) {
//			LPWSTR pUTF16 = new WCHAR[utf16size];
//			if (::MultiByteToWideChar(CP_ACP, 0, (LPCCH)pSJIS, -1, pUTF16, utf16size) != 0) {
//				//ŽŸ‚Éutf-16‚©‚çutf-8‚Ö•ÏŠ·
//				int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, 0, 0, 0, 0);
//				if (utf8size != 0) {
//					LPTSTR pUTF8 = new TCHAR[utf8size + 16];
//					ZeroMemory(pUTF8, utf8size + 16);
//					if (::WideCharToMultiByte(CP_UTF8, 0, pUTF16, -1, pUTF8, utf8size, 0, 0) != 0) {
//						utf8_string = std::string(pUTF8);
//						}
//					delete pUTF8;
//					}
//				}
//			delete pUTF16;
//			}
//		return utf8_string;
//		}
	std::string utf_16_to_shift_jis(const std::wstring& str) {
		//https://qiita.com/yumetodo/items/453d14eff41b805d8fc4
		static_assert(sizeof(wchar_t) == 2, "this function is windows only");
		const int len = ::WideCharToMultiByte(932/*CP_ACP*/, 0, str.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string re(len * 2, '\0');
		if (!::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, &re[0], len, nullptr, nullptr)) {
			const auto ec = ::GetLastError();
			switch (ec)
			{
			case ERROR_INSUFFICIENT_BUFFER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
			case ERROR_INVALID_FLAGS:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
			case ERROR_INVALID_PARAMETER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
			default:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
			}
		}
		const std::size_t real_len = std::strlen(re.c_str());
		re.resize(real_len);
		re.shrink_to_fit();
		return re;
	}
	std::string char_utf_16_to_shift_jis(const char* str) {
		//https://qiita.com/yumetodo/items/453d14eff41b805d8fc4
		static_assert(sizeof(wchar_t) == 2, "this function is windows only");
		const int len = ::WideCharToMultiByte(932/*CP_ACP*/, 0, (LPCWSTR)str, -1, nullptr, 0, nullptr, nullptr);
		std::string re(len * 2, '\0');
		if (!::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)str, -1, &re[0], len, nullptr, nullptr)) {
			const auto ec = ::GetLastError();
			switch (ec)
			{
			case ERROR_INSUFFICIENT_BUFFER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INSUFFICIENT_BUFFER"); break;
			case ERROR_INVALID_FLAGS:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_FLAGS"); break;
			case ERROR_INVALID_PARAMETER:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: ERROR_INVALID_PARAMETER"); break;
			default:
				throw std::runtime_error("in function utf_16_to_shift_jis, WideCharToMultiByte fail. cause: unknown(" + std::to_string(ec) + ')'); break;
			}
		}
		const std::size_t real_len = std::strlen(re.c_str());
		re.resize(real_len);
		re.shrink_to_fit();
		return re;
	}
	std::string unicode_2_utf8 (uint32_t x) {
		// https://rosettacode.org/wiki/UTF-8_encode_and_decode#VBA
		uint32_t r;
		std::string y;
		if (x <= 0x0000007F) {
			y.resize(1);
			y[0] = x;
			}
		else if (x <= 0x000007FF) {
			y.resize(2);
			y[0] = 192 + x / 64;
			y[1] = 128 + x % 64;
			}
		else if (x <= 0x00007FFF) {
			y.resize(3);
			y[2] = 128 + x % 64;
			r = x / 64;
			y[1] = 128 + r % 64;
			y[0] = 224 + r / 64;
			}
		else if (x <= 0x0000FFFF) {
			y.resize(3);
			y[2] = 128 + x % 64;
			r = x / 64;
			y[1] = 128 + r % 64;
			y[0] = 224 + r / 64;
			}
		else if (x <= 0x0000FFFF) {
			y.resize(3);
			y[2] = 128 + x % 64;
			r = x / 64;
			y[1] = 128 + r % 64;
			y[0] = 224 + r / 64;
			}
		else if (x <= 0x0010FFFF) {
			y.resize(4);
			y[3] = 128 + x % 64;
			r = x / 64;
			y[2] = 128 + r % 64;
			r = r / 64;
			y[1] = 128 + r % 64;
			y[0] = 240 + r / 64;
			}
		return y;
		}
	std::wstring utf8_2_unicode (std::string str) {
		std::wstring w;
		uint8_t byte;
		uint32_t uni;

		unsigned long i = 0;
		while (i < str.size()) {
			byte = str[i];
			if (byte <= 0x7F) {
				w += str[i];
				}
			else if (byte <= 0xDF) {
				uni = (((str[i] & 0x1F) << 6) & ((str[i + 1] & 0x3F)));
				w += uni;
				i++;
				}
			else if (byte <= 0xEF) {
				uni = (((str[i] & 0x0F) << 12) | ((str[i + 1] & 0x3F) << 6)  |  ((str[i + 2] & 0x3F) )  );
				w += uni;
				i+=2;
				}
			else if (byte <= 0xF7) {
				uni = (((str[i] & 0x07) << 18) | ((str[i + 1] & 0x3F) << 12)  |  ((str[i + 2] & 0x3F) << 6)    |  ((str[i + 3] & 0x3F) )  );
				w += uni;
				i+=3;
				}
			i++;
			}
		return w;
		}
	std::wstring getFilePathFromName(const std::wstring &fileToFind, const std::wstring &directory) {
		// https://stackoverflow.com/a/25640066
		std::wstring tmp = directory + L"\\*";
		signed long i = 0;
		WIN32_FIND_DATAW file;
		HANDLE search_handle = FindFirstFileW(tmp.c_str(), &file);
		if (search_handle != INVALID_HANDLE_VALUE) {
			std::vector<std::wstring> directories;
			do {
				if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					if ((!lstrcmpW(file.cFileName, L".")) || (!lstrcmpW(file.cFileName, L".."))) {
						continue;
						}
					}
				tmp = directory + L"\\" + std::wstring(file.cFileName);
				i = tmp.find_last_of(L"\\");
				if (i != std::wstring::npos) {
					if (tmp.substr(i + 1, tmp.length() - i - 1) == fileToFind) {
						FindClose(search_handle);
						return tmp;
						}
					}
				if (file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					directories.push_back(tmp);
					}
				}
			while (FindNextFileW(search_handle, &file));
			FindClose(search_handle);
			for(std::vector<std::wstring>::iterator iter = directories.begin(), end = directories.end(); iter != end; ++iter) {
				tmp = getFilePathFromName(fileToFind, *iter);
				i = tmp.find_last_of(L"\\");
				if (i != std::wstring::npos) {
					if (tmp.substr(i + 1, tmp.length() - i - 1) == fileToFind) {
						FindClose(search_handle);
						return tmp;
						}
					std::wcout << L"Found: (" << tmp.substr(i + 1, tmp.length() - i - 1) << L")" << std::endl;
					}
				}
			}
		return L"";
		}
	}

namespace myPaths {	// Handling File Paths
	std::string runningPath() {
		// https://stackoverflow.com/a/13310600
		char ownPth[MAX_PATH];
		// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
		HMODULE hModule = GetModuleHandle(NULL);
		if (hModule != NULL) {
			// Use GetModuleFileName() with module handle to get the path
			GetModuleFileNameA(hModule, ownPth, (sizeof(ownPth)));
			//cout << ownPth << endl;
			//system("PAUSE");
			return (std::string)ownPth;
			}
		else {
			//cout << "Module handle is NULL" << endl ;
			//system("PAUSE");
			return "";
			}
		}
	std::wstring runningPathW() {
		// https://stackoverflow.com/a/13310600
		wchar_t ownPth[MAX_PATH];
		// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
		HMODULE hModule = GetModuleHandle(NULL);
		if (hModule != NULL) {
			// Use GetModuleFileName() with module handle to get the path
			GetModuleFileNameW(hModule, ownPth, (sizeof(ownPth)));
			//cout << ownPth << endl;
			//system("PAUSE");
			return (std::wstring)ownPth;
			}
		else {
			//cout << "Module handle is NULL" << endl ;
			//system("PAUSE");
			return L"";
			}
		}
	std::string filenameFromPath(const std::string &str) {
		// filenameFromPath file  -- returns: "myImage.jpg"
		size_t found;
		std::string strt;
		found = str.find_last_of("/\\");
		if (found < str.size()) {
			strt = str.substr(found + 1, -1);
			return strt;
			}
		else {
			return str;
			}
		}
	std::string getFilenamePath (const std::string &str) {
		// getFilenamePath file   -- returns: "g:\subdir1\subdir2\"
		size_t found;
		std::string strt;
		found = str.find_last_of("/\\");
		if (found != std::string::npos) {
			strt = str.substr(0, found);
			return (strt + "\\");
			}
		else {
			return "";
			}
		}
	std::string getFilenameFile(const std::string &str) {
		// getFilenameFile file   -- returns: "myImage"
		size_t found;
		std::string strt;
		found = str.find_last_of("/\\");
		if (found < str.size()) {
			strt = str.substr(found + 1, -1);
			found = strt.find(".");
			if (found < strt.size()) {
				strt = strt.substr(0, found);
				}
			//return strt;
			}
		else {
			strt = str;
			//return str;
			}
		size_t lastdot = strt.find_last_of(".");
		if (lastdot == std::string::npos) return strt;
		return strt.substr(0, lastdot);
		}
	std::string getFilenameType (std::string const &path ) {
		// getFilenameType file -- returns: ".jpg"
		std::string ext;
		size_t dotIdx = path.find_last_of( "." );
		if ( dotIdx != std::string::npos ) {
			size_t dirSepIdx = path.find_last_of( "/\\" );
			if ( dotIdx > dirSepIdx + 1 ) {
				ext = path.substr( dotIdx );
				}
			}
		return ext;
		}
	std::wstring filenameFromPathW(const std::wstring &str) {
		// filenameFromPath file  -- returns: "myImage.jpg"
		wchar_t found;
		std::wstring strt;
		found = str.find_last_of(L"/\\");
		if (found < str.size()) {
			strt = str.substr(found + 1, -1);
			return strt;
			}
		else {
			return str;
			}
		}
	std::wstring getFilenamePathW (const std::wstring &str) {
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
	std::wstring getFilenameFileW(const std::wstring &str) {
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
	std::wstring getFilenameTypeW (std::wstring const &path ) {
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
	bool isPathRelative (std::string &path) {
		if (path.length() > 1) {
			if (path.substr(0, 2) == "..") {
				return true;
				}
			}
		return false;
		}
	void fixPathSlashes (std::string &path) {
		if (path.length() > 0) {
			for (unsigned long i = 0; i < path.length(); i++) {
				if (path[i] == '/') {path[i] = '\\';}
				}
			if (path[path.length() - 1] != '\\') {
				path += "\\";
				}
			}
		}
	std::string getAbsolutePathFromRelative (std::string basePath, std::string relPath) {
		unsigned long i = 0;
		unsigned long b = 0;
		signed long s = 0;

		// check if path valid
		if (relPath.length() < 3 || basePath.length() < 3) {return "";}

		// basically remove all / slashes to make things a bit easier
		// donno if that messes up anything, but ohwell
		// also appends a slash to the end of the string
		fixPathSlashes(basePath);
		fixPathSlashes(relPath);

		// removed the slash from basePath while doing the check
		s = basePath.find_last_of("\\");
		if (s != std::string::npos) {basePath = basePath.substr(0, s);}

		// check the string size again
		if (relPath.length() > 3) {
			// scan for back dir prefix '../'
			while (i < relPath.length()) {
				// if prefix is found, push cursor and count prefixes found
				if (relPath.substr(i, 3) == "..\\") {b++; i+=3;}
				else {
					// if prefix is not found, store remainder of string and break loop
					if (b > 0) {
						relPath = relPath.substr(i, relPath.length() - i);
						}
					i += relPath.length();
					}
				}
			}
		// check if prefixes were found
		if (b > 0) {
			// severe string based on our prefix count
			for (i = 0; i < b; i++) {
				s = basePath.find_last_of("\\");
				if (s != std::string::npos) {basePath = basePath.substr(0, s);}
				}
			}
		// append slashes to end of base path again
		basePath += "\\";
		// assemble new string
		return (basePath + relPath);
		}
	std::string getRelativePathFromAbsolute (std::string basePath, std::string targetPath) {
		fixPathSlashes(basePath);
		fixPathSlashes(targetPath);
		signed long s1;
		signed long s2;
		std::string ss1 = basePath;
		std::string ss2 = targetPath;
		std::string sss1;
		std::string sss2;
		std::string commonPath = "";
		unsigned long b = 0;
		do {
			s1 = ss1.find("\\");
			s2 = ss2.find("\\");
			if (s1 != std::string::npos) {
				sss1 = ss1.substr(0, s1);
				ss1 = ss1.substr(s1 + 1, ss1.length() - s1 - 1);
				}
			if (s2 != std::string::npos) {
				sss2 = ss2.substr(0, s2);
				ss2 = ss2.substr(s2 + 1, ss2.length() - s2 - 1);
				}
			if (sss1 == sss2) {
				commonPath += sss1 + "\\";
				b++;
				}
			}
		while (s1 != std::string::npos && s2 != std::string::npos && sss1 == sss2 && ss1.length() > 0 && ss2.length() > 0);
		if (commonPath.length() == 0) {return targetPath;}
		ss1 = basePath.substr(commonPath.length(), basePath.length() - commonPath.length());
		ss2 = "";
		do {
			s1 = ss1.find_last_of("\\");
			if (s1 != std::string::npos) {
				ss1 = ss1.substr(0, s1);
				ss2 += "../";
				}
			}
		while (s1 != std::string::npos);
		ss1 = targetPath.substr(commonPath.length(), targetPath.length() - commonPath.length());
		//cout << "CommonPath:\t" << commonPath << endl;
		return (ss2 + ss1);
		}
	}

namespace myOS {	// File System Queries
	std::wstring openfilenameW(wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL, unsigned long flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY) {
		// add to link -lcomdlg32 -lole32
		std::wstring filename(MAX_PATH, L'\0');
		OPENFILENAMEW ofn = { };
		//ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn); //sizeof(LPOPENFILENAMEW);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = filter;
		ofn.lpstrFile = &filename[0];  // use the std::wstring buffer directly
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrTitle = L"Select a File";
		ofn.Flags = flags;
		//OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_EXPLORER| OFN_ALLOWMULTISELECT|OFN_NOCHANGEDIR|OFN_HIDEREADONLY| OFN_SHAREAWARE;
		if (!GetOpenFileNameW(&ofn)) {return L"";}
		//std::size_t firstScan = filename.find_first_not_of("\0");
		//std::size_t first = 0;
		//if (firstScan == std::string::npos) {first = filename.length();}
		//else {first = firstScan;}
		//std::size_t last = filename.find_last_not_of("\0");
		//return filename.substr(first, last-first+1);
		return filename;
		}
	std::string openfilename(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
		// add to link -lcomdlg32 -lole32
		OPENFILENAMEA ofn;
		char fileName[MAX_PATH] = "";
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = filter;
		ofn.lpstrFile = fileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = "";
		std::string fileNameStr = "";
		if (GetOpenFileNameA(&ofn)) {
			fileNameStr = fileName;
			}
		return fileNameStr;
		}
	std::string savefilename(char *filter = "All Files (*.*)\0*.*\0", HWND owner = NULL) {
		// add to link -lcomdlg32 -lole32
		OPENFILENAMEA ofn;
		char fileName[MAX_PATH] = "";
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAMEA);
		ofn.hwndOwner = owner;
		ofn.lpstrFilter = filter;
		ofn.lpstrFile = fileName;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = "";
		std::string fileNameStr;
		if (GetSaveFileNameA(&ofn)) {
			fileNameStr = fileName;
			}
		return fileNameStr;
		}
	size_t getFileSize (std::string fileName) {
		/*
		std::ifstream file(name.c_str(), std::ios::binary | std::ios::ate );
		size_t fileSize = file.tellg();
		file.close();
		return fileSize;
		*/
		// Native Solution (therefore faster)
		WIN32_FILE_ATTRIBUTE_DATA fad;
		if (!GetFileAttributesExA((char*)fileName.c_str(), GetFileExInfoStandard, &fad))
			return -1; // error condition, could call GetLastError to find out more
		LARGE_INTEGER size;
		size.HighPart = fad.nFileSizeHigh;
		size.LowPart = fad.nFileSizeLow;
		return size.QuadPart;
		}
	size_t getFileSizeW(std::wstring fileName) {
		WIN32_FILE_ATTRIBUTE_DATA fad;
		if (!GetFileAttributesExW((wchar_t*)fileName.c_str(), GetFileExInfoStandard, &fad))
			return -1; // error condition, could call GetLastError to find out more
		LARGE_INTEGER size;
		size.HighPart = fad.nFileSizeHigh;
		size.LowPart = fad.nFileSizeLow;
		return size.QuadPart;
		}
	bool isFileWritable (std::string filename) {
		bool isGood = true;
		unsigned long timeout = 0;
		unsigned long timeout_limit = 10000;
		std::ifstream file(filename.c_str());
		while (!file.is_open() && timeout < timeout_limit) {
			Sleep(100);
			timeout += 100;
			file.open(filename.c_str());
			}
		if (timeout >= timeout_limit) {
			isGood = false;
			}
		return isGood;
		}
	bool doesFileExist (std::string fileName) {
		//std::ifstream infile(fileName.c_str());
		//return infile.good();
		DWORD dwAttrib = GetFileAttributesA(fileName.c_str());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
		}
	bool doesFileExistW (std::wstring fileName) {
		/*	Old function that used fstream

		std::ifstream infile(fileName.c_str());
		return infile.good();
		*/

		/*	Old function that used File Attributes

		DWORD dwAttrib = GetFileAttributesW((wchar_t*)fileName.c_str());
		return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
		*/
		return (PathFileExistsW((wchar_t*)fileName.c_str()));
		}
	bool doesFolderExist (std::string dirName_in) {
		//DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
		DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES) {
			return false;  //something is wrong with your path!
			}
		if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
			return true;   // this is a directory!
			}
		return false;    // this is not a directory!
		}
	bool doesFolderExistW (std::wstring dirName_in) {
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
	bool makeDirW(std::wstring wsPath) {
		// https://www.codeguru.com/cpp/w-p/files/article.php/c4439/CreatePath--Full-Path-Creation-wstring-version.htm
		unsigned long attr;
		size_t pos;
		bool result = false;
		std::wstring tmp;

		// Check for trailing slash:
		/* I dont understand what this code is doing
		pos = wsPath.find_last_of(L"\\");

		if (wsPath.length() == pos + 1) { // last character is "\"
			wsPath.resize(pos);
			}
		*/
		if (wsPath.length() > 0) {
			if (wsPath[wsPath.length() - 1] != '\\') {
				wsPath += L"\\";
				}
			// Look for existing object:
			attr = GetFileAttributesW(wsPath.c_str());

			//std::wcout << "CreatingFolder:\t" << wsPath << std::endl;
			//std::wcout << "Attribute:\t" << attr << std::endl;
			if (attr == 0xFFFFFFFF) { // doesn't exist yet - create it!
				pos = wsPath.find_last_of(L"\\", wsPath.length() - 2);
				//pos = wsPath.find_first_of(L"\\/");
				//std::wcout << "POS:\t" << pos << std::endl;
				if (pos != std::wstring::npos) {
					// Create parent dirs:
					//std::wcout << L"Build\t" << wsPath.substr(0, pos + 1) << std::endl;
					result = makeDirW(wsPath.substr(0, pos + 1));
					}
				// Create node:
				result = result && CreateDirectoryW(wsPath.c_str(), NULL);
				CreateDirectoryW(wsPath.c_str(), NULL);
				}
			else if (FILE_ATTRIBUTE_DIRECTORY != attr) {  // object already exists, but is not a dir
				//SetLastError(ERROR_FILE_EXISTS);
				result = false;
				}
			}
		return result;
		}
	bool copyFile (std::string existing_filename, std::string target_filename) {
		bool result = CopyFileA (existing_filename.c_str(), target_filename.c_str(), true);
		return result;
		}
	bool copyFileW (std::wstring existing_filename, std::wstring target_filename) {
		bool result = CopyFileW ((wchar_t*)existing_filename.c_str(), (wchar_t*)target_filename.c_str(), true);
		return result;
		}
	bool moveFileW (std::wstring existing_filename, std::wstring target_filename) {
		bool result = MoveFileW ((wchar_t*)existing_filename.c_str(), (wchar_t*)target_filename.c_str());
		return result;
		}
	void getFilesW (std::wstring* &dirFiles, unsigned long &numFiles, std::wstring pattern) {
		// http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
		/*
		std::wstring* dirFiles = NULL;
		unsigned long numFiles = 0;
		getFilesW(dirFiles, numFiles, L"G:\\SteamLibrary\\steamapps\\common\\Tomb Raider (VI) The Angel of Darkness\\data\\Maps\\unGMX_v.1.0\\_CLZ\\*.clz");
		std::cout << "NumFiles:\t" << numFiles << endl;
		for (unsigned long i = 0; i < numFiles; i++) {
			std::wcout << numFiles << L"\t" << dirFiles[i] << endl;
			}
		if (dirFiles!=NULL){delete[] dirFiles;}
		*/
		WIN32_FIND_DATAW data;
		HANDLE hFind;
		numFiles = 0;
		std::wstring fullPathW;
		if ((hFind = FindFirstFileW((wchar_t*)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
			do {
				if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0x10 ) {
					fullPathW = myPaths::getFilenamePathW(pattern);

					if (myOS::doesFileExistW(fullPathW + data.cFileName)) {
						numFiles++;
						//fileList.insert( fileList.end(), (fullPath + data.cFileName));
						}
					}

				} while (FindNextFileW(hFind, &data) != 0);
			FindClose(hFind);
			}
		if (numFiles > 0) {
			dirFiles = new std::wstring[numFiles];
			numFiles = 0;
			if ((hFind = FindFirstFileW((wchar_t*)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
				do {
					if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0x10) {
						fullPathW = myPaths::getFilenamePathW(pattern);
						if (myOS::doesFileExistW(fullPathW + data.cFileName)) {
							dirFiles[numFiles] = fullPathW + data.cFileName;
							numFiles++;
							}
						}
					} while (FindNextFileW(hFind, &data) != 0);
				FindClose(hFind);
				}
			}
		}
//	int messageBoxACustom (HWND hWnd = 0, LPCTSTR lpText = "TEXT", LPCTSTR lpCaption = "Caption", UINT uType = MB_OKCANCEL, UINT uIconResID = 0) {
//		// https://forums.codeguru.com/showthread.php?407479-How-to-use-a-custom-icon-in-a-message-box&p=1497200#post1497200
//		// need to add linker option -lwinmm
//		// MessageBox( 0, "Failed to open in notepad",  "Message", MB_OK + MB_ICONHAND );
//		MSGBOXPARAMSA mbp;
//		mbp.cbSize = sizeof(MSGBOXPARAMSA);
//		mbp.hwndOwner = hWnd;
//		mbp.hInstance = GetModuleHandleA(NULL);
//		mbp.lpszText = lpText;
//		mbp.lpszCaption = lpCaption;
//		mbp.dwStyle = uType | MB_USERICON;
//		mbp.dwLanguageId = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
//		mbp.lpfnMsgBoxCallback = NULL;
//		mbp.dwContextHelpId = 0;
//		mbp.lpszIcon = MAKEINTRESOURCEA(uIconResID);
//		return MessageBoxIndirectA(&mbp);
//		}
	int messageBoxW (HWND hWnd = 0, LPCTSTR lpText = L"TEXT", LPCTSTR lpCaption = L"Caption", UINT uType = MB_OKCANCEL) {
		return MessageBoxW(hWnd, lpText, lpCaption, uType);
		}
	bool doesDirContainFileExt (std::wstring folder, std::wstring fext) {
		WIN32_FIND_DATAW data;
		HANDLE hFind;
		std::wstring pattern = folder + L"\\*" + fext;
		if ((hFind = FindFirstFileW((wchar_t*)pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
			do {
				if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0x10 ) {
					if (data.cFileName != L"." && data.cFileName != L"..") {
						FindClose(hFind);
						return true;
						}
					}

				} while (FindNextFileW(hFind, &data) != 0);
			FindClose(hFind);
			}
		return false;
		}
	}

namespace myBuffer {	// specifically for dealing with char arrays
	namespace bytes {
		unsigned char readbyte (char* &f, size_t &pos) {
			unsigned char result = (uint8_t)f[pos];
			pos += 1;
			return result;
			}
		unsigned short readshort (char* &f, size_t &pos) {
			unsigned short result = {
				(unsigned int)((uint8_t)f[pos + 0] * 0x00000001) + \
				(unsigned int)((uint8_t)f[pos + 1] * 0x00000100)
				};
			pos += 2;
			return result;
			}
		unsigned long readlong (char* &f, size_t &pos) {
			unsigned long result = {
				(unsigned int)((uint8_t)f[pos + 0] * 0x00000001) + \
				(unsigned int)((uint8_t)f[pos + 1] * 0x00000100) + \
				(unsigned int)((uint8_t)f[pos + 2] * 0x00010000) + \
				(unsigned int)((uint8_t)f[pos + 3] * 0x01000000)
				};
			pos += 4;
			return result;
			}
		void writelong (char* &f, size_t pos = 0, unsigned long val = 0, bool swap_order = false) {
			if (swap_order) {
				f[pos + 3] = val & 0x00FF;
				f[pos + 2] = (val & 0xFF00) >> 0x08;
				f[pos + 1] = (val & 0xFF0000) >> 0x10;
				f[pos + 0] = (val & 0xFF000000) >> 0x18;
				}
			else {
				f[pos + 3] = (val & 0xFF000000) >> 0x18;
				f[pos + 2] = (val & 0xFF0000) >> 0x10;
				f[pos + 1] = (val & 0xFF00) >> 0x08;
				f[pos + 0] = val & 0x00FF;
				}
			}
		void writeshort (char* &f, size_t pos = 0, unsigned long val = 0, bool swap_order = false) {
			if (swap_order) {
				f[pos + 1] = val & 0x00FF;
				f[pos + 0] = (val & 0xFF00) >> 0x08;
				}
			else {
				f[pos + 1] = (val & 0xFF00) >> 0x08;
				f[pos + 0] = val & 0x00FF;
				}
			}
		}
	namespace chars {
		void writelong (std::string &f, size_t pos, unsigned long val, bool swap_order = false) {
			if (swap_order) {
				f[pos + 3] = val & 0x00FF;
				f[pos + 2] = (val & 0xFF00) >> 0x08;
				f[pos + 1] = (val & 0xFF0000) >> 0x10;
				f[pos + 0] = (val & 0xFF000000) >> 0x18;
				}
			else {
				f[pos + 3] = (val & 0xFF000000) >> 0x18;
				f[pos + 2] = (val & 0xFF0000) >> 0x10;
				f[pos + 1] = (val & 0xFF00) >> 0x08;
				f[pos + 0] = val & 0x00FF;
				}
			}
		}
	}

namespace myArray {	// Array Handling
	signed long findIntArrayItem (signed long item, signed long* &arr, signed long arrCount) {
		signed long index = -1;
		if (arrCount > 0) {
			for (unsigned int i = 0; i < arrCount; i++) {
				if (arr[i] == item) {
					index = i;
					break;
					}
				}
			}
		return index;
		}
	void sortIntArray (signed long* &arr, signed long arrCount) {
		signed long i = 1;
		signed long hold;
		i = arrCount - 1;
		if (i > 0) {
			//arr = new signed long[arrCount];
			while (i > 0) {
				if (arr[i] > arr[i - 1]) {
					hold = arr[i];
					arr[i] = arr[i - 1];
					arr[i - 1] = hold;
					if (i < arrCount - 1) {
						i += 1;
						}
					}
				else {
					i -= 1;
					}
				}
			}
		}

	class String {
	private:
		unsigned long num_elements;
		std::string* tmp;
		bool compareStrings (std::string str1, std::string str2, unsigned int campareMode = 0) {
			unsigned int i = 1;
			unsigned int len = 0;
			bool result = false;
			std::string s = " ";
			std::string ss = " ";
			switch (campareMode) {
				case 0: {	// < LessThan
					len = str1.size();
					if (str2.size() > len) {
						len = str2.size();
						}
					if (len > 0) {
						for (i = 0; i < len; i++) {
							s = "";
							ss = "";
							if (i <= str1.size()) {
								s = str1[i];
								}
							if (i <= str2.size()) {
								ss = str2[i];
								}
							if (s != ss) {
								if (s < ss) {
									result = true;
									}
								break;
								}
							}
						}
					break;
					}
				}
			return result;
			}
		void dim (std::string* &myArray, unsigned dim_size = 0) {
			if (myArray!=NULL) {
				delete[] myArray;
				}
			if (dim_size > 0) {
				myArray = new std::string[dim_size];
				}
			}
		void copyTo (std::string* &srcArray, unsigned long &srcArraySize, std::string* &desArray) {
			unsigned int i;
			if (srcArraySize > 0) {
				dim(desArray, srcArraySize);
				for (i = 0; i < srcArraySize; i++) {
					desArray[i] = srcArray[i];
					}
				}
			}
		void redim (std::string* &myArray, unsigned long &myArraySize, unsigned long dim_size = 0) {
			unsigned int i;
			if (dim_size > 0) {
				copyTo(myArray, myArraySize, tmp);
				}
			dim(myArray, dim_size);
			if (dim_size > 0) {
				for (i = 0; i < dim_size; i++) {
					if (i < myArraySize) {
						myArray[i] = tmp[i];
						}
					}
				//delete[] tmp;
				}
			myArraySize = dim_size;
			}

	public:
		std::string* item;
		String () {
			tmp = NULL;
			item = NULL;
			num_elements = 0;
			};
		~String () {
			if (tmp != NULL) {delete[] tmp;}
			if (item != NULL) {delete[] item;}
			}
		unsigned int count () {
			return num_elements;
			}
		void free () {
			if (tmp != NULL) {
				delete[] tmp;
				}
			if (item != NULL) {
				delete[] item;
				}
			num_elements = 0;
			item = NULL;
			tmp = NULL;
			}
		void size (unsigned long myArraySize = 0) {
			if (myArraySize > 0) {
				dim(item, myArraySize);
				}
			num_elements = myArraySize;
			}
		void append (std::string val = "") {
			unsigned int i;
			if (num_elements > 0) {
				dim(tmp, num_elements);
				for (i = 0; i < num_elements; i++) {
					tmp[i] = item[i];
					}
				dim(item, num_elements + 1);
				for (i = 0; i < num_elements; i++) {
					item[i] = tmp[i];
					}
				delete[] tmp;
				tmp = NULL;
				}
			else {
				dim(item, num_elements + 1);
				}
			item[num_elements] = val;
			num_elements+=1;
			}
		void deleteItem (unsigned long index) {
			unsigned int i = 0;
			unsigned int ii = 0;
			if (num_elements > 0 && index < num_elements) {
				dim(tmp, num_elements);
				for (i = 0; i < num_elements; i++) {
					tmp[i] = item[i];
					}
				dim(item, num_elements - 1);
				for (i = 0; i < num_elements; i++) {
					if (i != index) {
						item[ii] = tmp[i];
						ii++;
						}
					}
				num_elements-=1;
				delete[] tmp;
				tmp = NULL;
				}
			}
		void insertItem (std::string val, unsigned long index) {
			unsigned int i = 0;
			unsigned int ii = 0;
			if (index <= num_elements) {
				if (num_elements > 0) {
					dim(tmp, num_elements);
					for (i = 0; i < num_elements; i++) {
						tmp[i] = item[i];
						}
					dim(item, num_elements + 1);
					item[index] = val;
					for (i = 0; i < num_elements; i++) {
						if (i != index) {
							item[ii] = tmp[i];
							}
						else {
							ii += 1;
							item[ii] = tmp[i];
							}
						ii += 1;
						}
					delete[] tmp;
					tmp = NULL;
					}
				else {
					dim(item, num_elements + 1);
					item[num_elements] = val;
					}
				num_elements+=1;
				}
			}
		void join (String &mrgArray) {
			unsigned int i;
			unsigned int ii = 0;
			if (mrgArray.count() > 0) {
				redim(item, num_elements, num_elements + mrgArray.count());
				i = num_elements - mrgArray.count();
				for (i = num_elements - mrgArray.count(); i < num_elements; i++) {
					item[i] = mrgArray.item[ii];
					ii++;
					}
				}
			//delete[] tmp;
			}
		void filterString (std::string input, std::string delimiter) {
			unsigned long num_splits = 0;
			unsigned long pos = 0;
			bool isFound = false;
			bool logStr = false;
			std::string tmp = "";
			if (input.length() > 0 && delimiter.length() > 0) {
				delimiter = myString::toUpper(delimiter);
				scanStr:
				// loop through each character of our string
				for (unsigned long s = 0; s < input.length(); s++) {

					isFound = false; // store state for if we found a delimiter or not

					// check that none of the delimiters are in the character
					for (unsigned long d = 0; d < delimiter.length(); d++) {
						if (myString::toUpper(input.substr(s, 1)) == delimiter.substr(d, 1)) {
							isFound = true;
							break;
							}
						}

					// if delimiter was found then increase split count
					if (isFound) {
						if (tmp.length() > 0) {
							if (logStr) {item[num_splits] = tmp;}
							num_splits++;
							tmp = "";
							}
						}
					else {
						tmp += input.substr(s, 1);
						}
					}
				if (tmp.length() > 0) {
					if (logStr) {item[num_splits] = tmp;}
					num_splits++;
					}
				if (!logStr) {
					logStr = true;
					size(num_splits);
					num_splits = 0;
					pos = 0;
					tmp = "";
					goto scanStr;
					}
				}
			}
		signed long findItem (std::string val) {
			signed long index = -1;
			if (num_elements > 0) {
				for (unsigned int i = 0; i < num_elements; i++) {
					if (item[i] == val) {
						index = i;
						break;
						}
					}
				}
			return index;
			}
		void appendIfUnique (std::string val) {
			if (findItem(val) < 0) {
				append(val);
				}
			}
		void sort () {
			unsigned int i = 1;
			std::string hold;
			i = num_elements - 1;
			while (i > 0) {
				if (compareStrings(item[i], item[i - 1])) {
					hold = item[i];
					item[i] = item[i - 1];
					item[i - 1] = hold;
					if (i < num_elements - 1) {
						i += 1;
						}
					}
				else {
					i -= 1;
					}
				}
			}
		void print () {
			std::cout << "StringCount:\t" << num_elements << "\n" << std::endl;
			if (num_elements > 0) {
				for (unsigned long i = 0; i < num_elements; i++) {
					std::cout << "    " << (i + 1) << ").\t[" << item[i] << "]" <<std::endl;
					}
				}
			}
		};
	class Integer {
	private:
		unsigned long num_elements;
		unsigned long* tmp;
		void dim (unsigned long* &myArray, unsigned dim_size = 0) {
			if (myArray!=NULL) {
				delete[] myArray;
				}
			if (dim_size > 0) {
				myArray = new unsigned long[dim_size];
				}
			}
		void copyTo (unsigned long* &srcArray, unsigned long &srcArraySize, unsigned long* &desArray) {
			unsigned int i;
			if (srcArraySize > 0) {
				dim(desArray, srcArraySize);
				for (i = 0; i < srcArraySize; i++) {
					desArray[i] = srcArray[i];
					}
				}
			}
		void redim (unsigned long* &myArray, unsigned long &myArraySize, unsigned long dim_size = 0) {
			unsigned int i;
			if (dim_size > 0) {
				copyTo(myArray, myArraySize, tmp);
				}
			dim(myArray, dim_size);
			if (dim_size > 0) {
				for (i = 0; i < dim_size; i++) {
					if (i < myArraySize) {
						myArray[i] = tmp[i];
						}
					}
				//delete[] tmp;
				}
			myArraySize = dim_size;
			}

	public:
		unsigned long* item;
		Integer () {
			tmp = NULL;
			item = NULL;
			num_elements = 0;
			};
		~Integer () {
			if (tmp != NULL) {delete[] tmp;}
			if (item != NULL) {delete[] item;}
			}
		unsigned int count () {
			return num_elements;
			}
		void free () {
			if (tmp != NULL) {
				delete[] tmp;
				}
			if (item != NULL) {
				delete[] item;
				}
			num_elements = 0;
			item = NULL;
			tmp = NULL;
			}
		void size (unsigned long myArraySize = 0) {
			if (myArraySize > 0) {
				dim(item, myArraySize);
				}
			num_elements = myArraySize;
			}
		void append (unsigned long val = 0) {
			unsigned int i;
			if (num_elements > 0) {
				dim(tmp, num_elements);
				for (i = 0; i < num_elements; i++) {
					tmp[i] = item[i];
					}
				dim(item, num_elements + 1);
				for (i = 0; i < num_elements; i++) {
					item[i] = tmp[i];
					}
				delete[] tmp;
				tmp = NULL;
				}
			else {
				dim(item, num_elements + 1);
				}
			item[num_elements] = val;
			num_elements+=1;
			}
		void deleteItem (unsigned long index) {
			unsigned int i = 0;
			unsigned int ii = 0;
			if (num_elements > 0 && index < num_elements) {
				dim(tmp, num_elements);
				for (i = 0; i < num_elements; i++) {
					tmp[i] = item[i];
					}
				dim(item, num_elements - 1);
				for (i = 0; i < num_elements; i++) {
					if (i != index) {
						item[ii] = tmp[i];
						ii++;
						}
					}
				num_elements-=1;
				delete[] tmp;
				tmp = NULL;
				}
			}
		void insertItem (unsigned long val, unsigned long index) {
			unsigned int i = 0;
			unsigned int ii = 0;
			if (index <= num_elements) {
				if (num_elements > 0) {
					dim(tmp, num_elements);
					for (i = 0; i < num_elements; i++) {
						tmp[i] = item[i];
						}
					dim(item, num_elements + 1);
					item[index] = val;
					for (i = 0; i < num_elements; i++) {
						if (i != index) {
							item[ii] = tmp[i];
							}
						else {
							ii += 1;
							item[ii] = tmp[i];
							}
						ii += 1;
						}
					delete[] tmp;
					tmp = NULL;
					}
				else {
					dim(item, num_elements + 1);
					item[num_elements] = val;
					}
				num_elements+=1;
				}
			}
		void join (Integer &mrgArray) {
			unsigned int i;
			unsigned int ii = 0;
			if (mrgArray.count() > 0) {
				redim(item, num_elements, num_elements + mrgArray.count());
				i = num_elements - mrgArray.count();
				for (i = num_elements - mrgArray.count(); i < num_elements; i++) {
					item[i] = mrgArray.item[ii];
					ii++;
					}
				}
			//delete[] tmp;
			}
		signed long findItem (unsigned long val) {
			signed long index = -1;
			if (num_elements > 0) {
				for (unsigned int i = 0; i < num_elements; i++) {
					if (item[i] == val) {
						index = i;
						break;
						}
					}
				}
			return index;
			}
		void appendIfUnique (unsigned long val) {
			if (findItem(val) < 0) {
				append(val);
				}
			}
		void sort () {
			unsigned int i = 1;
			unsigned long hold;
			i = num_elements - 1;
			while (i > 0) {
				if (item[i] < item[i - 1]) {
					hold = item[i];
					item[i] = item[i - 1];
					item[i - 1] = hold;
					if (i < num_elements - 1) {
						i += 1;
						}
					}
				else {
					i -= 1;
					}
				}
			}
		void print () {
			std::cout << "IntegerCount:\t" << num_elements << "\n" << std::endl;
			if (num_elements > 0) {
				for (unsigned long i = 0; i < num_elements; i++) {
					std::cout << "    " << (i + 1) << ").\t[" << item[i] << "]" <<std::endl;
					}
				}
			}
		};
	class Bit {
	private:
		bool items_zeroed;
		unsigned long num_items;
		unsigned long num_true;
		unsigned char* items;
	public:
		Bit (unsigned long num_bits = 0) {
			num_items = 0;
			num_true = 0;
			items = NULL;
			items_zeroed = true;
			if (num_bits > 0) {
				num_true = num_bits;
				num_items = num_bits;
				items_zeroed = false;
				unsigned long array_length = ceil((float)num_items / 8.0f);
				items = new unsigned char[array_length];
				for (unsigned long i = 0; i < array_length; i++) {
					items[i] = 0xFF;
					}
				}
			}
		~Bit () {
			if (items != NULL) {delete[] items;}
			}
		const unsigned long& numberSet = num_true;
		const unsigned long& count = num_items;
		const bool& isEmpty = items_zeroed;
		bool get (unsigned long index) {
			if (index < num_items) {
				unsigned long byteNum = index / 8.0f;
				unsigned char bitNum = index - (byteNum * 8);
				return (items[byteNum] & ((unsigned char)1 << bitNum));
				}
			return false;
			}
		void set (unsigned long index, bool state) {
			if (index < num_items) {
				if (state) {
					if (!get(index)) {
						num_true++;
						unsigned long byteNum = index / 8.0f;
						unsigned char bitNum = index - (byteNum * 8);
						items[byteNum] = (items[byteNum] | (unsigned char)1 << bitNum);
						}
					}
				else {
					if (get(index)) {
						num_true--;
						unsigned long byteNum = index / 8.0f;
						unsigned char bitNum = index - (byteNum * 8);
						items[byteNum] = (items[byteNum] & ~((unsigned char)1 << bitNum));
						}
					}
				}
			if (num_true == 0 && !items_zeroed) {
				items_zeroed = true;
				}
			else if (!items_zeroed) {
				items_zeroed = false;
				}
			}
		void free () {
			if (items != NULL) {delete[] items;}
			num_items = 0;
			num_true = 0;
			items = NULL;
			items_zeroed = true;
			}
		void dim (unsigned long num_bits) {
			if (num_bits > 0) {
				if (items != NULL) {free();}
				num_true = num_bits;
				num_items = num_bits;
				items_zeroed = false;
				unsigned long array_length = ceil((float)num_items / 8.0f);
				items = new unsigned char[array_length];
				for (unsigned long i = 0; i < array_length; i++) {
					items[i] = 0xFF;
					}
				}
			}
		};
	}

namespace myBinary {	// Binary Reading / Writing
	class memory {
	private:
		unsigned long pos;
		std::string fname;
		std::string fpath;
		std::string fext;
		std::string fsource;
		bool endianLittle;
		bool is_valid_ansi(std::string str) {
			// https://stackoverflow.com/a/28311607
			unsigned char byte;
			unsigned int cp;
			int num;
			unsigned long i = 0;
			while (i < str.size()) {
				byte = str[i];
				if ((byte & 0x80) == 0x00) {cp = (byte & 0x7F); num = 1;}// U+0000 to U+007F
				else if ((byte & 0xE0) == 0xC0) {cp = (byte & 0x1F); num = 2;} // U+0080 to U+07FF
				else if ((byte & 0xF0) == 0xE0) {cp = (byte & 0x0F);num = 3;}// U+0800 to U+FFFF
				else if ((byte & 0xF8) == 0xF0) {cp = (byte & 0x07);num = 4;}// U+10000 to U+10FFFF
				else {return false;}
				i++;
				for (int i = 1; i < num; ++i) {
					if ((byte & 0xC0) != 0x80) {return false;}
					cp = (cp << 6) | (byte & 0x3F);
					i++;
					}
				if ((cp > 0x10FFFF) ||
					((cp >= 0xD800) && (cp <= 0xDFFF)) ||
					((cp <= 0x007F) && (num != 1)) ||
					((cp >= 0x0080) && (cp <= 0x07FF) && (num != 2)) ||
					((cp >= 0x0800) && (cp <= 0xFFFF) && (num != 3)) ||
					((cp >= 0x10000) && (cp <= 0x1FFFFF) && (num != 4)))
					{return false;}
				}
			return true;
			}
		std::wstring utf8_2_unicode (std::string str) {
			std::wstring w;
			uint8_t byte;
			uint32_t uni;
			unsigned long i = 0;
			while (i < str.size()) {
				byte = str[i];
				if (byte <= 0x7F) {
					w += str[i];
					}
				else if (byte <= 0xDF) {
					uni = (((str[i] & 0x1F) << 6) & ((str[i + 1] & 0x3F)));
					w += uni;
					i++;
					}
				else if (byte <= 0xEF) {
					uni = (((str[i] & 0x0F) << 12) | ((str[i + 1] & 0x3F) << 6)  |  ((str[i + 2] & 0x3F) )  );
					w += uni;
					i+=2;
					}
				else if (byte <= 0xF7) {
					uni = (((str[i] & 0x07) << 18) | ((str[i + 1] & 0x3F) << 12)  |  ((str[i + 2] & 0x3F) << 6)    |  ((str[i + 3] & 0x3F) )  );
					w += uni;
					i+=3;
					}
				i++;
				}
			return w;
			}
		std::string unicode_2_utf8 (std::wstring str) {
			// https://rosettacode.org/wiki/UTF-8_encode_and_decode#VBA
			std::string out = "";
			uint32_t x;
			uint32_t r;
			std::string y;
			for (unsigned long i = 0; i < str.length(); i++) {
				x = str[i];
				if (x <= 0x0000007F) {
					y.resize(1);
					y[0] = x;
					}
				else if (x <= 0x000007FF) {
					y.resize(2);
					y[0] = 192 + x / 64;
					y[1] = 128 + x % 64;
					}
				else if (x <= 0x00007FFF) {
					y.resize(3);
					y[2] = 128 + x % 64;
					r = x / 64;
					y[1] = 128 + r % 64;
					y[0] = 224 + r / 64;
					}
				else if (x <= 0x0000FFFF) {
					y.resize(3);
					y[2] = 128 + x % 64;
					r = x / 64;
					y[1] = 128 + r % 64;
					y[0] = 224 + r / 64;
					}
				else if (x <= 0x0000FFFF) {
					y.resize(3);
					y[2] = 128 + x % 64;
					r = x / 64;
					y[1] = 128 + r % 64;
					y[0] = 224 + r / 64;
					}
				else if (x <= 0x0010FFFF) {
					y.resize(4);
					y[3] = 128 + x % 64;
					r = x / 64;
					y[2] = 128 + r % 64;
					r = r / 64;
					y[1] = 128 + r % 64;
					y[0] = 240 + r / 64;
					}
				out += y;
				}
			return out;
			}
	public:
		char* f;
		unsigned long fsize;
		memory () {
			f = NULL;
			pos = 0;
			fsize = 0;
			endianLittle = true;
			}
		~memory () {
			if (fsize != NULL) {delete[] f;}
			pos = 0;
			fsize = 0;
			f = NULL;
			endianLittle = true;
			}
		std::string getFilepath () {return fsource;}
		std::string getPath () {return fpath;}
		std::string getFilename () {return fname;}
		std::string getFileExt () {return fext;}
		unsigned long ftell () {
			return pos;
			}
		unsigned long size () {
			return fsize;
			}
		void seek (unsigned long offset = 0, seekType dir = seekType::set) {
			switch (dir) {
				case seekType::set :
					pos = offset;
					break;
				case seekType::end :
					pos = fsize - offset;
					break;
				case seekType::cur :
					pos += offset;
					break;
				}
			}
		void alignCursor (unsigned long alignment) {
			seek((unsigned long)((alignment-(pos % alignment)) % alignment), seekType::cur);
			}
		bool openFile (std::string filename) {
			if (is_valid_ansi(filename)) {
				std::ifstream file;
				file.open(filename.c_str(), std::ios::binary | std::ios::ate);
				file.seekg (0, file.end); fsize = file.tellg(); file.seekg (0, file.beg);
				file.clear();
				f = new char[fsize];
				file.read(f, fsize);
				file.clear();
				file.close();
				}
			else {
				// open file in a file handle, set properties
				HANDLE hFile = CreateFileW(
					utf8_2_unicode(filename).c_str(),		// file to open
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
				// get / check file size is larger then 0
				fsize = GetFileSize(hFile, NULL);
				if (fsize == 0) {
					std::cout << "Failed to read file. File is Empty?\n";
					return false;
					}
				// size char for buffer
				f = new char[fsize];
				// attempt to read file contents into memory
				unsigned long dwBytesRead = 0;
				if(ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize) {
					std::cout << "Failed to copy file into memory\n";
					fsize = 0; delete[] f; f = NULL;
					CloseHandle(hFile);
					return false;
					}
				// close out handle :-)
				CloseHandle(hFile);
				}
			fname = myPaths::getFilenameFile(filename);
			fpath = myPaths::getFilenamePath(filename);
			fext = myPaths::getFilenameType(filename);
			fsource = filename;
			return true;
			}
		bool openFileW (std::wstring filename) {
			// open file in a file handle, set properties
			HANDLE hFile = CreateFileW(
				(wchar_t*)filename.c_str(),		// file to open
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
			// get / check file size is larger then 0
			fsize = GetFileSize(hFile, NULL);
			if (fsize == 0) {
				std::cout << "Failed to read file. File is Empty?\n";
				return false;
				}
			// size char for buffer
			f = new char[fsize];
			// attempt to read file contents into memory
			unsigned long dwBytesRead = 0;
			if(ReadFile(hFile, f, fsize, &dwBytesRead, NULL) == FALSE || dwBytesRead != fsize) {
				std::cout << "Failed to copy file into memory\n";
				fsize = 0; delete[] f; f = NULL;
				CloseHandle(hFile);
				return false;
				}
			// close out handle :-)
			CloseHandle(hFile);
			fname = unicode_2_utf8(myPaths::getFilenameFileW(filename));
			fpath = unicode_2_utf8(myPaths::getFilenamePathW(filename));
			fext = unicode_2_utf8(myPaths::getFilenameTypeW(filename));
			fsource = unicode_2_utf8(filename);
			return true;
			}
		bool writeFile (std::string filename, size_t pos = 0, size_t wsize = 0, bool doAppend = false) {
			if (wsize < 1) {wsize = fsize - pos;}
			if (pos + wsize > fsize) {wsize = fsize - pos;}
			if (is_valid_ansi(filename)) {
				std::ofstream file;
				if (!doAppend) {
					file.open(filename.c_str(), std::ios::out | std::ios::binary);
					}
				else {
					file.open(filename.c_str(), std::ios::app | std::ios::out | std::ios::binary);
					}
				file.write(f + pos, wsize);
				file.close();
				}
			else {
				HANDLE hFile;
				unsigned long dwBytesWritten = 0;
				unsigned long dwPos = 0;
				if (!doAppend) {
					hFile = CreateFileW(
						utf8_2_unicode(filename).c_str(),	// open One.txt
						GENERIC_WRITE,					// open for reading
						FILE_SHARE_READ,					// do not share
						NULL,								// no security
						CREATE_NEW,						// existing file only
						FILE_ATTRIBUTE_NORMAL,				// normal file
						NULL								// no attr. template
						);
					}
				else {
					hFile = CreateFileW(
						utf8_2_unicode(filename).c_str(),	// open One.txt
						FILE_APPEND_DATA,					// open for reading
						FILE_SHARE_READ,					// do not share
						NULL,								// no security
						OPEN_ALWAYS,						// existing file only
						FILE_ATTRIBUTE_NORMAL,				// normal file
						NULL								// no attr. template
						);
					}
				if (hFile == INVALID_HANDLE_VALUE) {return false;}
				dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
				LockFile(hFile, dwPos, 0, fsize, 0);
				WriteFile(hFile, f + pos, wsize, &dwBytesWritten, NULL);
				UnlockFile(hFile, dwPos, 0, fsize, 0);
				CloseHandle(hFile);
				}
			}
		bool writeFileW (std::wstring filename, size_t pos = 0, size_t wsize = 0, bool doAppend = false) {
			//std::wcout << "filename:\t" << filename << std::endl;
			if (wsize < 1) {wsize = fsize - pos;}
			if (pos + wsize > fsize) {wsize = fsize - pos;}
			HANDLE hFile;
			unsigned long dwBytesWritten = 0;
			unsigned long dwPos = 0;
			if (!doAppend) {
				hFile = CreateFileW(
					(wchar_t*)filename.c_str(),			// open One.txt
					GENERIC_WRITE,						// open for reading
					FILE_SHARE_READ,					// do not share
					NULL,								// no security
					CREATE_ALWAYS,							// existing file only
					FILE_ATTRIBUTE_NORMAL,				// normal file
					NULL								// no attr. template
					);
				}
			else {
				hFile = CreateFileW(
					(wchar_t*)filename.c_str(),			// open One.txt
					FILE_APPEND_DATA,					// open for reading
					FILE_SHARE_READ,					// do not share
					NULL,								// no security
					OPEN_ALWAYS,						// existing file only
					FILE_ATTRIBUTE_NORMAL,				// normal file
					NULL								// no attr. template
					);
				}
			if (hFile == INVALID_HANDLE_VALUE) {
				std::cout << "failed to write file" << std::endl;
				return false;
				}
			dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);
			LockFile(hFile, dwPos, 0, fsize, 0);
			WriteFile(hFile, f + pos, wsize, &dwBytesWritten, NULL);
			std::cout << "pos\t" << pos << std::endl;
			std::cout << "wsize\t" << wsize << std::endl;
			std::cout << "fsize\t" << fsize << std::endl;
			std::cout << "dwBytesWritten\t" << dwBytesWritten << std::endl;
			UnlockFile(hFile, dwPos, 0, fsize, 0);
			CloseHandle(hFile);
			}
		void close () {
			if (fsize != NULL) {delete[] f;}
			pos = 0;
			fsize = 0;
			f = NULL;
			endianLittle = true;
			}
		void sizeBuffer (size_t memSize) {
			if (memSize > 0) {
				// delete old buffer
				close();

				// make new buffer
				f = new char[memSize];

				// set new buffer properties
				pos = 0;
				fsize = memSize;
				}
			}
		bool amendFileW (std::wstring filename, size_t buffer_write_pos) {
			// open file in a file handle, set properties
			HANDLE hFile = CreateFileW(
				(wchar_t*)filename.c_str(),		// file to open
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
			// get / check file size is larger then 0
			size_t asize = GetFileSize(hFile, NULL);
			if (asize == 0) {
				std::cout << "Failed to read file. File is Empty?\n";
				return false;
				}
			if ((buffer_write_pos + asize) > fsize) {
				std::cout << "input file is to larger for buffer\n";
				CloseHandle(hFile);
				return false;
				}
			// attempt to read file contents into memory
			unsigned long dwBytesRead = 0;

			LockFile(hFile, 0, 0, 0xffffffff, 0xffffffff);
			if(ReadFile(hFile, &f[buffer_write_pos], asize, &dwBytesRead, NULL) == FALSE || dwBytesRead != asize) {
				std::cout << "Failed to copy file into memory\n";
				CloseHandle(hFile);
				UnlockFile(hFile, 0, 0, 0xffffffff, 0xffffffff);
				return false;
				}
			UnlockFile(hFile, 0, 0, 0xffffffff, 0xffffffff);
			CloseHandle(hFile);
			return true;
			}
		std::string readstring (int length = -1, unsigned char term = 0x00, bool isXNAaraL = true, bool isWideChar = false) {
			std::string result = "";
			unsigned int length2 = 0;
			unsigned char letter;
			unsigned short wletter;
			std::wstring wstr;
			std::string str;

			bool isTerm = false;
			if (length < 0) {
				while (isTerm == false) {
					if (pos < fsize) {
						letter = f[pos];
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
				if (length > 0) {
					if (length >= 128 && isXNAaraL) {
						length2 = (uint8_t)f[pos];
						pos++;
						length = (length % 128) + (length2 * 128);
						}
					if (isWideChar == true) {
						for (int i = 0; i < length; ++i) {
							if (f[pos] == 0 && f[pos + 1] == 0) {isTerm = true;}
							if (isTerm == false) {
								result += myUTF::unicode_2_utf8(f[pos] + (f[pos + 1] * 0x0100));
								}
							pos+=2;
							}
						}
					else {
						for (int i = 0; i < length; ++i) {
							letter = f[pos];
							pos++;
							if (letter == 0) {isTerm = true;}
							if (isTerm == false) {result += letter;}
							}
						}
					}
				}
			return result;
			}
		std::string readline () {
			uint32_t startpoint = pos;
			std::string line = "";
			while (pos < fsize && f[pos] != 0x0A && f[pos] != 0x0D) {
				pos++;
				}
			if (pos > startpoint) {
				line = std::string(&f[startpoint], &f[pos - startpoint]);
				}
			while (pos < fsize && (f[pos] == 0x0A || f[pos] == 0x0D)) {
				pos++;
				}
			return line;
			}
		signed long long unsigned_to_signed (unsigned long n, char nbits) {	// unsigned_to_signed 0x80 8 = -128
			signed long long result = n;
			//if (myBitWise::bit::get(n, nbits)) {
			if (n > pow(2, nbits) / 2) {
				result = n - pow(2, nbits);
				}
			return result;
			}
		signed short readbyte (signIs sign = signIs::Unsigned) {
			signed short result = (uint8_t)f[pos];
			if (sign == signIs::Signed) {result = unsigned_to_signed(result, 8);}
			pos++;
			return result;
			}
		signed long readshort (signIs sign = signIs::Unsigned) {
			unsigned char byteOrder[] = {0, 1};
			if (!endianLittle) {
				byteOrder[0] = 1; byteOrder[1] = 0;
				}
			signed long result = {
				(unsigned int)((uint8_t)f[pos + byteOrder[0]] * 0x0001) + \
				(unsigned int)((uint8_t)f[pos + byteOrder[1]] * 0x0100)
				};
			if (sign == signIs::Signed) {result = unsigned_to_signed(result, 16);}
			pos += 2;
			return result;
			}
		signed long long readlong (signIs sign = signIs::Unsigned) {
			unsigned char byteOrder[] = {0, 1, 2, 3};
			if (!endianLittle) {
				byteOrder[0] = 3; byteOrder[1] = 2;
				byteOrder[2] = 1; byteOrder[3] = 0;
				}
			signed long long result = {
				(unsigned int)((uint8_t)f[pos + byteOrder[0]] * 0x00000001) + \
				(unsigned int)((uint8_t)f[pos + byteOrder[1]] * 0x00000100) + \
				(unsigned int)((uint8_t)f[pos + byteOrder[2]] * 0x00010000) + \
				(unsigned int)((uint8_t)f[pos + byteOrder[3]] * 0x01000000)
				};
			if (sign == signIs::Signed) {result = unsigned_to_signed(result, 32);}
			pos += 4;
			return result;
			}
		long long readlonglong () {
			unsigned char byteOrder[] = {0, 1, 2, 3, 4, 5, 6, 7};
			if (!endianLittle) {
				byteOrder[0] = 7; byteOrder[1] = 6; byteOrder[2] = 5;
				byteOrder[3] = 4; byteOrder[4] = 3; byteOrder[5] = 2;
				byteOrder[6] = 1; byteOrder[7] = 0;
				}
			unsigned long long result = {
				((uint8_t)f[pos + byteOrder[0]] * (unsigned long long)0x0000000000000001) + \
				((uint8_t)f[pos + byteOrder[1]] * (unsigned long long)0x0000000000000100) + \
				((uint8_t)f[pos + byteOrder[2]] * (unsigned long long)0x0000000000010000) + \
				((uint8_t)f[pos + byteOrder[3]] * (unsigned long long)0x0000000001000000) + \
				((uint8_t)f[pos + byteOrder[4]] * (unsigned long long)0x0000000100000000) + \
				((uint8_t)f[pos + byteOrder[5]] * (unsigned long long)0x0000010000000000) + \
				((uint8_t)f[pos + byteOrder[6]] * (unsigned long long)0x0001000000000000) + \
				((uint8_t)f[pos + byteOrder[7]] * (unsigned long long)0x0100000000000000)
				};
			pos += 8;
			return result;
			}
		float readHalffloat () {
			float result = 0.0;
			uint16_t float16 = readshort();
			uint32_t integer32 = ((((float16 & 0x000003FF) << 13)|(((signed int)(((float16 & 0x7C00) >> 10) + 0x0070)) << 23))|(((float16 >> 15) & 0x00000001) << 31));
			memcpy(&result, &integer32, 4);
			return (result);
			}
		float readfloat () {
			float result = 0.0;
			unsigned long b = readlong();
			memcpy(&result, &b, 4);
			return result;
			}
		double readdouble () {
			double result = 0.0;
			unsigned long long b = readlonglong();
			memcpy(&result, &b, 8);
			return result;
			}
		void writebyte (unsigned char val) {
			f[pos] = val;
			pos++;
			}
		void writeshort (unsigned short val) {
			if (!endianLittle) {
				f[pos + 1] = val & 0x00FF;
				f[pos + 0] = (val & 0xFF00) >> 8;
				}
			else {
				f[pos + 1] = (val & 0xFF00) >> 8;
				f[pos + 0] = val & 0x00FF;
				}
			pos+=2;
			}
		void writelong (unsigned long val) {
			if (!endianLittle) {
				f[pos + 3] = val & 0x00FF;
				f[pos + 2] = (val & 0xFF00) >> 0x08;
				f[pos + 1] = (val & 0xFF0000) >> 0x10;
				f[pos + 0] = (val & 0xFF000000) >> 0x18;
				}
			else {
				f[pos + 3] = (val & 0xFF000000) >> 0x18;
				f[pos + 2] = (val & 0xFF0000) >> 0x10;
				f[pos + 1] = (val & 0xFF00) >> 0x08;
				f[pos + 0] = val & 0x00FF;
				}
			pos+=4;
			}
		void writefloat (float val) {
			unsigned char* c = (unsigned char*) &val;
			if (!endianLittle) {
				f[pos + 3] = c[0];
				f[pos + 2] = c[1];
				f[pos + 1] = c[2];
				f[pos + 0] = c[3];
				}
			else {
				f[pos + 3] = c[3];
				f[pos + 2] = c[2];
				f[pos + 1] = c[1];
				f[pos + 0] = c[0];
				}
			pos+=4;
			}
		void writestring (std::string str, unsigned long length = 0, bool isWide = false) {
			unsigned long i;
			if (isWide) {
				std::wstring wstr = utf8_2_unicode(str);
				if (length > 0) {
					for (i = 0; i < length; i++) {
						if (i < wstr.size()) {
							writeshort((int)(uint16_t)wstr[i]);
							}
						else {
							writeshort(0);
							}
						}
					}
				else if (wstr.size() > 0) {
					for (i = 0; i < wstr.size(); i++) {
						writeshort((int)(uint16_t)wstr[i]);
						}
					writeshort(0);
					}
				}
			else {
				if (length > 0) {
					for (i = 0; i < length; i++) {
						if (i < str.size()) {
							writebyte(str[i]);
							}
						else {
							writebyte(0);
							}
						}
					}
				else {
					for (i = 0; i < str.size(); i++) {
						writebyte(str[i]);
						}
					writebyte(0);
					}
				}
			}
		};

	}


#endif // HELPER_H
