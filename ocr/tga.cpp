#include "tga.h"

TGA::TGA()
{
}

bool TGA::texture(const char *filename)
{
	if (!filename)
		return false;

	if (!load(filename)) {
		return false;
	}

// 	cerr << "channels: " << channels << endl;
// 	cerr << "size_x: " << size_x << endl;
// 	cerr << "size_y: " << size_y << endl;
// 	cerr << "data: " << (int)data[0] << endl;

	return true;
}


bool TGA::load(const char *filename)
{
//	image *pImgData			= NULL;
	FILE *pFile			= NULL;
	int width			= 0;
	int height			= 0;
	char length			= 0;
	char imgType			= 0;
	char bits			= 0;
	int nchannels			= 0;
	int stride			= 0;
	int i				= 0;

	if((pFile = fopen(filename, "rb")) == NULL) 
	{
		cerr << "could not open file" << endl;
		return false;
	}

//	data = (image*)malloc(sizeof(image));
	
	fread(&length, sizeof(char), 1, pFile);
	
	fseek(pFile,1,SEEK_CUR); 
	
	fread(&imgType, sizeof(char), 1, pFile);
	
	fseek(pFile, 9, SEEK_CUR); 
	
	fread(&width,  sizeof(short), 1, pFile);
	fread(&height, sizeof(short), 1, pFile);
	fread(&bits,   sizeof(char), 1, pFile);
	
	fseek(pFile, length + 1, SEEK_CUR); 
	
	if(imgType != TGA_RLE)
	{
		// Check for 24 or 32 Bit
		if(bits == 24 || bits == 32)
		{
			
			nchannels = bits / 8;
			stride = nchannels * width;
			data = new unsigned char[stride * height];
			
			for(int y = 0; y < height; y++)
			{
				unsigned char *pLine = &(data[stride * y]);
				
				fread(pLine, stride, 1, pFile);
				
				for(i = 0; i < stride; i += nchannels)
				{
					int temp     = pLine[i];
					pLine[i]     = pLine[i + 2];
					pLine[i + 2] = temp;
				}
			}
		}
				
		// Check for 16 Bit
		else if(bits == 16)
		{
			unsigned short pixels = 0;
			int r=0, g=0, b=0;
			
			nchannels = 3;
			stride = nchannels * width;
			data = new unsigned char[stride * height];

			for(int i = 0; i < width*height; i++)
			{
				fread(&pixels, sizeof(unsigned short), 1, pFile);
				
				b = (pixels & 0x1f) << 3;
				g = ((pixels >> 5) & 0x1f) << 3;
				r = ((pixels >> 10) & 0x1f) << 3;
				
				data[i * 3 + 0] = r;
				data[i * 3 + 1] = g;
				data[i * 3 + 2] = b;

			}
		}	
	
		else
			return false;
	}
	
	else
	{
		
		int rleID = 0;
		int colorsRead = 0;
		nchannels = bits / 8;
		stride = nchannels * width;
		
		data = new unsigned char[stride * height];
		char *pColors = new char [nchannels];
		
		while(i < width*height)
		{
			
			fread(&rleID, sizeof(int), 1, pFile);
			
			
			if(rleID < 128)
			{
				rleID++;
				
				while(rleID)
				{
					fread(pColors, sizeof(char) * nchannels, 1, pFile);
					
					data[colorsRead + 0] = pColors[2];
					data[colorsRead + 1] = pColors[1];
					data[colorsRead + 2] = pColors[0];
					
					if(bits == 32) data[colorsRead + 3] = pColors[3];
					
					i++;
					rleID--;
					colorsRead += nchannels;
				}
			}
			
			else
			{
				rleID -= 127;
				
				fread(pColors, sizeof(char) * nchannels, 1, pFile);
				
				while(rleID)
				{
					data[colorsRead + 0] = pColors[2];
					data[colorsRead + 1] = pColors[1];
					data[colorsRead + 2] = pColors[0];
					
					if(bits == 32)	data[colorsRead + 3] = pColors[3];
					
					i++;
					rleID--;
					colorsRead += nchannels;
				}
			}
		}
		delete[] pColors;
	}
	
	fclose(pFile);
	
	
	channels  = nchannels;
	size_x    = width;
	size_y    = height;

	return true;
}

TGA::~TGA()
{
}


