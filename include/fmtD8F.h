#ifndef FMTD8F_H
#define FMTD8F_H

#include <iostream>
#include <string>
#include "bytestream.h"
#include "tgaheader.h"

struct fmtD8F_Image { 	// 8 + n Bytes
	uint32_t width;
	uint32_t height;
	char* data;
	fmtD8F_Image ();
	~fmtD8F_Image ();
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtD8F_Table { 	// 48 Bytes
	/*
	specification for this table was provided by SxnnyB
	*/
	wchar_t char_code; 	 	// [2 bytes] Ascii Character in hex
	int16_t unk1; 			// [2 bytes] Unknown [only seen FF]
	int32_t width; 	 		// Width - 1, in pixels
	int32_t height; 	 	// Height - 1, in pixels
	int32_t unk2;
	int8_t unk3;
	int8_t unk4;
	int8_t unk5;
	int8_t unk6;
	int32_t kerning; 	 	// horizontial spacing from start og glyph to the next, kerning = {1.2381 * width}
	int32_t unk7; 			// [4 bytes] unknown - only seen 0x00
	float rect_left; 		// Percentage, multiply by image total width to get pixels
	float rect_top; 		// Percentage, multiply by image total height to get pixels
	float rect_right;  		// Percentage, multiply by image total width to get pixels
	float rect_bottom; 		// Percentage, multiply by image total height to get pixels
	int32_t image_index; 	// [4 bytes] which character sheet to use for this character
	void read (bytestream &f);
	void write (bytestream &s);
	};

struct fmtD8F {
	uint16_t clut_size;
	char* clut;
	uint32_t table_count;
	uint32_t table_count2; // same as image_count but minus 1
	fmtD8F_Table* table;
	uint32_t spacing;
	uint32_t image_count;
	fmtD8F_Image* image;
	fmtD8F ();
	~fmtD8F ();
	void read (std::wstring file);
	void exportTga (std::wstring file);
	void write (std::wstring file);
	};



#endif // FMTD8F_H
