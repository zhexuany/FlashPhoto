#include "FlashPhotoApp.h"
using std::cout;
using std::endl;

FlashPhotoApp::FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    // Set the name of the window
    setCaption("FlashPhoto");

    // Initialize Interface
    initializeBuffers(backgroundColor, width, height);

    initGlui();
    initGraphics();
    initDrawTool();
    initFilter();
    m_queueSize = 10;
}

/*
* \Initialize the filter on load
* \none
* \void
*/
void FlashPhotoApp::initFilter(){
  m_filters = new Filter* [FilterFactory::getNumFilters()];
  for(int i = 0; i < FilterFactory::getNumFilters(); i++){
    m_filters[i] = FilterFactory::createFilter(i);
  }
}
/*
* \Initialize the draw tool on load
* \none
* \void
*/
void FlashPhotoApp::initDrawTool(){
  toolList = new DrawTool*[9];
  ColorData* color = new ColorData(0,0,0);
  PixelBuffer* init = new PixelBuffer(0,0, *color);
  m_tool = new DrawTool(color, 0, 0);
  toolList[0] = new Pen(color, 3);
  toolList[1] = new Eraser(21);
  toolList[2] = new SprayCan(color, 41);
  toolList[3] = new CalligraphyPen(color, 5, 15);
  toolList[4] = new Highlighter(color, 5, 15);
  toolList[5] = new WaterColor(color, 31);
  toolList[6] = new FillTool(color, m_width, m_height);
  toolList[7] = new Crayon(color, 20);
  toolList[8] = new Stamp(init, 0, 0);
  m_tool = toolList[0];
}


/*
* Update the current tool that is selected in the UI (stored in m_curTool)
* \none
* \void
*/
void FlashPhotoApp::updateCurrentTool() {
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
      case CRAYON:{
      m_tool = toolList[7];
      m_tool -> setToolColor(toolColor);
        break;
      }
      case STAMP:{
      m_tool = toolList[8];
        break;
      }
    }
    if (toolColor) delete toolColor;
}

void FlashPhotoApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

FlashPhotoApp::~FlashPhotoApp()
{
    if (m_displayBuffer) {
        delete m_displayBuffer;
    }
    if(m_tool) delete m_tool;
    for(int i = 0; i < 9; i++){
      if(toolList[i]){
        delete toolList[i];
      }
    }
    if(toolList) delete toolList;
}


void FlashPhotoApp::mouseDragged(int x, int y)
{
    if (m_tool -> allowDrag) {
        m_tool -> paint(x, y, m_prevX, m_prevY, m_displayBuffer);
        m_prevX = x;
        m_prevY = y;
    }
}

void FlashPhotoApp::mouseMoved(int x, int y)
{
    if(m_drag){
      mouseDragged(x, y);
    }
}

void FlashPhotoApp::leftMouseDown(int x, int y)
{
    updateUndo();
    m_prevX = x;
    m_prevY = y;
    m_tool -> paint(x, y, m_prevX, m_prevY, m_displayBuffer);
    //std::cout << "mousePressed " << x << " " << y << std::endl;
    m_drag = true;
}

void FlashPhotoApp::updateUndo() {
    //Enable undo and disable redo
    undoEnabled(true);
    redoEnabled(false);

    //Clear the redo stack
    std::stack<PixelBuffer*> empty;
    std::swap(redoQueue, empty);

    //Make a copy and save the current buffer
    PixelBuffer *newBuffer = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
    newBuffer->copyPixelBuffer(m_displayBuffer, newBuffer);
    undoQueue.push(newBuffer);
}

void FlashPhotoApp::leftMouseUp(int x, int y)
{
    m_drag = false;
}

/*
* \Clear the pixel buffer back to the default buffer color
* \none
* \void
*/
void FlashPhotoApp::clearPixelBuffer() {
    ColorData newBackground = m_displayBuffer -> getDefaultBackgroundColor();
    m_displayBuffer -> fillPixelBufferWithColor(newBackground);
    m_displayBuffer -> setBackgroundColor(&newBackground);
}


void FlashPhotoApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
}

void FlashPhotoApp::initGlui(){
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
        new GLUI_RadioButton(radio, "Eraser");
        new GLUI_RadioButton(radio, "Spray Can");
        new GLUI_RadioButton(radio, "Caligraphy Pen");
        new GLUI_RadioButton(radio, "Highlighter");
        new GLUI_RadioButton(radio, "WaterColor Brush");
        new GLUI_RadioButton(radio, "Fill Tool");
        new GLUI_RadioButton(radio, "Crayon");
        new GLUI_RadioButton(radio, "Stamp");
        new GLUI_RadioButton(radio, "Blur");
    }

    GLUI_Panel *colorPanel = new GLUI_Panel(m_glui, "Tool Color");
    {
        m_curColorRed = 0;
        m_gluiControlHooks.spinnerRed  = new GLUI_Spinner(colorPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
        m_gluiControlHooks.spinnerRed->set_float_limits(0, 1.0);

        m_curColorGreen = 0;
        m_gluiControlHooks.spinnerGreen  = new GLUI_Spinner(colorPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
        m_gluiControlHooks.spinnerGreen->set_float_limits(0, 1.0);

        m_curColorBlue = 0;
        m_gluiControlHooks.spinnerBlue  = new GLUI_Spinner(colorPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
        m_gluiControlHooks.spinnerBlue->set_float_limits(0, 1.0);

        new GLUI_Button(colorPanel, "Red", UI_PRESET_RED, s_gluicallback);
        new GLUI_Button(colorPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
        new GLUI_Button(colorPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
        new GLUI_Button(colorPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
        new GLUI_Button(colorPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
        new GLUI_Button(colorPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
        new GLUI_Button(colorPanel, "White", UI_PRESET_WHITE, s_gluicallback);
        new GLUI_Button(colorPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
    }

    // UNDO,REDO,QUIT
    {
        m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
        undoEnabled(false);
        m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
        redoEnabled(false);
        new GLUI_Button(m_glui, "Clear", UI_CLEAR, s_gluicallback);
        new GLUI_Separator(m_glui);
        new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
    }

    new GLUI_Column(m_glui, true);
    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *blurPanel = new GLUI_Panel(filterPanel, "Blur");
        {
            GLUI_Spinner * filterBlurAmount = new GLUI_Spinner(blurPanel, "Amount:", &m_filterParameters.blur_amount);
            filterBlurAmount->set_int_limits(0, 20);

            filterBlurAmount->set_int_val(5);

            new GLUI_Button(blurPanel, "Apply", UI_APPLY_BLUR, s_gluicallback);
        }

        GLUI_Panel *motionBlurPanel = new GLUI_Panel(filterPanel, "MotionBlur");
        {
            GLUI_Spinner * filterMotionBlurAmount = new GLUI_Spinner(motionBlurPanel, "Amount:", &m_filterParameters.motionBlur_amount);
            filterMotionBlurAmount->set_int_limits(0, 100);

            filterMotionBlurAmount->set_int_val(5);

            m_filterParameters.motionBlur_direction = 0;
            GLUI_RadioGroup *dirBlur = new GLUI_RadioGroup(motionBlurPanel, &m_filterParameters.motionBlur_direction);
            new GLUI_RadioButton(dirBlur, "North/South");
            new GLUI_RadioButton(dirBlur, "East/West");
            new GLUI_RadioButton(dirBlur, "NorthEawwst/SouthWest");
            new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");

            new GLUI_Button(motionBlurPanel, "Apply", UI_APPLY_MOTION_BLUR, s_gluicallback);
        }
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(0, 100);

            filterSharpAmount->set_int_val(5);

            new GLUI_Button(sharpenPanel, "Apply", UI_APPLY_SHARP, s_gluicallback);
        }
        GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");

        {
            new GLUI_Button(edgeDetPanel, "Apply", UI_APPLY_EDGE, s_gluicallback);
        }
        GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
        {
            GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel, "Level:", &m_filterParameters.threshold_amount);
            filterThresholdAmount->set_float_limits(0, 1);
            filterThresholdAmount->set_float_val(0.5);

            new GLUI_Button(thresPanel, "Apply", UI_APPLY_THRESHOLD, s_gluicallback);
        }

		new GLUI_Column(filterPanel, true);

        GLUI_Panel *saturPanel = new GLUI_Panel(filterPanel, "Saturation");
        {
            GLUI_Spinner * filterSaturationAmount = new GLUI_Spinner(saturPanel, "Amount:", &m_filterParameters.saturation_amount);
            filterSaturationAmount->set_float_limits(-10, 10);
            filterSaturationAmount->set_float_val(1);

            new GLUI_Button(saturPanel, "Apply", UI_APPLY_SATURATE, s_gluicallback);
        }

        GLUI_Panel *channelPanel = new GLUI_Panel(filterPanel, "Channels");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(channelPanel, "Red:", &m_filterParameters.channel_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(channelPanel, "Green:", &m_filterParameters.channel_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(channelPanel, "Blue:", &m_filterParameters.channel_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(channelPanel, "Apply", UI_APPLY_CHANNEL, s_gluicallback);
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }

        GLUI_Panel *specialFilterPanel = new GLUI_Panel(filterPanel, "Special Filter"); // YOUR SPECIAL FILTER PANEL
        {
            new GLUI_Button(specialFilterPanel, "Apply", UI_APPLY_SPECIAL_FILTER, s_gluicallback);
        }
    }

    new GLUI_Column(m_glui, true);

    GLUI_Panel *imagePanel = new GLUI_Panel(m_glui, "Image I/O");
    {
        m_gluiControlHooks.fileBrowser = new GLUI_FileBrowser(imagePanel, "Choose Image", false, UI_FILE_BROWSER, s_gluicallback);

        m_gluiControlHooks.fileBrowser->set_h(400);

        m_gluiControlHooks.fileNameBox = new     GLUI_EditText( imagePanel , "Image:", m_fileName, UI_FILE_NAME, s_gluicallback );
        m_gluiControlHooks.fileNameBox->set_w(200);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.currentFileLabel = new GLUI_StaticText(imagePanel, "Will load image: none");
        m_gluiControlHooks.loadCanvasButton = new GLUI_Button(imagePanel, "Load Canvas", UI_LOAD_CANVAS_BUTTON, s_gluicallback);
        m_gluiControlHooks.loadStampButton = new GLUI_Button(imagePanel, "Load Stamp", UI_LOAD_STAMP_BUTTON, s_gluicallback);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);

        loadCanvasEnabled(false);
        loadStampEnabled(false);
        saveCanvasEnabled(false);
    }
    return;
}

void FlashPhotoApp::gluiControl(int controlID)
{
    switch (controlID) {
        case UI_PRESET_RED:
            m_curColorRed = 1;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_ORANGE:
            m_curColorRed = 1;
            m_curColorGreen = 0.5;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_YELLOW:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_GREEN:
            m_curColorRed = 0;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_BLUE:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_PURPLE:
            m_curColorRed = 0.5;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_WHITE:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_BLACK:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_APPLY_BLUR:
            applyFilterBlur();
            break;
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_MOTION_BLUR:
            applyFilterMotionBlur();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_DITHER:
            applyFilterThreshold();
            break;
        case UI_APPLY_SATURATE:
            applyFilterSaturate();
            break;
        case UI_APPLY_CHANNEL:
            applyFilterChannel();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_APPLY_SPECIAL_FILTER:
            applyFilterSpecial();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_LOAD_STAMP_BUTTON:
            loadImageToStamp();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_FILE_NAME:
            setImageFile(m_fileName);
            break;
        case UI_UNDO:
            undoOperation();
            break;
        case UI_REDO:
            redoOperation();
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

    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();

    ColorData* toolColor = new ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue);
    m_tool -> setToolColor(toolColor);
}

// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how FlashPhotoApp should respond to the
// button presses.

/*
* \Load an image on to the canvas
* \none
* \void
*/
void FlashPhotoApp::loadImageToCanvas()
{
    updateUndo();
    cout << "Load Canvas has been clicked for file " << m_fileName << endl;
    ImageHandler *loader = new ImageHandler();

    //Pass in height and width by reference so we can resize the window after
    int Height, Width;
    PixelBuffer *newBuffer = loader->loadimage(m_fileName, Height, Width);
    setWindowDimensions(Width, Height);

    std::cout << Width << Height << "\n";
    //Reset the display buffer size so we can use copyPixelBuffer
    initializeBuffers(m_displayBuffer->getBackgroundColor(), Width, Height);
    m_displayBuffer->copyPixelBuffer(newBuffer, m_displayBuffer);
    //m_displayBuffer = newBuffer;
}

void FlashPhotoApp::loadImageToStamp()
{
    cout << "Load Stamp has been clicked for file " << m_fileName << endl;
    ImageHandler *loader = new ImageHandler();
    int Height, Width;
    // Deleting previous stamp tool.
    if (toolList[8]) {
        delete toolList[8];
    }
    PixelBuffer *newBuffer = loader->loadimage(m_fileName, Height, Width);
    m_stampHeight = Height;
    m_stampWidth = Width;
    // Creating new stamp based on new image on newBuffer
    // and re-assign it to m_tool, so it doesn't have to click on stamp button again.
    toolList[8] = new Stamp(newBuffer, m_stampWidth, m_stampHeight);
    m_tool = toolList[8];
}

/*
* \Save a canvas to file
* \none
* \void
*/
void FlashPhotoApp::saveCanvasToFile()
{
    cout << "Save Canvas been clicked for file " << m_fileName << endl;
    ImageHandler *loader = new ImageHandler();
    loader->saveimage(m_fileName, m_displayBuffer -> getHeight(), m_displayBuffer -> getWidth(), m_displayBuffer);
}

void FlashPhotoApp::applyFilterThreshold(){
    cout << "Apply has been clicked for Threshold has been clicked with amount =" << m_filterParameters.threshold_amount << endl;
    updateUndo();
    m_filters[FilterFactory::FILTER_THRESHOLD] -> setFilterParameter(m_filterParameters.threshold_amount);
    m_filters[FilterFactory::FILTER_THRESHOLD] -> applyFilter(m_displayBuffer);
}

void FlashPhotoApp::applyFilterChannel()
{
    cout << "Apply has been clicked for Channels with red = " << m_filterParameters.channel_colorRed
    << ", green = " << m_filterParameters.channel_colorGreen
    << ", blue = " << m_filterParameters.channel_colorBlue << endl;
    m_filters[FilterFactory::FILTER_CHANNEL]
      -> setFilterParameter(ColorData(m_filterParameters.channel_colorRed,
                                      m_filterParameters.channel_colorGreen,
                                      m_filterParameters.channel_colorBlue));
    updateUndo();
    m_filters[FilterFactory::FILTER_CHANNEL] -> applyFilter(m_displayBuffer);
}

void FlashPhotoApp::applyFilterSaturate()
{
    cout << "Apply has been clicked for Saturate with amount = " << m_filterParameters.saturation_amount << endl;
    m_filters[FilterFactory::FILTER_SATURATION] -> setFilterParameter(m_filterParameters.saturation_amount);
    updateUndo();
    m_filters[FilterFactory::FILTER_SATURATION] -> applyFilter(m_displayBuffer);
}

void FlashPhotoApp::applyFilterBlur()
{
    cout << "Apply has been clicked for Blur with amount = " << m_filterParameters.blur_amount << endl;
}

void FlashPhotoApp::applyFilterSharpen()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
}

void FlashPhotoApp::applyFilterMotionBlur()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.motionBlur_amount
    << " and direction " << m_filterParameters.motionBlur_direction << endl;
}

void FlashPhotoApp::applyFilterEdgeDetect() {
    cout << "Apply has been clicked for Edge Detect" << endl;
}

void FlashPhotoApp::applyFilterQuantize() {
    cout << "Apply has been clicked for Quantize with bins = " << m_filterParameters.quantize_bins << endl;
    m_filters[FilterFactory::FILTER_QUANTIZE] -> setFilterParameter((float) m_filterParameters.quantize_bins);
    updateUndo();
    m_filters[FilterFactory::FILTER_QUANTIZE] -> applyFilter(m_displayBuffer);
}

void FlashPhotoApp::applyFilterSpecial() {
    cout << "Apply has been clicked for Special" << endl;
}

void FlashPhotoApp::undoOperation()
{
    cout << "Undoing..." << endl;
    updateCanvas(undoQueue, redoQueue, true);
}

void FlashPhotoApp::redoOperation()
{
    cout << "Redoing..." << endl;
    updateCanvas(redoQueue, undoQueue, false);
}

/*
*Update the canvas with the top of the alpha stack, push current buffer onto beta stack
*stack to pop from, stack to push to, if it is an undo
*void
*TODO: there is currently no size limiting on the queue, I have not run into
*issues with size so far but it could be an issue in the future.
*/
void FlashPhotoApp::updateCanvas(std::stack<PixelBuffer*> &alpha, std::stack<PixelBuffer*> &beta, bool isUndo) {
    if (alpha.size() > 0) {
        //Save beta history
        PixelBuffer *betaBuffer = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
        betaBuffer->copyPixelBuffer(m_displayBuffer, betaBuffer);
        beta.push(betaBuffer);

        //Update pixel buffer with alpha buffer
        PixelBuffer *newBuffer = alpha.top();
        alpha.pop();
        int height = newBuffer->getHeight();
        int width = newBuffer->getWidth();
        if (height != m_displayBuffer->getHeight() || width != m_displayBuffer->getWidth()) {
            initializeBuffers(newBuffer->getBackgroundColor(),width, height);
            setWindowDimensions(width, height);
        }
        m_displayBuffer->copyPixelBuffer(newBuffer, m_displayBuffer);
        delete newBuffer;
    }
    if (isUndo) {
        redoEnabled(true);
    } else {
        undoEnabled(true);
    }
    //incase size is 0 after the pop
    //that's why we don't use else here
    if (alpha.size() == 0) {
        if (isUndo) {
            undoEnabled(false);
        } else {
            redoEnabled(false);
        }
    }
}
// ** END OF CALLBACKS **
// **********************


// **********************
// Provided code for managing the
// GLUI interface.

void FlashPhotoApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void FlashPhotoApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void FlashPhotoApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void FlashPhotoApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void FlashPhotoApp::loadStampEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadStampButton, enabled);
}

void FlashPhotoApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void FlashPhotoApp::updateColors() {
    m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
    m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
    m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
}

bool FlashPhotoApp::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}


bool FlashPhotoApp::isValidImageFileName(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool FlashPhotoApp::isValidImageFile(const std::string & name) {

    FILE *f;
    bool isValid = false;
    if (isValidImageFileName(name)) {
        if ((f = fopen( name.c_str(), "r"))) {
            isValid = true;
            fclose(f);
        }
    }
    return isValid;
}

bool FlashPhotoApp::isjpeg(const std::string & name) {
        if (hasSuffix(name, ".jpg")|| hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}



void FlashPhotoApp::setImageFile(const std::string & fileName)
{
    // If a directory was selected
    // instead of a file, use the
    // latest file typed or selected.
    std::string imageFile = fileName;
    if (!isValidImageFileName(imageFile)) {
        imageFile = m_fileName;
    }


    // TOGGLE SAVE FEATURE
    // If no file is selected or typed,
    // don't allow file to be saved. If
    // there is a file name, then allow
    // file to be saved to that name.

    if (!isValidImageFileName(imageFile)) {
        m_gluiControlHooks.saveFileLabel->set_text("Will save image: none");
        saveCanvasEnabled(false);
    } else {
        m_gluiControlHooks.saveFileLabel->set_text((std::string("Will save image: ") + imageFile).c_str());
        saveCanvasEnabled(true);
    }

    // TOGGLE LOAD FEATURE

    // If the file specified cannot be opened,
    // then disable stamp and canvas loading.
    if (isValidImageFile(imageFile)) {
        loadStampEnabled(true);
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);
    } else {
        loadStampEnabled(false);
        loadCanvasEnabled(false);
        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

void FlashPhotoApp::initGraphics() {
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
