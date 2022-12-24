// Copyright 2022 by Artem Ustsov

#include <gtest/gtest.h>

#include "program_options.hpp"

class ProgramOptionsEnvironment : public ::testing::Test {
 public:
  ArgumentParser parser = ArgumentParser("test_parser");
};


TEST_F(ProgramOptionsEnvironment, parse_parametrize_test) {
  EXPECT_EQ(parser.get_description(), "test_parser");
}

TEST_F(ProgramOptionsEnvironment, check_to_many_args) {
  try {
        parser.add_argument("-i", "--input", "int", 5, 4);
        FAIL() << "Expected std::logic_error";
    }
    catch(std::logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("too many arguments in template"));
    }
}

TEST_F(ProgramOptionsEnvironment, check_bad_check) {
  try {
        parser.add_argument("-i", "--input", "int", 5, 4);
        FAIL() << "Expected std::logic_error";
    }
    catch(std::logic_error const & err) {
        EXPECT_EQ(err.what(), std::string("too many arguments in template"));
    }
}

TEST_F(ProgramOptionsEnvironment, check_default_template_test) {
  parser.add_argument("-i", "int", 5);
  parser.add_argument("-f", "float", 5.52);
  parser.add_argument("-d", "double", 7.156656);
  parser.add_argument("-c", "string", "my_cstring");
  parser.add_argument("-s", "--storage", "string", "my_storage");
  parser.add_argument("-b", "--boolean", "bool", "true");

  std::map<std::string, std::vector<std::string>> default_template =
      parser.get_default_template();

  EXPECT_EQ(default_template["-i"][0], "int");
  EXPECT_EQ(default_template["-i"][1], "5");

  EXPECT_EQ(default_template["-f"][0], "float");
  EXPECT_EQ(default_template["-f"][1], "5.520000");

  EXPECT_EQ(default_template["-d"][0], "double");
  EXPECT_EQ(default_template["-d"][1], "7.156656");

  EXPECT_EQ(default_template["-c"][0], "string");
  EXPECT_EQ(default_template["-c"][1], "my_cstring");

  EXPECT_EQ(default_template["-s"][0], "string");
  EXPECT_EQ(default_template["-s"][1], "my_storage");
  EXPECT_EQ(default_template["--storage"][0], "string");
  EXPECT_EQ(default_template["--storage"][1], "my_storage");

  EXPECT_EQ(default_template["-b"][0], "bool");
  EXPECT_EQ(default_template["-b"][1], "true");
  EXPECT_EQ(default_template["--boolean"][0], "bool");
  EXPECT_EQ(default_template["--boolean"][1], "true");
}

TEST_F(ProgramOptionsEnvironment, check_parse_args_test) {
  parser.add_argument("-i", "int", 5);
  parser.add_argument("-f", "float", 5.52);
  parser.add_argument("-d", "double", 7.156656);
  parser.add_argument("-c", "string", "my_cstring");
  parser.add_argument("-s", "--storage", "string", "my_storage");
  parser.add_argument("-b", "--boolean", "bool", "true");

  int argc = 9;
  char const *argv[] = {"./program_options", "-i", "-10", "-f", "253.6561", "--storage=database", "-d", "20.3322", "--boolean=false"};
  parser.parse_args(argc, argv);

  EXPECT_EQ(parser.get_string_args()["-c"], "my_cstring");
  EXPECT_EQ(parser.get_string_args()["--storage"], "database");
  EXPECT_EQ(parser.get_int_args()["-i"], -10);
  EXPECT_EQ(parser.get_float_args()["-f"], std::stof("253.6561"));
  EXPECT_EQ(parser.get_double_args()["-d"], 20.3322);
  EXPECT_EQ(parser.get_bool_args()["--boolean"], false);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
