//
//  MIAApp.h
//  Originally created by the CSci-3081W TAs.
//  Modified by Juhwan Park
//


#ifndef MIAAPP_H
#define MIAAPP_H

#include "libphoto.h"
#include "libphotogui.h"
#include <iostream>
#include <cmath>
#include <deque>

class ColorData;
class PixelBuffer;

class MIAApp : public BaseGfxApp {
public:
    MIAApp(int argc, char* argv[]);
    MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~MIAApp();

    // Glut overrided function
    void mouseDragged(int x, int y) ;
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display();
    void gluiControl(int controlID);

    // Commandline mode functions
    PixelBuffer* c_loadImage(const std::string & fileName);
    void c_saveToFile(const std::string & fileName, PixelBuffer* imageBuffer);
    bool c_isValidImageFile(const std::string & name);
    std::string c_getImageNamePlusSeqOffset(const std::string & currentFileName, int offset);

    void c_applyFilterEdgeDetect(PixelBuffer* imageBuffer);
    void c_applyFilterSharpen(PixelBuffer* imageBuffer, int amount);
    void c_applyFilterThreshold(PixelBuffer* imageBuffer, double amount);
    void c_applyFilterMultiplyRGB(PixelBuffer* imageBuffer, double r, double g, double b);
    void c_applyFilterBlur(PixelBuffer* imageBuffer, double amount);
    void c_applyFilterQuantize(PixelBuffer* imageBuffer, int amount);
    void c_applyFilterSaturate(PixelBuffer* imageBuffer, double amount);

private:

    // GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_NEXT_IMAGE_BUTTON,
        UI_PREVIOUS_IMAGE_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_GRAYSCALE,
        UI_APPLY_MULTIPLY_RGB,
        UI_APPLY_QUANTIZE,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };
    void setImageFile(const std::string & filepath);
    bool isValidImageFileName(const std::string & name);
    bool isValidImageFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    std::string getImageNamePlusSeqOffset(const std::string & currentFileName, int offset);
    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    void previousImageEnabled(bool enabled);
    void nextImageEnabled(bool enabled);


    void initDrawTool();
    void initFilter();
    void updateCurrentTool();

    void loadImageToCanvas();
    void saveCanvasToFile();
    void loadNextImage();
    void loadPreviousImage();

    void applyFilterSharpen();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterMultiplyRGB();
    void applyFilterGrayScale();
    void applyFilterQuantize();

    void undoOperation();
    void redoOperation();

    void updateCanvas(std::deque<PixelBuffer*> &alpha, std::deque<PixelBuffer*> &beta, bool isUndo);


    void initGlui();
    void initGraphics();
    void initializeBuffers(ColorData initialColor, int width, int height);


    struct {
        float multiply_colorRed;
        float multiply_colorGreen;
        float multiply_colorBlue;
        float threshold_amount;
        float sharpen_amount;
        int quantize_bins;
    } m_filterParameters;

    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button* nextImageButton;
        GLUI_Button* previousImageButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;

        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;




    } m_gluiControlHooks;
    int m_queueSize;
    std::deque<PixelBuffer*> undoQueue;
    std::deque<PixelBuffer*> redoQueue;
    //TODO move isjpeg function into ImageHandler function.
    bool isjpeg(const std::string & name);
    int loadpng(FILE *fp);

    //Stores previous x and y positions
    int m_prevX;
    int m_prevY;
    //Stroes stamp image's height and width
    int m_stampHeight;
    int m_stampWidth;


    // This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;
    void updateUndo();

    // These are used to store the selections from the GLUI user interface
    DrawTool** toolList;
    DrawTool* m_tool;
    int m_curTool;
    Filter** m_filters;
    int m_curFilter;

    std::string m_fileName;
    std::string m_nextFileName;
    std::string m_prevFileName;

    enum ToolType{
      PEN,
      ARROW
    };
};


#endif
