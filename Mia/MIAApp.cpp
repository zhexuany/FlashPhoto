#include "MIAApp.h"
#include <sstream>

using std::cout;
using std::endl;

MIAApp::MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    // Set the name of the window
    setCaption("Medical Image Analysis (MIA)");

    // Initialize Interface
    initializeBuffers(backgroundColor, width, height);

    initGlui();
    initGraphics();

    initDrawTool();
    initFilter();
    m_queueSize = 20;
}

/*
* \Initialize the filter on load
* \none
* \void
*/
void MIAApp::initFilter(){
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
void MIAApp::initDrawTool(){
  toolList = new DrawTool*[1];
  ImageHandler *loader = new ImageHandler();
  int Height, Width;
  ColorData* color = new ColorData(1,0,0);
  PixelBuffer* init = loader->loadimage("marker.png", Height, Width, m_displayBuffer->getBackgroundColor());
  m_stampHeight = Height;
  m_stampWidth = Width;

  m_tool = new DrawTool(color, 0, 0);
  toolList[0] = new Pen(color, 3);
  toolList[1] = new Stamp(init, m_stampWidth, m_stampHeight);
  m_tool = toolList[0];
}

/*
* Update the current tool that is selected in the UI (stored in m_curTool)
* \none
* \void
*/
void MIAApp::updateCurrentTool() {
    switch (m_curTool) {
      case PEN: {
        m_tool = toolList[0];
        break;
      }
      case ARROW:{
        m_tool = toolList[1];
        break;
      }
    }
}

void MIAApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

MIAApp::~MIAApp()
{
    if (m_displayBuffer) {
        delete m_displayBuffer;
    }if(m_tool) delete m_tool;
    for(int i = 0; i < 2; i++){
      if(toolList[i]){
        delete toolList[i];
      }
    }
    if(toolList) delete toolList;
}


void MIAApp::mouseDragged(int x, int y)
{
  if (m_tool -> allowDrag) {
      m_tool -> paint(x, y, m_prevX, m_prevY, m_displayBuffer);
      m_prevX = x;
      m_prevY = y;
  }
}

void MIAApp::mouseMoved(int x, int y)
{
  if(m_drag){
    mouseDragged(x, y);
  }
}

void MIAApp::leftMouseDown(int x, int y)
{
    //std::cout << "mousePressed " << x << " " << y << std::endl;
    updateUndo();
    m_prevX = x;
    m_prevY = y;
    m_tool -> paint(x, y, m_prevX, m_prevY, m_displayBuffer);
    //std::cout << "mousePressed Done " << x << " " << y << std::endl;
    m_drag = true;
}

void MIAApp::updateUndo(){
    //Enable undo and disable redo
    undoEnabled(true);
    redoEnabled(false);

    //Clear the redo queue
    std::deque<PixelBuffer*> empty;
    std::swap(redoQueue, empty);

    //Make a copy and save the current buffer
    PixelBuffer *newBuffer = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
    newBuffer->copyPixelBuffer(m_displayBuffer, newBuffer);
    if ((int)undoQueue.size() >= m_queueSize) {
        undoQueue.pop_back();
    }
    undoQueue.push_front(newBuffer);
}

void MIAApp::leftMouseUp(int x, int y)
{
    //std::cout << "mouseReleased " << x << " " << y << std::endl;
    m_drag = false;
}

void MIAApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
    m_drag = false;
}

void MIAApp::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;



    new GLUI_Column(m_glui, false);
    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
        new GLUI_RadioButton(radio, "Arrow");

    }


    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(1, 10);
            filterSharpAmount->set_int_val(1);
            filterSharpAmount->set_speed(0.1);

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

        GLUI_Panel *multiplyPanel = new GLUI_Panel(filterPanel, "Multiply RGB");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(multiplyPanel, "R:", &m_filterParameters.multiply_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(multiplyPanel, "G:", &m_filterParameters.multiply_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(multiplyPanel, "B:", &m_filterParameters.multiply_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(multiplyPanel, "Apply", UI_APPLY_MULTIPLY_RGB, s_gluicallback);
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }

        GLUI_Panel *grayPanel = new GLUI_Panel(filterPanel, "Grayscale");
        {

            new GLUI_Button(grayPanel, "Apply", UI_APPLY_GRAYSCALE, s_gluicallback);
        }



        // UNDO,REDO,QUIT
        {
            m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
            undoEnabled(false);
            m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
            redoEnabled(false);

            new GLUI_Separator(m_glui);
            new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
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

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);


        m_gluiControlHooks.previousImageButton = new GLUI_Button(imagePanel, "Previous Image", UI_PREVIOUS_IMAGE_BUTTON, s_gluicallback);
        m_gluiControlHooks.nextImageButton = new GLUI_Button(imagePanel, "Next Image", UI_NEXT_IMAGE_BUTTON, s_gluicallback);


        loadCanvasEnabled(false);
        saveCanvasEnabled(false);
        nextImageEnabled(false);
        previousImageEnabled(false);
    }
    return;
}

void MIAApp::gluiControl(int controlID)
{

    switch (controlID) {
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_GRAYSCALE:
            applyFilterGrayScale();
            break;
        case UI_APPLY_MULTIPLY_RGB:
            applyFilterMultiplyRGB();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_NEXT_IMAGE_BUTTON:
            loadNextImage();
            break;
        case UI_PREVIOUS_IMAGE_BUTTON:
            loadPreviousImage();
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
        case UI_TOOLTYPE:
            updateCurrentTool();
            break;
        default:
            break;
    }

    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();
}

// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how MIAApp should respond to the
// button presses.

void MIAApp::loadImageToCanvas()
{
    cout << "Load Canvas has been clicked for file " << m_fileName << endl;
    // TODO: Perform loading task
	updateUndo();
	ImageHandler *loader = new ImageHandler();
	//Pass in height and width by reference so we can resize the window after
	int Height, Width;
    PixelBuffer *newBuffer = loader->loadimage(m_fileName, Height, Width, m_displayBuffer->getBackgroundColor());
    if (newBuffer == NULL) {
        std::cout << "Error loading image" << std::endl;
    }
    setWindowDimensions(Width, Height);

    //Reset the display buffer size so we can use copyPixelBuffer
    initializeBuffers(m_displayBuffer->getBackgroundColor(), Width, Height);
    m_displayBuffer->copyPixelBuffer(newBuffer, m_displayBuffer);
    //m_displayBuffer = newBuffer;
    delete newBuffer;

    // Determining whether there are next or previous images
    m_nextFileName = getImageNamePlusSeqOffset(m_fileName, 1);
    m_prevFileName = getImageNamePlusSeqOffset(m_fileName, -1);

    nextImageEnabled(isValidImageFile(m_nextFileName));
    previousImageEnabled(isValidImageFile(m_prevFileName));
}

void MIAApp::saveCanvasToFile()
{
    cout << "Save Canvas been clicked for file " << m_fileName << endl;
    ImageHandler *loader = new ImageHandler();
    loader->saveimage(m_fileName, m_displayBuffer);
}

void MIAApp::applyFilterThreshold()
{
    cout << "Apply has been clicked for Threshold has been clicked with amount =" << m_filterParameters.threshold_amount << endl;
    updateUndo();
    m_filters[FilterFactory::FILTER_THRESHOLD] -> setFilterParameter(m_filterParameters.threshold_amount);
    m_filters[FilterFactory::FILTER_THRESHOLD] -> applyFilter(m_displayBuffer);
}

void MIAApp::applyFilterMultiplyRGB()
{
    cout << "Apply has been clicked for Multiply RGB with red = " << m_filterParameters.multiply_colorRed
    << ", green = " << m_filterParameters.multiply_colorGreen
    << ", blue = " << m_filterParameters.multiply_colorBlue << endl;
	m_filters[FilterFactory::FILTER_CHANNEL]
      -> setFilterParameter(ColorData(m_filterParameters.multiply_colorRed,
                                      m_filterParameters.multiply_colorGreen,
                                      m_filterParameters.multiply_colorBlue));
    updateUndo();
    m_filters[FilterFactory::FILTER_CHANNEL] -> applyFilter(m_displayBuffer);
}

void MIAApp::applyFilterGrayScale()
{
    cout << "Apply has been clicked for Grayscale" << endl;
	updateUndo();
    m_filters[FilterFactory::FILTER_SPECIAL] -> applyFilter(m_displayBuffer);
}


void MIAApp::applyFilterSharpen()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
    m_filters[FilterFactory::FILTER_SHARPEN]
      -> setFilterParameter(m_filterParameters.sharpen_amount);
    updateUndo();
    m_filters[FilterFactory::FILTER_SHARPEN] -> applyFilter(m_displayBuffer);
}

void MIAApp::applyFilterEdgeDetect() {
    cout << "Apply has been clicked for Edge Detect" << endl;
    updateUndo();
    m_filters[FilterFactory::FILTER_DETECT_EDGES] -> applyFilter(m_displayBuffer);
}

void MIAApp::applyFilterQuantize() {
    cout << "Apply has been clicked for Quantize with bins = " << m_filterParameters.quantize_bins << endl;
    m_filters[FilterFactory::FILTER_QUANTIZE] -> setFilterParameter((float) m_filterParameters.quantize_bins);
    updateUndo();
    m_filters[FilterFactory::FILTER_QUANTIZE] -> applyFilter(m_displayBuffer);
}

void MIAApp::undoOperation()
{
    cout << "Undoing..." << endl;
    updateCanvas(undoQueue, redoQueue, true);
}

void MIAApp::redoOperation()
{
    cout << "Redoing..." << endl;
    updateCanvas(redoQueue, undoQueue, false);
}

void MIAApp::updateCanvas(std::deque<PixelBuffer*> &alpha, std::deque<PixelBuffer*> &beta, bool isUndo) {
    if (alpha.size() > 0) {
        //Save beta history
        PixelBuffer *betaBuffer = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
        betaBuffer->copyPixelBuffer(m_displayBuffer, betaBuffer);
        beta.push_front(betaBuffer);

        //Update pixel buffer with alpha buffer
        PixelBuffer *newBuffer = alpha.front();
        alpha.pop_front();
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

void MIAApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void MIAApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void MIAApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void MIAApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void MIAApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void MIAApp::previousImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.previousImageButton, enabled);
}

void MIAApp::nextImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.nextImageButton, enabled);
}

void MIAApp::loadNextImage()
{
    setImageFile(m_nextFileName);
    loadImageToCanvas();
}

void MIAApp::loadPreviousImage()
{
    setImageFile(m_prevFileName);
    loadImageToCanvas();
}


bool MIAApp::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}

bool MIAApp::isValidImageFileName(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool MIAApp::isValidImageFile(const std::string & name) {

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

bool MIAApp::isjpeg(const std::string & name) {
        if (hasSuffix(name, ".jpg")|| hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

std::string MIAApp::getImageNamePlusSeqOffset(const std::string & currentFileName, int offset)
{

    int digitCount = 3;

    std::string extension, name, number;
    size_t dotPos = currentFileName.find_last_of(".");
    if (dotPos ==  std::string::npos || dotPos == 0) {
        return "";
    }

    extension = currentFileName.substr(dotPos+1);
    name = currentFileName.substr(0,dotPos);
    if ((int)name.length() < digitCount) {
        return "";
    }

    number = name.substr(name.length()-digitCount);
    name = name.substr(0,name.length()-digitCount);
    int num;
    std::istringstream ( number ) >> num;
    int output_num = num +offset;
    if (output_num < 0) {
        return "";
    }
    std::stringstream ss;
    ss << output_num;
    std::string output_number;
    ss >> output_number;

    // Append zero chars
    size_t str_length = output_number.length();
    for (int i = 0; i < digitCount - (int)str_length; i++)
        output_number = "0" + output_number;





    return (name + output_number + "." + extension);
}

void MIAApp::setImageFile(const std::string & fileName)
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
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);
    } else {
        loadCanvasEnabled(false);
        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

void MIAApp::initGraphics() {
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
