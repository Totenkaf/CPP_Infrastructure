// Copyright 2022 by Artem Ustsov
#include <sstream>

#include "program_options.hpp"

void ArgumentParser::fill_by_default_args() {
  for (const auto& [key, value] : argtemplate) {
    fill_args(key, value[0], value[1]);
  }
}

auto ArgumentParser::parse_parametrize_arg(std::string arg)
    -> std::pair<std::string, std::string> {
  std::string delimiter = "=";
  std::string token = arg.substr(0, arg.find(delimiter));
  arg.erase(0, arg.find(delimiter) + delimiter.length());
  return std::make_pair(token, arg);
}

void ArgumentParser::fill_args(const std::string& arg, const std::string& type,
                               const std::string& value) {
  try {
    if (type == "int") {
      int_args[arg] = stoi(value);
    } else if (type == "float") {
      float_args[arg] = stof(value);
    } else if (type == "double") {
      double_args[arg] = stod(value);
    } else if (type == "bool") {
      bool_args[arg] = to_bool(value);
    } else {
      string_args[arg] = value;
    }
  } catch (const std::exception& e) {
    throw std::invalid_argument(
        "value of arg <<" + arg + ">> is not convertable\n" +
        "template type is <<" + type + ">>\n" + "gave <<" + value + ">>");
  }
}

auto ::ArgumentParser::parse_args(int argc, char const* argv[]) -> int {
  if (argc < 2) {
    std::cerr << "too few arguments, need at least 2, <prog> <--param=value> or <prog> <-pos> <value>" << std::endl;
    return _EXIT_FAULT;
  }
  try {
    fill_by_default_args();

    for (int i = 1; i < argc; ++i) {
      auto arg = std::string(argv[i]);
      if (arg.starts_with("--")) {
        auto parsed_arg = parse_parametrize_arg(arg);
        auto type = argtemplate.at(parsed_arg.first)[0];
        fill_args(parsed_arg.first, type, parsed_arg.second);
      } else {
        auto type = argtemplate.at(arg)[0];
        fill_args(arg, type, argv[++i]);
      }
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return _EXIT_FAULT;
  }
  return _EXIT_SUCCESS; 
}

std::string ArgumentParser::to_str(const char* c) { return std::string(c); }

void ArgumentParser::make_args_template(const std::vector<std::string>& keys,
                                        const std::string& type,
                                        const std::string& value) {
  for (const auto& key : keys) {
    if (!key.empty()) {
      auto template_pair =
          std::make_pair(key, std::vector<std::string>{type, value});
      if (!argtemplate.insert(template_pair).second) {
        throw std::invalid_argument("key already exists");
      }
    }
  }
}

void ArgumentParser::print_argument_map() {
  for (const auto& [key, value] : argtemplate) {
    std::cout << key << ", " << value[0] << ", " << value[1] << std::endl;
  }
}

auto ArgumentParser::check_params(const std::string& first,
                                  const std::vector<std::string>& params) const
    -> bool {
  static const size_t MAX_SHORT_KEY_SIZE = 3;

  auto short_prefix = std::string_view("-");
  auto first_string = std::string(first);
  std::set<std::string> valid_values = {"string", "int", "float", "double", "bool"};

  if (!first_string.starts_with(short_prefix) ||
      first_string.size() > MAX_SHORT_KEY_SIZE) {
    std::cerr << first_string << " is not short key" << std::endl;
    return false;
  }

  auto long_prefix = std::string_view("--");
  switch (params.size()) {
    case 3:
      if (!params[0].starts_with(long_prefix)) {
        std::cerr << params[0] << " is not long key" << std::endl;
        return false;
      } else if (valid_values.find(params[1]) == valid_values.end()) {
        std::cerr << "wrong type value" << std::endl;
        return false;
      }
      break;
    case 2:
      if (valid_values.find(params[0]) == valid_values.end()) {
        std::cerr << "wrong type value" << std::endl;
        return false;
      }
      break;
    default:
      std::cerr << "bad number of arguments" << std::endl;
      return false;
  }
  return true;
}

auto ArgumentParser::get_default_template() const
    -> std::map<std::string, std::vector<std::string>> {
  return argtemplate;
}

auto ArgumentParser::to_bool(std::string val) -> bool {
    std::transform(val.begin(), val.end(), val.begin(), ::tolower);
    std::istringstream is(val);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}
