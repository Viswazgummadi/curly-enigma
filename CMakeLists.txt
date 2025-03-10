cmake_minimum_required(VERSION 3.10)

project(compiler)

# Find Flex and Bison
find_program(FLEX_EXECUTABLE flex)
find_program(BISON_EXECUTABLE bison)

if (NOT FLEX_EXECUTABLE)
  message(FATAL_ERROR "flex not found")
endif()

if (NOT BISON_EXECUTABLE)
  message(FATAL_ERROR "bison not found")
endif()

# Define generated source locations in the build directory
set(LEXER_OUTPUT_C "${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c")
set(PARSER_OUTPUT_C "${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c")
set(PARSER_OUTPUT_H "${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h")

# Configure Flex and Bison
add_custom_command(
  OUTPUT ${LEXER_OUTPUT_C} ${PARSER_OUTPUT_C} ${PARSER_OUTPUT_H}
  COMMAND ${FLEX_EXECUTABLE} -o ${LEXER_OUTPUT_C} ${CMAKE_SOURCE_DIR}/src/lexer/lexer.l
  COMMAND ${BISON_EXECUTABLE} -Wcounterexamples -d -o ${PARSER_OUTPUT_C} ${CMAKE_SOURCE_DIR}/src/parser/parser.y
  DEPENDS ${CMAKE_SOURCE_DIR}/src/lexer/lexer.l ${CMAKE_SOURCE_DIR}/src/parser/parser.y
)

# Define source files
set(SOURCE_FILES
  src/main.c
  src/ast/ast.c
  src/semantic/semantic.c
  src/codegen/codegen.c
  src/symbol/symbol.c
  ${LEXER_OUTPUT_C}
  ${PARSER_OUTPUT_C}
)

# Add include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/ast
  ${CMAKE_SOURCE_DIR}/src/symbol
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Create executable
add_executable(compiler ${SOURCE_FILES})

# Set properties for generated files
set_source_files_properties(
    ${PARSER_OUTPUT_C}
    PROPERTIES
    GENERATED TRUE
)
set_source_files_properties(
    ${LEXER_OUTPUT_C}
    PROPERTIES
    GENERATED TRUE
)

# Link against math library, if needed
target_link_libraries(compiler m)

