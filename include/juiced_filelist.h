/*	======================================================================

	Title:		[PC] Juiced
	Author:		mariokart64n
	Version:	0.1
	Date:		December 19, 2021

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		get names for hashes in juiced

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Credits:
		Ekey, SxnnyB

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2021-12-19]
		added the hash function that Ekey (hax0r) pulled from the game
		added the name list that SxnnyB compiled using Ekey (hax0r)'s
		string dumper.

	======================================================================	*/
#ifndef JUICED_FILELIST_H
#define JUICED_FILELIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "resource.h"
#include "bytestream.h"
#include "stringext.h"
#include "filesystem.h"


struct Juiced_NameDB_Word {
	uint32_t addr;
	uint16_t size;
	Juiced_NameDB_Word (uint32_t a, uint16_t s) {
		addr = a; size = s;
		}
	void read (bytestream &f);
	};

struct Juiced_NameDB_Hash {
	uint32_t 		hash;
	uint16_t 		path;
	uint16_t 		prefix;
	uint16_t 		name;
	uint16_t 		serial;
	uint16_t 		suffix;
	uint16_t 		type;
	void read (bytestream &f);
	void write (bytestream &s);
	};
struct Juiced_WordDB {
	std::vector<std::string> path;
	std::vector<std::string> prefix;
	std::vector<std::string> name;
	std::vector<std::string> serial;
	std::vector<std::string> sufix;
	std::vector<std::string> type;
	};
struct Juiced_NameDB {
	uint32_t fileid; // 0x54534C46 "FLST"
	uint16_t version; // encase I need to make a revision
	uint16_t word_count;
	uint32_t word_addr;
	uint32_t hash_count;
	Juiced_NameDB_Hash* hash;
	bytestream buffer;
	uint32_t word_table_addr;
	Juiced_NameDB ();
	~Juiced_NameDB ();
	uint32_t getHash (std::string m_String);
	std::string getWord (int16_t index);
	std::string getName (uint32_t jhash);

	void read ();
	int getWordEntry (std::vector<Juiced_NameDB_Word> &table, Juiced_NameDB_Word word) {
		signed int index = -1;
		for (unsigned int i = 0; i < table.size(); i++) {
			if (table[i].addr == word.addr && table[i].size == word.size) {
				return i;
				}
			}
		if (index == -1) {
			index = table.size();
			table.push_back(word);
			}
		return index;
		}
	void appendWordTable (std::vector<Juiced_NameDB_Word> &table, std::string &word, std::string &words, uint16_t &pos) {
		if (word.size() > 0) {
			size_t index = words.find(word);
			if (index == std::string::npos) {
				pos = getWordEntry(table, Juiced_NameDB_Word(words.size(), word.size()));
				words += word;
				}
			else {
				pos = getWordEntry(table, Juiced_NameDB_Word(index, word.size()));
				}
			}
		}
	void writeStringBuffer (std::vector<std::string> &buf, std::string filename) {
		std::ofstream myfile(filename.c_str());
		if (myfile.is_open()) {
			for (unsigned int i = 0; i < buf.size(); i++) {
				myfile << buf[i] << "\n";
				}
			myfile.close();
			}
		}
	void txt2lst (std::string fileName) {

		Juiced_WordDB 						w;						// (for debugging purposes) store the the words in categories
		std::vector<std::string> 			stable;					// Store the names
		std::vector<Juiced_NameDB_Word> 	wtable;
		std::string 						words = "";
		std::ifstream 						in(fileName.c_str());
		std::string 						str;
		std::string 						tmp;
		std::string 						fpath;
		std::string 						d,p,b,n,s,t;
		unsigned int 						index;
		size_t								str_buf_size;
		size_t 								padding;

		if (!in) {
			std::cout << "Cannot open the File\t:" << fileName << std::endl;
			return;
			}
		while (std::getline(in, str)) {
			if (str.size() > 0) {
				stable.push_back(tolower(str));
				}
			}
		in.close();
		fpath = getFilenamePath(fileName);
		if (stable.size() == 0) {return;}
		hash = new Juiced_NameDB_Hash[stable.size()];
		hash_count = stable.size();

		for (unsigned int i = 0; i < stable.size(); i++) {


			//stable[i] = "TEST.BIN";

			//std::cout << "INPUT(" << stable[i].size() << "):\t" << stable[i] << std::endl << std::endl;

			hash[i].hash 		= getHash(stable[i]);
			hash[i].path 		= 0xFFFF;
			hash[i].prefix 		= 0xFFFF;
			hash[i].name 		= 0xFFFF;
			hash[i].serial 		= 0xFFFF;
			hash[i].suffix 		= 0xFFFF;
			hash[i].type 		= 0xFFFF;


			d = "";		// Directory
			p = "";		// Prefix
			b = "";		// Base Name
			n = "";		// Number
			s = "";		// Suffix
			t = "";		// Type


			// PATH
			index = stable[i].find_last_of("/\\");
			if (index != std::string::npos) {
				d = stable[i].substr(0, index + 1);
				stable[i] = stable[i].substr(d.size());
				}

			// TYPE
			index = stable[i].find(".");
			if (index != std::string::npos && index < stable[i].size()) {
				t = stable[i].substr(index);
				stable[i] = stable[i].substr(0, stable[i].size() - t.size());
				}

			// SERIAL
			index = stable[i].find_first_of("0123456789");
			if (index != std::string::npos && index < stable[i].size()) {

				// Store Number portion as the serial
				n = stable[i].substr(index, stable[i].find_last_of("0123456789") - index + 1);

				// Store anything RIGHT of the numbers as the Suffix
				index = stable[i].find_last_of("0123456789");
				if (index < stable[i].size()) {
					s = stable[i].substr(index + 1);
					}

				// Store anything LEFT of the numbers as the name
				index = stable[i].find_first_of("0123456789");
				if (index != std::string::npos) {
					// split out the prefix and name
					stable[i] = stable[i].substr(0, index);
					index = stable[i].find_last_of(" _");
					if (index != std::string::npos && index > 0 && index < stable[i].size()) {
						// Get Prefix
						p = stable[i].substr(0, index + 1);

						// NAME
						b = stable[i].substr(p.size());
						}
					else {
						// Name only
						b = stable[i];
						}
					}

				}
			else {
				// NO SERIAL, Check for other Split Character, such as a underscore or space
				index = stable[i].find(" ");
				if (index == std::string::npos) {index = stable[i].find("_");}
				if (index != std::string::npos && index < stable[i].size()) {

					p = stable[i].substr(0, index + 1);

					// remainder becomes the name
					stable[i] = stable[i].substr(p.size());
					index = stable[i].find_last_of("_");
					if (index != std::string::npos && index < stable[i].size()) {
						// Name
						b = stable[i].substr(0, index);

						// Suffix
						s = stable[i].substr(b.size());
						}
					else {
						b = stable[i];
						}
					}
				else {
					// No Splits, the left over is used as the whole name
					b = stable[i];
					}
				}

			//std::cout << d << p << b << n << s << t << std::endl;
			//break;

			if (d.size() > 0 && std::find(w.path.begin(), 		w.path.end(), 		d) == 	w.path.end()) 		{w.path.push_back	(d);}
			if (p.size() > 0 && std::find(w.prefix.begin(), 	w.prefix.end(), 	p) == 	w.prefix.end()) 	{w.prefix.push_back	(p);}
			if (b.size() > 0 && std::find(w.name.begin(), 		w.name.end(), 		b) == 	w.name.end()) 		{w.name.push_back	(b);}
			if (n.size() > 0 && std::find(w.serial.begin(), 	w.serial.end(), 	n) == 	w.serial.end()) 	{w.serial.push_back	(n);}
			if (s.size() > 0 && std::find(w.sufix.begin(), 		w.sufix.end(), 		s) == 	w.sufix.end()) 		{w.sufix.push_back	(s);}
			if (t.size() > 0 && std::find(w.type.begin(), 		w.type.end(), 		t) == 	w.type.end()) 		{w.type.push_back	(t);}

			appendWordTable(wtable, d, words, hash[i].path);
			appendWordTable(wtable, p, words, hash[i].prefix);
			appendWordTable(wtable, b, words, hash[i].name);
			appendWordTable(wtable, n, words, hash[i].serial);
			appendWordTable(wtable, s, words, hash[i].suffix);
			appendWordTable(wtable, t, words, hash[i].type);
			}


		str_buf_size = 16 + (stable.size() * 16) + (wtable.size() * 6);
		padding = (16-(str_buf_size % 16)) % 16;
		buffer.resize(str_buf_size + padding + words.size());
		buffer.seek(0);
        buffer.writelong(0x54534C46);
        buffer.writeshort(1);
        buffer.writeshort(wtable.size());
        buffer.writelong(str_buf_size + padding);
        buffer.writelong(stable.size());

		for (unsigned int i = 0; i < stable.size(); i++) {
			buffer.writelong(hash[i].hash);
			buffer.writeshort(hash[i].path);
			buffer.writeshort(hash[i].prefix);
			buffer.writeshort(hash[i].name);
			buffer.writeshort(hash[i].serial);
			buffer.writeshort(hash[i].suffix);
			buffer.writeshort(hash[i].type);
			}
		for (unsigned int i = 0; i < wtable.size(); i++) {
			buffer.writelong(str_buf_size + padding + wtable[i].addr);
			buffer.writeshort(wtable[i].size);
			}
		for (unsigned int i = 0; i < padding; i++) {
			buffer.writebyte(0);
			}
		buffer.writestring(words, words.size());

		//std::cout << "\nwords(" << words.size() << "):\n";



		//std::cout << words << std::endl;
		//std::cout << words.size() << std::endl;
		buffer.writeFile(fileName + "_new.lst");
		if (w.path.size() > 0) {
			std::sort(w.path.begin(), w.path.end());
			writeStringBuffer(w.path, fpath + "PATHS.TXT");
			}
		if (w.prefix.size() > 0) {
			std::sort(w.prefix.begin(), w.prefix.end());
			writeStringBuffer(w.prefix, fpath + "PREFIXES.TXT");
			}
		if (w.name.size() > 0) {
			std::sort(w.name.begin(), w.name.end());
			writeStringBuffer(w.name, fpath + "NAMES.TXT");
			}
		if (w.serial.size() > 0) {
			std::sort(w.serial.begin(), w.serial.end());
			writeStringBuffer(w.serial, fpath + "SERIALS.TXT");
			}
		if (w.sufix.size() > 0) {
			std::sort(w.sufix.begin(), w.sufix.end());
			writeStringBuffer(w.sufix, fpath + "SUFFIES.TXT");
			}
		if (w.type.size() > 0) {
			std::sort(w.type.begin(), w.type.end());
			writeStringBuffer(w.type, fpath + "TYPES.TXT");
			}

		}
	void createListOfUnsolvedHashes (std::string fpath);
	void bruteForceHashes (std::string file);
	};




#endif // JUICED_FILELIST_H
