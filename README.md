[![.github/workflows/ci.yml](https://github.com/Totenkaf/CPP_Infrastructure/actions/workflows/ci.yml/badge.svg)](https://github.com/Totenkaf/CPP_Infrastructure/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/Totenkaf/CPP_Infrastructure/branch/HW_1-Artem-dev/graph/badge.svg?token=zHVutFCla6)](https://codecov.io/gh/Totenkaf/CPP_Infrastructure)
# VK | SEM II_CPP_Infrastructure | HW_1

================================================================ 

## Program Options (Python like)

Студент (выполнил): __А.Усцов__  
Студент (проверил): __М. Кежаев__  

Преподаватель: __Ф.Петряйкин__

### Описание:

Реализуйте аналог библиотеки для разбора program options. Нужно поддерживать:  
- Позиционные аргументы (строки)
- Именованные аргументы (числа, строки).

Ваша реализация должна уметь:
Получать схему аргументов (какие могут быть именованные, какого типа, …), сколько ожидается позиционных
Получать их значение после парсинга через operator[](<name>).

__Примечание:__
Достаточно реализации основных методов объекта, описанного в задании. Т.е. если у вас не будет, например, перегрузки конструктора с initializer_list, std::in_place или возможности использовать кастомный аллокатор - ничего страшного.
Главное - реализовать основную идею

Ссылка на распределение - [здесь](https://docs.google.com/spreadsheets/d/1SBwOcvxeQsJSgYD9QoMnDZc5UwioBjbNM4z8Ojmn25Y/edit#gid=0)


__Code:__   
- ЯП: C++20
- Codestyle: snake_case, format=Google

__Решение:__
Работа будет осуществляться с чтением из консоли дополнительных позиционных и именованных аргументов.   
За дополнительные аргументы в С++ отвечают переменные int argc - количество переданных аргументов (всегда не меньше 1) и char* argv[] - массив указателей на строки.   

Функционал парсера реализует класс ArgumentParser.   
У класса реализован конструктор по умолчанию, и конструктор с одним параметром, который принимает имя парсера.  
~~~cpp
parser = ArgumentParser("my_parser");
parser.get_description();
~~~   

Пользователь внутри кода может самостоятельно указать схему аргументов: полное (для именованных) или сокращенное (для позиционных) имя аргумента, тип передаваемого аргумента, 
значение по умолчанию, если аргумент не передан. В шаблон аргументов обязательно должно быть передано сокращенное имя <-pos> и не более 3 дополнительных аргументов.    

За назначение схемы данных отвечает метод add_argument():
~~~
// общая схема
parser.add_argument(<postional>, <parametrized>(optional), <data type>, <default value>);
~~~
Поддерживаются следующие типы данных (<data type>):
- int - целочисленный
- string - строковый
- float - вещественный одинарной точности
- double - вещественный двойной точности
- bool - булев тип (принимается значение true/false, внутри программы воспринимается как bool (0/1))    


Примеры задания схем:    
~~~cpp
// позиционный целочисленный аргумент со значением по умолчанию = 5.
parser.add_argument("-i", "int", 5);

// позиционный или именованный строковый аргумент со значением по умолчанию = .my_storage
parser.add_argument("-s", "--storage", "string", "my_storage");
~~~

Каждый вызов функции add_argument() создает новую запись - схему данных.
Обработанные команды и значения по умолчанию хранятся внутри класса в хеш-таблице (std::map) argtemplates.   

Пользователские аргументы передаются через argc и argv.  
Для разбора аргументов командной строки у класса ArgumentParser существует метод parse_args, который принимает argc и argv.    
Работа метода заключается в том, чтобы разбить полученный массив символов argv, заполнить шаблон argtemplates шаблонами по умолчанию, провалидировать
входные значения. Стоит отметить, что итерирование по последовательности символов не учитывает название передаваемой программы.    

Метод разбивает строчку аргументов, валидирует передаваемые аргументы, и в зависимости от типа данных помещает аргументы в соотвествующие хеш-таблицы:    
- get_int_args - целочисленные аргументы    
- get_string_args - строковые аргументы   
- get_float_args - вешественные одинарной точности   
- get_double_args - вещественные двойной точности   
- get_bool_args - логические аргументы   

Для получения конкретного аргумента конкретного типа используются геттеры и [].   
Пример:
  
~~~cpp
parser = ArgumentParser("my_parser");
parser.add_argument("-i", "int", 5);
parser.add_argument("-s", "--storage", "string", "my_storage");

parser.parse_args(argc, argv);
std::cout << parser.get_int_args()["-i"] << std::endl;
std::cout << parser.get_string_args()["--storage"] << std::endl;
~~~


__Примечание:__
В реализации библиотеки умышленно сделано две ошибки:  
- Ошибка линковки. 
- Ошибка работы исключения. 

Проверяющему требуется найти и исправить их в виде пулл-реквеста в рабочую ветку проекта.  

## Quick Start
Корректная реализация библиотеки и тестов лежит в correct_realisation.zip 
Распаковка 
~~~
unzip correct_realisation.zip -d ./correct_realisation && rm -rf correct_realisation.zip
~~~


Установка зависимостей
~~~
sudo apt-get update && sudo apt-get install -y gcc g++
sudo apt-get update && sudo apt-get install -y cmake
sudo apt-get update && sudo apt-get install -y valgrind
sudo apt-get update && sudo apt-get install -y lcov
sudo apt-get update && sudo apt-get install -y python3-pip
~~~

Установка GTest
~~~
git clone https://github.com/google/googletest
pwd
cd ./googletest
pwd
mkdir -p build && cd build
sudo cmake ..
sudo make
sudo make install
cd ../../
pwd
~~~

Сборка проекта (динамическая библиотека, включение тестов, включение покрытия)
~~~
mkdir build && cd build
sudo cmake -DBUILD_DYNAMIC=ON -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON ..
make
~~~

Запуск программы
~~~
./program_options -i 5 -f 253.656 --storage=databse -d 20.33215669 --boolean=false
~~~

Запуск юнит тестов
~~~
сd test
./po_test
cd ../
~~~

Запуск интеграционных тестов
~~~
сd build
python3 ../test/program_options_integrity_test.py
cd ../
~~~

Проверка покрытия и вывод отчета в консоль (только после запуска тестов)
~~~
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' "${HOME}" '/.cache/*' --output-file coverage.info
lcov --list coverage.info
cd ..
~~~
