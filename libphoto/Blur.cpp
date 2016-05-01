#include "Blur.h"

#define filterWidth 3
#define filterHeight 3

Blur::Blur(int radius)
  : DrawTool(radius, radius){
  fillInfluence();
}

Blur::~Blur(){
}


void Blur::fillInfluence(){
  Mask const * mask = getMask();
  float** influence = mask -> getInfluence();
  int width = mask -> getWidth();
  float dx, dy, dist;
  float radius = width/2.0;
  for(int i = 0; i < width; i++){
    for(int j = 0; j < width; j++){
      dx = (radius - i)*(radius - i);
      dy = (radius - j)*(radius - j);
      dist  = sqrt(dx + dy);
      if(dist <= radius - 1.5){
        influence[i][j] = 1.0 - (dist / (radius - 1.5));
      }else{
        influence[i][j] = 0.0;
      }
    }
  }
}

void Blur::applyInfluence(int x, int y, PixelBuffer* buffer){
  float filter[filterHeight][filterWidth] =
  {
    {0.0, 0.2, 0.0},
    {0.2, 0.2, 0.2},
    {0.0, 0.2, 0.0}
  };

  Mask const * mask = getMask();
  int height = mask -> getHeight();
  int width = mask -> getWidth();
  int bufferHeight = buffer -> getHeight(); // canvas's buffer's height
  int bufferWidth = buffer -> getWidth();
  x -= width/2;
  y = bufferHeight - y - height/2;
  float** influence = mask -> getInfluence();

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {

      float red = 0.0, green = 0.0, blue = 0.0;

      for (int filterY = 0; filterY < filterHeight; filterY++) {
        for (int filterX = 0; filterX < filterWidth; filterX++) {
					int X = x + ((i - filterWidth / 2 + filterX + width) % width);
					int Y = y + ((j - filterHeight / 2 + filterY + height) % height);

					if (X < 0 || X >= bufferWidth || Y < 0 || Y >= bufferHeight) {
						continue;
					}

					ColorData currentPixelColor = buffer -> getPixel(X, Y);
					red += (float) (currentPixelColor.getRed() * filter[filterY][filterX]);
					green += (float) (currentPixelColor.getGreen() * filter[filterY][filterX]);
					blue += (float) (currentPixelColor.getBlue() * filter[filterY][filterX]);
        }
      }

	  	ColorData newPixel = ColorData(red, green, blue);
      newPixel = newPixel.clampedColor();

      if (influence[i][j] > 0.0) {
				if (x + i > 0 && x + i < bufferWidth -1 && y + j > 0 && y + j < bufferHeight -1) {
					 buffer -> setPixel(x + i, y + j, newPixel);
				}
      }
    }
  }
}

string Blur::getName(){
  return "Blur";
}
