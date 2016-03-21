#ifndef _ARGPARSER_HPP_
#define _ARGPARSER_HPP_

#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <cassert>

// Simple function to separate a filepath into a 'path' part and a 'filename' part
inline void separate_path_and_file(const std::string &full_path, std::string& path, std::string& filename) {
  // Index of last '/' character in path
  // Start with last = -1 (which is also the "substring not found" flag)
  size_t last = std::string::npos;
  // Starting at zero, find the next '/' in the string until the end of the string is reached
  for (size_t next = 0; next != std::string::npos; next = full_path.find('/',next)) {
    last = next; // update last every time a new '/' is found
  }

  // if there is no '/' then change the filename to the full path and leave the default path
  if (last == std::string::npos) { filename = full_path; }
  // otherwise split up the full path based on the last '/'
  else {
    path = full_path.substr(0,last);
    filename = full_path.substr(last+1,full_path.size());
  }
}

class ArgParser {
public:
  // File paths and names
  std::string input_path;
  std::string input_file;
  std::string source_path;
  std::string vertex_shader;
  std::string fragment_shader;
  // Window parameters
  int width;
  int height;

  // Constructors
  // Default
  ArgParser() { this->DefaultValues(); }
  // Parse accepted paramters from command line at runtime
  ArgParser(int argc, char* argv[]) {
    this->DefaultValues();
    for (int i = 1; i < argc; i++) {
      if ( !strcmp(argv[i],"-input") || !strcmp(argv[i],"-i") ) {
        ++i; assert(i < argc);
        separate_path_and_file(std::string(argv[i]), input_path, input_file);
      }
      else if ( !strcmp(argv[i], "-shaders") ) {
        // Do something
      }
      else {
        std::cerr << "Unknown parameter: " << argv[i] << " ... skipping" << std::endl;
      }
    }
  }

  // Destructor, trivial
  ~ArgParser() {}

  void DefaultValues() {
    // input file
    input_path = "../inputs";
    input_file = "example.obj";
    // shader files
    source_path = "../src";
    vertex_shader = "default.vs";
    fragment_shader = "default.fs";
    // window size
    width = 500;
    height = 500;
  }
};

#endif
