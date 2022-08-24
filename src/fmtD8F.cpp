#include "fmtD8F.h"


fmtD8F_Image::fmtD8F_Image () {
	data = NULL;
	}

fmtD8F_Image::~fmtD8F_Image () {
	if (data != NULL) {delete[] data;}
	}

void fmtD8F_Image::read (bytestream &f) {
	width = f.readUlong();
	height = f.readUlong();
	uint32_t pitch = width * height;
	if (pitch > 0) {
		data = new char[pitch];
		for (uint32_t i = 0; i < pitch; i++) {
			data[i] = f.readUbyte();
			}
		}
	}

void fmtD8F_Image::write (bytestream &s) {
	s.writelong(width);
	s.writelong(height);
	uint32_t pitch = width * height;
	for (uint32_t i = 0; i < pitch; i++) {
		s.writebyte(data[i]);
		}
	}


void fmtD8F_Table::read (bytestream &f) {
	char_code 			= f.readshort();
	unk1 				= f.readshort();
	width 				= f.readlong();
	height 				= f.readlong();
	unk2 				= f.readlong();
	unk3 				= f.readUbyte();
	unk4 				= f.readUbyte();
	unk5 				= f.readUbyte();
	unk6 				= f.readUbyte();
	kerning 			= f.readlong();
	unk7 				= f.readlong();
	rect_left 			= f.readfloat();
	rect_top 			= f.readfloat();
	rect_right 			= f.readfloat();
	rect_bottom 		= f.readfloat();
	image_index 		= f.readlong();
	}

void fmtD8F_Table::write (bytestream &s) {
	s.writeshort(char_code);
	s.writeshort(unk1);
	s.writelong(width);
	s.writelong(height);
	s.writelong(unk2);
	s.writebyte(unk3);
	s.writebyte(unk4);
	s.writebyte(unk5);
	s.writebyte(unk6);
	s.writelong(kerning);
	s.writelong(unk7);
	s.writefloat(rect_left);
	s.writefloat(rect_top);
	s.writefloat(rect_right);
	s.writefloat(rect_bottom);
	s.writelong(image_index);
	}

fmtD8F::fmtD8F () {
	clut_size = 1024;
	clut = NULL;
	table = NULL;
	image = NULL;
	}

fmtD8F::~fmtD8F () {
	if (clut != NULL) {delete[] clut;}
	if (table != NULL) {delete[] table;}
	if (image != NULL) {delete[] image;}
	}

void fmtD8F::read (std::wstring file) {
	bytestream f;
	if (f.openFileW(file)) {
		clut_size = 1024;
		clut = new char[clut_size];
		for (uint16_t i = 0; i < clut_size; i++) {
			clut[i] 	= f.readbyte();
			}
		table_count 		= f.readUlong();
		table_count2 		= f.readUlong();
		spacing 				= f.readUlong();
		if (table_count > 0) {
			table = new fmtD8F_Table[table_count];
			for (uint32_t i = 0; i < table_count; i++) {
				table[i].read(f);
				}
			}
		image_count 		= f.readUlong();
		if (image_count > 0) {
			image = new fmtD8F_Image[image_count];
			for (uint32_t i = 0; i < image_count; i++) {
				image[i].read(f);
				}
			}
		f.close();
		} else {std::cout << "failed to open file\n";}
	}

void fmtD8F::exportTga (std::wstring file) {
	if (image == NULL && image_count > 0) {
		std::cout << "Image Array Is Invalid\n";
		return;
		}
	bool canTether = true;
	for (unsigned int i = 0; i < image_count; i++) {
		if (image[0].width != image[i].width || image[0].width != image[i].width) {
			canTether = false;
			break;
			}
		}
	if (!canTether) {
		std::cout << "images are not the same dimension\n";
		return;
		}
	bytestream s;
	s.resize(1042 + (image[0].width * image_count * image[0].height));
	tgaheader h;
	h.write_header(s, image[0].width * image_count, image[0].height);
	s.seek(18);
	for (unsigned int i = 0; i < clut_size; i++) {
		s.writebyte(clut[i]);
		}
	unsigned int v = image[0].height;
	for (unsigned int y = 0; y < image[0].height; y++) {
		s.seek(1042 + (--v * (image_count * image[0].width)));
		for (unsigned int i = 0; i < image_count; i++) {
			for (unsigned int x = 0; x < image[0].width; x++) {
				s.writebyte(image[i].data[x + (image[0].width * y)]);
				}
			}
		}
	s.writeFileW(file);
	}

void fmtD8F::write (std::wstring file) {
	clut_size = 1024;
	size_t fsize = clut_size + 16 + (table_count * 48);
	for (uint16_t i = 0; i < table_count; i++) {
		fsize += (table[i].width * table[i].width) + 8;
		}
	bytestream s;
	s.resize(fsize);
	s.seek(0);
	for (uint16_t i = 0; i < clut_size; i++) {
		s.writebyte(clut[i]);
		}
	s.writelong(table_count);
	s.writelong(table_count2);
	s.writelong(spacing);
	for (uint32_t i = 0; i < table_count; i++) {
		table[i].write(s);
		}
	s.writelong(image_count);
	for (uint32_t i = 0; i < image_count; i++) {
		image[i].write(s);
		}
	s.writeFileW(file);
	s.close();
	}


