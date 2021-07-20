
# Zinet

## Tools
+ **Build Tool**
  + [CMake](https://cmake.org/)
+ **Package Manager**
  + [CMake](https://cmake.org/)
+ **Tests**
  + [Google Test](https://github.com/google/googletest)
+ **CI - Continuous Integration**
  + **TODO**
+ **Static Analyzer**
  + **TODO**
  
## Additional Tools
+ **TODO**

## Scripting
+ [**Language: Python 3.X**](https://www.python.org/)
+ [**Binder: PyBind11**](https://github.com/pybind/pybind11)

## Libs
+ [**PyBind11**](https://github.com/pybind/pybind11)
+ [**SPDLOG**](https://github.com/gabime/spdlog)
+ [**SFML**](https://www.sfml-dev.org/)
+ [**Google Test**](https://github.com/google/googletest)
+ [**Json**](https://github.com/nlohmann/json)
+ **TODO**

## Style **TODO**
+ **Establishing a style guideline with Clang Format.** **TODO**
+ **C++ Naming Conventions**
  + Types start with upper case:  `MyClass`.
  + Methods and member variables start with upper case:  `MyFoo`.
  + Static methods and member variables start with upper case: `Create`.
  + Constants start with upper case:  `const double Pi=3.1415;`.
  + Template parameters start with upper case and have postfix "Type": `ElementType`.
  + Free functions start with upper case: `add`.
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
  + In most times use `explicit` keyword. **TODO**
  + Do not pass and return simple types by const reference.
  + **Avoid raw pointers**.
  + `STL containers` over ~~C style containers~~.
  + `Exceptions` ~~std::optional~~ ~~error codes~~.
  + `static_cast` ~~c style cast~~
  + `Variadic template`  ~~variadic function~~
  + `Avoid macros`
  + Forward declaration
  + `'\n'` ~~"\n"~~