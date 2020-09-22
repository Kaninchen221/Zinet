
# Zinet
## Tools
+ **Build Tool**
  + [CMake](https://cmake.org/)
+ **Package Manager**
  + [Conan](https://conan.io/)
+ **Tests**
  + [Google Test](https://github.com/google/googletest)
+ **CI - Continuous Integration**
  + [Travis CI](https://travis-ci.org/)
+ **Static Analyzer**
  + **TODO**
## Additional Tools
+ **Code Coverage Analysis**
  + **TODO**
+ **Clang-Format**
+ **TODO: Clang-Tidy**
## Scripting
+ [**Language: Python 3.X**](https://www.python.org/)
+ [**Binder: PyBind11**](https://github.com/pybind/pybind11)
## Libs
+ [**PyBind11**](https://github.com/pybind/pybind11)
+ [**SPDLOG**](https://github.com/gabime/spdlog)
+ [**SFML**](https://www.sfml-dev.org/)
+ [**Google Test**](https://github.com/google/googletest)
+ [**Json**](https://github.com/nlohmann/json)
## Style
+ **Establishing a style guideline with Clang Format.**
+ **C++ Naming Conventions**
  + Types start with upper case:  `MyClass`.
  + Methods and member variables start with lower case:  `myFoo`.
  + Static methods and member variables start with upper case: `Create`.
  + Constants are all upper case:  `const double PI=3.1415;`.
  + Template parameters start with upper case:  `T`, `Size`.
  + Free functions start with lower case: `add`.
  + Macro names use upper case with underscores:  `API_MACRO`.
  + `Name private data without any prefix`.
  + `Name function parameters without any prefix`.
  + Use only `//` comments
  + Instead `include guards` use `#pragma once`. 
  + Prefer `{}` for default initialization.
  + `Don't use prefixes, use namespace instead`.
  + Use .hpp and .cpp for C++ file extensions.
## Practises
  + Use less often overloading for faster reflection.
  + In most times use `explicit` keyword.
  + Do not pass and return simple types by const reference.
  + **Avoid raw pointers**.
  + `STL containers` over ~~C style containers~~.
  + `Exceptions` ~~std::optional~~ ~~error codes~~.
  + `static_cast` ~~c style cast~~
  + `Variadic template`  ~~variadic function~~
  + `Avoid macros`
  + Forward declaration
  + `'\n'` ~~"\n"~~