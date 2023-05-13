#cmake_minimum_required(VERSION 3.10)

#project(MyProject)

# Locate and include headers in the 'inc' directory
#include_directories(inc)

# Add all source files in the 'src' directory to the project
#aux_source_directory(src SOURCES)

# Create an executable with the given sources
#add_executable(main ${SOURCES} main.cpp)

# Specify any necessary linker flags
#target_link_libraries(main)

cmake_minimum_required(VERSION 3.5)

project(my_project)

set(CMAKE_CXX_STANDARD 17)

# Add source files
set(SOURCES 
    src/main.cpp
    src/core.cpp
)

# Add header files
set(HEADERS
    inc/overload.hh
    inc/vector.hh
    inc/core.hh
)

# Add operator header files
set(OPERATORS_HEADERS
    #inc/operators.hh
)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${OPERATORS_HEADERS})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Set compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# Set linker flags
target_link_libraries(${PROJECT_NAME} PRIVATE -lpthread)
