#ifndef _IFS_ARGPARSER_HPP_
#define _IFS_ARGPARSER_HPP_

#include "../core/ArgParser.hpp"

class IFSArgParser : public ArgParser {
public:
  unsigned int points;
  unsigned int iterations;
  bool deterministic;

  // Default Constructor
  IFSArgParser() : ArgParser() { this->DefaultValues(); }
  // Command Line Parameters Constructor
  IFSArgParser(int argc, char* argv[])
  : ArgParser(argc,argv) {
    this->DefaultValues();
    for (int i = 1; i < argc; i++) {
      if ( !strcmp(argv[i], "-iterations") || !strcmp(argv[i], "-iters") ) {
        ++i; assert(i < argc);
        iterations = atoi(argv[i]);
      }
    }
  }

  void DefaultValues() {
    input_path = "../inputs/ifs";
    input_file = "sierpinkski.txt";
    points = 10000;
    iterations = 3;
    deterministic = true;
  }
};

#endif
