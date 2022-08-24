#include "juiced_filelist.h"

void Juiced_NameDB_Word::read (bytestream &f) {
	addr = f.readUlong();
	size = f.readUshort();
	}

void Juiced_NameDB_Hash::read (bytestream &f) {
	hash 		= f.readUlong();
	path 		= f.readUshort();
	prefix 		= f.readUshort();
	name 		= f.readUshort();
	serial 		= f.readUshort();
	suffix 		= f.readUshort();
	type 		= f.readUshort();
	}

void Juiced_NameDB_Hash::write (bytestream &s) {
	s.writelong(hash);
	s.writeshort(path);
	s.writeshort(prefix);
	s.writeshort(name);
	s.writeshort(serial);
	s.writeshort(suffix);
	s.writeshort(type);
	}




Juiced_NameDB::Juiced_NameDB () {
	fileid = 0x54534C46;
	version = 0;
	word_count = 0;
	word_addr = 0;
	hash_count = 0;
	hash = NULL;
	}

Juiced_NameDB::~Juiced_NameDB () {
	if (hash != NULL) {delete[] hash;}
	}

uint32_t Juiced_NameDB::getHash (std::string m_String) {
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

std::string Juiced_NameDB::getWord (int16_t index) {
	if (index != -1 && index < word_count) {
		buffer.seek(word_table_addr + (6 * index));
		uint32_t addr = buffer.readUlong();
		uint32_t size = buffer.readUshort();

		//std::cout << "INDEX:\t" << index << "\t" << word_table_addr + (6 * index) << " \t(" << addr << ") " << size << std::endl;
		buffer.seek(addr);
		return buffer.readstring(size);
		}
	return "";
	}

std::string Juiced_NameDB::getName (uint32_t jhash) {

	for (uint32_t i = 0; i < hash_count; i++) {
		if (jhash == hash[i].hash) {
			std::string name = "";
			//std::cout << jhash << "\t" << hash[i].path << "\t" << hash[i].prefix << "\t" << hash[i].name;
			//std::cout << "\t" << hash[i].serial << "\t" << hash[i].suffix << "\t" << hash[i].type << std::endl;
			name += getWord(hash[i].path);
			name += getWord(hash[i].prefix);
			name += getWord(hash[i].name);
			name += getWord(hash[i].serial);
			name += getWord(hash[i].suffix);
			name += getWord(hash[i].type);
			return name;
			}
		}
	//std::cout << "Hash Not Found" << std::endl;
	return "";
	}

void Juiced_NameDB::read () {
	if (!buffer.openResource(NAMELIST, "BINARY")) {
		std::cout << "failed to read resource\n";
		return;
		}

	if (buffer.size < 16) {
		std::cout << "invalid size\n";
		return;
		}

	fileid = buffer.readUlong();
	if (fileid != 0x54534C46) {
		std::cout << "invalid file\n";
		return;
		}

	version = buffer.readUshort();
	if (version != 1) {
		std::cout << "version not supported\n";
		return;
		}

	word_count = buffer.readUshort();
	if (word_count == 0) {
		std::cout << "no words\n";
		return;
		}
	word_addr = buffer.readUlong();
	hash_count = buffer.readUlong();
	if (hash_count == 0) {
		std::cout << "no hashes\n";
		return;
		}
	hash = new Juiced_NameDB_Hash[hash_count];
	for (uint32_t i = 0; i < hash_count; i++) {
		hash[i].read(buffer);
		}

	word_table_addr = (hash_count + 1) * 16;
	//std::cout << "word_table_addr:\t" << word_table_addr << std::endl;
	}

void Juiced_NameDB::createListOfUnsolvedHashes (std::string fpath) {
	std::ifstream file((fpath + "HASHES.TXT").c_str());
	if (file.is_open()) {
		std::string str;
		std::string hsh;
		std::stringstream ss;
		uint32_t hashid;
		std::ofstream myfile((fpath + "UHASHES.TXT").c_str());
		//std::cout << fpath << std::endl;
		while (std::getline(file, str)) {
			if (str.size() > 2) {
				ss.clear();
				ss.str("");
				ss << std::hex << str.substr(2);
				ss >> hashid;
				hsh = getName(hashid);
				if (hsh.size() > 0) {
					//std::cout << str << ":\t'" << hsh << "'" << std::endl;
					}
				else {
					//std::cout << str << std::endl;
					myfile << str << "\n";
					}
				}
			}
		myfile.close();
		file.close();
		} else {std::cout << "failed to locate HASHES.TXT\n";}
	}

void readTxtToStringVector (std::string file, std::vector<std::string> &arr) {
    std::ifstream f(file.c_str());
    if (f.is_open()) {
		std::string str;
		while (std::getline(f, str)) {
			if (str.size() > 0) {
				arr.push_back(str);
				}
			}
		f.close();
		}
	}

void Juiced_NameDB::bruteForceHashes (std::string file) {
	std::string fpath = getFilenamePath(file);
    std::vector<uint32_t> hashes;
    std::vector<std::string> uhash({""});
    std::vector<std::string> names({""});
    std::vector<std::string> paths({""});
    std::vector<std::string> nums({""});
    std::vector<std::string> prefix({""});
    std::vector<std::string> sufix({""});
    std::vector<std::string> types({""});

	if (win::doesFileExist(fpath + "UHASHES.TXT")) {readTxtToStringVector(fpath + "UHASHES.TXT", uhash);}
	if (win::doesFileExist(fpath + "NAMES.TXT")) {readTxtToStringVector(fpath + "NAMES.TXT", names);}
	if (win::doesFileExist(fpath + "PATHS.TXT")) {readTxtToStringVector(fpath + "PATHS.TXT", paths);}
	if (win::doesFileExist(fpath + "SERIALS.TXT")) {readTxtToStringVector(fpath + "SERIALS.TXT", nums);}
	if (win::doesFileExist(fpath + "PREFIXES.TXT")) {readTxtToStringVector(fpath + "PREFIXES.TXT", prefix);}
	if (win::doesFileExist(fpath + "SUFFIES.TXT")) {readTxtToStringVector(fpath + "SUFFIES.TXT", sufix);}
	if (win::doesFileExist(fpath + "TYPES.TXT")) {readTxtToStringVector(fpath + "TYPES.TXT", types);}

    uint32_t x;
    std::string str;

    std::stringstream ss;
    for (unsigned int i = 0; i < uhash.size(); i++) {
		if (uhash[i].size() < 2) {continue;}
		ss.str(std::string());
		ss << std::hex << uhash[i].substr(2);
		ss >> x;
		hashes.push_back(x);
		}
	std::ofstream out;
	out.open((fpath + "OUTPUT.TXT").c_str(), std::ios::out | std::ios::app);

	for (unsigned int d = 0; d < paths.size(); d++) {
		for (unsigned int p = 0; p < prefix.size(); p++) {
			for (unsigned int b = 0; b < names.size(); b++) {
				for (unsigned int n = 0; n < nums.size(); n++) {
					for (unsigned int s = 0; s < sufix.size(); s++) {
						for (unsigned int t = 0; t < types.size(); t++) {
							str = paths[d] + prefix[p] + names[b] + nums[n] + sufix[s] + types[t];
							x = getHash(str);
							for (unsigned int h = 0; h < hashes.size(); h++) {
								if (x == hashes[h]) {
									out << uhash[h] << "\t" << str << std::endl;
									std::cout << uhash[h] << "\t" << str << std::endl;
									break;
									}
								}
							}
						}
					}
				}
			}
		}


	out.close();
	}
