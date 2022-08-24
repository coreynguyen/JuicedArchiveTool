/*
i was converting this over from my maxscript
..but i dont really see the point of reading it now

the pmd is a material script, it someone wants to it
the script just open it notepad..
*/

#ifndef FMTPMD_H
#define FMTPMD_H

#include <iostream>
#include <fstream>
#include <string>
#include "bytestream.h"
#include "stringext.h"

struct fmtPMD_Enabled {
	bool additive;
	bool alpha_test_texture;
	bool alpha_texture;
	bool base_opacity;
	bool car_colour;
	bool colour;
	bool disable_fog;
	bool double_sided;
	bool end_fade;
	bool front_fresnel;
	bool metallic;
	bool metallic_colour;
	bool metallic_shininess;
	bool opaque_texture;
	bool paint_work;
	bool pearlescent_colour;
	bool pearlescent_shininess;
	bool scratch;
	bool scratch_and_reflect;
	bool shininess;
	bool side_fresnel;
	bool single_sided;
	bool specular_colour;
	bool specular_highlight;
	bool start_fade;
	bool texture;
	bool z_bias;
	bool z_write;
	fmtPMD_Enabled () {
		additive 				= false;
		alpha_test_texture 		= false;
		alpha_texture 			= false;
		base_opacity 			= false;
		car_colour 				= false;
		colour 					= false;
		disable_fog 			= false;
		double_sided 			= false;
		end_fade 				= false;
		front_fresnel 			= false;
		metallic 				= false;
		metallic_colour 		= false;
		metallic_shininess 		= false;
		opaque_texture 			= false;
		paint_work 				= false;
		pearlescent_colour 		= false;
		pearlescent_shininess 	= false;
		scratch 				= false;
		scratch_and_reflect 	= false;
		shininess 				= false;
		side_fresnel 			= false;
		single_sided 			= false;
		specular_colour 		= false;
		specular_highlight 		= false;
		start_fade 				= false;
		texture 				= false;
		z_bias 					= false;
		z_write 				= false;
		}
	};

struct fmtPMD {
	fmtPMD_Enabled 	isEnabled;
	std::string 	material_program;
	/*
	Car Body
	Car Glass
	Chrome
	Coloured Spec ABlend
	Coloured Spec Opaque
	Shiny Opaque
	Specular Opaque
	Standard Alpha Blend
	Standard Alpha Test
	Standard Opaque
	Unlit ABlend

	profiles:
		"#{"Material Program = Car Body", "Car Colour ", "Side Fresnel ", "Front Fresnel ", "Metallic Colour ", "Pearlescent Colour ", "Metallic Shininess ", "Pearlescent Shininess ", "Metallic ", "Double-sided ", "Paint Work ", "Scratch & Reflect ", "Z-Bias "}"
		"#{"Material Program = Car Body", "Car Colour ", "Side Fresnel ", "Front Fresnel ", "Metallic Colour ", "Pearlescent Colour ", "Metallic Shininess ", "Pearlescent Shininess ", "Metallic ", "Double-sided ", "Z-Bias ", "Paint Work ", "Scratch & Reflect "}"
		"#{"Material Program = Car Glass", "Side Fresnel ", "Front Fresnel ", "Base Opacity ", "Start Fade ", "End Fade ", "Colour ", "Texture ", "Scratch "}"
		"#{"Material Program = Chrome", "Colour ", "Texture "}"
		"#{"Material Program = Chrome", "Colour ", "Z-Bias ", "Texture "}"
		"#{"Material Program = Coloured Spec ABlend", "Colour ", "Specular Colour ", "Specular Highlight ", "Shininess ", "Additive ", "Texture "}"
		"#{"Material Program = Coloured Spec ABlend", "Colour ", "Specular Colour ", "Specular Highlight ", "Shininess ", "Additive ", "Texture ", "Z-Bias "}"
		"#{"Material Program = Coloured Spec Opaque", "Colour ", "Specular Colour ", "Specular Highlight ", "Shininess ", "Texture ", "Z-Bias "}"
		"#{"Material Program = Coloured Spec Opaque", "Colour ", "Specular Colour ", "Specular Highlight ", "Shininess ", "Z-Bias ", "Texture "}"
		"#{"Material Program = Shiny Opaque", "Side Fresnel ", "Front Fresnel ", "Z-Bias ", "Texture "}"
		"#{"Material Program = Specular Opaque", "Shininess ", "Specular Colour ", "Specular Highlight ", "Double-sided ", "Z-Bias ", "Opaque Texture "}"
		"#{"Material Program = Standard Alpha Blend", "Z-Write ", "Alpha Texture ", "Z-Bias "}"
		"#{"Material Program = Standard Alpha Blend", "Z-Write ", "Disable Fog ", "Z-Bias ", "Alpha Texture "}"
		"#{"Material Program = Standard Alpha Test", "Single-sided ", "Z-Bias ", "Alpha Test Texture "}"
		"#{"Material Program = Standard Opaque", "Double-sided ", "Opaque Texture "}"
		"#{"Material Program = Standard Opaque", "Double-sided ", "Z-Bias ", "Opaque Texture "}"
		"#{"Material Program = Unlit ABlend", "Disable Fog ", "Texture "}"
		"#{"Material Program = Unlit ABlend", "Texture "}"

	*/
	bool 			additive; 				// always false
	std::string 	alpha_test_texture; 	// *.ptd
	std::string 	alpha_texture; 			// *.ptd
	int 			base_opacity; 			// always 0
	char 			car_colour[3];
	char 			colour[3];
	bool 			disable_fog; 			// always false
	bool 			double_sided; 			// always false
	int 			end_fade; 				// range[3000, 10000]
	int 			front_fresnel; 			// always 0
	bool 			metallic;
	char 			metallic_colour[3];
	int 			metallic_shininess; 	// range[0, 30, 35]
	std::string 	opaque_texture; 		// *.ptd
	std::string 	paint_work; 			// *.ptd
	char 			pearlescent_colour[3];
	float 			pearlescent_shininess; 	// always 0.0
	std::string 	scratch; 				// *.ptd
	std::string 	scratch_and_reflect; 	// *.ptd
	float 			shininess; 				// range[22.5, 25, 30, 35, 128]
	float 			side_fresnel; 			// range[0.0 - 1.0]
	bool 			single_sided;
	char 			specular_colour[3];
	float 			specular_highlight; 	// range[204, 255]
	float 			start_fade; 			// range[0.0 - 1000.0]
	std::string 	texture; 				// *.ptd
	float 			z_bias; 				// range[0.0 - 1.0]
	bool 			z_write; 				// always false
	fmtPMD () {
		material_program 		= "";
		additive 				= false;
		alpha_test_texture 		= "";
		alpha_texture 			= "";
		base_opacity 			= 0;
		car_colour 				= {128, 128, 128};
		colour 					= {0, 0, 0};
		disable_fog 			= false;
		double_sided 			= false;
		end_fade 				= 3000;
		front_fresnel 			= 0;
		metallic 				= false;
		metallic_colour 		= {0, 0, 0};
		metallic_shininess 		= 0;
		opaque_texture 			= "";
		paint_work 				= "";
		pearlescent_colour 		= {128, 128, 128};
		pearlescent_shininess 	= 0.0f;
		scratch 				= "";
		scratch_and_reflect 	= "";
		shininess 				= 128.0f;
		side_fresnel 			= 0.0f;
		single_sided 			= true;
		specular_colour 		= {255, 255, 255};
		specular_highlight 		= 255.0f;
		start_fade 				= 1000.0f;
		texture 				= "";
		z_bias 					= 0.0f;
		z_write 				= false;
		}
	int getShaderIndexFromName (std::string str_name) {
		str_name = tolower(str_name);
		std::string shaders[11] = {
			"car body",
			"car glass",
			"chrome",
			"coloured spec ablend",
			"coloured spec opaque",
			"shiny opaque",
			"specular opaque",
			"standard alpha blend",
			"standard alpha test",
			"standard opaque",
			"unlit ablend"
			};
		for (int i = 0; i < 11; i++) {
			if (str_name == shaders[i]) {
				return i;
				break;
				}
			}
		return -1;
		}
	void read (std::string file) {
		bytestream 		f;
		std::string 	s = ""
		std::string 	v = ""
		unsigned int 	i = 0;
		if (f.openFile(file)) {
			while (f.tell() < f.size) do {
				s = tolower(f.readline());
				v = "";
				i = s.find("=");
				if (i != std::string::npos) do {
					v = s.substr(i + 1);
					}
				if (s == "material program = ") 			{material_program 					= v;}
				else if (s == "material program = ") 		{isEnabled.additive 				= true; additive 				= convert_to<bool>(v);}
				else if (s == "alpha test texture = ") 		{isEnabled.alpha_test_texture 		= true; alpha_test_texture 		= v;}
				else if (s == "alpha texture = ") 			{isEnabled.alpha_texture 			= true; alpha_texture 			= v;}
				else if (s == "base opacity = ") 			{isEnabled.base_opacity 			= true; base_opacity 			= convert_to<int>(v);}
//				else if (s == "car colour = ") 				{isEnabled.car_colour 				= true; car_colour 				= execute {"color " + v;}}
//				else if (s == "colour = ") 					{isEnabled.colour 					= true; colour 					= execute {"color " + v;}}
				else if (s == "disable fog = ") 			{isEnabled.disable_fog 				= true; disable_fog 			= convert_to<bool>(v);}
				else if (s == "double-sided = ") 			{isEnabled.double_sided 			= true; double_sided 			= convert_to<bool>(v);}
				else if (s == "end fade = ") 				{isEnabled.end_fade 				= true; end_fade 				= convert_to<int>(v);}
				else if (s == "front fresnel = ") 			{isEnabled.front_fresnel 			= true; front_fresnel 			= convert_to<int>(v);}
				else if (s == "metallic = ") 				{isEnabled.metallic 				= true; metallic 				= convert_to<bool>(v);}
//				else if (s == "metallic colour = ") 		{isEnabled.metallic_colour 			= true; metallic_colour 		= execute {"color " + v;}}
				else if (s == "metallic shininess = ") 		{isEnabled.metallic_shininess 		= true; metallic_shininess 		= convert_to<int>(v);}
				else if (s == "opaque texture = ") 			{isEnabled.opaque_texture 			= true; opaque_texture 			= v;}
				else if (s == "paint work = ") 				{isEnabled.paint_work 				= true; paint_work 				= v;}
//				else if (s == "pearlescent colour = ") 		{isEnabled.pearlescent_colour 		= true; pearlescent_colour 		= execute {"color " + v;}}
				else if (s == "pearlescent shininess = ") 	{isEnabled.pearlescent_shininess 	= true; pearlescent_shininess 	= convert_to<float>(v);}
				else if (s == "scratch = ") 				{isEnabled.scratch 					= true; scratch 				= v;}
				else if (s == "scratch & reflect = ") 		{isEnabled.scratch_and_reflect 		= true; scratch_and_reflect 	= v;}
				else if (s == "shininess = ") 				{isEnabled.shininess 				= true; shininess 				= convert_to<float>(v);}
				else if (s == "side fresnel = ") 			{isEnabled.side_fresnel 			= true; side_fresnel 			= convert_to<float>(v);}
				else if (s == "single-sided = ") 			{isEnabled.single_sided 			= true; single_sided 			= convert_to<bool>(v);}
//				else if (s == "specular colour = ") 		{isEnabled.specular_colour 			= true; specular_colour 		= execute {"color " + v;}}
				else if (s == "specular highlight = ") 		{isEnabled.specular_highlight 		= true; specular_highlight 		= convert_to<float>(v);}
				else if (s == "start fade = ") 				{isEnabled.start_fade 				= true; start_fade 				= convert_to<float>(v);}
				else if (s == "texture = ") 				{isEnabled.texture 					= true; texture 				= v;}
				else if (s == "z-bias = ") 					{isEnabled.z_bias 					= true; z_bias 					= convert_to<float>(v);}
				else if (s == "z-write = ") 				{isEnabled.z_write 					= true; z_write 				= convert_to<bool>(v);}
				else {std::cout << "unknown material paramater\n";}
				}
			f.close();
			} else {std::cout << "failed to read:\t" << file << "\n";}
		}
	void write (std::string file) {

		ofstream pmdfile(file.c_str());
		if (pmdfile.is_good()) {
			std::string shader = toLower(material_program);
			if (shader == "Car Body") {
				pmdfile << "Material Program = Car Body\n";
				pmdfile << "Car Colour = %\n" {printColour car_colour} to:s
				pmdfile << "Side Fresnel = %\n" {printFloat side_fresnel} to:s
				pmdfile << "Front Fresnel = %\n" {printFloat front_fresnel} to:s
				pmdfile << "Metallic Colour = %\n"  {printColour metallic_colour} to:s
				pmdfile << "Pearlescent Colour = %\n"  {printColour pearlescent_colour} to:s
				pmdfile << "Metallic Shininess = %\n" {printFloat metallic_shininess} to:s
				pmdfile << "Pearlescent Shininess = %\n" {printFloat pearlescent_shininess} to:s
				pmdfile << "Metallic = %\n" {printBool metallic} to:s
				pmdfile << "Double-sided = %\n" {printBool double_sided} to:s
				pmdfile << "Paint Work = %\n" {if paint_work != "" then paint_work else ""} to:s
				pmdfile << "Scratch & Reflect = %\n" {if scratch_and_reflect != "" then scratch_and_reflect else ""} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Car Glass") {
				pmdfile << "Material Program = %\n" "Car Glass" to:s
				pmdfile << "Side Fresnel = %\n" {printFloat side_fresnel} to:s
				pmdfile << "Front Fresnel = %\n" {printFloat front_fresnel} to:s
				pmdfile << "Base Opacity = %\n" {printFloat base_opacity} to:s
				pmdfile << "Start Fade = %\n" {printFloat start_fade} to:s
				pmdfile << "End Fade = %\n" {printFloat end_fade} to:s
				pmdfile << "Colour = %\n" {printColour colour} to:s
				pmdfile << "Texture = %\n" {if texture != "" then texture else "dummy.ptd"} to:s
				pmdfile << "Scratch = %\n" {if scratch != "" then scratch else "dummy.ptd"} to:s
				}
			else if (shader == "Chrome") {
				pmdfile << "Material Program = %\n" "Chrome" to:s
				pmdfile << "Colour = %\n" {printColour colour} to:s
				pmdfile << "Texture = %\n" {if texture != "" then texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Coloured Spec ABlend") {
				pmdfile << "Material Program = %\n" "Coloured Spec ABlend" to:s
				pmdfile << "Colour = %\n" {printColour colour} to:s
				pmdfile << "Specular Colour = %\n" {printColour specular_colour} to:s
				pmdfile << "Specular Highlight = %\n" {printFloat specular_highlight} to:s
				pmdfile << "Shininess = %\n" {printFloat shininess} to:s
				pmdfile << "Additive = %\n" {printBool additive} to:s
				pmdfile << "Texture = %\n" {if texture != "" then texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Coloured Spec Opaque") {
				pmdfile << "Material Program = %\n" "Coloured Spec Opaque" to:s
				pmdfile << "Colour = %\n" {printColour colour} to:s
				pmdfile << "Specular Colour = %\n" {printColour specular_colour} to:s
				pmdfile << "Specular Highlight = %\n" {printFloat specular_highlight} to:s
				pmdfile << "Shininess = %\n" {printFloat shininess} to:s
				pmdfile << "Texture = %\n" {if texture != "" then texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Shiny Opaque") {
				pmdfile << "Material Program = %\n" "Shiny Opaque" to:s
				pmdfile << "Side Fresnel = %\n" {printFloat side_fresnel} to:s
				pmdfile << "Front Fresnel = %\n" {printFloat front_fresnel} to:s
				pmdfile << "Texture = %\n" {if texture != "" then texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Specular Opaque") {
				pmdfile << "Material Program = %\n" "Specular Opaque" to:s
				pmdfile << "Shininess = %\n" {printFloat shininess} to:s
				pmdfile << "Specular Colour = %\n" {printColour specular_colour} to:s
				pmdfile << "Specular Highlight = %\n" {printFloat specular_highlight} to:s
				pmdfile << "Double-sided = %\n" {printBool double_sided} to:s
				pmdfile << "Opaque Texture = %\n" {if opaque_texture != "" then opaque_texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Standard Alpha Blend") {
				pmdfile << "Material Program = %\n" "Standard Alpha Blend" to:s
				pmdfile << "Z-Write = %\n"  {printBool z_write} to:s
				pmdfile << "Disable Fog = %\n" {printBool disable_fog} to:s
				pmdfile << "Alpha Texture = %\n" {if alpha_texture != "" then alpha_texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Standard Alpha Test") {
				pmdfile << "Material Program = %\n" "Standard Alpha Test" to:s
				pmdfile << "Single-sided = %\n" {printBool single_sided} to:s
				pmdfile << "Alpha Test Texture = %\n" {if alpha_test_texture != "" then alpha_test_texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Standard Opaque") {
				pmdfile << "Material Program = %\n" "Standard Opaque" to:s
				pmdfile << "Double-sided = %\n" {printBool double_sided} to:s
				pmdfile << "Opaque Texture = %\n" {if opaque_texture != "" then opaque_texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			else if (shader == "Unlit ABlend") {
				pmdfile << "Material Program = %\n" "Unlit ABlend" to:s
				pmdfile << "Disable Fog = %\n" {printBool disable_fog} to:s
				pmdfile << "Texture = %\n" {if texture != "" then texture else "dummy.ptd"} to:s
				}
			else {
				pmdfile << "Material Program = %\n" "Standard Opaque" to:s
				pmdfile << "Double-sided = %\n" {printBool double_sided} to:s
				pmdfile << "Opaque Texture = %\n" {if opaque_texture != "" then opaque_texture else "dummy.ptd"} to:s
				if z_bias > 0.0 do pmdfile << "Z-Bias = %\n" {printFloat z_bias} to:s
				}
			pmdfile.close();
			}
		}
	};













#endif // FMTPMD_H
