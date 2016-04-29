//
//  main.cpp
//


#include "MIAApp.h"
#include "libphoto.h"
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>
#include <string>

#define no_argument 0
#define required_argument 1

using namespace std;

static int help_flag, edge_flag, comp_flag, sharpen_flag, thresh_flag, quant_flag, blur_flag, satur_flag, mult_flag;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    MIAApp *app = new MIAApp(argc, argv,
                                         800, 800, ColorData(1, 1, 0.95));
    // runMainLoop returns when the user closes the graphics window.
    app->runMainLoop();
    delete app;
  } else {
    MIAApp *app = new MIAApp(argc, argv);

      static struct option longopts[] =
      {
        {"h",           no_argument,        &help_flag, 1},
        {"edgedetect",  no_argument,        &edge_flag, 1},
        {"compare",     no_argument,        &comp_flag, 1},
        {"sharpen",     required_argument,  &sharpen_flag, 1},
        {"thresh",      required_argument,  &thresh_flag, 1},
        {"quantize",    required_argument,  &quant_flag, 1},
        {"blur",        required_argument,  &blur_flag, 1},
        {"saturate",    required_argument,  &satur_flag, 1},
        {"multrgb",     required_argument,  &mult_flag, 1},
        {0, 0, 0, 0}
      };

      int index = 0;

      string firstArg, secondArg;

      // first argument
      firstArg = argv[1];

      // checking the first target is file of not by finding "."
      // if it is npos, then it is dir. Otherwise, it is image file.
      size_t found = firstArg.find("/");

      // Flag to indicate target is file or not
      int isFile;

      // Setting the flag for future use
      if (found == string::npos) {
        isFile = 1;
      } else {
        isFile = 0;
      }
      cout << "isFile: " << isFile << endl;


      // parsing options and setting the flag
      int iarg = 0;
      while(iarg != -1) {
        iarg = getopt_long_only(argc, argv, "", longopts, &index);
      }


      // TODO: Need to check isFile flag and if it is directory, then the effect of filter need to be applied to all of the files in the directory
      if (help_flag) {
        cout << argv[0] <<"Command line mode usage: [target] [options] [amount(optional)] [target] : amount is required for certain filters" << endl;
          // TODO: Making helpful messages
      }
      else if (edge_flag) {
          cout << "Edgedetect!" << endl;
          if (argc  == 4) {
              if (!isFile) {
                cout << "It is Directory!" << endl;
                secondArg = argv[3];
                string dir = secondArg.substr(0, secondArg.find("/"));
                const char * directory = dir.c_str();
                if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                    cout << "Error on making directory" << endl;
                    exit(-1);
                };
                cout << "directory: " << directory << " is created" << endl;
                while (app->c_isValidImageFile(firstArg)) {
                    cout << "Second arg: " << secondArg<< endl;
                    PixelBuffer *imageBuffer;
                    imageBuffer = app->c_loadImage(firstArg);
                    if (imageBuffer == NULL) {
                        cout << "Error loading image. No such file exist." << endl;
                        break;
                    } else {
                        cout << "image loaded" << endl;
                        app->c_applyFilterEdgeDetect(imageBuffer);
                        cout << "applying fliter" << endl;
                        app->c_saveToFile(secondArg, imageBuffer);
                        cout << "save" << endl;
                    }
                    firstArg = app->c_getImageNamePlusSeqOffset(firstArg, 1);
                    secondArg = app->c_getImageNamePlusSeqOffset(secondArg, 1);
                }
              } else {
                secondArg = argv[3];
                cout << "Second arg: " << secondArg<< endl;
                PixelBuffer *imageBuffer;
                imageBuffer = app->c_loadImage(firstArg);
                if (imageBuffer == NULL) {
                    cout << "Error loading image. No such file exist." << endl;

                } else {
                    cout << "image loaded" << endl;
                    app->c_applyFilterEdgeDetect(imageBuffer);
                    cout << "applying fliter" << endl;
                    app->c_saveToFile(secondArg, imageBuffer);
                    cout << "save" << endl;
                }
            }
          } else {
              cout << "Arguments are not matched"<< endl;
          }
      }
      else if (comp_flag) {
          cout << "Compare!" << endl;
          secondArg = argv[3];
          cout << "Second arg: " << secondArg<< endl;
            // TODO: compare files
      }
      else if (sharpen_flag) {
          cout << "sharpen!" << endl;
          if (argc == 5) {
            if (!isFile) {
              cout << "It is Directory!" << endl;
              secondArg = argv[3];
              string dir = secondArg.substr(0, secondArg.find("/"));
              const char * directory = dir.c_str();
              if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                  cout << "Error on making directory" << endl;
                  exit(-1);
              };
              cout << "directory: " << directory << " is created" << endl;
              int amount = atoi(argv[3]);
              while (app->c_isValidImageFile(firstArg)) {
                  cout << "Second arg: " << secondArg<< endl;
                  PixelBuffer *imageBuffer;
                  imageBuffer = app->c_loadImage(firstArg);
                  if (imageBuffer == NULL) {
                      cout << "Error loading image. No such file exist." << endl;
                      break;
                  } else {
                      cout << "image loaded" << endl;
                      app->c_applyFilterSharpen(imageBuffer, amount);
                      cout << "applying fliter" << endl;
                      app->c_saveToFile(secondArg, imageBuffer);
                      cout << "save" << endl;
                  }
                  firstArg = app->c_getImageNamePlusSeqOffset(firstArg, 1);
                  secondArg = app->c_getImageNamePlusSeqOffset(secondArg, 1);
              }
            } else {
                secondArg = argv[4];
                cout << "Second arg: " << secondArg<< endl;
                int amount = atoi(argv[3]);
                PixelBuffer *imageBuffer;
                imageBuffer = app->c_loadImage(firstArg);
                if (imageBuffer == NULL) {
                    cout << "Error loading image. No such file exist." << endl;
                } else {
                    cout << "image loaded" << endl;
                    app->c_applyFilterSharpen(imageBuffer, amount);
                    cout << "applying fliter" << endl;
                    app->c_saveToFile(secondArg, imageBuffer);
                    cout << "save" << endl;
                }
            }
          } else {
              cout << "Arguments are not matched"<< endl;
          }
      }
      else if (thresh_flag) {
          cout << "Thresh!" << endl;
          if (argc == 5) {
            if (!isFile) {
              cout << "It is Directory!" << endl;
              secondArg = argv[3];
              string dir = secondArg.substr(0, secondArg.find("/"));
              const char * directory = dir.c_str();
              if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                  cout << "Error on making directory" << endl;
                  exit(-1);
              };
              cout << "directory: " << directory << " is created" << endl;
              double amount = atof(argv[3]);
              while (app->c_isValidImageFile(firstArg)) {
                  cout << "Second arg: " << secondArg<< endl;
                  PixelBuffer *imageBuffer;
                  imageBuffer = app->c_loadImage(firstArg);
                  if (imageBuffer == NULL) {
                      cout << "Error loading image. No such file exist." << endl;
                      break;
                  } else {
                      cout << "image loaded" << endl;
                      app->c_applyFilterThreshold(imageBuffer, amount);
                      cout << "applying fliter" << endl;
                      app->c_saveToFile(secondArg, imageBuffer);
                      cout << "save" << endl;
                  }
                  firstArg = app->c_getImageNamePlusSeqOffset(firstArg, 1);
                  secondArg = app->c_getImageNamePlusSeqOffset(secondArg, 1);
              }
            } else {
                secondArg = argv[4];
                cout << "Second arg: " << secondArg<< endl;
                double amount = atof(argv[3]);
                PixelBuffer *imageBuffer;
                imageBuffer = app->c_loadImage(firstArg);
                if (imageBuffer == NULL) {
                    cout << "Error loading image. No such file exist." << endl;
                } else {
                    cout << "image loaded" << endl;
                    app->c_applyFilterThreshold(imageBuffer, amount);
                    cout << "applying fliter" << endl;
                    app->c_saveToFile(secondArg, imageBuffer);
                    cout << "save" << endl;
                }
            }
          } else {
              cout << "Arguments are not matched"<< endl;
          }
      }
      else if (quant_flag) {
          cout << "Quantize!" << endl;
          if (argc == 5) {
            if (!isFile) {
              cout << "It is Directory!" << endl;
              secondArg = argv[3];
              string dir = secondArg.substr(0, secondArg.find("/"));
              const char * directory = dir.c_str();
              if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                  cout << "Error on making directory" << endl;
                  exit(-1);
              };
              cout << "directory: " << directory << " is created" << endl;
              int amount = atoi(argv[3]);
              while (app->c_isValidImageFile(firstArg)) {
                  cout << "Second arg: " << secondArg<< endl;
                  PixelBuffer *imageBuffer;
                  imageBuffer = app->c_loadImage(firstArg);
                  if (imageBuffer == NULL) {
                      cout << "Error loading image. No such file exist." << endl;
                      break;
                  } else {
                      cout << "image loaded" << endl;
                      app->c_applyFilterQuantize(imageBuffer, amount);
                      cout << "applying fliter" << endl;
                      app->c_saveToFile(secondArg, imageBuffer);
                      cout << "save" << endl;
                  }
                  firstArg = app->c_getImageNamePlusSeqOffset(firstArg, 1);
                  secondArg = app->c_getImageNamePlusSeqOffset(secondArg, 1);
              }
            } else {
                secondArg = argv[4];
                cout << "Second arg: " << secondArg<< endl;
                int amount = atoi(argv[3]);
                PixelBuffer *imageBuffer;
                imageBuffer = app->c_loadImage(firstArg);
                if (imageBuffer == NULL) {
                    cout << "Error loading image. No such file exist." << endl;
                } else {
                    cout << "image loaded" << endl;
                    app->c_applyFilterQuantize(imageBuffer, amount);
                    cout << "applying fliter" << endl;
                    app->c_saveToFile(secondArg, imageBuffer);
                    cout << "save" << endl;
                }
            }
          } else {
              cout << "Arguments are not matched"<< endl;
          }
      }
      else if (blur_flag) {
          cout << "Blur!" << endl;
          if (argc == 5) {
            if (!isFile) {
              cout << "It is Directory!" << endl;
              secondArg = argv[3];
              string dir = secondArg.substr(0, secondArg.find("/"));
              const char * directory = dir.c_str();
              if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                  cout << "Error on making directory" << endl;
                  exit(-1);
              };
              cout << "directory: " << directory << " is created" << endl;
              double amount = atof(argv[3]);
              while (app->c_isValidImageFile(firstArg)) {
                  cout << "Second arg: " << secondArg<< endl;
                  PixelBuffer *imageBuffer;
                  imageBuffer = app->c_loadImage(firstArg);
                  if (imageBuffer == NULL) {
                      cout << "Error loading image. No such file exist." << endl;
                      break;
                  } else {
                      cout << "image loaded" << endl;
                      app->c_applyFilterBlur(imageBuffer, amount);
                      cout << "applying fliter" << endl;
                      app->c_saveToFile(secondArg, imageBuffer);
                      cout << "save" << endl;
                  }
                  firstArg = app->c_getImageNamePlusSeqOffset(firstArg, 1);
                  secondArg = app->c_getImageNamePlusSeqOffset(secondArg, 1);
              }
            } else {
                secondArg = argv[4];
                cout << "Second arg: " << secondArg<< endl;
                double amount = atof(argv[3]);
                PixelBuffer *imageBuffer;
                imageBuffer = app->c_loadImage(firstArg);
                if (imageBuffer == NULL) {
                    cout << "Error loading image. No such file exist." << endl;
                } else {
                    cout << "image loaded" << endl;
                    app->c_applyFilterBlur(imageBuffer, amount);
                    cout << "applying fliter" << endl;
                    app->c_saveToFile(secondArg, imageBuffer);
                    cout << "save" << endl;
                }
            }
          } else {
              cout << "Arguments are not matched"<< endl;
          }
      }
      else if (satur_flag) {
          cout << "Saturate!" << endl;
          if (argc == 5) {
            if (!isFile) {
              cout << "It is Directory!" << endl;
              secondArg = argv[3];
              string dir = secondArg.substr(0, secondArg.find("/"));
              const char * directory = dir.c_str();
              if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                  cout << "Error on making directory" << endl;
                  exit(-1);
              };
              cout << "directory: " << directory << " is created" << endl;
              double amount = atof(argv[3]);
              while (app->c_isValidImageFile(firstArg)) {
                  cout << "Second arg: " << secondArg<< endl;
                  PixelBuffer *imageBuffer;
                  imageBuffer = app->c_loadImage(firstArg);
                  if (imageBuffer == NULL) {
                      cout << "Error loading image. No such file exist." << endl;
                      break;
                  } else {
                      cout << "image loaded" << endl;
                      app->c_applyFilterSaturate(imageBuffer, amount);
                      cout << "applying fliter" << endl;
                      app->c_saveToFile(secondArg, imageBuffer);
                      cout << "save" << endl;
                  }
                  firstArg = app->c_getImageNamePlusSeqOffset(firstArg, 1);
                  secondArg = app->c_getImageNamePlusSeqOffset(secondArg, 1);
              }
            } else {
                secondArg = argv[4];
                cout << "Second arg: " << secondArg<< endl;
                double amount = atof(argv[3]);
                PixelBuffer *imageBuffer;
                imageBuffer = app->c_loadImage(firstArg);
                if (imageBuffer == NULL) {
                    cout << "Error loading image. No such file exist." << endl;
                } else {
                    cout << "image loaded" << endl;
                    app->c_applyFilterSaturate(imageBuffer, amount);
                    cout << "applying fliter" << endl;
                    app->c_saveToFile(secondArg, imageBuffer);
                    cout << "save" << endl;
                }
            }
          } else {
              cout << "Arguments are not matched"<< endl;
          }
      }
      else if (mult_flag) {
          cout << "multrgb!" << endl;
          if (argc == 5) {
            if (!isFile) {
              cout << "It is Directory!" << endl;
              secondArg = argv[4];
              string dir = secondArg.substr(0, secondArg.find("/"));
              const char * directory = dir.c_str();
              if (mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                  cout << "Error on making directory" << endl;
                  exit(-1);
              };
              cout << "directory: " << directory << " is created" << endl;
              char* amount = argv[2];
              double r = .0, g = .0, b = .0 ;
              char* str;
              str = strtok(amount," ,");
              while (str != NULL) {
                  if (r == .0) {
                    r = atof(str);
                  } else if (g == .0) {
                    g = atof(str);
                  } else {
                    b = atof(str);
                  }
                  str = strtok (NULL, " ,");
              }
              if (!r || !g || !b) {
                  cout << "Error getting r, g, b amount. Properly input rgb amount as <float>,<float>,<float>" << endl;
                  exit(-1);
              }
              while (app->c_isValidImageFile(firstArg)) {
                  cout << "Second arg: " << secondArg<< endl;
                  PixelBuffer *imageBuffer;
                  imageBuffer = app->c_loadImage(firstArg);
                  if (imageBuffer == NULL) {
                      cout << "Error loading image. No such file exist." << endl;
                      break;
                  } else {
                      cout << "image loaded" << endl;
                      app->c_applyFilterMultiplyRGB(imageBuffer, r, g, b);
                      cout << "applying fliter" << endl;
                      app->c_saveToFile(secondArg, imageBuffer);
                      cout << "save" << endl;
                  }
                  firstArg = app->c_getImageNamePlusSeqOffset(firstArg, 1);
                  secondArg = app->c_getImageNamePlusSeqOffset(secondArg, 1);
              }
            } else {
                secondArg = argv[4];
                char* amount = argv[2];
                cout << "Second arg: " << secondArg<< endl;
                double r = .0, g = .0, b = .0 ;
                char* str;
                str = strtok(amount," ,");
                while (str != NULL) {
                    if (r == .0) {
                      r = atof(str);
                    } else if (g == .0) {
                      g = atof(str);
                    } else {
                      b = atof(str);
                    }
                    str = strtok (NULL, " ,");
                }
                if (!r || !g || !b) {
                    cout << "Error getting r, g, b amount. Properly input rgb amount as <float>,<float>,<float>" << endl;
                } else {
                    PixelBuffer *imageBuffer;
                    imageBuffer = app->c_loadImage(firstArg);
                    if (imageBuffer == NULL) {
                        cout << "Error loading image. No such file exist." << endl;
                    } else {
                        cout << "image loaded" << endl;
                        app->c_applyFilterMultiplyRGB(imageBuffer, r, g, b);
                        cout << "applying fliter" << endl;
                        app->c_saveToFile(secondArg, imageBuffer);
                        cout << "save" << endl;
                    }
                }
            }
          } else {
              cout << "Arguments are not matched"<< endl;
          }
      }
      else {
        // TODO: convert an image in the different format
      }
      cout << "End of command line mode" << endl;
      delete app;
  }
  exit(0);
}
