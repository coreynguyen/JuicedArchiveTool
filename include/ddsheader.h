/*	======================================================================

	Title:		DDS Helper Library
	Author:		mariokart64n
	Version:	???
	Date:		February 01 2019

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Description:
		Read and Write a DDS Header

	""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

	Change Log:

	[2019-01-28]
		wrote it!

	======================================================================	*/
#ifndef DDSHEADER_H
#define DDSHEADER_H


#include <iostream>
#include <fstream>
#include <string>
#include <climits>

// usage: swap_endian<uint32_t>(42).
// https://stackoverflow.com/a/4956493
template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}


template <class T> const T& max (const T& a, const T& b);

// Map Direct3D 9 Formats to Direct3D 10
// https://docs.microsoft.com/en-us/windows/win32/direct3d10/d3d10-graphics-programming-guide-resources-legacy-formats
/*
D3DFMT_UNKNOWN                          DXGI_FORMAT_UNKNOWN
D3DFMT_R8G8B8                           Not_available
D3DFMT_A8R8G8B8                         DXGI_FORMAT_B8G8R8A8_UNORM
D3DFMT_X8R8G8B8                         DXGI_FORMAT_B8G8R8X8_UNORM
D3DFMT_R5G6B5                           DXGI_FORMAT_B5G6R5_UNORM
D3DFMT_X1R5G5B5                         Not_available
D3DFMT_A1R5G5B5                         DXGI_FORMAT_B5G5R5A1_UNORM
D3DFMT_A4R4G4B4                         DXGI_FORMAT_B4G4R4A4_UNORM
D3DFMT_R3G3B2                           Not_available
D3DFMT_A8                               DXGI_FORMAT_A8_UNORM
D3DFMT_A8R3G3B2                         Not_available
D3DFMT_X4R4G4B4                         Not_available
D3DFMT_A2B10G10R10                      DXGI_FORMAT_R10G10B10A2
D3DFMT_A8B8G8R8                         DXGI_FORMAT_R8G8B8A8_UNORM
D3DFMT_X8B8G8R8                         Not_available
D3DFMT_G16R16                           DXGI_FORMAT_R16G16_UNORM
D3DFMT_A2R10G10B10                      Not_available
D3DFMT_A16B16G16R16                     DXGI_FORMAT_R16G16B16A16_UNORM
D3DFMT_A8P8                             Not_available
D3DFMT_P8                               Not_available
D3DFMT_L8                               DXGI_FORMAT_R8_UNORM
D3DFMT_A8L8                             Not_available
D3DFMT_A4L4                             Not_available
D3DFMT_V8U8                             DXGI_FORMAT_R8G8_SNORM
D3DFMT_L6V5U5                           Not_available
D3DFMT_X8L8V8U8                         Not_available
D3DFMT_Q8W8V8U8                         DXGI_FORMAT_R8G8B8A8_SNORM
D3DFMT_V16U16                           DXGI_FORMAT_R16G16_SNORM
D3DFMT_W11V11U10                        Not_available
D3DFMT_A2W10V10U10                      Not_available
D3DFMT_UYVY                             Not_available
D3DFMT_R8G8_B8G8                        DXGI_FORMAT_G8R8_G8B8_UNORM
D3DFMT_YUY2                             Not_available
D3DFMT_G8R8_G8B8                        DXGI_FORMAT_R8G8_B8G8_UNORM
D3DFMT_DXT1                             DXGI_FORMAT_BC1_UNORM
D3DFMT_DXT2                             DXGI_FORMAT_BC2_UNORM
D3DFMT_DXT3                             DXGI_FORMAT_BC2_UNORM
D3DFMT_DXT4                             DXGI_FORMAT_BC3_UNORM
D3DFMT_DXT5                             DXGI_FORMAT_BC3_UNORM
D3DFMT_D16                              and
D3DFMT_D32                              Not_available
D3DFMT_D15S1                            Not_available
D3DFMT_D24S8                            Not_available
D3DFMT_D24X8                            Not_available
D3DFMT_D24X4S4                          Not_available
D3DFMT_D16                              DXGI_FORMAT_D16_UNORM
D3DFMT_D32F_LOCKABLE                    DXGI_FORMAT_D32_FLOAT
D3DFMT_D24FS8                           Not_available
D3DFMT_S1D15                            Not_available
D3DFMT_S8D24                            DXGI_FORMAT_D24_UNORM_S8_UINT
D3DFMT_X8D24                            Not_available
D3DFMT_X4S4D24                          Not_available
D3DFMT_L16                              DXGI_FORMAT_R16_UNORM
D3DFMT_INDEX16                          DXGI_FORMAT_R16_UINT
D3DFMT_INDEX32                          DXGI_FORMAT_R32_UINT
D3DFMT_Q16W16V16U16                     DXGI_FORMAT_R16G16B16A16_SNORM
D3DFMT_MULTI2_ARGB8                     Not_available
D3DFMT_R16F                             DXGI_FORMAT_R16_FLOAT
D3DFMT_G16R16F                          DXGI_FORMAT_R16G16_FLOAT
D3DFMT_A16B16G16R16F                    DXGI_FORMAT_R16G16B16A16_FLOAT
D3DFMT_R32F                             DXGI_FORMAT_R32_FLOAT
D3DFMT_G32R32F                          DXGI_FORMAT_R32G32_FLOAT
D3DFMT_A32B32G32R32F                    DXGI_FORMAT_R32G32B32A32_FLOAT
D3DFMT_CxV8U8                           Not_available
D3DDECLTYPE_FLOAT1                      DXGI_FORMAT_R32_FLOAT
D3DDECLTYPE_FLOAT2                      DXGI_FORMAT_R32G32_FLOAT
D3DDECLTYPE_FLOAT3                      DXGI_FORMAT_R32G32B32_FLOAT
D3DDECLTYPE_FLOAT4                      DXGI_FORMAT_R32G32B32A32_FLOAT
D3DDECLTYPED3DCOLOR                     Not_available
D3DDECLTYPE_UBYTE4                      DXGI_FORMAT_R8G8B8A8_UINT
D3DDECLTYPE_SHORT2                      DXGI_FORMAT_R16G16_SINT
D3DDECLTYPE_SHORT4                      DXGI_FORMAT_R16G16B16A16_SINT
D3DDECLTYPE_UBYTE4N                     DXGI_FORMAT_R8G8B8A8_UNORM
D3DDECLTYPE_SHORT2N                     DXGI_FORMAT_R16G16_SNORM
D3DDECLTYPE_SHORT4N                     DXGI_FORMAT_R16G16B16A16_SNORM
D3DDECLTYPE_USHORT2N                    DXGI_FORMAT_R16G16_UNORM
D3DDECLTYPE_USHORT4N                    DXGI_FORMAT_R16G16B16A16_UNORM
D3DDECLTYPE_UDEC3                       Not_available
D3DDECLTYPE_DEC3N                       Not_available
D3DDECLTYPE_FLOAT16_2                   DXGI_FORMAT_R16G16_FLOAT
D3DDECLTYPE_FLOAT16_4                   DXGI_FORMAT_R16G16B16A16_FLOAT
*/


enum DDS_DWCAPS {
	DDSCAPS_COMPLEX = 0x08,
	DDSCAPS_MIPMAP = 0x400000,
	DDSCAPS_TEXTURE = 0x1000
	};

enum D3D10_RESOURCE_MISC_FLAG {
	D3D10_RESOURCE_MISC_GENERATE_MIPS,
	D3D10_RESOURCE_MISC_SHARED,
	D3D10_RESOURCE_MISC_TEXTURECUBE,
	D3D10_RESOURCE_MISC_SHARED_KEYEDMUTEX,
	D3D10_RESOURCE_MISC_GDI_COMPATIBLE
	};

enum D3D10_RESOURCE_DIMENSION {
	D3D10_RESOURCE_DIMENSION_UNKNOWN,
	D3D10_RESOURCE_DIMENSION_BUFFER,
	D3D10_RESOURCE_DIMENSION_TEXTURE1D,
	D3D10_RESOURCE_DIMENSION_TEXTURE2D,
	D3D10_RESOURCE_DIMENSION_TEXTURE3D
	};

enum DDS_HEADER_DWFLAGS {
	DDSD_CAPS = 0x01,
	DDSD_HEIGHT = 0x02,
	DDSD_WIDTH = 0x04,
	DDSD_PITCH = 0x08,
	DDSD_PIXELFORMAT = 0x1000,
	DDSD_MIPMAPCOUNT = 0x20000,
	DDSD_LINEARSIZE = 0x80000,
	DDSD_DEPTH = 0x800000
	};

enum DDS_PIXELFORMAT_DWFLAGS {
	DDPF_ALPHAPIXELS = 0x01,
	DDPF_ALPHA = 0x02,
	DDPF_FOURCC = 0x04,
	DDPF_RGB = 0x40,
	DDPF_YUV = 0x200,
	DDPF_LUMINANCE = 0x20000
	};

enum DXGI_FORMAT {
	DXGI_FORMAT_UNKNOWN,
	DXGI_FORMAT_R32G32B32A32_TYPELESS,
	DXGI_FORMAT_R32G32B32A32_FLOAT,
	DXGI_FORMAT_R32G32B32A32_UINT,
	DXGI_FORMAT_R32G32B32A32_SINT,
	DXGI_FORMAT_R32G32B32_TYPELESS,
	DXGI_FORMAT_R32G32B32_FLOAT,
	DXGI_FORMAT_R32G32B32_UINT,
	DXGI_FORMAT_R32G32B32_SINT,
	DXGI_FORMAT_R16G16B16A16_TYPELESS,
	DXGI_FORMAT_R16G16B16A16_FLOAT,
	DXGI_FORMAT_R16G16B16A16_UNORM,
	DXGI_FORMAT_R16G16B16A16_UINT,
	DXGI_FORMAT_R16G16B16A16_SNORM,
	DXGI_FORMAT_R16G16B16A16_SINT,
	DXGI_FORMAT_R32G32_TYPELESS,
	DXGI_FORMAT_R32G32_FLOAT,
	DXGI_FORMAT_R32G32_UINT,
	DXGI_FORMAT_R32G32_SINT,
	DXGI_FORMAT_R32G8X24_TYPELESS,
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
	DXGI_FORMAT_R10G10B10A2_TYPELESS,
	DXGI_FORMAT_R10G10B10A2_UNORM,
	DXGI_FORMAT_R10G10B10A2_UINT,
	DXGI_FORMAT_R11G11B10_FLOAT,
	DXGI_FORMAT_R8G8B8A8_TYPELESS,
	DXGI_FORMAT_R8G8B8A8_UNORM,
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
	DXGI_FORMAT_R8G8B8A8_UINT,
	DXGI_FORMAT_R8G8B8A8_SNORM,
	DXGI_FORMAT_R8G8B8A8_SINT,
	DXGI_FORMAT_R16G16_TYPELESS,
	DXGI_FORMAT_R16G16_FLOAT,
	DXGI_FORMAT_R16G16_UNORM,
	DXGI_FORMAT_R16G16_UINT,
	DXGI_FORMAT_R16G16_SNORM,
	DXGI_FORMAT_R16G16_SINT,
	DXGI_FORMAT_R32_TYPELESS,
	DXGI_FORMAT_D32_FLOAT,
	DXGI_FORMAT_R32_FLOAT,
	DXGI_FORMAT_R32_UINT,
	DXGI_FORMAT_R32_SINT,
	DXGI_FORMAT_R24G8_TYPELESS,
	DXGI_FORMAT_D24_UNORM_S8_UINT,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT,
	DXGI_FORMAT_R8G8_TYPELESS,
	DXGI_FORMAT_R8G8_UNORM,
	DXGI_FORMAT_R8G8_UINT,
	DXGI_FORMAT_R8G8_SNORM,
	DXGI_FORMAT_R8G8_SINT,
	DXGI_FORMAT_R16_TYPELESS,
	DXGI_FORMAT_R16_FLOAT,
	DXGI_FORMAT_D16_UNORM,
	DXGI_FORMAT_R16_UNORM,
	DXGI_FORMAT_R16_UINT,
	DXGI_FORMAT_R16_SNORM,
	DXGI_FORMAT_R16_SINT,
	DXGI_FORMAT_R8_TYPELESS,
	DXGI_FORMAT_R8_UNORM,
	DXGI_FORMAT_R8_UINT,
	DXGI_FORMAT_R8_SNORM,
	DXGI_FORMAT_R8_SINT,
	DXGI_FORMAT_A8_UNORM,
	DXGI_FORMAT_R1_UNORM,
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
	DXGI_FORMAT_R8G8_B8G8_UNORM,
	DXGI_FORMAT_G8R8_G8B8_UNORM,
	DXGI_FORMAT_BC1_TYPELESS,
	DXGI_FORMAT_BC1_UNORM,
	DXGI_FORMAT_BC1_UNORM_SRGB,
	DXGI_FORMAT_BC2_TYPELESS,
	DXGI_FORMAT_BC2_UNORM,
	DXGI_FORMAT_BC2_UNORM_SRGB,
	DXGI_FORMAT_BC3_TYPELESS,
	DXGI_FORMAT_BC3_UNORM,
	DXGI_FORMAT_BC3_UNORM_SRGB,
	DXGI_FORMAT_BC4_TYPELESS,
	DXGI_FORMAT_BC4_UNORM,
	DXGI_FORMAT_BC4_SNORM,
	DXGI_FORMAT_BC5_TYPELESS,
	DXGI_FORMAT_BC5_UNORM,
	DXGI_FORMAT_BC5_SNORM,
	DXGI_FORMAT_B5G6R5_UNORM,
	DXGI_FORMAT_B5G5R5A1_UNORM,
	DXGI_FORMAT_B8G8R8A8_UNORM,
	DXGI_FORMAT_B8G8R8X8_UNORM,
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
	DXGI_FORMAT_B8G8R8A8_TYPELESS,
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
	DXGI_FORMAT_B8G8R8X8_TYPELESS,
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
	DXGI_FORMAT_BC6H_TYPELESS,
	DXGI_FORMAT_BC6H_UF16,
	DXGI_FORMAT_BC6H_SF16,
	DXGI_FORMAT_BC7_TYPELESS,
	DXGI_FORMAT_BC7_UNORM,
	DXGI_FORMAT_BC7_UNORM_SRGB,
	DXGI_FORMAT_AYUV,
	DXGI_FORMAT_Y410,
	DXGI_FORMAT_Y416,
	DXGI_FORMAT_NV12,
	DXGI_FORMAT_P010,
	DXGI_FORMAT_P016,
	DXGI_FORMAT_420_OPAQUE,
	DXGI_FORMAT_YUY2,
	DXGI_FORMAT_Y210,
	DXGI_FORMAT_Y216,
	DXGI_FORMAT_NV11,
	DXGI_FORMAT_AI44,
	DXGI_FORMAT_IA44,
	DXGI_FORMAT_P8,
	DXGI_FORMAT_A8P8,
	DXGI_FORMAT_B4G4R4A4_UNORM,
	DXGI_FORMAT_P208,
	DXGI_FORMAT_V208,
	DXGI_FORMAT_V408,
	DXGI_FORMAT_FORCE_UINT = 0xFFFFFFFF
	};

class img_dds {
private:
	const static char* DXGI_FORMAT_TABLE[];
	const static int DXGI_FORMAT_BPP_TABLE[];
	const static bool DXGI_COMPRESSED_TABLE[];
	unsigned long max (unsigned long a, unsigned long b);
	bool isDX10;
	unsigned long dwMagic;
	unsigned long dwSize;
	unsigned long dwFlags;
	unsigned long dwHeight;
	unsigned long dwWidth;
	unsigned long dwPitch;
	unsigned long dwLinearSize;
	unsigned long dwDepth;
	unsigned long dwMipMapCount;
	unsigned long dwReserved1[11];
	unsigned long fmSize;
	unsigned long fmFlags;
	unsigned long fmFourCC;
	unsigned long dxgiFormat;
	unsigned long resourceDimension;
	unsigned long miscFlag;
	unsigned long arraySize;
	unsigned long miscFlags2;
	unsigned long dwRGBBitCount;
	unsigned long dwRBitMask;
	unsigned long dwGBitMask;
	unsigned long dwBBitMask;
	unsigned long dwABitMask;
	unsigned long dwCaps;
	unsigned long dwCaps2;
	unsigned long dwCaps3;
	unsigned long dwCaps4;
	unsigned long dwReserved2;

public:
	unsigned long width;
	unsigned long height;
	unsigned long mipCount;
	unsigned long type;
	img_dds (unsigned long texWidth = 0, unsigned long texHeight = 0, unsigned long texMips = 1, unsigned long texType = 0);
	std::string getFormatName (unsigned long id);
	unsigned long SET_DWFLAGS (bool CAPS = false, bool HEIGHT = false, bool WIDTH = false, bool PITCH = false, bool PIXELFORMAT = false, bool MIPMAPCOUNT = false, bool LINEARSIZE = false, bool DEPTH = false);
	DXGI_FORMAT getFormatFromName (std::string name);
	std::string formatID_to_formatName (unsigned long formatid);
	bool isFormatDX10 ();
	bool set_isDX10_flag (unsigned long id);
	void storeLong (char* &buf, unsigned long idx, unsigned long value);
	void setHeader (unsigned long texWidth, unsigned long texHeight, unsigned long texMips, DXGI_FORMAT texType);
	void writeHeader (char* &header, size_t pos = 0);
	};


#endif // DDSHEADER_H
