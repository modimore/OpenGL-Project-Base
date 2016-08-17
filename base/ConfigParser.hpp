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
  size_t next = full_path.find('/',0);
  while (next != std::string::npos) {
    // update last every time a new '/' is found
    last = next;
    next = full_path.find('/',last+1);
  }

  // if there is no '/' then change the filename to the full path and leave the default path
  if (last == std::string::npos) { filename = full_path; }
  // otherwise split up the full path based on the last '/'
  else {
    path = full_path.substr(0,last);
    filename = full_path.substr(last,full_path.size());
    std::cout << path << std::endl;
    std::cout << filename << std::endl;
  }
}

class ConfigParser {
public:
  // default input
  std::string input_path = "../inputs";
  std::string input_file = "cube.obj";
  // default shaders and shader location
  bool generate_shaders = false;
  std::string shader_path = "../shaders";
  std::string vertex_shader = "default.vs";
  std::string fragment_shader = "default.fs";
  // View parameters
  std::string camera = "orthographic";
  int width = 500;
  int height = 500;

  // Constructors
  // Default, trivial
  ConfigParser() {}
  // Parse accepted paramters from command line at runtime
  ConfigParser(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) ParseCommand(argc,argv,i);
  }

  // Destructor, trivial
  ~ConfigParser() {}

  virtual void ParseCommand(int argc, char* argv[], int& i) {
    if ( !strcmp(argv[i],"-input") || !strcmp(argv[i],"-i") ) {
      ++i; assert(i < argc);
      separate_path_and_file(std::string(argv[i]), input_path, input_file);
    }
    else if (!strcmp(argv[i], "-generate_shaders") || !strcmp(argv[i], "-gs")) {
      generate_shaders = true;
    }
    else if ( !strcmp(argv[i], "-shader_files") ) {
      ++i; assert(i < argc);
      separate_path_and_file(std::string(argv[i]), shader_path, vertex_shader);
      ++i; assert(i < argc);
      separate_path_and_file(std::string(argv[i]), shader_path, fragment_shader);
    }
    else {
      std::cout << "Unknown parameter: " << argv[i] << " ... skipping" << std::endl;
    }
  }

  virtual std::string get_input_path() { return input_path + "/" + input_file; }
  virtual std::string get_vs_path() { return shader_path + "/" + vertex_shader; }
  virtual std::string get_fs_path() { return shader_path + "/" + fragment_shader; }
};

#endif
