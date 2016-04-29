#ifndef LIBPHOTO_H
#define LIBPHOTO_H

#include "../BaseGfxApp.h"

class ColorData{
public:
	ColorData();
	ColorData(float r, float g, float b );
	ColorData(float r, float g, float b, float a);

	void setRed(float r);
	void setBlue(float b);
	void setGreen(float g);
	void setAlpha(float a);

	float getRed() const;
	float getBlue() const;
	float getGreen() const;
	float getAlpha() const;

	// Returns the "brightness" of the color according to a perceptual metric that
	// weights the red, green, and blue components of the color non-uniformly.
  float getLuminance() const;

  // get the sume of all RGB color
  float getColorSum() const;
	// Return a clamped version of this ColorData
	ColorData clampedColor() const;

	// Arithmatic operators (friends so that non-member functions can access private variables)
  friend ColorData operator* (const ColorData& a, float f);
  friend ColorData operator* (const ColorData& a, const ColorData& b);
	friend ColorData operator+ (const ColorData& a, const ColorData& b);
	friend ColorData operator- (const ColorData& a, const ColorData& b);

private:

	// General helper function for clamping values between 0 and 1
	static inline float clampValue(float input, float a, float b)
	{return input < a ? a : (input > b ? b : input);}

	float m_red;
	float m_green;
	float m_blue;
	float m_alpha;
};
class PixelBuffer{
public:

	PixelBuffer(int w, int h, ColorData backgroundColor);
	virtual ~PixelBuffer();

	// Sets the color of a specific pixel
	void setPixel(int x, int y, const ColorData& color);

	// Fills the enitre pixel buffer with the specified color
	void fillPixelBufferWithColor(ColorData color);

  void convertToLuminance();
	// Returns the color of a specific pixel
	ColorData getPixel(int x, int y) const;

	// Returns a pointer to the raw ColorData array for fast access to ColorData
  ColorData const * getData() const;
    
	// Returns the background color for the PixelBuffer
	ColorData getBackgroundColor();

	// Returns the background color that was used to initialize the PixelBuffer
	ColorData getDefaultBackgroundColor();

	int getHeight() const;
	int getWidth() const;

    // A static method to copy one pixel buffer to another
	static void copyPixelBuffer(PixelBuffer * sourceBuffer, PixelBuffer * destinationBuffer);
    static void copyPixelBuffer(PixelBuffer sourceBuffer, PixelBuffer * destinationBuffer);
    void setBackgroundColor(ColorData* color);
    
private:

	// Array of pixel colors
	ColorData * m_pixels;

	// Pointer to the single color used as the "background color" to initialize the PixelBuffer
	ColorData * m_backgroundColor;
    
    //A backup background color for the fill tool
    ColorData * m_defaultBackgroundColor;
	// Dimensions
	const int m_width;
	const int m_height;
};
class Mask{
public:
    Mask(int w, int h);
    virtual ~Mask();
    int getHeight() const;
    int getWidth() const;
    float** getInfluence() const;
protected:
    int height;
    int width;
    float** influence;
};

class DrawTool {
public:
    DrawTool(ColorData* toolColor, int width, int height);
    DrawTool(int width, int height);
    DrawTool(PixelBuffer* newBuffer, int width, int height);
    virtual ~DrawTool();
    virtual void fillInfluence();
    virtual void paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer);
    virtual void applyInfluence(int x, int y, PixelBuffer* buffer);
    virtual string getName() = 0;
    Mask const * getMask() const;
    ColorData const * getToolColor() const;
    void setToolColor(ColorData* color);
  // printfInfluence use for debuging
    void printfInfluence();
    bool allowDrag;
protected:
    Mask* m_mask;
    ColorData* m_toolColor;
    PixelBuffer* imageBuffer;
};

class Filter {
public:
  virtual void applyFilter(PixelBuffer* imageBuffer) = 0;
  virtual std::string getName() = 0;
  virtual void setFilterParameter(float parameter){ f_parameter = parameter;}
  virtual void setFilterParameter(ColorData parameter){ c_parameter = parameter;}
  void setBlurDirection(int direction){blurDirection = direction;}
  float getFloatParameter(){ return f_parameter;}
  ColorData getColorParameter(){return c_parameter;}
  int getBlurDiection(){return blurDirection;}
private:
  float f_parameter;
  ColorData c_parameter;
  int blurDirection;
};
class FilterFactory {
public:
  enum FILTERS{
      FILTER_THRESHOLD = 0,
      FILTER_CHANNEL = 1,
      FILTER_SATURATION = 2,
      FILTER_QUANTIZE = 3,
      FILTER_BLUR = 4,
      FILTER_MOTION_BLUR = 5,
      FILTER_SHARPEN = 6,
      FILTER_DETECT_EDGES = 7,
      FILTER_SPECIAL = 8,
      NUMFILTERS = 9
  };
  static int getNumFilters();
  static Filter* createFilter(int filterID);
};
class Blur : public DrawTool {
 public :
  Blur(int radius);
  ~Blur();
  void fillInfluence();
  void applyInfluence(int x, int y, PixelBuffer* buffer);
};
class CalligraphyPen : public DrawTool {
 public :
  CalligraphyPen(ColorData* toolColor, int height, int width);
  ~CalligraphyPen();
  void fillInfluence();
};
class Crayon : public DrawTool {
 public :
  Crayon(ColorData* toolColor, int radius);
  ~Crayon();
  void fillInfluence();
};
class Eraser : public DrawTool{
public:
  Eraser(int radius);
  ~Eraser();
  void applyInfluence(int x, int y, PixelBuffer* buffer);
  void fillInfluence();
};
class FBlur : public Filter{
public:
  typedef std::vector<float> kernelRow;
  typedef std::vector<kernelRow> kernelType;
  FBlur();
  ~FBlur();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
  virtual kernelType buildKernel(int radius);
  kernelType boxFilter(int radius);
  kernelType emptyFilter(int radius);
  kernelType GaussianBlur(float sigma);
  kernelType getKernel(){ return kernel;}
  //this is debug only
  void printKernel();
private:
  kernelType kernel;
};
class FChannel : public Filter{
public:
  FChannel();
  ~FChannel();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};
class FEdgeDetection : public FBlur{
public:
  FEdgeDetection();
  ~FEdgeDetection();
  std::string getName();
  kernelType buildKernel(int radius);
  //PixelBuffer ProcessImage(PixelBuffer* imageBuffer, float sigma, float lowThreshold, float hightThresold);
  //void PreProcessImage(float sigma);
  // void PostProcessImage();
  // void GaussianBlur();
  // void EdgeDetection();
  // void NonMaxSuppressin();
  // void Hystersis(float lowThreshold, float hightThresold);
private:
  const int size = 3;
};
class FillTool : public DrawTool{
public:
  FillTool(ColorData* toolColor, int height, int width);
  ~FillTool();
  void paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer);
  void applyInfluence(int x, int y, PixelBuffer* buffer);
  void fillInfluence();
private:
  bool compareColorData(ColorData x, ColorData y);
};
class FMotionBlur : public FBlur{
public:
  FMotionBlur();
  ~FMotionBlur();
  std::string getName();
  kernelType buildKernel(int radius);
private:
  enum MotionBlurDirections {
    DIR_N_S,
    DIR_E_W,
    DIR_NE_SW,
    DIR_NW_SE
  };
};
class FQuantize : public Filter{
public:
  FQuantize();
  ~FQuantize();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
private:
};
class FSaturation : public Filter{
public:
  FSaturation();
  ~FSaturation();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};
class FSharpen : public FBlur{
public:
  FSharpen();
  ~FSharpen();
  std::string getName();
  kernelType buildKernel(int radius);
private:
  const int size = 3;
  const float DEFAULT_FACTOR = 100.0;
};
class FSpecial : public Filter{
public:
  FSpecial();
  ~FSpecial();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};
class FThreshold : public Filter{
public:
  FThreshold();
  ~FThreshold();
  void applyFilter(PixelBuffer* imageBuffer);
  std::string getName();
};
class Highlighter : public DrawTool {
 public:
  Highlighter(ColorData* toolColor, int width, int height);
  ~Highlighter();
  void fillInfluence();
  void applyInfluence(int x, int y, PixelBuffer* buffer);
};
class ImageHandler{
public :
  ImageHandler();
  ~ImageHandler();
  PixelBuffer* loadimage(const std::string & filename, int &height, int &width, ColorData backgroundColor);
  void saveimage(const std::string & filename, PixelBuffer *buffer);
private :
  bool isjpeg(const std::string & name);
  bool ispng(const std::string & name);
  bool isValidImageFileName(const std::string & name);
  bool isValidFile(const std::string & name);
  bool hasSuffix(const std::string & str, const std::string & suffix);
  void savepng(FILE* file, int height, int width, PixelBuffer *buffer);
  void savejpg(FILE* infile, int height, int width, PixelBuffer *buffer);
  PixelBuffer* loadpng(FILE *fp, int &height, int &width, ColorData backgroundColor);
  PixelBuffer* loadjpg(FILE *infile, int &height, int &width, ColorData backgroundColor);
};
class Pen : public DrawTool {
 public:
  Pen(ColorData* toolColor, int radius);
  ~Pen();
  void fillInfluence();
};
class SprayCan : public DrawTool{
 public :
  SprayCan(ColorData* toolColor, int radius);
  ~SprayCan();
  void fillInfluence();
  void paint(int x, int y, int prevX, int prevY, PixelBuffer* buffer);
};

class Stamp : public DrawTool {
 public :
  Stamp(PixelBuffer* newBuffer, int stampWidth, int stampHeight);
  ~Stamp();
  void fillInfluence();
  void applyInfluence(int x, int y, PixelBuffer* buffer);
};
class WaterColor : public DrawTool {
 public :
  WaterColor(ColorData* toolColor, int radius);
  ~WaterColor();
  void fillInfluence();
};








#endif
