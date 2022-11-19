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
Получать их значение после парсинга через operator[](<name>)

__Примечание:__
Достаточно реализации основных методов объекта, описанного в задании. Т.е. если у вас не будет, например, перегрузки конструктора с initializer_list, std::in_place или возможности использовать кастомный аллокатор - ничего страшного. Главное - реализовать основную идею

Контейнеры должны быть шаблонными, если в задании не указано иное.


Ссылка на распределение - [здесь](https://docs.google.com/spreadsheets/d/1SBwOcvxeQsJSgYD9QoMnDZc5UwioBjbNM4z8Ojmn25Y/edit#gid=0)

__Решение:__
Работа будет осуществляться с чтением из консоли дополнительных параметров для работы программы.

За дополнительные аргументы в С++ отвечают переменные int argc - количество переданных аргументов (всегда не меньше 1) и char* argv[] - массив указателей на строки. 

Требуется назначить схему данных, за нее будет отвечать класс - <имя>. У класса определен конструктор по умолчанию () и конструктор с параметром (имя парсера).

Класс в качестве параметра конструктора получает название парсера <название>.

Далее у класса существует публичный метод add_argument(), аргументами которого могут являться <-i> - краткое описание позиционного аргумента, <--input> - полное описание документа <string> - тип данных значения, <value> - значение по умолчанию.


Каждый вызов функции add_argument() создает новую запись - схему данных
Обработанные команды и значения по умолчанию хранятся внутри класса в хеш-таблице (std::map) argtemplates

Затем у класса существовует публичный метод parse_args(), который должен обращаться к argc и argv и производить их сравнение со схемой данных, полученной из add_argument().
После сравнения, аргументы записываются в соотвествующие хеш-таблицы согласно указанному типу данных.

Вызвать аргументы можно через [], к примеру, int_args["-i"] или int_args["--storage"]

__Примечание:__
В реализации библиотеки умышленно сделано две ошибки:  
- Ошибка при сборке. 
- Ошибка компилляции. 

Проверяющему требуется исправить их

## Quick Start
Корректная реализация библиотеки лежит в program_options_lib.zip  
Распаковка 
~~~
unzip program_options_lib.zip && rm -rf program_options_lib.zip
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
./program_options -i 5 -f 253.656 --storage=databse -d 20.33215669
~~~

Запуск тестов
~~~
сd test
./po_test
cd ../
~~~

Проверка покрытия и вывод отчета в консоль (только после запуска тестов)
~~~
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' "${HOME}" '/.cache/*' --output-file coverage.info
lcov --list coverage.info
cd ..
~~~
