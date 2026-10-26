cmake_minimum_required(VERSION 3.16)
project(CzasZadanie5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CheckCXXSourceCompiles)
check_cxx_source_compiles([=[
    #include <chrono>
    int main() {
        const std::chrono::zoned_time<std::chrono::seconds> czas{
            "Europe/Warsaw", std::chrono::sys_seconds{}};
        return czas.get_time_zone() == nullptr;
    }
]=] CHRONO_HAS_TIME_ZONES)

if(NOT CHRONO_HAS_TIME_ZONES)
    message(FATAL_ERROR
        "Zadanie 5 wymaga std::chrono::zoned_time z C++20. "
        "Wybrany kompilator lub jego biblioteka standardowa nie zapewnia "
        "wymaganej obslugi stref czasowych. Samo wlaczenie C++20 nie wystarczy. "
        "Wybierz srodowisko z obsluga chrono time zones i skonfiguruj projekt "
        "w nowym katalogu budowania. Szczegoly: ../README.md.")
endif()

add_executable(program main.cpp)
