#ifdef CALIGRAPHYPEN_H
#define CALIGRAPHYPEN_H
#include "Drawtool.h"

class CaligraphyPen : public DrawTool {
 public :
  CaligraphyPen(ColorData* toolColor, int height, int width);
  ~CaligraphyPen();
  virtual void fillInfluence();
}
#endif // CALIGRAPHYPEN_H
