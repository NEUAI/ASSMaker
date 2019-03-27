cmake_minimum_required(VERSION 3.1.0)

project(ASSMaker)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(ASSMaker_SRCS
    src/ASSMaker.cpp
)
# Tell CMake to create the ASSMaker executable
add_executable(ASSMaker ${ASSMaker_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(ASSMaker Qt5::Widgets)
