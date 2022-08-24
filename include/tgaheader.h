/*	======================================================================

	Title:		Targa Image Library
	Author:		mariokart64n
	Version:	0.1
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		TGA I/O Library

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		Only half-assed enough to read a few things from the header

	======================================================================	*/

#ifndef TGAHEADER_H
#define TGAHEADER_H

#include <iostream>
#include "bytestream.h"

struct tgaheader {
	char  idlength;
	char  colourmaptype;
	/*
		0	No image data included.
		1	Uncompressed, color-mapped images.
		2	Uncompressed, RGB images.
		3	Uncompressed, black and white images.
		9	Runlength encoded color-mapped images.
		10	Runlength encoded RGB images.
		11	Compressed, black and white images.
		32	Compressed color-mapped data, using Huffman, Delta, and runlength encoding.
		33	Compressed color-mapped data, using Huffman, Delta, and runlength encoding.  4-pass quadtree-type process.
	*/
	char  datatypecode;
	short int clut_start;
	short int clut_length;
	char  clut_bbp;
	short int x_origin;
	short int y_origin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor; // bits 3-0 give the alpha channel depth, bits 5-4 give direction
	tgaheader ();
	void write_header (bytestream &s, int img_width, int img_height);
	};

#endif // TGAHEADER_H
