/*
D8M: DirectX 8 Model
*/

#include "fmtD8M.h"


void fmtD8M_Vertex_FVF::read (bytestream &f) {
	flag = f.readUshort();
	pos = f.readUshort();
	data = f.readUshort();
	type = f.readUbyte();
	map = f.readUbyte();
	}

void fmtD8M_Vertex_FVF::write (bytestream &s ) {
	s.writeshort(flag);
	s.writeshort(pos);
	s.writeshort(data);
	s.writebyte(type);
	s.writebyte(map);
	}

void fmtD8M_Float4::read (bytestream &f) {
	x = f.readfloat();
	y = f.readfloat();
	z = f.readfloat();
	w = f.readfloat();
	}

void fmtD8M_Float3::read (bytestream &f) {
	x = f.readfloat();
	y = f.readfloat();
	z = f.readfloat();
	}

void fmtD8M_Float2::read (bytestream &f) {
	u = f.readfloat();
	v = f.readfloat();
	}

void fmtD8M_Colour4::read (bytestream &f) {
	r = f.readbyte() / 255.0;
	g = f.readbyte() / 255.0;
	b = f.readbyte() / 255.0;
	a = f.readbyte() / 255.0;
	}

fmtD8M_Vertex::fmtD8M_Vertex () {
	definitions = NULL;
	position = NULL;
	normal = NULL;
	vcolour = NULL;
	texcoord0 = NULL;
	texcoord1 = NULL;
	}

fmtD8M_Vertex::~fmtD8M_Vertex () {
	if (definitions != NULL) {delete[] definitions;}
	if (position != NULL) {delete[] position;}
	if (normal != NULL) {delete[] normal;}
	if (vcolour != NULL) {delete[] vcolour;}
	if (texcoord0 != NULL) {delete[] texcoord0;}
	if (texcoord1 != NULL) {delete[] texcoord1;}
	}

void fmtD8M_Vertex::readVertex (bytestream &f) {
	size_t p = 0;
	float r[4];

	definition_count = f.readUlong();
	if (definition_count > 0) {
		definitions = new fmtD8M_Vertex_FVF[definition_count];
		for (unsigned int i = 0; i < definition_count; i++) {
			definitions[i].read(f);
			}
		}
	else {
		// Xbox Flavor (there is no count, 256 buffer is reserved = 16 entries)
		f.seek(f.tell() - 4);
		definition_count = 16;
		definitions = new fmtD8M_Vertex_FVF[definition_count];
		for (unsigned int i = 0; i < definition_count; i++) {
			definitions[i].flag = f.readlong();
			definitions[i].pos = f.readlong();
			definitions[i].data = f.readlong();
			definitions[i].type = f.readshort();
			definitions[i].map = f.readshort();
			// convert the fvf to the PC one
			switch (i) {
				case 0: {definitions[i].type = 0x00; break;}
				case 1: {definitions[i].type = 0x0A; break;}
				case 2: {definitions[i].type = 0x03; break;}
				case 3: {definitions[i].type = 0x05; break;}
				case 4: {definitions[i].type = 0x05; definitions[i].map = 1; break;}
				default: {
					if (definitions[i].data != 2) {
						std::cout << "unknown vertex index:\t" << i << " \t @ " << f.tell() << "\n";
						}
					}
				}
			switch (definitions[i].data) {
				case 0x02: {} // ignore
				case 0x22: {definitions[i].data = 0x01;}
				case 0x32: {definitions[i].data = 0x02;}
				case 0x40: {definitions[i].data = 0x04;}
				default: {
					std::cout << "unknown vertex tyoe:\t" << definitions[i].data << " \t @ " << f.tell() << "\n";
					}
				}
			}
		}
	stride = f.readUlong();
	count = f.readUlong();
	if (count > 0) {
		position = new fmtD8M_Float3[count];
		normal = new fmtD8M_Float3[count];
		vcolour = new fmtD8M_Colour4[count];
		texcoord0 = new fmtD8M_Float2[count];
		texcoord1 = new fmtD8M_Float2[count];
		for (unsigned int v = 0; v < count; v++) {
			p = f.tell();
			position[v] = {0.0, 0.0, 0.0};
			normal[v] = {0.0, 0.0, 0.0};
			vcolour[v] = {0, 0, 0, 0};
			texcoord0[v] = {0.0, 0.0};
			texcoord1[v] = {0.0, 0.0};
			for (unsigned int i = 0; i < definition_count; i++) {
				if (definitions[i].flag != 0) {
					break;
					}
				f.seek(p + definitions[i].pos);
				r[0] = 0.0; r[1] = 0.0; r[2] = 0.0; r[3] = 0.0;
				switch (definitions[i].data) {
					case 1: {
						r[0] = f.readfloat();
						r[1] = f.readfloat();
						break;
						}
					case 2: {
						r[0] = f.readfloat();
						r[1] = f.readfloat();
						r[2] = f.readfloat();
						break;
						}
					case 4: {
						r[0] = f.readbyte() / 255.0f;
						r[1] = f.readbyte() / 255.0f;
						r[2] = f.readbyte() / 255.0f;
						r[3] = f.readbyte() / 255.0f;
						break;
						}
					}
				switch (definitions[i].type) {
					case 0x00: {position[v] = {r[0], r[1], r[2]}; break;} // Position
					case 0x03: {normal[v] = {r[0], r[1], r[2]}; break;} // normals
					case 0x0A: {vcolour[v] = {r[0], r[1], r[2], r[3]}; break;} // vcolour
					case 0x05: { // UVs
						if (definitions[i].map == 0) {
							texcoord0[v] = {r[0], 1.0f-r[1]};
							}
						else {
							texcoord1[v] = {r[0], 1.0f-r[1]};
							}
						break;
						}
					}

				}
			f.seek(p + stride);
			}
		}
	}

void fmtD8M_Object::read (bytestream &f) {
	position.read(f);
	scaler = f.readfloat();
	bound_sphere = f.readfloat();
	bound_min.read(f);
	bound_max.read(f);
	}

void fmtD8M_Mesh::readMesh (bytestream &f) {
	size_t mesh_name_pos = f.tell() + 32;
	mesh_name = f.readstring();
	f.seek(mesh_name_pos);

	face_start = f.readUlong();
	face_count = f.readUlong();
	face_type = f.readUlong();
	object.read(f);
	lod_dist_spawn = f.readfloat();
	lod_dist_despawn = f.readfloat();
	render_flag = f.readUlong();
	vertices.readVertex(f);
	}


fmtD8M_File::fmtD8M_File () {
	faces = NULL;
	meshs = NULL;
	}

fmtD8M_File::~fmtD8M_File () {
	if (faces != NULL) {delete[] faces;}
	if (meshs != NULL) {delete[] meshs;}
	}

void fmtD8M_File::read (bytestream &f) {
	face_count = f.readUlong();
	if (face_count > 0) {
		faces = new int16_t[face_count];
		for (unsigned int i = 0; i < face_count; i++) {
			faces[i] = f.readUshort();
			}
		}
	mesh_count = f.readUlong();
	if (mesh_count > 0) {
		meshs = new fmtD8M_Mesh[mesh_count];
		for (unsigned int i = 0; i < mesh_count; i++) {
			meshs[i].readMesh(f);
			}
		}
	bound.read(f);
	}

void fmtD8M_File::readJuicedBeta (bytestream &f) {

	bound.read(f);

	uint32_t vertex_count = f.readUlong();
	uint32_t vertex_stride = 0x24;
	size_t vertex_pos = f.tell();
	f.seek(vertex_pos + (vertex_count * vertex_stride));

	uint32_t index_count = f.readUlong();
	uint16_t face_stride = 0x02;
	size_t index_pos = f.tell();
	f.seek(f.tell() + (index_count * face_stride));

	mesh_count = f.readUlong();
	size_t material_pos = f.tell();
	f.seek(f.size);
	// {O_o} the stride changes Wtf
	uint32_t mesh_def_stride = (((f.tell()) - material_pos) / mesh_count);
	fmtD8M_Float3* vertArray = NULL;
	fmtD8M_Float2* tvertArray = NULL;
	fmtD8M_Float3* normArray = NULL;
	fmtD8M_Colour4* colrArray = NULL;
	f.seek(vertex_pos);

	if (vertex_count > 0) {
		vertArray = new fmtD8M_Float3[vertex_count];
		tvertArray = new fmtD8M_Float2[vertex_count];
		normArray = new fmtD8M_Float3[vertex_count];
		colrArray = new fmtD8M_Colour4[vertex_count];

		for (unsigned int x = 0; x < vertex_count; x++) {
			vertArray[x].read(f);
			normArray[x].read(f);
			colrArray[x].read(f);
			tvertArray[x].read(f);
			}
		}

	size_t face_buf_pos = 0;
	uint32_t face_buf_count = 0;
	size_t vertex_buf_pos = 0;
	uint32_t vertex_buf_count = 0;
	uint8_t face_type = 0;
	int numfaces = 0;
	if (mesh_count > 0) {
		meshs = new fmtD8M_Mesh[mesh_count];
		for (unsigned int i = 0; i < mesh_count; i++) {

			f.seek(material_pos + (i * mesh_def_stride));
			meshs[i].mesh_name = f.readstring();
			f.seek(material_pos + (i * mesh_def_stride) + 0x20);

			face_buf_pos = f.readUlong();
			face_buf_count = f.readUlong();
			vertex_buf_pos = f.readUlong();
			vertex_buf_count = f.readUlong();
			face_type = 0;//f.readUbyte();

			meshs[i].face_type = face_type;
			meshs[i].face_start = numfaces;
			meshs[i].face_count = face_buf_count;
			meshs[i].vertices.count = vertex_buf_count;
			meshs[i].vertices.stride = vertex_stride;


			meshs[i].vertices.definitions = new fmtD8M_Vertex_FVF[5];
			meshs[i].vertices.definitions[0] = {0, 2, 0, 0};	// Position
			meshs[i].vertices.definitions[1] = {12, 2, 3, 0};	// Normal
			meshs[i].vertices.definitions[2] = {24, 4, 10, 0};	// Colour
			meshs[i].vertices.definitions[3] = {28, 1, 5, 0};	// UV0
			meshs[i].vertices.definitions[4] = {255, 0, 17, 0};	// END



			f.seek(index_pos + (face_buf_pos * face_stride));
			if (face_buf_count > 0) {
				faces = new int16_t[face_buf_count];
				for (unsigned int x = 0; x < face_buf_count; x++) {
					faces[i] =  f.readUshort() - vertex_buf_pos;
					numfaces++;
					}
				}


			if (vertex_buf_count > 0) {
				meshs[i].vertices.position = new fmtD8M_Float3[vertex_buf_count];
				meshs[i].vertices.normal = new fmtD8M_Float3[vertex_buf_count];
				meshs[i].vertices.vcolour = new fmtD8M_Colour4[vertex_buf_count];
				meshs[i].vertices.texcoord0 = new fmtD8M_Float2[vertex_buf_count];
				for (unsigned int x = 0; x < vertex_buf_count; x++) {
					meshs[i].vertices.position[x] = vertArray[x + vertex_buf_pos];
					meshs[i].vertices.normal[x] = normArray[x + vertex_buf_pos];
					meshs[i].vertices.vcolour[x] = colrArray[x + vertex_buf_pos];
					meshs[i].vertices.texcoord0[x] = tvertArray[x + vertex_buf_pos];
					}
				}

			}

		}
//	if (vertArray != NULL} {delete[] vertArray;}
//	if (tvertArray != NULL} {delete[] tvertArray;}
//	if (normArray != NULL} {delete[] normArray;}
//	if (colrArray != NULL} {delete[] colrArray;}
	}

void read_d8m_model (std::wstring filename) {
	bytestream f;
	if (f.openFileW(filename)) {
		bool retail = true;

		if (f.size > 16) {
			f.seek(12);
			if (f.readUlong() == 0x3F800000) {
				retail = false;
				}
			} else {return;}
		f.seek(0);
		fmtD8M_File d8m;
		if (retail) {
			d8m.read(f);


			}
		else {
			d8m.readJuicedBeta(f);
			}

		if (d8m.mesh_count > 0) {
			for (unsigned int i = 0; i < d8m.mesh_count; i++) {
				std::cout << d8m.meshs[i].mesh_name << std::endl;
				}
			}

		}
	}
