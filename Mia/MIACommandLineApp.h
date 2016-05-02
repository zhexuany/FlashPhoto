#ifndef MIACOMMANDLINEAPP_H
#define MIACOMMANDLINEAPP_H
#include "MIAApp.h"
#include "libphoto.h"
using std::string;
using std::vector;
class MIACommandLineApp {
public:
  MIACommandLineApp();
  ~MIACommandLineApp();
  PixelBuffer* readFile(string file){
    int height, width;
    if(m_buffer != nullptr)
    delete m_buffer;
    m_buffer = m_loader -> loadimage(file, height, width, ColorData());
    return m_buffer;
  }

  void writeFile(string file){
    m_loader -> saveimage(file, m_buffer);
  }

  void handleEdgeDetect();
  void handleBlur(float parameter);
  void handleSatur(float parameter);
  void handleThresh(float parameter);
  void handleSharpen(int parameter);
  int handleCompare(string input, string ouput);
  void handleMultgb(ColorData color);
  void handleQuant(int parameter);
private:
  PixelBuffer* m_buffer;
  ImageHandler* m_loader;

};


#endif // MIACOMMANDLINEAPP_H
