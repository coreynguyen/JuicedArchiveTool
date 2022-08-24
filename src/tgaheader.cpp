#include "tgaheader.h"


tgaheader::tgaheader () {
	idlength = 0;
	colourmaptype   = 1; // CLUT 256
	datatypecode    = 1;
	clut_start      = 0;
	clut_length     = 256;
	clut_bbp        = 32;
	x_origin        = 0;
	y_origin        = 0;
	width           = 0;
	height          = 0;
	bitsperpixel    = 8;
	imagedescriptor = 0;
	}

void tgaheader::write_header (bytestream &s, int img_width, int img_height) {
	s.seek(0);
	s.writebyte(idlength);
	s.writebyte(colourmaptype);
	s.writebyte(datatypecode);
	s.writeshort(clut_start);
	s.writeshort(clut_length);
	s.writebyte(clut_bbp);
	s.writeshort(x_origin);
	s.writeshort(y_origin);
	s.writeshort(img_width);
	s.writeshort(img_height);
	s.writebyte(bitsperpixel);
	s.writebyte(imagedescriptor);
	}

