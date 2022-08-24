
int test (std::wstring filename) {


	ilInit();
	printf("DevIL has been initialized\n");

	// get width and height of your desktop
	int width  = 512 ;
	int height = 512;

	int bytesToUsePerPixel = 4 ;  // RGB
	// we coulda used 4, if we wanted a "transparency" component,
	// but we don't want this png to use trans.

	// duh, the size of a byte is obviously ONE BYTE,
	// but this is just a formality to PERHAPS
	// make the code a bit more clear.
	int sizeOfByte = sizeof( unsigned char ) ;

	// So this computation gets the size
	// that the image data array should be.
	// (width*height)   *   (#bytes to use per pixel) really.
	int theSize = width * height * sizeOfByte * bytesToUsePerPixel ;

//	unsigned char * imData =(unsigned char*)malloc( theSize ) ;
//
//	for( int i = 0 ; i < theSize ; i++ )
//	{
//	imData[ i ] = i % 255 ;
//	}

	binary_stream f;
	f.openFile(filename);



	// Let's make an image now.
	// the next line "generates an image" within the
	// DevIL STATE MACHINE.

	// DevIL is cool because it has this concept of
	// your "currently selected image".

	// So, when you call all the DevIL library functions,
	// (such as ilTexImage to change an images properties),
	// notice how there's no passing of any big data struct,
	// pointer to an image, or anything like that.

	// That's because the ONLY reference YOU get
	// as the user of the OpenIL API IS this INT
	// value:
	ILuint imageID = ilGenImage() ;

	// there.  We just created a NEW image (which will start out
	// to being 1x1 pixels or something like that)
	// our REFERENCE to this 1x1 pixel image IS
	// the integer number imageID.

	// NOW, we "select-in" the image we just generated
	// as the one we're currently working on.
	ilBindImage( imageID ) ;

	// From HENCE FORTH (until we call ilBindImage() again)
	// WE ARE WORKING ON "imageID".  ANY calls to
	// ilTexImage, or ilGetInteger, or WHATEVER are in
	// reference to the LAST IMAGE WE LAST BOUND.

	// So the new image we just created is rather.. empty.

	cout << "IL_IMAGE_ORIGIN:\t" << (int)ilGetInteger(IL_IMAGE_ORIGIN) << endl;
	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_LOWER_LEFT, 0);
	//ilSetInteger(IL_ORIGIN_UPPER_LEFT, false);
	//ilDisable(IL_ORIGIN_SET);
	cout << "IL_ORIGIN_MODE:\t" << (int)ilGetInteger(IL_ORIGIN_MODE) << endl;


	ilLoadL(IL_DDS,
			f.stream,
			f.size
			);

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	printf("New image!  width=%d,  height=%d,  bpp=%d\n",

		ilGetInteger( IL_IMAGE_WIDTH ),
		ilGetInteger( IL_IMAGE_HEIGHT ),
		ilGetInteger( IL_IMAGE_BPP )
		);







		// Get the Image Size
		ILuint writtenToLump = ilSaveL(IL_TGA, NULL, 0);

		// Check if Image Size is Valid
		if (writtenToLump > 0) {

			// Create a Buffer to save to Image to
			binary_stream s;
			s.resize(writtenToLump);

			// Create Image data
			ilSaveL(IL_TGA, s.stream, writtenToLump);

			// Write Image to File
			s.writeFile(L"C:\\_TEMP\\trunk-15507\\test.tga");

			}






	//bool st = ilSave( IL_PNG, (filename + L".png").c_str()) ;
	//ILboolean st = ilSave( IL_TGA, L"C:\\_TEMP\\trunk-15507\\test.png" ) ;
	//cout << (bool)st << endl;



//
//	// allow openIL to overwrite the file
//	// we created last time
//	ilEnable(IL_FILE_OVERWRITE);
//
//	// actually save out as png
//	ilSave( IL_PNG, "output.png" ) ;
//
//	// now try saving as jpg
//	ilSave( IL_JPG, "output.jpg" ) ;
//
//	// now save as bmp
//	ilSave( IL_BMP, "output.bmp" ) ;
//
//
//	// Look at the file sizes!  For this TYPE
//	// of image, png is the best because its
//	// flat colors repeated.
//
//	// On my mahcin eht png is 94KB and the BMP is 11000kB!
//	// the jpg comes out at 3000kb.
//
//	// PNG RULES!!
//
//	// lets give another example where jpg will
//	// be better...
//
//	// cahnge im data to being just pure noise
//	for( int i = 0 ; i < theSize ; i++ )
//	{
//	imData[ i ] = rand()%255 ;
//	}
//
//
//	// now set the data in the image with this new data array
//	ilSetData( imData ) ;
//
//	// save again
//
//	// actually save out as png
//	ilSave( IL_PNG, "outputNoise.png" ) ;
//
//	// now try saving as jpg
//	ilSave( IL_JPG, "outputNoise.jpg" ) ;
//
//	// now save as bmp
//	ilSave( IL_BMP, "outputNoise.bmp" ) ;
//
//
//	// Wowo!   So for this last test, PNG was
//	// worse than jpg and bmp!  that's remarkable.
//	// I actually didn't know that coudl happen.
//
//	printf("and done");
//

	return 1;
	}
