//
//  FlashPhotoApp.h
//  Originally created by the CSci-3081W TAs.
//

#ifndef FLASHPHOTOAPP_H
#define FLASHPHOTOAPP_H

#include "libphoto.h"
#include "libphotogui.h"
#include <cmath>
#include <iostream>

#include <deque>

class PixelBuffer;
class ColorData;

class FlashPhotoApp : public BaseGfxApp {
public:

    FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~FlashPhotoApp();

    void mouseDragged(int x, int y) ;
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display();
    void gluiControl(int controlID);

private:
    // GLUI INTERFACE ELEMENTS
    enum UIControlType {
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
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_LOAD_STAMP_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_BLUR,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_DITHER,
        UI_APPLY_SATURATE,
        UI_APPLY_CHANNEL,
        UI_APPLY_QUANTIZE,
        UI_APPLY_MOTION_BLUR,
        UI_APPLY_SPECIAL_FILTER,
        UI_UNDO,
        UI_REDO,
        UI_CLEAR,
        UI_QUIT
    };
    void setImageFile(const std::string & filepath);
    bool isValidImageFileName(const std::string & name);
    bool isValidImageFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    void loadStampEnabled(bool enabled);
    void updateColors();
    // function for load picture files
    void initDrawTool();
    void initFilter();
    void updateCurrentTool();
    void loadImageToCanvas();
    void loadImageToStamp();
    void saveCanvasToFile();

    // function for filter operation
    void applyFilterBlur();
    void applyFilterSharpen();
    void applyFilterMotionBlur();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterChannel();
    void applyFilterSaturate();
    void applyFilterQuantize();
    void applyFilterSpecial();

    // function for redo/undo operation
    void undoOperation();
    void redoOperation();

    void updateCanvas(std::deque<PixelBuffer*> &alpha, std::deque<PixelBuffer*> &beta, bool isUndo);

    void initGlui();
    void initGraphics();
    void initializeBuffers(ColorData initialColor, int width, int height);

    enum UIMotionBlurDirections {
        DIR_N_S,
        DIR_E_W,
        DIR_NE_SW,
        DIR_NW_SE
    };

    struct {
        float channel_colorRed;
        float channel_colorGreen;
        float channel_colorBlue;
        float saturation_amount;
        float threshold_amount;
        float blur_amount;
        float sharpen_amount;
        float motionBlur_amount;
        int motionBlur_direction;
        int quantize_bins;
    } m_filterParameters;

    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *loadStampButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;
        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;

        GLUI_Spinner *spinnerRed;
        GLUI_Spinner *spinnerGreen;
        GLUI_Spinner *spinnerBlue;
    } m_gluiControlHooks;

	///The size of the undo queue
    int m_queueSize;
    std::deque<PixelBuffer*> undoQueue;
    std::deque<PixelBuffer*> redoQueue;
    //TODO move isjpeg function into ImageHandler function.
    bool isjpeg(const std::string & name);
    int loadpng(FILE *fp);
    void clearPixelBuffer();
    ///Stores previously clicked x position for comparing mouse movement
    int m_prevX;
	///Stores previously clicked y position for comparing mouse movement
	int m_prevY;
    ///Stores stamp image's height
    int m_stampHeight;
    ///Stores stamp image's width
    int m_stampWidth;
    // This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;
    void updateUndo();

    ///These are used to store the selections from the GLUI user interface
    DrawTool** toolList;
	///The current tool selected by the user
    DrawTool* m_tool;
	///Callback value for user tool selection
    int m_curTool;
    Filter** m_filters;
	///Callback value for user filter selection
    int m_curFilter;
	float m_curColorRed, m_curColorGreen, m_curColorBlue;
    std::string m_fileName;
    // const int value use for switch current tool
    enum ToolType{
      PEN,
      ERASER,
      SPRAYCAN,
      CALIGRAPHYPEN,
      HIGHLIGHTER,
      WATERCOLOR,
      FILLTOOL,
      CRAYON,
      STAMP,
      BLUR
    };
};


#endif
