//
//  BrushWorkApp.cpp
//  Originally created by the CSci-3081W TAs.
//


#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;
BrushWorkApp::BrushWorkApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) :
    BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50) {
    // Set the name of the window
    setCaption("BrushWork");

    // Initialize Interface
    initializeBuffers(backgroundColor, width, height);
    // Initialize drawTools
    initDrawTool();
    initGlui();
    initGraphics();
}
void BrushWorkApp::initDrawTool(){
  toolList = new DrawTool*[8];
  ColorData* color = new ColorData(0,0,0);
  m_tool = new DrawTool(color, 0, 0);
  toolList[0] = new Pen(color, 3);
  toolList[1] = new Eraser(21);
  toolList[2] = new SprayCan(color, 41);
  toolList[3] = new CalligraphyPen(color, 5, 15);
  toolList[4] = new Highlighter(color, 5, 15);
  toolList[5] = new WaterColor(color, 31);
  toolList[6] = new FillTool(color, m_width, m_height);
  m_tool = toolList[0];
}
void BrushWorkApp::display() {
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
    int err;
    if ((err = glGetError()) != GL_NO_ERROR) {
      cerr << "GL is in an error state after call to glDrawPixels()" << endl;
      cerr << "(GL error code " << err << ")\n";
    }
}

void BrushWorkApp::updateCurrentTool() {
    ColorData* toolColor = new ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue);
    switch (m_curTool) {
      case PEN: {
        m_tool = toolList[0];
        m_tool -> setToolColor(toolColor);
        break;
      }
      case ERASER: {
        m_tool = toolList[1];
        m_tool -> setToolColor(toolColor);
        break;
      }
      case SPRAYCAN: {
        m_tool = toolList[2];
        m_tool -> setToolColor(toolColor);
        break;
      }
      case CALIGRAPHYPEN: {
        m_tool = toolList[3];
        m_tool -> setToolColor(toolColor);
        break;
      }
      case HIGHLIGHTER: {
        m_tool = toolList[4];
        m_tool -> setToolColor(toolColor);
        break;
      }
      case WATERCOLOR:{
        m_tool = toolList[5];
        m_tool -> setToolColor(toolColor);
        break;
      }
      case FILLTOOL:{
	    m_tool = toolList[6];
	    m_tool -> setToolColor(toolColor);
        break;
      }
    }
    if (toolColor) delete toolColor;
}


BrushWorkApp::~BrushWorkApp() {
    if (m_displayBuffer) {
        delete m_displayBuffer;
    }
    if(m_tool) delete m_tool;
    for(int i = 0; i < 6; i++){
      if(toolList[i]){
        delete toolList[i];
      }
    }
    if(toolList) delete toolList;
}


void BrushWorkApp::mouseDragged(int x, int y) {
    if (m_tool -> allowDrag) {
        m_tool -> paint(x, y, m_prevX, m_prevY, m_displayBuffer);
        m_prevX = x;
        m_prevY = y;
    }
    //std::cout << "mouseDragged " << x << " " << y << std::endl;
}

void BrushWorkApp::mouseMoved(int x, int y) {
    if(m_drag){
      mouseDragged(x, y);
    }
}

void BrushWorkApp::leftMouseDown(int x, int y) {
    m_prevX = x;
    m_prevY = y;
    m_tool -> paint(x, y, m_prevX, m_prevY, m_displayBuffer);
    //std::cout << "mousePressed " << x << " " << y << std::endl;
    m_drag = true;
}

void BrushWorkApp::leftMouseUp(int x, int y) {
  //std::cout << "mouseReleased " << x << " " << y << std::endl;
    m_drag = false;
}

void BrushWorkApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
}

void BrushWorkApp::initGlui() {
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);

    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "WaterColor Brush");
    new GLUI_RadioButton(radio, "Fill Tool");

    GLUI_Panel *colPanel = new GLUI_Panel(m_glui, "Tool Color");

    m_curColorRed = 0;
    m_spinnerR  = new GLUI_Spinner(colPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
    m_spinnerR->set_float_limits(0, 1.0);

    m_curColorGreen = 0;
    m_spinnerG  = new GLUI_Spinner(colPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
    m_spinnerG->set_float_limits(0, 1.0);

    m_curColorBlue = 0;
    m_spinnerB  = new GLUI_Spinner(colPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
    m_spinnerB->set_float_limits(0, 1.0);
    new GLUI_Button(colPanel, "Red", UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(colPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
    new GLUI_Button(colPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
    new GLUI_Button(colPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
    new GLUI_Button(colPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
    new GLUI_Button(colPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
    new GLUI_Button(colPanel, "White", UI_PRESET_WHITE, s_gluicallback);
    new GLUI_Button(colPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
    new GLUI_Button(m_glui, "Clear", UI_CLEAR, s_gluicallback);
    new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
}


void BrushWorkApp::initGraphics() {
    // Initialize OpenGL for 2D graphics as used in the BrushWork app
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, m_width, 0, m_height);
    glViewport(0, 0, m_width, m_height);
}


// catch mouse change color option in panel
void BrushWorkApp::gluiControl(int controlID) {
    switch (controlID) {
        case UI_PRESET_RED:
            m_curColorRed = 1;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            break;
        case UI_PRESET_ORANGE:
            m_curColorRed = 1;
            m_curColorGreen = 0.5;
            m_curColorBlue = 0;
            break;
        case UI_PRESET_YELLOW:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            break;
        case UI_PRESET_GREEN:
            m_curColorRed = 0;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            break;
        case UI_PRESET_BLUE:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            break;
        case UI_PRESET_PURPLE:
            m_curColorRed = 0.5;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            break;
        case UI_PRESET_WHITE:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 1;
            break;
        case UI_PRESET_BLACK:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            break;
        //Case UI_TOOLTYPE is the case define in UIControlType, selected tool resides in m_curTool
        case UI_TOOLTYPE:
            updateCurrentTool();
            break;
        case UI_CLEAR:
            clearPixelBuffer();
            break;
        default:
            break;
    }

    m_spinnerB->set_float_val(m_curColorBlue);
    m_spinnerG->set_float_val(m_curColorGreen);
    m_spinnerR->set_float_val(m_curColorRed);
    
    ColorData* toolColor = new ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue);
    m_tool -> setToolColor(toolColor);
}

void BrushWorkApp::clearPixelBuffer() {
    m_displayBuffer -> fillPixelBufferWithColor(m_displayBuffer -> getBackgroundColor());
}
