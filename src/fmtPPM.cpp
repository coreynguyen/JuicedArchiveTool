#include "fmtPPM.h"


fmtPPM_Float4::fmtPPM_Float4 (float a, float b, float c, float d) {
	x = a; y = b; z = c; w = d;
	}

void fmtPPM_Float4::read (bytestream &f) {
	x = f.readfloat();
	y = f.readfloat();
	z = f.readfloat();
	w = f.readfloat();
	}

void fmtPPM_Bound::read (bytestream &f) {
	pos.read(f);
	sphere_radius = f.readfloat();
	min.read(f);
	max.read(f);
	}

void fmtPPM_Vertex::read (bytestream &f) {
	p01 = f.readfloat();
	p02 = f.readfloat();
	p03 = f.readfloat();
	p04 = f.readfloat();
	p05 = f.readfloat();
	p06 = f.readfloat();
	p07 = f.readfloat();
	p08 = f.readfloat();
	p09 = f.readfloat();
	p10 = f.readfloat();
	p11 = f.readfloat();
	p12 = f.readfloat();
	p13 = f.readfloat();
	p14 = f.readfloat();
	p15 = f.readfloat();
	p16 = f.readfloat();
	}

fmtPPM_Mesh::fmtPPM_Mesh () {
	vertices = NULL;
	}

fmtPPM_Mesh::~fmtPPM_Mesh () {
	if (vertices != NULL) {
		delete[] vertices;
		}
	}

void fmtPPM_Mesh::read (bytestream &f) {
	for (int i = 0; i < 32; i++) {
		mesh_name[i] = f.readbyte();
		}
	unk = f.readfloat();
	spawn_start = f.readfloat();
	spawn_end = f.readfloat();
	count1 = f.readlong();
	count2 = f.readlong();
	count3 = f.readlong();
	count4 = f.readlong();
	if (count4 > 0) {
		vertices = new fmtPPM_Vertex[count4];
		for (unsigned int i = 0; i < count4; i++) {
			vertices[i].read(f);
			}
		}
	}

fmtPPM::fmtPPM () {
	mesh = NULL;
	}

fmtPPM::~fmtPPM () {
	if (mesh != NULL) {
		delete[] mesh;
		}
	}

void fmtPPM::read (bytestream &f) {

	bound.read(f);
	mesh_count = f.readlong();
	if (mesh_count > 0) {
		mesh = new fmtPPM_Mesh[mesh_count];
		for (unsigned int i = 0; i < mesh_count; i++) {
			mesh[i].read(f);
			}
		}

	}

void read_ppm_file (std::wstring file) {
	bytestream f;
	fmtPPM ppm;
	if (f.openFileW(file)) {
		ppm.read(f);
		f.close();
		} else {std::wcout << L"failed to open file:\t" << file << std::endl;}
	}
