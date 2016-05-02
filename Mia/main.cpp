//
//  main.cpp
//  Modified by Juhwan Park
//

#include "MIAApp.h"
#include "MIACommandLineApp.h"
#include "libphoto.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
using namespace boost;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

using namespace std;


// A helper function to simplify the main part.
template<class T>
ostream& operator<<(ostream& os, const vector<T>& v){
  copy(v.begin(), v.end(), ostream_iterator<T>(os, " "));
  return os;
}
bool hasSuffix(const string& str, const string& suffix){
  return str.find(suffix,str.length()-suffix.length()) != string::npos;
}

bool isValidImageFile(const string& name){
  return hasSuffix(name, ".png") || hasSuffix(name, "jpg") || hasSuffix(name, "jpeg");
}
//A helper function to append all files in the input director to a vector container
// if the input is regular file, then just add the one into vector
vector<string> getFilesFromPath(string input){
  vector<string> res;
  fs::path p(input);
  if(fs::is_directory(p)){
    // if the input is directory, then we need create a directory for output
    for(auto& entry : boost::make_iterator_range(fs::directory_iterator(p), {})){
      if(isValidImageFile(entry.path().string()))
        res.push_back(entry.path().string());
    }
  }
  else {
    res.push_back(input);
  }
  return res;
}

void createDirs(string output){
  vector<string> strs;
  boost::split(strs, output, boost::is_any_of("/"));
  for(int i = 1; i < strs.size(); i++){
    fs::create_directory(strs.at(i - 1));
  }
  fs::create_directory(strs.at(0));
}
//split input as token "/" if size is 1 then input is file, so does outputPath
string getOutputFilePath(string input, string outputPath){
  vector<string> strs;
  boost::split(strs, input, boost::is_any_of("/"));
  return outputPath+ "/" + strs.back();
}

int main(int ac, char* av[]) {
  if (ac == 1) {
    //enter GUI mode
    MIAApp *app = new MIAApp(ac, av,
                                         800, 800, ColorData(1, 1, 0.95));
    // runMainLoop returns when the user closes the graphics window.
    app->runMainLoop();
    delete app;
  } else {
    //enter command line mode
    try{
      po::options_description desc("Allowed options");
      desc.add_options()
        ("help,h", "print help message")
        ("input,i", po::value<string>(), "Specified input file/directory path")
        ("output,o", po::value<string>(), "Specified output file/directory path")
        ("edgedetect,e", "Detect edge of a picture")
        ("compare,c", "Compare two pictures. 1 means identical, 0 means different")
        ("sharpen", po::value<int>(), "Sharpen a picture or directory")
        ("thresh,t", po::value<float>(), "Threshold an image by <float> value")
        ("quantize,q", po::value<int>(), "Quantize an image by <integer> value.")
        ("blur,b", po::value<float>(), "Blur an image by <float> value" )
        ("saturate", po::value<float>(), "Saturate an image by <float> value")
        ("multrgb,m", po::value<vector<float>>() -> multitoken(), "Multiply an image by <r>,<g>,<b> value.")
;

      po::variables_map vm;
      po::store(po::command_line_parser(ac, av).
                options(desc).style(
                                    po::command_line_style::unix_style
                                    | po::command_line_style::allow_long_disguise
                                    ).run(), vm);
      po::notify(vm);

      // Do we need check file path is valid image or not? Answer is no.
      // ImageHandler
      // will return NULL if the file is not a valid image. In this case,
      // we simplely exit and report to user
      MIACommandLineApp* commApp = new MIACommandLineApp();
      if(vm.count("help")){
        cout << "Usage: MIA [options]\n";
        std::stringstream stream;
        stream << desc;
        string helpMsg = stream.str ();
        boost::algorithm::replace_all (helpMsg, "--", "-");
        cout << helpMsg << endl;
        return 0;
      }

      if(vm.count("input") && vm.count("output")) {
        string input = vm["input"].as<string>();
        string output = vm["output"].as<string>();

        //If the input is directory, call this function to get all files in that
        //directory.
        // if the input is just a file, then return itself
        vector<string> inputFiles = getFilesFromPath(input);
        //create output directories
        createDirs(output);
        bool isDirectory = (inputFiles.size() > 1) ? true : false;
        for(auto file : inputFiles){
          //need read file to commApp first
          commApp -> readFile(file);

          if(vm.count("multrgb")){
            vector<float> rgbs = vm["multrgb"].as<vector<float>>();
            if(rgbs.size() != 3) {
              cerr << "ERROR: Illgeal usage. Need 3 float, but provided "
                   << rgbs.size() << " parameters" << endl;
              return 0;
            }
            ColorData color = ColorData(rgbs.at(0), rgbs.at(1) , rgbs.at(2));
            commApp -> handleMultgb(color);
          }

          if(vm.count("edgedetect")){
            commApp -> handleEdgeDetect();
          }

          if(vm.count("quantize")){
            int para = vm["quantize"].as<int>();
            cout << "quantize enabled. Level is " << para << endl;
            commApp -> handleQuant(para);
          }

          if(vm.count("blur")){
            float para = vm["blur"].as<float>();
            cout << "blur enabled. Level is " << para << endl;
            commApp -> handleBlur(para);
          }

          if(vm.count("thresh")){
            float para = vm["thresh"].as<float>();
            cout << "Threshold enabled. Level is"<< para << endl;
            commApp -> handleThresh(para);
          }

          if(vm.count("saturate")){
            float para = vm["saturate"].as<float>();
            cout << "Saturation enabled. Level is " << para << endl;
            commApp -> handleSatur(para);
          }

          if(vm.count("sharpen")){
            int para = vm["sharpen"].as<int>();
            cout << "Sharpen enabled. Level is " << para << endl;
            commApp -> handleSharpen(para);
          }

          if(vm.count("compare")){
            //need check input or output are file or not
            if(fs::is_regular_file(fs::path(file))
               && fs::is_regular_file(fs::path(output)))
              cout << commApp -> handleCompare(file, output) << endl;
            else {
              cerr << "ERROR: input and output are not regular file" << endl;
            }
          }
          if(isDirectory)
            commApp -> writeFile(getOutputFilePath(file, output));
          else
            commApp -> writeFile(output);
        }
      }
      else{
        cerr << "ERROR: input and output file/directory must be specified" << endl;
      }
    } catch(const po::required_option& e){
      string errorINFO = e.what();
      boost::algorithm::replace_all (errorINFO, "--", "-");
      cerr << errorINFO << endl;
      return 0;
    } catch(const po::error& e){
      string errorINFO = e.what();
      boost::algorithm::replace_all (errorINFO, "--", "-");
      cerr << errorINFO << endl;
      return 0;
    }
  }
}

