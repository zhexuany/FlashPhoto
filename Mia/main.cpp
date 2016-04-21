//
//  main.cpp
//


#include "MIAApp.h"
#include "libphoto.h"
int main(int argc, char* argv[]) {
    MIAApp *app = new MIAApp(argc, argv,
                                         800, 800, ColorData(1,1,.95));
    // runMainLoop returns when the user closes the graphics window.
    app->runMainLoop();
    delete app;
    exit(0);
}
