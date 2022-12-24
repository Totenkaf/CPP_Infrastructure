// Copyright 2022 by Artem Ustsov

#include <iostream>

#include "program_options.hpp"

auto main(int argc, char const *argv[]) -> int {
  ArgumentParser parser = ArgumentParser("my_parser");

  try {
    parser.add_argument("-i", "int", 5);
    parser.add_argument("-f", "float", 5.52);
    parser.add_argument("-d", "double", 7.1566568);
    parser.add_argument("-c", "string", "my_cstring");
    parser.add_argument("-s", "--storage", "string", "my_storage");
    parser.add_argument("-b", "--boolean", "bool", "true");
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << '\n';
    return _EXIT_FAULT;
  }
  

  if(!parser.parse_args(argc, argv)) {
      std::cout << parser.get_string_args()["--storage"] << std::endl;
      std::cout << parser.get_string_args()["-c"] << std::endl;
      std::cout << parser.get_int_args()["-i"] << std::endl;
      std::cout << parser.get_float_args()["-f"] << std::endl;
      std::cout << parser.get_double_args()["-d"] << std::endl;
      std::cout << parser.get_double_args()["--boolean"] << std::endl;
  }
  return _EXIT_SUCCESS;
}
