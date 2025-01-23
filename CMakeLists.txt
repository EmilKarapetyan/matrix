cmake_minimum_required(VERSION 3.22.)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    ../main.cpp
    ../matrix.h
)

add_executable(matrix_lib ${SOURCE_FILES})

find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy REQUIRED)
# Add a CMake target for clang-tidy
find_program(CLANG_TIDY "clang-tidy")

if(CMAKE_BUILD_TYPE MATCHES Debug )
   # set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,bugprone-* ")
    add_custom_target(clang-tidy-check ALL
    COMMAND ${CLANG_TIDY_EXECUTABLE} -checks=-*,modernize-use-override,-warnings-as-errors -fix -format-style=file 
            -p ${CMAKE_BINARY_DIR}/compile_commands.json
            ${SOURCE_FILES}
            -header-filter=.*
)

  add_dependencies(matrix_lib clang-tidy-check) 
endif() 


# Add Clang-Format target
add_custom_target(clang-format-check ALL
    COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILES}
)

