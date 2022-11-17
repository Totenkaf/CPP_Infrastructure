// Copyright 2022 by Artem Ustsov

#include <iostream>
#include "program_options.hpp"

int main(int argc, char const *argv[]) {
    ArgumentParser parser = ArgumentParser("my_parser");
    parser.add_argument("-i", "int", 5);
    parser.add_argument("-f", "float", 5.52);
    parser.add_argument("-d", "double", 7.1566568);
    parser.add_argument("-c", "string", "my_cstring");
    parser.add_argument("-s", "--storage", "string", "my_storage");
    parser.parse_args(argc, argv);

    std::cout << parser.string_args["--storage"] << std::endl;
    std::cout << parser.string_args["-c"] << std::endl;
    std::cout << parser.int_args["-i"] << std::endl;
    std::cout << parser.float_args["-f"] << std::endl;
    std::cout << parser.double_args["-d"] << std::endl;
}
