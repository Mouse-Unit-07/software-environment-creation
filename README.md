# Development Environment Creation Repo
  - A development environment creation repository to test building a project w/ CMake, CppUTest, CppCheck, gcovr, and clang-format.
  - Original plan was to migrate to a Docker container, until seeing that Windows Docker containers require Windows Pro, and that our MCU doesn't have a mainstream Linux toolchain. 
  - A uniform development can still be made, it just requires a list of installation and setup instructions when Docker is out of the picture.

## cmake directory
- Generic build space to clone down your source code repo and build w/ CMake to target both Atmel/Microchip's AVR32 MCU and Windows. 
- Hello World project may be cloned into src/ as an example
- Provides unit testing, CppCheck, and format checking when a project is built for Windows

- **Dependent on**
  - MSYS2 MINGW64 installation: C:/msys64/mingw64/bin
    - gcc 15.0.1
    - g++ 15.0.1
    - gcov 15.0.1
    - CMake 4.0.2
    - Ninja 1.12.1
  - Python 3.9
    - pip 25.1.1 -> gcovr 8.3 (Python wrapper around gcov)
  - CppUTest: https://github.com/cpputest/cpputest.git
  - AVR32 toolchain: C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr32/avr32-gnu-toolchain/bin
  - AVR32 include library: C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/UC3L_DFP/1.0.59/include/AT32UC3L0256
- **Build Instructions**
  - AVR32 MCU build
    - navigate to top level project directory w/ MSYS2 MINGW64 terminal
    - `cmake --preset mcu-build`
    - `cmake --build --preset mcu-build`
  - Windows build
    - navigate to top level project directory w/ MSYS2 MINGW64 terminal
    - `cmake --preset windows-build`
    - `cmake --build --preset windows-build`
    - `ctest --preset windows-build` to run CppUTest unit tests
  - running CppCheck
    - build Windows build
    - navigate to the Windows build directory `build/windows_build` w/ MSYS2 MINGW64 terminal, then run CMake "build" command to run CppCheck
    - `cmake --build . --target cppcheck`
  - running clang-format_sources
    - build Windows build
    - navigate to the Windows build directory `build/windows_build` w/ MSYS2 MINGW64 terminal, then run CMake "build" command to run clang-format
    - `cmake --build . --target format_sources`
    - formatted copies of source files will be in build/windows_build/clang-format-output
  - running gcovr
    - build Windows build and run ctest
    - open Windows command prompt where gcovr's been installed through pip
    - navigate to top level project directory
    - `gcovr -r . --filter=src/`

## microchip-studio-ide directory
- Hello World project that builds using Microchip Studio IDE
- Exists to analyze the compiler/linker flags needed for CMake to build a project using the AVR32 toolchain
- **Dependent on**
  - Microchip Studio installation