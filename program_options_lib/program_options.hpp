// Copyright 2022 by Artem Ustsov

#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class ArgumentParser {
 public:
  explicit ArgumentParser(std::string description_)
      : description(std::move(description_)) {}

  template <typename... Params>
  void add_argument(const char* first, const Params&... params);

  void print_argument_map();
  void parse_args(int argc, char const* argv[]);

  [[nodiscard]] auto get_default_template() const
      -> std::map<std::string, std::vector<std::string>>;

  [[nodiscard]] auto get_description() const -> std::string {
    return description;
  }

  std::map<std::string, int> int_args;
  std::map<std::string, float> float_args;
  std::map<std::string, double> double_args;
  std::map<std::string, std::string> string_args;

 private:
  std::string description;
  std::map<std::string, std::vector<std::string>> argtemplate;

  void make_args_template(const std::vector<std::string>& keys,
                          const std::string& type, const std::string& value);
  [[nodiscard]] auto check_params(const std::string& first,
                                  const std::vector<std::string>& params) const
      -> bool;

  void fill_by_default_args();
  void fill_args(const std::string& arg, const std::string& type,
                 const std::string& value);
  static auto parse_parametrize_arg(std::string arg)
      -> std::pair<std::string, std::string>;

  template <typename ValueType>
  auto to_str(const ValueType& val) -> std::string;

  auto to_str(const char* c) -> std::string;
};

template <typename... Params>
void ArgumentParser::add_argument(const char* first, const Params&... params) {
  static const size_t MAX_ARGUMENTS = 3;

  if (sizeof...(params) > MAX_ARGUMENTS) {
    std::cout << "too many arguments in template" << std::endl;
    return;
  }

  std::vector<std::string> params_vector{to_str(params)...};
  std::string short_key;
  std::string long_key;
  std::string type;
  std::string value;

  if (check_params(std::string(first), params_vector)) {
    short_key = std::string(first);
    if (params_vector.size() == 3) {
      long_key = params_vector[0];
      type = params_vector[1];
      value = params_vector.back();
    } else if (params_vector.size() == 2) {
      type = params_vector[0];
      value = params_vector.back();
    }
    try {
      make_args_template(std::vector<std::string>{short_key, long_key}, type,
                         value);
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
    }
  } else {
    std::cout << "bad check" << std::endl;
  }
}
