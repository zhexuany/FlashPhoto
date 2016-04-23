//
//  main.cpp
//


#include "MIAApp.h"
#include "libphoto.h"
#include <unistd.h>
#include <getopt.h>
#include <string>

#define no_argument 0
#define required_argument 1

using namespace std;

static int help_flag;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    MIAApp *app = new MIAApp(argc, argv,
                                         800, 800, ColorData(1, 1, 0.95));
    // runMainLoop returns when the user closes the graphics window.
    
    app->runMainLoop();
    delete app;
  } else {
      static struct option longopts[] =
      {
      //  {"h",      no_argument,        &help_flag, 1},
        {"edgedetect",  no_argument,        0, 'e'},
        {"compare",     no_argument,        0, 'c'},
        {"sharpen",     required_argument,  0, 's'},
        {"thresh",      required_argument,  0, 't'},
        {"quantize",    required_argument,  0, 'q'},
        {"blur",        required_argument,  0, 'b'},
        {"saturate",    required_argument,  0, 'a'},
        {"multrgb",     required_argument,  0, 'm'},
        {0, 0, 0, 0}
      };

      int index = 0;



      //int isFile = string(argv[1]).find("."); // if it is -1, then it is dir. Otherwise, it is image file.

      string firstArg, secondArg;

      firstArg = string(argv[1]); // first argument





      int iarg = 0;
      while(iarg != -1) {
        iarg = getopt_long(argc, argv, "hces:t:q:b:a:m:", longopts, &index);

        switch (iarg)
        {
          case 'h':
            cout << "Help!" << endl;
            help_flag = 1;
            break;
          case 'e':
            cout << "Edgedetect!" << endl;
            //optarg
            secondArg = string(argv[optind]);
            // call edgedetection with optarg value
            // and saves the file name with secondArg
            break;

          case 'c':
            cout << "Compare!" << endl;\
            cout << optarg << endl;
            //secondArg = optarg;

            // compare secondArg with firstArg
            break;

          case 's':
            std::cout << "Sharpen!" << std::endl;
            //optarg
            secondArg = string(argv[optind]);
            // call Sharpen with optarg value
            // and saves the file name with secondArg
            break;

          case 't':
            std::cout << "Thresh!" << std::endl;
            //optarg
            secondArg = string(argv[optind]);
            // call thresh with optarg value
            // and saves the file name with secondArg
            break;

          case 'q':
            std::cout << "Quantize!" << std::endl;
            //optarg
            secondArg = string(argv[optind]);
            // call quantize with optarg value
            // and saves the file name with secondArg
            break;

          case 'b':
            std::cout << "Blur!" << std::endl;
            //optarg
            secondArg = string(argv[optind]);
            // call blur with optarg value
            // and saves the file name with secondArg
            break;
          case 'a':
            std::cout << "Saturate!" << std::endl;
            //optarg
            secondArg = string(argv[optind]);
            // call saturate with optarg value
            // and saves the file name with secondArg
            break;
          case 'm':
            std::cout << "Multrgb!" << std::endl;
            //optarg // need to be parsed into three float point values
            secondArg = string(argv[optind]);
            // call rbb with optarg value
            // and saves the file name with secondArg
            break;
          default:
            break;
        }
      }

      if (help_flag) {
        cout << "Usage:  [options] [target] : only single target is allowed." << endl;
        cout << "Usage:  [options] [target] : only single target is allowed." << endl;
        cout << "Usage:  [options] [target] : only single target is allowed." << endl;
        cout << "Usage:  [options] [target] : only single target is allowed." << endl;
        exit(0);
      }

  }
  exit(0);
}
