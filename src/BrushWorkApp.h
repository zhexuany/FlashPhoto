//
//  BrushWorkApp.h
//  Originally created by the CSci-3081W TAs.
//


#ifndef BRUSHWORKAPP_H
#define BRUSHWORKAPP_H

#include "BaseGfxApp.h"
#include "Pen.h"
#include "Eraser.h"
#include "SprayCan.h"
#include "CalligraphyPen.h"
#include "Highlighter.h"
#include "WaterColor.h"
#include "FillTool.h"
#include "Crayon.h"
class PixelBuffer;
class DrawTool;
class ColorData;

/** This is the main class for BrushWork.  It is a graphics app that derives from BaseGfxApp.
    It creates two graphics windows, one for 2D painting and one for the buttons and other
    UI widgets to control the brushes.
*/
class BrushWorkApp : public BaseGfxApp{
public:

    BrushWorkApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~BrushWorkApp();

    // Glut overrided function
    void mouseDragged(int x, int y) ;
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display();
    void gluiControl(int controlID);


private:

    // GLUI INTERFACE ELEMENTS
    enum UIControlType{
        UI_TOOLTYPE,
        UI_COLOR_R,
        UI_COLOR_G,
        UI_COLOR_B,
        UI_PRESET_RED,
        UI_PRESET_ORANGE,
        UI_PRESET_YELLOW,
        UI_PRESET_GREEN,
        UI_PRESET_BLUE,
        UI_PRESET_PURPLE,
        UI_PRESET_WHITE,
        UI_PRESET_BLACK,
        UI_CLEAR,
        UI_QUIT
    };

    // BrushWork-specific functions
    void initGlui();
    void initGraphics();
    void initDrawTool();
    void initializeBuffers(ColorData initialColor, int width, int height);
    void updateCurrentTool();
    void clearPixelBuffer();
    // This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;
    DrawTool* m_tool;
    DrawTool** toolList;
    //Stores previous x and y positions
    int m_prevX;
    int m_prevY;
    // These are used to store the selections from the GLUI user interface
    int m_curTool;

    float m_curColorRed, m_curColorGreen, m_curColorBlue;
    GLUI_Spinner *m_spinnerR;
    GLUI_Spinner *m_spinnerG;
    GLUI_Spinner *m_spinnerB;

    // const int value use for switch current tool
    enum ToolType{
      PEN,
      ERASER,
      SPRAYCAN,
      CALIGRAPHYPEN,
      HIGHLIGHTER,
      WATERCOLOR,
      FILLTOOL,
      CRAYON
  };
};

#endif
