/*	======================================================================

	Title:		[PC] Juiced
	Author:		mariokart64n
	Version:	0.1
	Date:		May 23 2021

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		dumps bin file

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2021-05-23]
		wrote it

	[2021-12-06]
		added an additional statement for ddt files
		the way i was calculating the dds header was wrong
		I should probably revamp the code, but i wrote in
		fixes for the pitch calculation only for dxt1 and dxt5

	[2021-12-07]
		Compiled FreeImage, and effectively removed old functions
		that used Dev-IL.
		All functions were moved out of main

	[2021-12-09]
		Ported Ekey's Hash function:
		https://github.com/Ekey/JCED2.JFS.Tool/blob/main/JCED2.Unpacker/JCED2.Unpacker/FileSystem/Package/JfsHash.cs

		removed helper.h and divided its functions into
		bytestream.h
		filesystem.h
		stringext.h
		wstringext.h

		possibly a bad idea, but helper.h was so cluttered

	[2021-12-18]
		I ported my string splitting code from maxscript to c++
		this will take a fullpath like C:/test/file.bin and
		cut it into parts such a path, name, extension.
		The function does two things, it will generate a lst
		which can be dropped into the res folder and when
		compiled the list of known files will be included
		as a resource. it will also split the string list
		into several files like PATHS.TXT, NAMES.TXT, TYPES.TXT
		etc..

	[2021-12-19]
		Had a look at the model samples SxnnyB sent from each
		console, there was;

			D8M = DirectX8 Model
			XBM = Xbox Model
			PPM = Playstation Pocket Model
			P2M = Playstation 2 Model

		I wrote a format specification for PPM and adapted the
		D8M structure to work with the XBM files.

		P2M files contain VIF commands and I'm not sure how to
		decode, so I'll skip it support for P2M for now.

		There was also image formats, but they are all console
		specific and I don't have a code base to deal with those.
		again I'll skip those for now.

	======================================================================	*/


#include <iostream>		// needed for console printing
#include <fstream>
#include <windows.h>
#include <shellapi.h>	// needed for GetCommandLineW

#include "fmtDAT_Archive.h"
#include "fmtDDT.h"
#include "fmtD8M.h"
#include "fmtD8F.h"
#include "fmtPPM.h"

#include "filesystem.h"
#include "bytestream.h"
#include "stringext.h"
#include "wstringext.h"
#include "resource.h"
#include "interface.h"
#include "juiced_filelist.h"


//#include "helpers.h"

//#include "IL/il.h"
//#include "IL/ilu.h"  // for image creation and manipulation funcs.
//#include "IL/ilut.h"

//#include "splat2.h"
//#include "carrev.h"

using namespace std;


int main(int argc, char* argv[]) {
	db.read();

	// Check Inputs
	int argcW; LPWSTR *argvW = CommandLineToArgvW(GetCommandLineW(), &argcW); if (argcW == 0) {return 0;} // Get UNICODE Command line
	if (argcW > 1) {
		// Multiple Inputs
		std::wstring ftype;
		std::wstring file;
		std::wstring fname;
		std::wstring fpath;
		bool throwHappyMsg = true;
		// process each input
		for (signed long i = 1; i < argcW; i++) {

			// convert char* to string
			file = (std::wstring)argvW[i];
			fname = getFilenameFileW(file);
			fpath = getFilenamePathW(file);

			// get the file type of the file
			ftype = toUpperW(getFilenameTypeW(file));

			// run operation  based on the type
			if (ftype == L".DAT") {	// Unpacks the dat
				// init the hash names
				Juiced_NameDB db;
				db.read();
				// unpack dat file
				unpack_archive(file);
				}
			else if (ftype == L".LIST") { // Split Ekey's name list into name components
				Juiced_NameDB db;
				db.txt2lst(argv[i]);
				//db.createListOfUnsolvedHashes(getFilenamePath(argv[0]));
				}
			else if (ftype == L".TXT") {
				db.bruteForceHashes(argv[i]);
				}
			else if (ftype == L".D8M" || ftype == L".BIN" || ftype == L".XBM") {	// reads pc / pc beta / xbox model
				read_d8m_model(file);
				}
			else if (ftype == L".D8F") {	// reads psp model
				fmtD8F d8f;
				d8f.read(file);
				d8f.exportTga(fpath + fname + L".tga");
				}
			else if (ftype == L".PPM") {	// reads psp model
				read_ppm_file(file);
				}
			else if (ftype == L".PTD" || ftype == L".DDT") { // converts the game texture to a usable texture format
				fmtDDT ddt;
				bytestream f;
				if (f.openFileW(file)) {
					ddt.read(f);
					ddt.save(fpath + fname + L".dds");
					}
				}
			else if (ftype == L".DDS") {
				//convert_texture_to_ddt(argvW[i], ftype);
				fmtDDT ddt;
				ddt.write(file);
				}
			else {
				std::wcout << L"File Unsupported [" << ftype << L"]\n";
				throwHappyMsg = false;
				}
			}
		if (throwHappyMsg) {
			  MessageBoxA (
				0,
				"Files Processed!",
				"Yay!",
				MB_OK
				);
			}
		}
	else {
		// No Inputs

		/*
		std::cout << "=====================================================================\n";
		std::cout << "Juiced - Archive Tool\n\n";
		std::cout << "Written By:\tmariokart64n\n";
		std::cout << "Released:\tJune 05 2021\n\n";
		std::cout << "Usage:\n\tjatool.exe <file>\n\n";
		std::cout << "=====================================================================\n";
		std::cout << "Press ENTER to continue...";
		std::cin.clear();
		std::cin.sync();
		std::cin.get();
		*/

		// Launch UI
		make_window();

		//PlaySoundA(array_carrev, GetModuleHandle(NULL), SND_MEMORY | SND_ASYNC);
		return Fl::run();
		}


	// CleanUp
	LocalFree(argvW); // Free memory allocated for CommandLineToArgvW arguments.
	return 0;
	}

