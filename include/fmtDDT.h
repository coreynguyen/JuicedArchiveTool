/*	======================================================================

	Title:		[PC] Juiced
	Author:		mariokart64n
	Version:	0.1
	Date:		Dec 19 2021

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Parse DDT (Direct Draw Texture)

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2021-06-09]
		wrote it

	======================================================================	*/
#ifndef FMTDDT_H
#define FMTDDT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include "FreeImage.h"
#include "FreeImagePlus.h"

#include "ddsheader.h"
#include "bytestream.h"
#include "stringext.h"

struct fmtDDT {
	uint32_t 						type;
	uint32_t 						height;
	uint32_t 						width;
	uint32_t 						mipcount;
	uint32_t 						unk1; 				// always 1?
	uint32_t 						unk2; 				// always 1?
	uint32_t 						unk3; 				// always 1?
	uint32_t 						unk4; 				// always 1?
	uint32_t 						unk5; 				// always 1?
	float 							unk6; 				// -1.5
	float 							unk7; 				// 0.0
	uint32_t 						unk8;
	uint32_t 						pal_size;
	bytestream						data;
	fmtDDT () {
		type 						= 0;
		height 						= 0;
		width 						= 0;
		mipcount 					= 0;
		unk1 						= 0;
		unk2 						= 0;
		unk3 						= 0;
		unk4 						= 0;
		unk5 						= 0;
		unk6 						= 0.0f;
		unk7 						= 0.0f;
		unk8 						= 0;
		pal_size 					= 0;
		}
	void read (bytestream &f, size_t bsize = 0) {		// Read a DDT / PTD and stores a DDS header
		/*
			image data is automatically converted to a dds format
		*/
		// Get Start Position of File
		size_t pos 					= f.tell();
		if (bsize == 0) {bsize = f.size;}
		// Read Header
		type 						= f.readlong();
		height 						= f.readlong();
		width 						= f.readlong();
		mipcount 					= f.readlong();
		unk1 						= f.readlong();
		unk2 						= f.readlong();
		unk3 						= f.readlong();
		unk4 						= f.readlong();
		unk5 						= f.readlong();
		unk6 						= f.readfloat();
		unk7 						= f.readfloat();
		unk8 						= 0;
		pal_size 					= 0;

		// Create Image Headers
		img_dds dds;
		DXGI_FORMAT ddsfmt;
		size_t dds_header_size 		= 128;
		uint32_t wsize 				= bsize - (f.tell() - pos);

		switch (type) {
			case 0x31545844: {						// DXT1
				ddsfmt 					= DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
				break;
				}
			case 0x32545844: {						// DXT2
				ddsfmt 					= DXGI_FORMAT::DXGI_FORMAT_BC1_UNORM;
				break;
				}
			case 0x33545844: {						// DXT3
				ddsfmt 					= DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM;
				break;
				}
			case 0x34545844: {						// DXT4
				ddsfmt 					= DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM;
				break;
				}
			case 0x35545844: {						// DXT5
				ddsfmt 					= DXGI_FORMAT::DXGI_FORMAT_BC3_UNORM;
				break;
				}
			default: {
				ddsfmt 					= DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
				unk8 					= f.readlong();
				pal_size 				= f.readlong();
				if (pal_size == 1024 && unk8 == 0) {
					wsize 					-= 8;
					}
				data.resize				(dds_header_size + wsize);
				}
			}


		if (pal_size == 1024 && unk8 == 0) {	// 256 palette
			/*
			convert to raw because the P8 support in dds
			is widely supported
			*/
			data.resize				(dds_header_size + (width * height * 4));
			dds.setHeader			(width, height, 1, ddsfmt);
			dds.writeHeader			(data.stream);
			data.seek				(dds_header_size);
			uint32_t pitch 			= width * height;
			int32_t pixel;
			for (uint32_t i = 0; i < pitch; i++) {
				f.seek(pos + 0x0434 + i);					// Seek to pixel, get palette index
				f.seek(pos + 0x0034 + (f.readUbyte() * 4));	// Read Pixel, Seek to colour in palette
				pixel = f.readlong();					// Read Colour from Palette
				data.writelong(pixel);					// Write Colour to destination Image
				}
			}
		else {
			dds.setHeader			(width, height, mipcount, ddsfmt);
			data.resize				(dds_header_size + wsize);
			data.seek				(0);
			dds.writeHeader			(data.stream);
			//data.seek				(0x54);
			//data.writelong			(type);
			data.seek				(dds_header_size);
			f.seek					(0x2C);
			for (uint32_t i = 0; i < wsize; i++) {
				data.writebyte		(f.readbyte());
				}
			}
		}
	void write (std::wstring filename) {				// read a dds and trim the header off, save as DDT / PTD
		// Open the DDS file
		if (!data.openFileW(filename)) {
			return;
			std::cout << "invalid dds\n";
			}

		// Check DDS Header
		data.seek(0);
		if (data.size < 128 && data.readlong() != 0x20534444) {
			std::cout << "Data is not valid DDS data\n";
			return;
			}

		// Set DDT/PTD Header Defaults
		unk1 						= 1;
		unk2 						= 1;
		unk3 						= 1;
		unk4 						= 1;
		unk5 						= 1;
		unk6 						= -1.5f;
		unk7 						= 0.0f;
		unk8 						= 0;
		pal_size 					= 0;


		// Search for script file, to load the header values
		bytestream s;
		std::wstring fpath = s.getFilenamePathW(filename);
		std::wstring fname = s.getFilenameFileW(filename);
		std::wstring hf 			= fpath + fname + L".pts";
		if (s.doesFileExistW(hf)) {
			// Collect Header Details from Text file
			s.openFileW(hf);
			std::string l;
			std::vector<std::string> t;
			while (s.tell() < s.size) {
				l = ReplaceAll(s.readline(), " ", "");
				t = split(l, "=");
				if (t.size() > 1) {
					t[0] = tolower(t[0]);
					if (t[0] == "format") {
						t[1] = toupper(t[1]);
						if (t[1] == "DXT1") {
							type = 0x31545844;
							}
						else if (t[1] == "DXT2") {
							type = 0x32545844;
							}
						else if (t[1] == "DXT3") {
							type = 0x33545844;
							}
						else if (t[1] == "DXT4") {
							type = 0x34545844;
							}
						else if (t[1] == "DXT5") {
							type = 0x35545844;
							}
						else {
							type = convert_to<int>(t[1]);
							}
						}
					else if (t[0] == "width") {
						width = convert_to<int>(t[1]);
						}
					else if (t[0] == "height") {
						height = convert_to<int>(t[1]);
						}
					else if (t[0] == "lods") {
						mipcount = convert_to<int>(t[1]);
						}
					else if (t[0] == "param1") {
						unk1 = convert_to<int>(t[1]);
						}
					else if (t[0] == "param2") {
						unk2 = convert_to<int>(t[1]);
						}
					else if (t[0] == "param3") {
						unk3 = convert_to<int>(t[1]);
						}
					else if (t[0] == "param4") {
						unk4 = convert_to<int>(t[1]);
						}
					else if (t[0] == "param5") {
						unk5 = convert_to<int>(t[1]);
						}
					else if (t[0] == "param6") {
						unk6 = convert_to<float>(t[1]);
						}
					else if (t[0] == "param7") {
						unk7 = convert_to<float>(t[1]);
						}
					else if (t[0] == "param8") {
						unk8 = convert_to<int>(t[1]);
						}
					}
				t.clear();
				}
			s.close();
			}

		// Get Image Dimensions
		data.seek					(12);
		height 						= data.readlong();
		width 						= data.readlong();

		// Get Mip Count
		data.seek					(28);
		mipcount 					= data.readlong();
		if (mipcount == 0) {mipcount = 1;}

		// Create DDT / PTD
		bytestream d;
		d.resize(data.size - 84);
		d.seek(0);
		if (type == 0) {type = 0x15;}
		d.writelong(type);
		d.writelong(width);
		d.writelong(height);
		if (mipcount == 0) {mipcount = 1;}
		d.writelong(mipcount);
		d.writelong(unk1);
		d.writelong(unk2);
		d.writelong(unk3);
		d.writelong(unk4);
		d.writelong(unk5);
		d.writefloat(unk6);
		d.writefloat(unk7);
		int pitch = data.size - 128;
		data.seek(128);
		for (int i = 0; i < pitch; i++) {
			d.writebyte(data.readbyte());
			}
		d.writeFileW(fpath + fname + L".ddt");
		}
	void save (std::wstring filename) {					// Writes the Image Data and Pre-made DDS header
		// Check that there is image data in the stream
		if (data.size > 0) {
			// Write data directly out to a file
			data.writeFileW				(filename);

			// Assemble a text file containing the header contents
			std::string t = "; Juiced Texture Conversion Script\r\n\r\n";
			switch (type) {
				case 0x31545844: {						// DXT1
					t += "format  = DXT1\r\n";
					break;
					}
				case 0x32545844: {						// DXT2
					t += "format  = DXT2\r\n";
					break;
					}
				case 0x33545844: {						// DXT3
					t += "format  = DXT3\r\n";
					break;
					}
				case 0x34545844: {						// DXT4
					t += "format  = DXT4\r\n";
					break;
					}
				case 0x35545844: {						// DXT5
					t += "format  = DXT5\r\n";
					break;
					}
				default: {
					t += "format  = " + to_string(type) + "\r\n";
					}
				}

			t += "width   = " + to_string(width) 		+ "\r\n";
			t += "height  = " + to_string(height) 		+ "\r\n";
			t += "lods    = " + to_string(mipcount) 	+ "\r\n";
			t += "param1  = " + to_string(unk1) 		+ "\r\n";
			t += "param2  = " + to_string(unk2) 		+ "\r\n";
			t += "param3  = " + to_string(unk3) 		+ "\r\n";
			t += "param4  = " + to_string(unk4) 		+ "\r\n";
			t += "param5  = " + to_string(unk5) 		+ "\r\n";
			t += "param6  = " + to_string(unk6) 		+ "\r\n";
			t += "param7  = " + to_string(unk7) 		+ "\r\n";
			t += "param8  = " + to_string(unk8) 		+ "\r\n";

			// Write header to a text file
			std::wstring outfile 	= data.getFilenamePathW(filename) + data.getFilenameFileW(filename) + L".pts";
			data.writeFileW			(outfile, 0, t.size(), (char*)t.c_str());
			}
		}
	void import (std::wstring filename) {				// Convert Image Data
		/*
		I need to open any image format specified in 'filename'
		then convert that to either RAW 32bit RGBA
		or Compress it to DXT1 then save that to my bytestream

		Previously I was using Dev-ImageLibrary but it was having
		bugs reading or writing unicode files.

		So I've replaced it with FreeImage, but I'm not sure
		how to do texture conversions in memory yet.

		*/

		// Start Free Image
		FreeImage_Initialise();

		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		//pointer to the image, once loaded
		FIBITMAP *dib(0);

		//check the file signature and deduce its format
		fif = FreeImage_GetFileTypeU((wchar_t*)filename.c_str(), 0);

		//if still unknown, try to guess the file format from the file extension
		if(fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilenameU((wchar_t*)filename.c_str());
			}


		//if still unkown, return failure
		if(fif == FIF_UNKNOWN) {
			std::cout << "failed to identify image type\n";
			}

		//check that the plugin has reading capabilities and load the file
		if(FreeImage_FIFSupportsReading(fif)) {
			dib = FreeImage_LoadU(fif, (wchar_t*)filename.c_str());
			}


		//if the image failed to load, return failure
		if(!dib) {
			std::cout << "failed to load image\n";
			}

		//retrieve the image data
		unsigned char* bits = NULL;
		bits = FreeImage_GetBits(dib);
		int width = FreeImage_GetWidth(dib);
		int height = FreeImage_GetHeight(dib);

		if((bits == NULL) || (width == 0) || (height == 0)) {
			std::cout << "loaded image is invalid\n";
			}

		std::cout << "width:\t" << width << std::endl;
		std::cout << "height:\t" << height << std::endl;

		//FreeImage_FlipVertical(dib);
		FIMEMORY* img = FreeImage_OpenMemory();

		if(!FreeImage_SaveToMemory(FIF_DDS, dib, img, PNG_DEFAULT)) {
			std::cout << "failed to create memory image" << std::endl;

			}
		//FreeImage_Save(FIF_TARGA, dib, "S:\\Private\\Coding\\Cpp\\Projects\\JuicedArchiveTool\\bin\\Release\\test\\plop.tga", 0);



		//Free FreeImage's copy of the data
		FreeImage_CloseMemory(img);
		if (bits != NULL) {delete[] bits;}
		FreeImage_Unload(dib);
		FreeImage_DeInitialise();


		}
	};

#endif // FMTDDT_H
