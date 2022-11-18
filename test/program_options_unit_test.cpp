// Copyright 2022 by Artem Ustsov

#include <gtest/gtest.h>

#include "program_options.hpp"

class ProgramOptionsEnvironment : public ::testing::Test {
 public:
  ArgumentParser parser = ArgumentParser("test_parser");
};

TEST_F(ProgramOptionsEnvironment, get_description_test) {
  EXPECT_EQ(parser.get_description(), "test_parser");
}

TEST_F(ProgramOptionsEnvironment, check_default_template) {
  parser.add_argument("-i", "int", 5);
  parser.add_argument("-f", "float", 5.52);
  parser.add_argument("-d", "double", 7.156656);
  parser.add_argument("-c", "string", "my_cstring");
  parser.add_argument("-s", "--storage", "string", "my_storage");

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
}

// add_argument("-d", 7.256);
// add_argument("-f", "--flag", 7.256);
// add_argument("-i", "--input", 5);

// add_argument("-i", "int", 5);
// add_argument("-i", "--validation", "int", 5);
// add_argument("-f", "float", 5.52);
// add_argument("-f", "double", 7.1566568);
// add_argument("-s", "--storage", "string", "my_string");
// parser.add_argument("-i", "--validation", "int", 5);

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
