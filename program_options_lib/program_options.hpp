// Copyright 2022 by Artem Ustsov

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>


class ArgumentParser {
public:
    explicit ArgumentParser(std::string description_)
    : description(description_)
    {}

    template <typename... Params> 
    void add_argument(const char* first, const Params&... params);

    void print_argument_map();
    void parse_args(int argc, char const *argv[]);

    std::map<std::string, std::vector<std::string>> get_default_template() const;

    std::string get_description() const {
        return description;
    }

    std::map<std::string, int> int_args;
    std::map<std::string, float> float_args;
    std::map<std::string, double> double_args;
    std::map<std::string, std::string> string_args;

private:
    std::string description;
    std::map<std::string, std::vector<std::string>> argtemplate;

    void make_args_template(std::vector<std::string> keys, std::string type, std::string value);
    bool check_params(std::string first, const std::vector<std::string>& params) const;

    void fill_by_default_args();
    void fill_args(std::string arg, std::string type, std::string value);
    auto parse_parametrize_arg(std::string);
    
    template <typename ValueType>
    std::string to_str(const ValueType &val);

    std::string to_str(const char* c);
};

template <typename... Params> 
void ArgumentParser::add_argument(const char* first, const Params&... params) {
    static const size_t MAX_ARGUMENTS = 3;

    if (sizeof ...(params) > MAX_ARGUMENTS) {
        std::cout << "too many arguments in template" << std::endl;
        return;
    }
    
    std::vector<std::string> params_vector {to_str(params)...};
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
        }
        else if (params_vector.size() == 2) {
            type = params_vector[0];
            value = params_vector.back();
        }
        try {
            make_args_template(std::vector<std::string> {short_key, long_key}, type, value);
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    } else {
        std::cout << "bad check" << std::endl;
    }
}

template <typename T>
std::string ArgumentParser::to_str(const T &val) {
    return std::to_string(val);
}
