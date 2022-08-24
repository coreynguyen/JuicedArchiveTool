/*	======================================================================
	Author:		mariokart64n
	Version:	0.1
	Date:		December 9 2021

	** If you Improve The Code Please Share Your Revisions **

	======================================================================	*/

#include "fmtDAT_Archive.h"

Juiced_NameDB lst;

fmtDAT_Archive_Chunk::fmtDAT_Archive_Chunk () {
	chunkAddr = 0;
	chunkSize = 0;
	stream = NULL;
	}

fmtDAT_Archive_Chunk::~fmtDAT_Archive_Chunk () {
	if (stream != NULL) {delete[] stream; stream = NULL;}
	}

void fmtDAT_Archive_Chunk::readChunk (bytestream &f) {
	chunkAddr = f.readlong();
	chunkSize = f.readlong();
	if (chunkSize > 0) {
		f.seek(chunkAddr);
		stream = new char[chunkSize];
		for (unsigned long i = 0; i < chunkSize; i++) {
			stream[i] = f.readbyte();
			}
		}
	}

fmtDAT_Archive_File::fmtDAT_Archive_File () {
	fileHash = 0;
	fileAddr = 0;
	numChunks = 0;
	zlibSize = 0;
	destSize = 0;
	isFolder = false;
	isCompressed = false;
	chunks = NULL;
	}

fmtDAT_Archive_File::~fmtDAT_Archive_File () {
	if (chunks != NULL) {
		delete[] chunks; chunks = NULL;
		}
	}

void fmtDAT_Archive_File::readFile (bytestream &f) {
	fileHash = f.readlong();
	fileAddr = f.readlong();
	numChunks = f.readlong();
	zlibSize = f.readlong();
	destSize = f.readlong();
	isFolder = false;
	isCompressed = true;
	if (numChunks == 0 && zlibSize == 0 && destSize == 0) {
		isFolder = true;
		}
	else {
		if (chunks != NULL) {delete[] chunks; chunks = NULL;}
		chunks = new fmtDAT_Archive_Chunk[numChunks];
		for (unsigned long i = 0; i < numChunks; i++) {
			f.seek(fileAddr + (8 * i));
			chunks[i].readChunk(f);
			}
		}
	}

uint32_t fmtDAT_Archive_File::JfsHash (std::string m_String) {
	/*
	Ekay (hax0r) discovered the hashing function in juiced
	https://github.com/Ekey/JCED.DAT.Tool


	Mine is based off his, but here is the call from IDApro

	unsigned int __stdcall sub_4FCD00(const char *a1)
	{
		unsigned int v1; // ebx
		unsigned int v3; // ebp
		unsigned int v4; // ecx
		int v5; // edi
		int v6; // esi
		int v7; // edi
		unsigned int v8; // [esp+4h] [ebp-4h]

		v1 = strlen(a1);
		if ( !v1 )
			return 0;
		v3 = 0;
		v8 = 0;
		if ( v1 != 1 )
		{
			do
			{
				v4 = v3;
				if ( v3 < v1 )
				{
					v5 = a1[v3];
					v6 = v5 + v3;
					v7 = v5 + 7;
					do
					{
						v8 += v6 * v7 * (a1[v4] + 19) * (a1[v4] + v4);
						++v4;
					}
					while ( v4 < v1 );
				}
				++v3;
			}
			while ( v3 < v1 - 1 );
		}
		return v8 % 0xEE6B2800;
	}

	*/
	uint32_t dwHash = 0;
	int32_t dwLength = m_String.size();
	int32_t whLength = dwLength - 1;
	if (dwLength < 2) {return 0;}
	for (int i = 0; i < whLength; i++) {
		for (int j = i; j < dwLength; j++) {
			dwHash += (uint32_t)(
				((uint8_t)m_String.at(i) + i) *
				((uint8_t)m_String.at(i) + 7) *
				((uint8_t)m_String.at(j) + 19) *
				((uint8_t)m_String.at(j) + j)
				);
			}
		}
	return (dwHash % 0xEE6B2800);
	}

fmtDAT_Archive::fmtDAT_Archive () {
	files = NULL;
	}

fmtDAT_Archive::~fmtDAT_Archive () {
	if (files != NULL) {delete[] files; files = NULL;}
	}

bool fmtDAT_Archive::isFileValid (bytestream &f) {
	bool valid = true;

	if (f.size < 8) {valid = false;}

	f.seek(0);
	uint32_t numFiles = f.readlong();
	uint32_t tableAddr = f.readlong();
	if (numFiles > tableAddr) {valid = false;}
	if (tableAddr > f.size - 20) {valid = false;}

	f.seek(tableAddr + 4);
	uint32_t fileAddr = f.readlong();
	if (fileAddr + 8 > f.size) {valid = false;}

	f.seek(fileAddr);
	uint32_t chunkAddr = f.readlong();
	if (chunkAddr > f.size) {valid = false;}

	f.seek(0);
	return valid;
	}

void fmtDAT_Archive::readArchive (bytestream &f, bool verbose) {
	numFiles = f.readlong();
	dirAddr = f.readlong();
	if (numFiles > 0) {
		if (files != NULL) {delete[] files; files = NULL;}
		files = new fmtDAT_Archive_File[numFiles];

		if (verbose) {std::cout << "FileHash\tAddress\t#Chunks\tZipSize\tRawSize\tisFolder\n\n";}


		for (unsigned long i = 0; i < numFiles; i++) {
			f.seek(dirAddr + (20 * i));
			files[i].readFile(f);

			if (verbose) {
				std::cout << files[i].fileHash << "\t";
				std::cout << files[i].fileAddr << "\t";
				std::cout << files[i].numChunks << "\t";
				std::cout << files[i].zlibSize << "\t";
				std::cout << files[i].destSize << "\t";
				std::cout << files[i].isFolder;

//					std::cout << "\t";
//					for (unsigned long c = 0; c < files[i].numChunks; c++) {
//						std::cout << "\t" << files[i].chunks[c].chunkSize;
//						}


				std::cout << "\n";
				}

			}
		}
	}

std::string fmtDAT_Archive::genHexString (unsigned long hashID) {
	unsigned long i;
	unsigned char c;
	std::string str = "";
	std::stringstream ss;
	ss << std::hex << hashID;
	str = ss.str();
	for (i = 0; i < str.length(); i++) {
		c = str[i];
		if (c > 96 && c < 103) {
			str[i] = c - 32;
			}
		}
	str = "00000000" + str;
	str = "0x" + str.substr(str.length() - 8);
	return str;
	}

std::wstring fmtDAT_Archive::guessExtension (bytestream &f, size_t length) {
	std::wstring fext = L".bin";
	unsigned long check1 = f.readlong();
	unsigned long check2 = f.readlong();
	unsigned long check3 = f.readlong();
	unsigned long check4 = f.readlong();
	unsigned long check5 = f.readlong();
//	unsigned long check6 = f.readlong();
//	unsigned long check7 = f.readlong();
	unsigned long check8 = f.readlong();


	if (check1 == 0x6574614D) {
		f.seek(19);
		fext = L" - " + string_to_wstring(f.readstring(-1, 0x0D)) + L".mat";
		}
	else if (check1 == 0x65746F6E) {
		fext = L".bat";
		}
	else if (check1 == 0x20534444) {
		fext = L".dds";
		}
	else if (check4 == 0x3F800000) {
		fext = L".d7m";
		}
//		else if (check1 == 0x31545844 || check1 == 0x33545844 || check1 == 0x35545844) {
//			fext = L".ptd";
//			}
	else if ((check2 == 8 || check2 == 16 || check2 == 32 || check2 == 64 || check2 == 128 || check2 == 256 || check2 == 512 || check2 == 1024 || check2 == 2048 || check2 == 4096) &&
			(check3 == 8 || check3 == 16 || check3 == 32 || check3 == 64 || check3 == 128 || check3 == 256 || check3 == 512 || check3 == 1024 || check3 == 2048 || check3 == 4096)
			) {
		fext = L".ptd";
		}
	else if ((check1 == 8 || check1 == 16 || check1 == 32 || check1 == 64 || check1 == 128 || check1 == 256 || check1 == 512 || check1 == 1024 || check1 == 2048 || check1 == 4096) &&
			(check2 == 8 || check2 == 16 || check2 == 32 || check2 == 64 || check2 == 128 || check2 == 256 || check2 == 512 || check2 == 1024 || check2 == 2048 || check2 == 4096) &&
			check4 == 0x000000FF
			) {
		fext = L".ttd";
		}
	else if (check1 == 0x0000004B && check2 == 0x00000002 && check3 == 0x0000003C) {
		fext = L".d6m";
		}

	else if ((check1 * 2 < length && check2 == 0x00010000) || (check1 == 4 && check2 == 0 && check3 == 0 && check4 == 1)) {
		f.seek((check1 * 2) + 8);
		fext = L" - " + toLowerW(string_to_wstring(f.readstring((check1 * 2) + 41, 32))) + L".d8m";
		}
	else if ((check1 * 16 < length && check5 == 0x3F800000) || ((check1 * 120) + 4 == length)) {
		fext = L".cam";
		}
	else if ((check1 & 0x0000FFFF) == 0x0A0D) {
		fext = L".ini";
		}
	else if ((check1 & 0x0000FFFF) == 0x9C78) {
		fext = L".zlb";
		}
	else if ((check1 & 0x0000FFFF) == 0xFEFF) {
		fext = L".msg";
		}
	else if (((check1 & 0x000000FF) == 0x5B) || ((check1 & 0x000000FF) == 0x3B) || ((check1 & 0x000000FF) == 0x3B)) {
		fext = L".ini";
		}
	else if ((check8 & 0x00FFFFFF) == 0x00545844) {
		fext = L".lst";
		}
	else if ((check1 & 0xFFFFFF00) == 0x00000100 && check2 == 3 && check3 == 2 && check4 == 4) {
		fext = L".tda";
		}
	return fext;
	}

void fmtDAT_Archive::unpack (std::wstring fpath) {
	bytestream s;
	const int CHUNK = 32767;
	zlibcomplete::ZLibDecompressor decompressor;
	std::string input = "";
	std::wstring fname;
	std::wstring fext;
	input.reserve(CHUNK);
	std::string output = "";
	std::string hashName = "";
	s.makeDirW(fpath);
	s.fpath = fpath;
	//std::cout << "numFiles:\t" << numFiles <<  std::endl;
	for (unsigned long i = 0; i < numFiles; i++) {
		fext = L"";
		hashName = db.getName(files[i].fileHash);
		//hashName = "";
		//std::cout << "HashName:\t" << hashName << std::endl;
		if (hashName != "") {
			fname = fpath + string_to_wstring(hashName);
			s.fname = string_to_wstring(hashName);
			s.makeDirW(getFilenamePathW(fname));
			}
		else {
			//fname = fpath + string_to_wstring(genHexString(files[i].fileHash));
			fname = fpath + string_to_wstring(   to_string(files[i].fileAddr)    ) + L" - " + string_to_wstring(genHexString(files[i].fileHash));
			s.fname = string_to_wstring(   to_string(files[i].fileAddr)    ) + L" - " + string_to_wstring(genHexString(files[i].fileHash));
			}

		if (!files[i].isFolder) {
			if (files[i].isCompressed) {
				output = "";
				output.reserve(files[i].destSize);

				for (unsigned long c = 0; c < files[i].numChunks; c++) {

					zlibcomplete::ZLibDecompressor decompressor;
					input = std::string(files[i].chunks[c].stream, files[i].chunks[c].chunkSize);
					output += decompressor.decompress(input);
					}
//				if (output.size() > 0) {
//					buffer = new char[output.size()];
//					for (unsigned long c = 0; c < output.size(); c++) {
//						buffer[c] = output[c];
//						}
//					//std::cout << output.size() << std::endl;
//					if (hashName == "") {fext = guessExtension(buffer, output.size());}
//					s.writeFile(fname + fext, 0, output.size(), (char*)output.c_str());
//					delete[] buffer;
//					}

				}
			else {


//				if (hashName == "") {fext = guessExtension(files[i].chunks[0].stream, files[i].chunks[0].chunkSize);}
//				s.writeFile(fname + fext, 0, files[i].chunks[0].chunkSize, files[i].chunks[0].stream);


				output = "";
				//output.reserve(files[i].destSize);

				for (unsigned long c = 0; c < files[i].numChunks; c++) {

					zlibcomplete::ZLibDecompressor decompressor;
					input = std::string(files[i].chunks[c].stream, files[i].chunks[c].chunkSize);
					output += decompressor.decompress(input);
					}
//				if (output.size() > 0) {
//					buffer = new char[output.size()];
//					for (unsigned long c = 0; c < output.size(); c++) {
//						buffer[c] = output[c];
//						}
//					//std::cout << output.size() << std::endl;
//					if (hashName == "") {fext = guessExtension(buffer, output.size());}
//					s.writeFile(fname + fext, 0, output.size(), (char*)output.c_str());
//					delete[] buffer;
//					}


				}

			if (output.size() > 0) {

				s.resize(output.size());
				for (unsigned long c = 0; c < output.size(); c++) {
					s.stream[c] = output[c];
					}
				//std::cout << output.size() << std::endl;
				if (hashName == "") {
					fext = guessExtension(s, s.size);
					}

				s.writeFileW(fname + fext);
				if (hashName != "") {
					fext = toLowerW(string_to_wstring(getFilenameType(hashName)));
					}
				//std::wcout << "Extension:\t" << fext << std::endl;
				if (fext == L".ptd" || fext == L".ddt") {
					s.seek(0);
					//convertPTD2TGA(s, s.size);
					fmtDDT ddt;
					ddt.read(s, s.size);
					ddt.save(getFilenamePathW(fname) + getFilenameFileW(fname) + L".dds");

					}
				}
			}
		s.close();
		}
	}

fmtDAT_FL_Entry::fmtDAT_FL_Entry (uint32_t _hashID, std::string _name) {
	hashID = _hashID;
	name = _name;
	}

void fmtDAT_Archive_Filelist::readFileListIni (std::wstring filename, bool verbose) {
	unsigned int ei = -1;
	uint32_t hashid;
	std::string fname;
	bytestream fi;
	fi.openFileW(filename);
	std::stringstream ss;
	std::string line;
	unsigned int first;
	unsigned int last;
	while (fi.tell() < fi.size) {
		line = fi.readline();
		line = rtrim(line);
		if (line.size() > 2) {
			ei = line.find("=");

			hashid = 0;
			fname = "";
			if (line.substr(0, 2) != "//" && ei != std::string::npos) {


				if (verbose) {std::cout << "Line:\t" << line.substr(2, ei - 2) << std::endl;}


				hashid = convert_to<uint32_t>(line.substr(0, ei));

				line = line.substr(ei + 1);


				first = line.find("\"");
				last = line.find_last_of("\"");

				if (first != std::string::npos && last != std::string::npos) {
					fname = line.substr (first + 1, last - first - 1);
					if (fname.find("/") != std::string::npos) {
						fname = ReplaceAll(fname, "/", "\\");
						}

					}




				//std::cout << "hashid:\t" << hashid << "\tfname:\t" << fname << std::endl;




				}



			if (hashid != 0 && fname != "") {
				fileList.push_back(fmtDAT_FL_Entry(hashid, fname));
				}


			}


		}


	fi.close();
	}

void fmtDAT_Archive_Filelist::getFileListIni (bool verbose) {
	std::wstring app_path = getFilenamePathW(win::runningPathW());
	std::wstring filelist_path = app_path + L"filelist.ini";

	//std::wcout << "filelist_path:\t" << app_path << L"filelist\\" << std::endl << "isFound:\t" << win::doesFolderExistW(app_path + L"filelist\\") << std::endl;


	if (win::doesFileExistW(filelist_path)) {
		//std::wcout << "READING FILELILST.INI" << std::endl;
		readFileListIni(filelist_path);
		}
	else if (win::doesFolderExistW(app_path + L"filelist\\")) {
		//std::wcout << "READING FILELILST DIRECTORY" << std::endl;
		filelist_path = app_path + L"filelist\\*.ini";

		std::wstring* dirFiles = NULL;
		unsigned long numFiles = 0;


		win::getFilesW (dirFiles, numFiles, filelist_path);

		//std::wcout << "FilesDiscovered:\t" << numFiles << std::endl;
		if (numFiles > 0) {
			for (unsigned long i = 0; i < numFiles; i++) {
				if (verbose) {std::wcout << L"File" << i << L"\t" << dirFiles[i] << std::endl;}
				readFileListIni(dirFiles[i]);
				}

			}

		if (dirFiles != NULL)  {delete[] dirFiles;}

		}

	}

void unpack_archive (std::wstring filename) {

	// read entire file into memory
	bytestream f;
	if (!f.openFileW(filename)) {
		std::cout << "failed to open archive\n";
		return;
		}

	// because '.dat' is a common extension,
	// check that dat is a valid juiced archive
	fmtDAT_Archive dat;
	if (!dat.isFileValid(f)) {
		std::wcout << L"Invalid Dat Archive:\t" << f.fname << f.fext << std::endl;
		return;
		}

	// read the dat archive into dat structure
	dat.readArchive(f);

	// call unpack function
	dat.unpack(f.fpath + f.fname + L"\\");
	}
