//
// Trying to do some change here 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel;

typedef struct {
     uint16_t x, y;
     pixel *data;
} image;

void writeImage(const char *filename, image *img);

int main(int argc, char *argv[])
{
	uint16_t w = 1000;	
	uint16_t h = 800;
	uint32_t numOfPix = w*h;

	pixel *pi = malloc(sizeof(pixel)*numOfPix);	
	image *img = malloc(sizeof(image));
	img->x = w;
	img->y = h;
	img->data = pi;	  
	
	int cPix = 0;
	
  //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
  double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
  double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
  double zoom = 1, moveX = 0, moveY = 0; //you can change these to zoom and change position
  int maxIterations = 300; //after how much iterations the function should stop

  //pick some values for the constant c, this determines the shape of the Julia Set
  cRe = -0.7;
  cIm = 0.27015;

  //loop through every pixel
  for(int y = 0; y < h; y++)
  for(int x = 0; x < w; x++)
  {
    //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
    newRe = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
    newIm = (y - h / 2) / (0.5 * zoom * h) + moveY;
    //i will represent the number of iterations
    int i;
    //start the iteration process
    for(i = 0; i < maxIterations; i++)
    {
      //remember value of previous iteration
      oldRe = newRe;
      oldIm = newIm;
      //the actual iteration, the real and imaginary part are calculated
      newRe = oldRe * oldRe - oldIm * oldIm + cRe;
      newIm = 2 * oldRe * oldIm + cIm;
      //if the point is outside the circle with radius 2: stop
      if((newRe * newRe + newIm * newIm) > 4) break;
    }
    //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
		
		//printf("%d ",i);
		img->data[cPix].r = 100;
		img->data[cPix].g = 50;
		img->data[cPix++].b = 10;
		//color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));
    
  }
  //make the Julia Set visible and wait to exit
  
	writeImage("out.ppm", img);
  return 0;
}

void writeImage(const char *filename, image *img)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //write the header file
    //image format
    fprintf(fp, "P6\n");

    //image size
    fprintf(fp, "%d %d\n",img->x,img->y);

    // rgb component depth
    fprintf(fp, "%d\n",255);

    // pixel data
    fwrite(img->data, 3 * img->x, img->y, fp);
    fclose(fp);
}
