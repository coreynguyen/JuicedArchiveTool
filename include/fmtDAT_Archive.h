/*	======================================================================

	Title:		[PC] Juiced
	Author:		mariokart64n
	Version:	0.1
	Date:		Dec 19 2021

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Unpack DAT Archive

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2021-06-09]
		wrote it

	[2021-12-19]
		added compatibility with XBM (XBOX Model)


	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Notes:

	Specification for the DAT Archived used in Juiced
	is on documented over on the xentax wiki written
	by: Ikskoks

	http://wiki.xentax.com/index.php/Juiced_DAT

	uint32 {4}   - Number Of Files
	uint32 {4}   - Directory Offset

	// File Data
		// for each file
			// for each file part
				uint32 {4}   - File Part Offset
				uint32 {4}   - File Part Length

			// for each file part
				byte {X}     - File Part Data

	// Directory
		// for each file
			uint32 {4}   - Unknown
			uint32 {4}   - File Offset
			uint32 {4}   - Number of File Parts
			uint32 {4}   - Compressed File Size
			uint32 {4}   - Decompressed File Size

	// Notes and Comments
		- Files are ZLib compressed

		- The files in the archive are in a different order to the files in the directory.
		  eg File 1 in the directory may be File 523 in the archive.

		- Each file can have multiple compressed parts. Each part is described at each file offset.
		  To determine how many parts there are in a file, go to the file offset and read the first field
		  (firstPartOffset). Then do (firstPartOffset-fileOffset)/8 and you have the number of parts.
		  (or you can just read the field in the directory!)
	======================================================================	*/

#ifndef FMTDAT_ARCHIVE_H
#define FMTDAT_ARCHIVE_H

//#include <string>
//#include <sstream>		// convert a number to string
//#include <windows.h>	// needed for opening files and such
//#include <dirent.h>		// needed to loop through files
//#include <stdio.h>		// needed for GetCommandLineW
//#include <stdlib.h>
//#include <vector>
//#include <sstream>      // needed for std::ostringstream
//#include <iomanip>		// needed for setfill
//#include <algorithm>	// needed for std::sort
//#include <time.h>		// needed for get_part_date
#include <zlc/zlibcomplete.hpp>	// add linker option: -lzlibcomplete    -lz
//#include <shlwapi.h>	// needed for PathIsDirectoryW() add linker flags -lshlwapi -lwinmm


//#include "helpers.h"
#include "bytestream.h"
#include "wstringext.h"
#include "filesystem.h"
#include "juiced_filelist.h"
#include "interface.h"
#include "fmtDDT.h"
extern Juiced_NameDB lst;

struct fmtDAT_Archive_Chunk { 		// Compressed Chunk
	uint32_t chunkAddr;
	uint32_t chunkSize;
	char* stream;
	fmtDAT_Archive_Chunk ();
	virtual ~fmtDAT_Archive_Chunk ();
	void readChunk (bytestream &f);
	};

struct fmtDAT_Archive_File {		// File Entry
	uint32_t fileHash;
	uint32_t fileAddr;
	uint32_t numChunks; // the file is cut into 32767 byte chunks and compressed
	uint32_t zlibSize;
	uint32_t destSize;
	bool isFolder;
	bool isCompressed;
	fmtDAT_Archive_Chunk* chunks;
	fmtDAT_Archive_File ();
	virtual ~fmtDAT_Archive_File ();
	void readFile (bytestream &f);
	uint32_t JfsHash (std::string m_String);	// tolower input
	};

struct fmtDAT_FL_Entry {			// Hash/Name Table Entry
	/*
	EKey (hax0r)
	has written his own dat archive tool and has
	created a hook and hash function to properly
	dump all the filenames in the game.
	*/
	uint32_t hashID;
	std::string name;
	fmtDAT_FL_Entry (uint32_t _hashID = 0, std::string _name = "");
	};

struct fmtDAT_Archive_Filelist {	// Hash/Name Database
	std::vector<fmtDAT_FL_Entry> fileList;
	void readFileListIni (std::wstring filename, bool verbose = false);
	void getFileListIni (bool verbose = false);
	};

struct fmtDAT_Archive {				// File Header
	uint32_t numFiles;
	uint32_t dirAddr;
	fmtDAT_Archive_File* files;
	fmtDAT_Archive ();
	~fmtDAT_Archive ();
	bool isFileValid (bytestream &f);
	void readArchive (bytestream &f, bool verbose = false);
	std::string genHexString (unsigned long hashID);
	std::wstring guessExtension (bytestream &f, size_t length);
	void unpack (std::wstring fpath);
	};

void unpack_archive (std::wstring filename);

#endif // FMTDAT_ARCHIVE_H
