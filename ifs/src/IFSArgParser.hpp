#ifndef _IFS_ARGPARSER_HPP_
#define _IFS_ARGPARSER_HPP_

#include "../../base/ArgParser.hpp"

class IFSArgParser : public ArgParser {
public:
  // Default input file and path
  std::string input_path = "../inputs";
  std::string input_file = "sierpinski.txt";
  // IFS-related parameters
  unsigned int points = 10000;
  unsigned int iterations = 3;
  bool deterministic = false;

  // Default Constructor
  IFSArgParser() : ArgParser() { }
  // Command Line Parameters Constructor
  IFSArgParser(int argc, char* argv[]) : ArgParser()
  {
    std::cout << input_file << std::endl;
    for (int i = 1; i < argc; i++) {
      if ( !strcmp(argv[i], "-iterations") || !strcmp(argv[i], "-iters") ) {
        ++i; assert(i < argc);
        iterations = atoi(argv[i]);
      }
      else if ( !strcmp(argv[i],"-points") || !strcmp(argv[i],"-p")) {
        ++i; assert(i < argc);
        points = atoi(argv[i]);
      }
      else if ( !strcmp(argv[i],"-deterministic") || !strcmp(argv[i],"-d") ) {
        deterministic = true;
      }
      else if ( !strcmp(argv[i],"-input") || !strcmp(argv[i],"-i") ) {
        ++i; assert(i < argc);
        std::cout << input_file << std::endl;
        separate_path_and_file(std::string(argv[i]), input_path, input_file);
        std::cout << input_file << std::endl;
      }
      else if ( !strcmp(argv[i], "-shaders") ) {
        assert(i+3 < argc);
        std::string temp;
        separate_path_and_file(std::string(argv[++i]), shader_path, temp);
        separate_path_and_file(std::string(argv[++i]), temp, vertex_shader);
        separate_path_and_file(std::string(argv[++i]), temp, fragment_shader);
      }
      else {
        std::cerr << "Unknown parameter: " << argv[i] << " ... skipping" << std::endl;
      }
    }
  }
};

#endif
