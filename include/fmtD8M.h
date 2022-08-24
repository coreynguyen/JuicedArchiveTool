/*	======================================================================

	Title:		[PC] Juiced
	Author:		mariokart64n
	Version:	0.1
	Date:		Dec 19 2021

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Parse D8M (DirectX 8 Model)

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2021-06-09]
		wrote it

	[2021-12-19]
		added compatibility with XBM (XBOX Model)

	======================================================================	*/
#ifndef FMTD8M_H
#define FMTD8M_H

#include <iostream>
#include <string>
#include <vector>
#include "bytestream.h"

struct fmtD8M_Vertex_FVF {
	int16_t flag;	// always 0 {-1 only on the termination entry}
	int16_t pos;
	int16_t data; // Range[1 {8bytes}, 2 {12bytes}, 4 {4bytes}] {17 only on the termination entry} 0x01=Float32[2], 0x02=Float32[3], 0x04=int8[3], 11=END
	int8_t type; // 0x0000=Position, 0x0003=Normal, 0x0005=TexCoord, 0x000A=VertexColour, 0x0105=???
	int8_t map; // map channel
	/*
	fvf requires a termination entry at the End
	255, 0, 17, 0

	Profiles:
	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=1 type=5 map=0	// UV0


	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=4 type=10 map=0	// Colour


	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=2 type=3 map=0	// Normal
	pos=24 data=1 type=5 map=0	// UV0

	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=4 type=10 map=0	// Colour
	pos=16 data=1 type=5 map=0	// UV0


	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=2 type=3 map=0	// Normal
	pos=24 data=1 type=5 map=0	// UV0
	pos=32 data=1 type=5 map=1	// UV1


	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=2 type=3 map=0	// Normal
	pos=24 data=4 type=10 map=0	// Colour
	pos=28 data=1 type=5 map=0	// UV0


	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=4 type=10 map=0	// Colour
	pos=16 data=1 type=5 map=0	// UV0
	pos=24 data=1 type=5 map=1	// UV1


	pos=0 data=2 type=0 map=0	// Position
	pos=12 data=2 type=3 map=0	// Normal
	pos=24 data=4 type=10 map=0	// Colour
	pos=28 data=1 type=5 map=0	// UV0
	pos=36 data=1 type=5 map=1	// UV1


	*** ALWAYS THE LAST ENTRY
	flag=255 pos=0 data=17 type=0 map=0
	*/
	void read (bytestream &f);
	void write (bytestream &s);
	};
struct fmtD8M_Float4 {
	float x; float y; float z; float w;
	void read (bytestream &f);
	};
struct fmtD8M_Float3 {
	float x; float y; float z;
	void read (bytestream &f);
	};
struct fmtD8M_Float2 {
	float u; float v;
	void read (bytestream &f);
	};
struct fmtD8M_Colour4 {
	float r; float g; float b; float a;
	void read (bytestream &f);
	};
struct fmtD8M_Vertex {
	uint32_t definition_count;
	fmtD8M_Vertex_FVF* definitions;
	uint32_t stride; // vert stride
	uint32_t count; // num verts
	fmtD8M_Float3* position;
	fmtD8M_Float3* normal;
	fmtD8M_Colour4* vcolour;
	fmtD8M_Float2* texcoord0;
	fmtD8M_Float2* texcoord1;
	fmtD8M_Vertex ();
	~fmtD8M_Vertex ();
	void readVertex (bytestream &f);
	};
struct fmtD8M_Object {
	fmtD8M_Float3 position;
	float scaler; // is 1.0 for materials, then 0.0 for final mesh
	float bound_sphere;
	/*
	the position applied to the mesh causes misalignments of the objects
	the position seems to only be applied to the bound sphere so that
	the sphere builts correctly around the mesh.

	likely I need to subtract the position from the vertices and
	offset the object position. this will store this position
	as the objects pivot position. This only needs to be done
	so that on re-export this position is restored here.
	*/
	fmtD8M_Float3 bound_min;
	fmtD8M_Float3 bound_max;
	void read (bytestream &f);
	};
struct fmtD8M_Mesh {
	std::string mesh_name;
	uint32_t face_start; // ?
	uint32_t face_count; // some count
	uint32_t face_type; // always 0? face type?
	fmtD8M_Object object;
	float lod_dist_spawn; // fade in distance 0.0?
	/* known values
		0
		250000
		562500
		1000000
		2250000
		4000000
		9000000
		25000000
		100000000
		225000000
		625000000
		900000000
		1000000000000
		4000000000000
	*/
	float lod_dist_despawn; // fade out distance, observed 100 000 000 wow <_<
	/*
		250000
		562500
		1000000
		2250000
		4000000
		9000000
		25000000
		49000000
		100000000
		144000000
		225000000
		625000000
		900000000
		122500000000
		1000000000000
		4000000000000
		9000000000000
		340282000000000000000000000000000000000
	*/
	uint32_t render_flag; // render type? shadow type? range:[0, 1, 3]
	/*
		the first value is always smaller then the second
		looks like the values starts at [0 - 250000]



		0	250000
		0	562500
		0	1000000
		0	49000000
		0	100000000
		0	225000000
		0	122500000000
		0	340282000000000000000000000000000000000
		250000	1000000
		562500	2250000
		1000000	2250000
		1000000	4000000
		2250000	9000000
		2250000	25000000
		4000000	9000000
		9000000	25000000
		9000000	100000000
		9000000	144000000
		25000000	100000000
		25000000	144000000
		25000000	225000000
		100000000	625000000
		100000000	1000000000000
		100000000	4000000000000
		100000000	9000000000000
		225000000	900000000
		225000000	4000000000000
		225000000	9000000000000
		625000000	1000000000000
		900000000	1000000000000
		1000000000000	4000000000000
		4000000000000	9000000000000

	*/
	fmtD8M_Vertex vertices;
	void readMesh (bytestream &f);
	};
struct fmtD8M_File {
	uint32_t face_count;
	int16_t* faces;
	uint32_t mesh_count;
	fmtD8M_Mesh* meshs;
	fmtD8M_Object bound;
	fmtD8M_File ();
	~fmtD8M_File ();
	void read (bytestream &f);
	void readJuicedBeta (bytestream &f);
	};


void read_d8m_model (std::wstring filename);

#endif // FMTD8M_H
