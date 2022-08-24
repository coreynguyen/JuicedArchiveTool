#include "ddsheader.h"

const char* img_dds::DXGI_FORMAT_TABLE[120] = {
	"UNKNOWN",
	"R32G32B32A32_TYPELESS",
	"R32G32B32A32_FLOAT",
	"R32G32B32A32_UINT",
	"R32G32B32A32_SINT",
	"R32G32B32_TYPELESS",
	"R32G32B32_FLOAT",
	"R32G32B32_UINT",
	"R32G32B32_SINT",
	"R16G16B16A16_TYPELESS",
	"R16G16B16A16_FLOAT",
	"R16G16B16A16_UNORM",
	"R16G16B16A16_UINT",
	"R16G16B16A16_SNORM",
	"R16G16B16A16_SINT",
	"R32G32_TYPELESS",
	"R32G32_FLOAT",
	"R32G32_UINT",
	"R32G32_SINT",
	"R32G8X24_TYPELESS",
	"D32_FLOAT_S8X24_UINT",
	"R32_FLOAT_X8X24_TYPELESS",
	"X32_TYPELESS_G8X24_UINT",
	"R10G10B10A2_TYPELESS",
	"R10G10B10A2_UNORM",
	"R10G10B10A2_UINT",
	"R11G11B10_FLOAT",
	"R8G8B8A8_TYPELESS",
	"R8G8B8A8_UNORM",
	"R8G8B8A8_UNORM_SRGB",
	"R8G8B8A8_UINT",
	"R8G8B8A8_SNORM",
	"R8G8B8A8_SINT",
	"R16G16_TYPELESS",
	"R16G16_FLOAT",
	"R16G16_UNORM",
	"R16G16_UINT",
	"R16G16_SNORM",
	"R16G16_SINT",
	"R32_TYPELESS",
	"D32_FLOAT",
	"R32_FLOAT",
	"R32_UINT",
	"R32_SINT",
	"R24G8_TYPELESS",
	"D24_UNORM_S8_UINT",
	"R24_UNORM_X8_TYPELESS",
	"X24_TYPELESS_G8_UINT",
	"R8G8_TYPELESS",
	"R8G8_UNORM",
	"R8G8_UINT",
	"R8G8_SNORM",
	"R8G8_SINT",
	"R16_TYPELESS",
	"R16_FLOAT",
	"D16_UNORM",
	"R16_UNORM",
	"R16_UINT",
	"R16_SNORM",
	"R16_SINT",
	"R8_TYPELESS",
	"R8_UNORM",
	"R8_UINT",
	"R8_SNORM",
	"R8_SINT",
	"A8_UNORM",
	"R1_UNORM",
	"R9G9B9E5_SHAREDEXP",
	"R8G8_B8G8_UNORM",
	"G8R8_G8B8_UNORM",
	"BC1_TYPELESS",
	"BC1_UNORM",
	"BC1_UNORM_SRGB",
	"BC2_TYPELESS",
	"BC2_UNORM",
	"BC2_UNORM_SRGB",
	"BC3_TYPELESS",
	"BC3_UNORM",
	"BC3_UNORM_SRGB",
	"BC4_TYPELESS",
	"BC4_UNORM",
	"BC4_SNORM",
	"BC5_TYPELESS",
	"BC5_UNORM",
	"BC5_SNORM",
	"B5G6R5_UNORM",
	"B5G5R5A1_UNORM",
	"B8G8R8A8_UNORM",
	"B8G8R8X8_UNORM",
	"R10G10B10_XR_BIAS_A2_UNORM",
	"B8G8R8A8_TYPELESS",
	"B8G8R8A8_UNORM_SRGB",
	"B8G8R8X8_TYPELESS",
	"B8G8R8X8_UNORM_SRGB",
	"BC6H_TYPELESS",
	"BC6H_UF16",
	"BC6H_SF16",
	"BC7_TYPELESS",
	"BC7_UNORM",
	"BC7_UNORM_SRGB",
	"AYUV",
	"Y410",
	"Y416",
	"NV12",
	"P010",
	"P016",
	"420_OPAQUE",
	"YUY2",
	"Y210",
	"Y216",
	"NV11",
	"AI44",
	"IA44",
	"P8",
	"A8P8",
	"B4G4R4A4_UNORM",
	"P208",
	"V208",
	"V408",
	"FORCE_UINT"
	};

const int img_dds::DXGI_FORMAT_BPP_TABLE[120] = {
	0,	// UNKNOWN
	128,	// R32G32B32A32_TYPELESS
	128,	// R32G32B32A32_FLOAT
	128,	// R32G32B32A32_UINT
	128,	// R32G32B32A32_SINT
	96,	// R32G32B32_TYPELESS
	96,	// R32G32B32_FLOAT
	96,	// R32G32B32_UINT
	96,	// R32G32B32_SINT
	64,	// R16G16B16A16_TYPELESS
	64,	// R16G16B16A16_FLOAT
	64,	// R16G16B16A16_UNORM
	64,	// R16G16B16A16_UINT
	64,	// R16G16B16A16_SNORM
	64,	// R16G16B16A16_SINT
	64,	// R32G32_TYPELESS
	64,	// R32G32_FLOAT
	64,	// R32G32_UINT
	64,	// R32G32_SINT
	64,	// R32G8X24_TYPELESS
	64,	// D32_FLOAT_S8X24_UINT
	64,	// R32_FLOAT_X8X24_TYPELESS
	64,	// X32_TYPELESS_G8X24_UINT
	32,	// R10G10B10A2_TYPELESS
	32,	// R10G10B10A2_UNORM
	32,	// R10G10B10A2_UINT
	32,	// R11G11B10_FLOAT
	32,	// R8G8B8A8_TYPELESS
	32,	// R8G8B8A8_UNORM
	32,	// R8G8B8A8_UNORM_SRGB
	32,	// R8G8B8A8_UINT
	32,	// R8G8B8A8_SNORM
	32,	// R8G8B8A8_SINT
	32,	// R16G16_TYPELESS
	32,	// R16G16_FLOAT
	32,	// R16G16_UNORM
	32,	// R16G16_UINT
	32,	// R16G16_SNORM
	32,	// R16G16_SINT
	32,	// R32_TYPELESS
	32,	// D32_FLOAT
	32,	// R32_FLOAT
	32,	// R32_UINT
	32,	// R32_SINT
	32,	// R24G8_TYPELESS
	32,	// D24_UNORM_S8_UINT
	32,	// R24_UNORM_X8_TYPELESS
	32,	// X24_TYPELESS_G8_UINT
	16,	// R8G8_TYPELESS
	16,	// R8G8_UNORM
	16,	// R8G8_UINT
	16,	// R8G8_SNORM
	16,	// R8G8_SINT
	16,	// R16_TYPELESS
	16,	// R16_FLOAT
	16,	// D16_UNORM
	16,	// R16_UNORM
	16,	// R16_UINT
	16,	// R16_SNORM
	16,	// R16_SINT
	8,	// R8_TYPELESS
	8,	// R8_UNORM
	8,	// R8_UINT
	8,	// R8_SNORM
	8,	// R8_SINT
	8,	// A8_UNORM
	1,	// R1_UNORM
	32,	// R9G9B9E5_SHAREDEXP
	32,	// R8G8_B8G8_UNORM
	32,	// G8R8_G8B8_UNORM
	4,	// BC1_TYPELESS
	4,	// BC1_UNORM
	4,	// BC1_UNORM_SRGB
	8,	// BC2_TYPELESS
	8,	// BC2_UNORM
	8,	// BC2_UNORM_SRGB
	8,	// BC3_TYPELESS
	8,	// BC3_UNORM
	8,	// BC3_UNORM_SRGB
	4,	// BC4_TYPELESS
	4,	// BC4_UNORM
	4,	// BC4_SNORM
	8,	// BC5_TYPELESS
	8,	// BC5_UNORM
	8,	// BC5_SNORM
	16,	// B5G6R5_UNORM
	16,	// B5G5R5A1_UNORM
	32,	// B8G8R8A8_UNORM
	32,	// B8G8R8X8_UNORM
	32,	// R10G10B10_XR_BIAS_A2_UNORM
	32,	// B8G8R8A8_TYPELESS
	32,	// B8G8R8A8_UNORM_SRGB
	32,	// B8G8R8X8_TYPELESS
	32,	// B8G8R8X8_UNORM_SRGB
	8,	// BC6H_TYPELESS
	8,	// BC6H_UF16
	8,	// BC6H_SF16
	8,	// BC7_TYPELESS
	8,	// BC7_UNORM
	8,	// BC7_UNORM_SRGB
	8,	// AYUV
	8,	// Y410
	8,	// Y416
	8,	// NV12
	8,	// P010
	8,	// P016
	24,	// 420_OPAQUE
	2,	// YUY2
	12,	// Y210
	18,	// Y216
	2,	// NV11
	8,	// AI44
	8,	// IA44
	8,	// P8
	16,	// A8P8
	16,	// B4G4R4A4_UNORM
	8,	// P208
	8,	// V208
	8,	// V408
	8	// FORCE_UINT
	};

const bool img_dds::DXGI_COMPRESSED_TABLE[120] = {
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	true,
	true,
	true,
	true,
	true,
	true,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false
	};

unsigned long img_dds::max (unsigned long a, unsigned long b) {
	return (a<b)?b:a;
	}

img_dds::img_dds (unsigned long texWidth, unsigned long texHeight, unsigned long texMips, unsigned long texType) {
	/*
	huh this doesnt do much? i still need to call set header to calculate everything right
	*/
	isDX10 = false;
	//pos = 0;
	//size = 0;
	width = texWidth;
	height = texHeight;
	type = texType;
	dwMagic = 0x20534444;
	dwSize = 0x7C;
	dwFlags = 0x0002100F;
	dwHeight = width;
	dwWidth = width;
	dwLinearSize = (width * 8 + 7) / 8;
	dwDepth = 0;
	dwMipMapCount = 0;
	dwReserved1[0] = 0;
	dwReserved1[1] = 0;
	dwReserved1[2] = 0;
	dwReserved1[3] = 0;
	dwReserved1[4] = 0;
	dwReserved1[5] = 0;
	dwReserved1[6] = 0;
	dwReserved1[7] = 0;
	dwReserved1[8] = 0;
	dwReserved1[9] = 0;
	dwReserved1[10] = 0;
	fmSize = 0x20;
	fmFlags = 0x04;
	fmFourCC = 0x30315844;
	dxgiFormat = 0;
	resourceDimension = 0;
	miscFlag = 0;
	arraySize = 0;
	miscFlags2 = 0;
	dwRGBBitCount = 0x00401008;
	dwRBitMask = 0;
	dwGBitMask = 0;
	dwBBitMask = 0;
	dwABitMask = 0;
	dwCaps = 0x00401008;
	dwCaps2 = 3;
	dwCaps3 = 0;
	dwCaps4 = 1;
	dwReserved2 = 0;
	}

std::string img_dds::getFormatName (unsigned long id) {
	return ((std::string)DXGI_FORMAT_TABLE[id]);
	}

unsigned long img_dds::SET_DWFLAGS (bool CAPS, bool HEIGHT, bool WIDTH, bool PITCH, bool PIXELFORMAT, bool MIPMAPCOUNT, bool LINEARSIZE, bool DEPTH) {
	return (DDSD_CAPS * CAPS | DDSD_HEIGHT * HEIGHT | DDSD_WIDTH * WIDTH | DDSD_PITCH * PITCH | DDSD_PIXELFORMAT * PIXELFORMAT | DDSD_MIPMAPCOUNT * MIPMAPCOUNT | DDSD_LINEARSIZE * LINEARSIZE | DDSD_DEPTH * DEPTH);
	}

DXGI_FORMAT img_dds::getFormatFromName (std::string name) {
	DXGI_FORMAT result = DXGI_FORMAT_UNKNOWN;
	if (name.size() > 0) {
		for (int i = 0; i < 120; i++) {
			if (name == (std::string)DXGI_FORMAT_TABLE[i]) {
				result = DXGI_FORMAT(i);
				break;
				}
			}
		}
	return result;
	}

std::string img_dds::formatID_to_formatName (unsigned long formatid) {
	return DXGI_FORMAT_TABLE[formatid];
	}

bool img_dds::isFormatDX10 () {
	return isDX10;
	}

bool img_dds::set_isDX10_flag (unsigned long id) {
	bool result = false;
	switch (id) {
		case DXGI_FORMAT_R32G32B32A32_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R32G32B32A32_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R32G32B32_FLOAT :
			result = true;
			break;
		case DXGI_FORMAT_R32G32B32_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R32G32B32_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R16G16B16A16_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R16G16B16A16_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R32G32_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R32G32_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R10G10B10A2_UNORM :
			result = true;
			break;
		case DXGI_FORMAT_R10G10B10A2_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R11G11B10_FLOAT :
			result = true;
			break;
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB :
			result = true;
			break;
		case DXGI_FORMAT_R8G8B8A8_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R8G8B8A8_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R16G16_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R16G16_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R32_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R32_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R8G8_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R8G8_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R16_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R16_SNORM :
			result = true;
			break;
		case DXGI_FORMAT_R16_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R8_UINT :
			result = true;
			break;
		case DXGI_FORMAT_R8_SNORM :
			result = true;
			break;
		case DXGI_FORMAT_R8_SINT :
			result = true;
			break;
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP :
			result = true;
			break;
		case DXGI_FORMAT_BC1_UNORM_SRGB :
			result = true;
			break;
		case DXGI_FORMAT_BC2_UNORM_SRGB :
			result = true;
			break;
		case DXGI_FORMAT_BC3_UNORM_SRGB :
			result = true;
			break;
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM :
			result = true;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB :
			result = true;
			break;
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB :
			result = true;
			break;
		case DXGI_FORMAT_BC6H_UF16 :
			result = true;
			break;
		case DXGI_FORMAT_BC6H_SF16 :
			result = true;
			break;
		case DXGI_FORMAT_BC7_UNORM :
			result = true;
			break;
		case DXGI_FORMAT_BC7_UNORM_SRGB :
			result = true;
			break;
		case DXGI_FORMAT_AYUV :
			result = true;
			break;
		case DXGI_FORMAT_Y410 :
			result = true;
			break;
		case DXGI_FORMAT_Y416 :
			result = true;
			break;
		case DXGI_FORMAT_Y210 :
			result = true;
			break;
		case DXGI_FORMAT_Y216 :
			result = true;
			break;
		default :
			result = false;
		}
	return result;
	}

void img_dds::storeLong (char* &buf, unsigned long idx, unsigned long value) {
	buf[idx+0] = (char)(value & 0x000000ff);
	buf[idx+1] = (char)((value & 0x0000ff00) >> 8);
	buf[idx+2] = (char)((value & 0x00ff0000) >> 16);
	buf[idx+3] = (char)((value & 0xff000000) >> 24);
	//idx+=4;
	}

void img_dds::setHeader (unsigned long texWidth, unsigned long texHeight, unsigned long texMips, DXGI_FORMAT texType) {
	isDX10 = set_isDX10_flag(texType);

	//cout << "texType " << texType << " " << isDX10 << endl;

	dwWidth = texWidth;
	dwHeight = texHeight;
	dwMipMapCount = texMips;


	//std::cout << ((unsigned int)DXGI_FORMAT_BPP_TABLE[texType]) << std::endl;
	//std::cout << (((float)DXGI_FORMAT_BPP_TABLE[texType] / 8.0f)) << std::endl;
	//std::cout << ((texWidth * texHeight)) << std::endl;
	//std::cout << ((texWidth * texHeight) * ((float)DXGI_FORMAT_BPP_TABLE[texType] / 8.0f)) << std::endl;


	dwPitch = (int)(((float)(dwWidth * dwHeight)) * ((float)DXGI_FORMAT_BPP_TABLE[texType] / 8.0f));
	//std::cout << dwPitch << std::endl;

	fmFourCC = 0;
	dwRGBBitCount = 0x00401008;
	dwRBitMask = 0;
	dwGBitMask = 0;
	dwBBitMask = 0;
	dwABitMask = 0;
	dwCaps = 0x00401008;
	dwCaps2 = 3;
	dwCaps3 = 0;
	dwCaps4 = 1;
	dwReserved2 = 0;

	unsigned int block_size = 8;	// The block-size is 8 bytes for DXT1, BC1, and BC4 formats, and 16 bytes for other block-compressed formats.
	unsigned long imgBpp = 8;	// huh why did i not put this in the class

	switch (texType) {
		case DXGI_FORMAT_R32G32B32A32_FLOAT:
			fmFourCC = 0x00000074;
			dwRGBBitCount = 0x00;
			dwLinearSize = ( dwWidth * 128 + 7 ) / imgBpp;
			break;
		case DXGI_FORMAT_R32G32B32A32_UINT:
			dwLinearSize = ( dwWidth * 128 + 7 ) / imgBpp;
			dwCaps = 3;
			break;
		case DXGI_FORMAT_R32G32B32A32_SINT:
			dwLinearSize = ( dwWidth * 96 + 7 ) / imgBpp;
			dwCaps = 4;
			break;
		case DXGI_FORMAT_R32G32B32_FLOAT:
			dwLinearSize = ( dwWidth * 96 + 7 ) / imgBpp;
			dwCaps = 6;
			break;
		case DXGI_FORMAT_R32G32B32_UINT:
			dwLinearSize = ( dwWidth * 96 + 7 ) / imgBpp;
			dwCaps = 7;
			break;
		case DXGI_FORMAT_R32G32B32_SINT:
			dwLinearSize = ( dwWidth * 96 + 7 ) / imgBpp;
			dwCaps = 8;
			break;
		case DXGI_FORMAT_R16G16B16A16_FLOAT:
			fmFourCC = 0x00000071;
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_R16G16B16A16_UNORM:
			fmFourCC = 0x00000024;
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_R16G16B16A16_UINT:
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwCaps = 12;
			break;
		case DXGI_FORMAT_R16G16B16A16_SNORM:
			fmFourCC = 0x0000006E;
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_R16G16B16A16_SINT:
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwCaps = 14;
			break;
		case DXGI_FORMAT_R32G32_FLOAT:
			fmFourCC = 0x00000073;
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_R32G32_UINT:
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwCaps = 17;
			break;
		case DXGI_FORMAT_R32G32_SINT:
			dwLinearSize = ( dwWidth * 64 + 7 ) / imgBpp;
			dwCaps = 18;
			break;
		case DXGI_FORMAT_R10G10B10A2_UNORM:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 24;
			break;
		case DXGI_FORMAT_R10G10B10A2_UINT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 25;
			break;
		case DXGI_FORMAT_R11G11B10_FLOAT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 26;
			break;
		case DXGI_FORMAT_R8G8B8A8_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwRGBBitCount = 0x20;
			fmFlags = 0x00000041;
			dwRBitMask = 0x00FF0000;
			dwGBitMask = 0x0000FF00;
			dwBBitMask = 0x000000FF;
			dwABitMask = 0xFF000000;
			dwCaps = 0x00001000;
			dwCaps2 = 0x00000000;
			dwCaps3 = 0x00000000;
			dwCaps4 = 0x00000000;
			dwReserved2 = 0x00000000;
			break;
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 29;
			break;
		case DXGI_FORMAT_R8G8B8A8_UINT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 30;
			break;
		case DXGI_FORMAT_R8G8B8A8_SNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			fmFlags = 0x00080000;
			dwRGBBitCount = 0x20;
			break;
		case DXGI_FORMAT_R8G8B8A8_SINT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 32;
			break;
		case DXGI_FORMAT_R16G16_FLOAT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_R16G16_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			fmFlags = 0x00000041;
			dwRGBBitCount = 0x20;
			break;
		case DXGI_FORMAT_R16G16_UINT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 36;
			break;
		case DXGI_FORMAT_R16G16_SNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			fmFlags = 0x00080000;
			dwRGBBitCount = 0x20;
			break;
		case DXGI_FORMAT_R16G16_SINT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 38;
			break;
		case DXGI_FORMAT_R32_FLOAT:
			fmFourCC = 0x00000072;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_R32_UINT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 42;
			break;
		case DXGI_FORMAT_R32_SINT:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 43;
			break;
		case DXGI_FORMAT_R8G8_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 16 + 7 ) / imgBpp;
			fmFlags = 0x00020001;
			dwRGBBitCount = 0x10;
			break;
		case DXGI_FORMAT_R8G8_UINT:
			dwLinearSize = ( dwWidth * 16 + 7 ) / imgBpp;
			dwCaps = 50;
			break;
		case DXGI_FORMAT_R8G8_SNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 16 + 7 ) / imgBpp;
			dwRGBBitCount = 0x10;
			fmFlags = 0x00080000;
			break;
		case DXGI_FORMAT_R8G8_SINT:
			dwLinearSize = ( dwWidth * 16 + 7 ) / imgBpp;
			dwCaps = 52;
			break;
		case DXGI_FORMAT_R16_FLOAT:
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_R16_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			fmFlags = 0x00020000;
			dwRGBBitCount = 0x10;
			break;
		case DXGI_FORMAT_R16_UINT:
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwCaps = 57;
			break;
		case DXGI_FORMAT_R16_SNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwCaps = 58;
			break;
		case DXGI_FORMAT_R16_SINT:
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwCaps = 59;
			break;
		case DXGI_FORMAT_R8_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			fmFlags = 0x00020000;
			dwRGBBitCount = 0x08;
			break;
		case DXGI_FORMAT_R8_UINT:
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwCaps = 62;
			break;
		case DXGI_FORMAT_R8_SNORM:
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwCaps = 63;
			break;
		case DXGI_FORMAT_R8_SINT:
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwCaps = 64;
			break;
		case DXGI_FORMAT_A8_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwRGBBitCount = 0x08;
			break;
		case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwCaps = 67;
			break;
		case DXGI_FORMAT_R8G8_B8G8_UNORM:
			fmFourCC = 0x47424752;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_G8R8_G8B8_UNORM:
			fmFourCC = 0x42475247;
			dwLinearSize = ( dwWidth * 32 + 7 ) / imgBpp;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_BC1_UNORM:
			fmFourCC = 0x31545844;	//DXT1
			imgBpp = 4;
			block_size = 8;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * block_size;
			dwFlags = 0x000A1007;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_BC1_UNORM_SRGB:
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 4;
			dwCaps = 72;
			dwFlags = 0x000A1007;
			break;
		case DXGI_FORMAT_BC2_UNORM:
			fmFourCC = 0x33545844;	//DXT3
			imgBpp = 4;
			dwLinearSize = (dwWidth * dwHeight) / 2;
			dwFlags = 0x000A1007;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_BC2_UNORM_SRGB:
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwCaps = 75;
			dwFlags = 0x000A1007;
			break;
		case DXGI_FORMAT_BC3_UNORM:
			fmFourCC = 0x35545844;	//DXT5
			imgBpp = 8;
			dwLinearSize = dwWidth * dwHeight;
			dwFlags = 0x000A1007;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_BC3_UNORM_SRGB:
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwCaps = 78;
			dwFlags = 0x000A1007;
			break;
		case DXGI_FORMAT_BC4_UNORM:
			fmFourCC = 0x55344342;	//BC4U
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 4;
			dwFlags = 0x000A1007;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_BC4_SNORM:
			fmFourCC = 0x53344342;	// BC4S
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 4;
			dwFlags = 0x000A1007;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_BC5_UNORM:
			fmFourCC = 0x55354342;	// BC5U
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwFlags = 0x000A1007;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_BC5_SNORM:
			fmFourCC = 0x53354342;	// BC5S
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwFlags = 0x000A1007;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_B5G6R5_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 016 + 7 ) / imgBpp;
			fmFlags = 0x00000040;
			dwRGBBitCount = 0x10;
			break;
		case DXGI_FORMAT_B5G5R5A1_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 016 + 7 ) / imgBpp;
			fmFlags = 0x00000041;
			dwRGBBitCount = 0x10;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 032 + 7 ) / imgBpp;
			fmFlags = 0x00000041;
			dwRGBBitCount = 0x20;
			break;
		case DXGI_FORMAT_B8G8R8X8_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 032 + 7 ) / imgBpp;
			fmFlags = 0x00000040;
			dwRGBBitCount = 0x20;
			break;
		case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
			dwLinearSize = ( dwWidth * 032 + 7 ) / imgBpp;
			dwCaps = 89;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
			dwLinearSize = ( dwWidth * 032 + 7 ) / imgBpp;
			dwCaps = 91;
			break;
		case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
			dwLinearSize = ( dwWidth * 032 + 7 ) / imgBpp;
			dwCaps = 93;
			break;
		case DXGI_FORMAT_BC6H_UF16:
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwCaps = 95;
			dwFlags = 0x000A1007;
			break;
		case DXGI_FORMAT_BC6H_SF16:
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwCaps = 96;
			dwFlags = 0x000A1007;
			break;
		case DXGI_FORMAT_BC7_UNORM:
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwCaps = 98;
			dwFlags = 0x000A1007;
			break;
		case DXGI_FORMAT_BC7_UNORM_SRGB:
			imgBpp = 4;
			dwLinearSize = max(1, ((dwWidth + 3) / imgBpp) ) * 8;
			dwCaps = 99;
			dwFlags = 0x000A1007;
			break;
		case DXGI_FORMAT_AYUV:
			imgBpp = 1;
			dwLinearSize = ((dwWidth + 1) >> imgBpp) * 4;
			dwCaps = 100;
			break;
		case DXGI_FORMAT_Y410:
			imgBpp = 1;
			dwLinearSize = ((dwWidth + 1) >> imgBpp) * 4;
			dwCaps = 101;
			break;
		case DXGI_FORMAT_Y416:
			dwLinearSize = ( dwWidth * 8 + 7 ) / imgBpp;
			dwCaps = 102;
			break;
		case DXGI_FORMAT_YUY2:
			imgBpp = 1;
			fmFourCC = 0x32595559;
			dwLinearSize = ((dwWidth + 1) >> imgBpp) * 4;
			dwRGBBitCount = 0x00;
			break;
		case DXGI_FORMAT_Y210:
			imgBpp = 1;
			dwLinearSize = ((dwWidth + 1) >> imgBpp) * 4;
			dwCaps = 108;
			break;
		case DXGI_FORMAT_Y216:
			imgBpp = 1;
			dwLinearSize = ((dwWidth + 1) >> imgBpp) * 4;
			dwCaps = 109;
			break;
		case DXGI_FORMAT_B4G4R4A4_UNORM:
			fmFourCC = 0x00000000;
			dwLinearSize = ( dwWidth * 016 + 7 ) / imgBpp;
			fmFlags = 0x00000041;
			dwRGBBitCount = 0x10;
			break;
		default: break;
		}
	// i'll just set it here
	dwFlags = 0x000A1007; // if no mips
	if (dwMipMapCount > 0) {
		dwFlags = 0x00081007; // if mips
		}

	//dwPitch = dwLinearSize;
//	dwPitch = (dwWidth * dwHeight * imgBpp) / 8;


//	dwPitch = (dwWidth + 3) / 4;
//	if (dwPitch < 1) {dwPitch = 1;}
//	dwPitch *= block_size;
//
//
//	dwPitch = ( dwWidth * imgBpp + 7 ) / 8l;

	}

void img_dds::writeHeader (char* &header, size_t pos) {
	//if (isDX10) {size = 148;} else {size = 128;}
	//cout << "DX10 " << isDX10 << endl;
	// = new char[size];
	//pos = 0;
	storeLong(header, pos, dwMagic);pos+=4;
	storeLong(header, pos, dwSize);pos+=4;
	storeLong(header, pos, dwFlags);pos+=4;
	storeLong(header, pos, dwWidth);pos+=4;
	storeLong(header, pos, dwHeight);pos+=4;
	storeLong(header, pos, dwPitch);pos+=4;
	storeLong(header, pos, dwDepth);pos+=4;
	storeLong(header, pos, dwMipMapCount);pos+=4;
	storeLong(header, pos, dwReserved1[0]);pos+=4;
	storeLong(header, pos, dwReserved1[1]);pos+=4;
	storeLong(header, pos, dwReserved1[2]);pos+=4;
	storeLong(header, pos, dwReserved1[3]);pos+=4;
	storeLong(header, pos, dwReserved1[4]);pos+=4;
	storeLong(header, pos, dwReserved1[5]);pos+=4;
	storeLong(header, pos, dwReserved1[6]);pos+=4;
	storeLong(header, pos, dwReserved1[7]);pos+=4;
	storeLong(header, pos, dwReserved1[8]);pos+=4;
	storeLong(header, pos, dwReserved1[9]);pos+=4;
	storeLong(header, pos, dwReserved1[10]);pos+=4;
	storeLong(header, pos, fmSize);pos+=4;
	storeLong(header, pos, fmFlags);pos+=4;
	storeLong(header, pos, fmFourCC);pos+=4;
	if (isDX10) {
		storeLong(header, pos, dxgiFormat);pos+=4;
		storeLong(header, pos, resourceDimension);pos+=4;
		storeLong(header, pos, miscFlag);pos+=4;
		storeLong(header, pos, arraySize);pos+=4;
		storeLong(header, pos, miscFlags2);pos+=4;
		}
	storeLong(header, pos, dwRGBBitCount);pos+=4;
	storeLong(header, pos, dwRBitMask);pos+=4;
	storeLong(header, pos, dwGBitMask);pos+=4;
	storeLong(header, pos, dwBBitMask);pos+=4;
	storeLong(header, pos, dwABitMask);pos+=4;
	storeLong(header, pos, dwCaps);pos+=4;
	storeLong(header, pos, dwCaps2);pos+=4;
	storeLong(header, pos, dwCaps3);pos+=4;
	storeLong(header, pos, dwCaps4);pos+=4;
	storeLong(header, pos, dwReserved2);pos+=4;
	//OutFile.write(header, size);
	//delete[] header;
	}



