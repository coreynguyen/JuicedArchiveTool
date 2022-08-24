/*	======================================================================

	Title:		[PSP] Juiced
	Author:		mariokart64n
	Version:	0.1
	Date:		Dec 19 2021

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Parse PPM (Playstation Pocket Model)

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2021-12-19]
		wrote it

	======================================================================	*/
#ifndef FMTPPM_H
#define FMTPPM_H

#include <iostream>
#include <string>
#include "bytestream.h"

struct fmtPPM_Float4 {
	float x; float y; float z; float w;
	fmtPPM_Float4 (float a = 0, float b = 0, float c = 0, float d = 0);
	void read (bytestream &f);
	};

struct fmtPPM_Bound {	// 52 Bytes
	fmtPPM_Float4 pos;
	float sphere_radius;
	fmtPPM_Float4 min;
	fmtPPM_Float4 max;
	void read (bytestream &f);
	};

struct fmtPPM_Vertex {	// 64 bytes
	float p01;
	float p02;
	float p03;
	float p04;
	float p05;
	float p06;
	float p07;
	float p08;
	float p09;
	float p10;
	float p11;
	float p12;
	float p13;
	float p14;
	float p15;
	float p16;
	void read (bytestream &f);
	};

struct fmtPPM_Mesh {	// 112bytes + (n * 64 bytes)
	char mesh_name[32];
	fmtPPM_Bound bound;
	float unk;
	float spawn_start;
	float spawn_end;
	uint32_t count1;
	uint32_t count2;
	uint32_t count3;
	uint32_t count4;
	fmtPPM_Vertex* vertices;
	fmtPPM_Mesh ();
	~fmtPPM_Mesh ();
	void read (bytestream &f);
	};

struct fmtPPM {	// 56 Bytes + (n * mesh_count)
	fmtPPM_Bound bound;
	uint32_t mesh_count;
	fmtPPM_Mesh* mesh;
	fmtPPM ();
	~fmtPPM ();
	void read (bytestream &f);
	};

void read_ppm_file (std::wstring file);

#endif // FMTPPM_H
