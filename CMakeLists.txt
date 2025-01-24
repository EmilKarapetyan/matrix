cmake_minimum_required(VERSION 3.22)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    ../main.cpp
    ../matrix.h
)

# Find clang-format
find_program(CLANG_FORMAT clang-format)

# Check if clang-format is found
if(CLANG_FORMAT)
    message(STATUS "clang-format found at: ${CLANG_FORMAT}")

    # Add a target to format the code
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILES}
        COMMENT "Running clang-format"
    )
else()
    message(WARNING "clang-format not found, skipping formatting.")
endif()

# Add the executable target
add_executable(matrix_lib ${SOURCE_FILES})

# Add the format target as a dependency to matrix_lib after it's defined
add_dependencies(matrix_lib format)  # Correct place for this line

# Find clang-tidy
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy REQUIRED)
find_program(CLANG_TIDY "clang-tidy")

# If in Debug mode, add clang-tidy checks
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_custom_target(clang-tidy-check ALL
        COMMAND ${CLANG_TIDY_EXECUTABLE} -checks=-*,modernize-use-override,-warnings-as-errors -fix -format-style=file 
            -p ${CMAKE_BINARY_DIR}/compile_commands.json
            ${SOURCE_FILES}
            -header-filter=.*)

    add_dependencies(matrix_lib clang-tidy-check)  # Correct, no changes needed here
endif()

# Add Clang-Format check target (optional)
add_custom_target(clang-format-check ALL
    COMMAND ${CLANG_FORMAT} -i ${SOURCE_FILES}
)
