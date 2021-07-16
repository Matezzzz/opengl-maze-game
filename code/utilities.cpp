#include "utilities.h"


void GLUtilities::makeScreenshot(string filename, int screen_width, int screen_height)
{
  //This prevents the images getting padded
 // when the width multiplied by 3 is not a multiple of 4
  glPixelStorei(GL_PACK_ALIGNMENT, 1);

  int nSize = screen_width*screen_height*3;
  // First let's create our buffer, 3 channels per Pixel
  char* dataBuffer = (char*)malloc(nSize*sizeof(char));

  assert(dataBuffer && "Cannot create buffer for screen shot.");

   // Let's fetch them from the backbuffer
   // We request the pixels in GL_BGR format, thanks to Berzeger for the tip
   glReadPixels((GLint)0, (GLint)0,
		(GLint)screen_width, (GLint)screen_height,
		 GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);

   //Now the file creation
   filename += ".tga";
   FILE *filePtr = fopen(filename.c_str(), "wb");
   assert(filePtr && "Cannot create file.");

   unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
   unsigned char header[6]
   {
        static_cast<unsigned char>(screen_width % 256),
        static_cast<unsigned char>(screen_width / 256),
        static_cast<unsigned char>(screen_height % 256),
        static_cast<unsigned char>(screen_height / 256),
        24,
        0
    };
   // We write the headers
   fwrite(TGAheader,	sizeof(unsigned char),	12,	filePtr);
   fwrite(header,	sizeof(unsigned char),	6,	filePtr);
   // And finally our image data
   fwrite(dataBuffer,	sizeof(GLubyte),	nSize,	filePtr);
   fclose(filePtr);

   free(dataBuffer);
}
