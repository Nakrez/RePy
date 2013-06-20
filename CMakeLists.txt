cmake_minimum_required(VERSION 2.8)

project(TyPy CXX)

FIND_PROGRAM(BISON_EXECUTABLE NAMES bison bison.exe )

IF(BISON_EXECUTABLE)
     SET(BISON_FOUND TRUE)

     EXECUTE_PROCESS(COMMAND ${BISON_EXECUTABLE} --version
         OUTPUT_VARIABLE _BISON_VERSION
     )
     string (REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" BISON_VERSION 
"${_BISON_VERSION}")
ENDIF(BISON_EXECUTABLE)

IF(BISON_FOUND)
   IF(NOT Bison_FIND_QUIETLY)
     MESSAGE(STATUS "Found Bison: ${BISON_EXECUTABLE}")
   ENDIF(NOT Bison_FIND_QUIETLY)
ELSE(BISON_FOUND)
   IF(Bison_FIND_REQUIRED)
     MESSAGE(FATAL_ERROR "Could not find Bison")
   ENDIF(Bison_FIND_REQUIRED)
ENDIF(BISON_FOUND)

FIND_PROGRAM(FLEX_EXECUTABLE NAMES flex flex.exe )

IF(FLEX_EXECUTABLE)
     SET(FLEX_FOUND TRUE)

     EXECUTE_PROCESS(COMMAND ${FLEX_EXECUTABLE} --version
         OUTPUT_VARIABLE _FLEX_VERSION
     )
     string (REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" FLEX_VERSION
"${_FLEX_VERSION}")
ENDIF(FLEX_EXECUTABLE)

IF(FLEX_FOUND)
   IF(NOT Flex_FIND_QUIETLY)
     MESSAGE(STATUS "Found Flex: ${FLEX_EXECUTABLE}")
   ENDIF(NOT Flex_FIND_QUIETLY)
ELSE(FLEX_FOUND)
   IF(Flex_FIND_REQUIRED)
     MESSAGE(FATAL_ERROR "Could not find Flex")
   ENDIF(Flex_FIND_REQUIRED)
ENDIF(FLEX_FOUND)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -std=c++0x -I${CMAKE_CURRENT_SOURCE_DIR}/src -I${CMAKE_CURRENT_SOURCE_DIR}/lib -O0 -g -ggdb")

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -std=c++0x -I${CMAKE_CURRENT_SOURCE_DIR}/src -I${CMAKE_CURRENT_SOURCE_DIR}/lib -O2 -s -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")

ADD_LIBRARY(typy_lib STATIC
            lib/misc/error.cc
            lib/misc/indent.cc
            )

SET_TARGET_PROPERTIES(
    typy_lib
    PROPERTIES
    VERSION 0.0.1
    OUTPUT_NAME typy
)

##########################
#         BISON          #
##########################

SET(src_parser "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/parser.yy")
SET(dst_parser "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/parser.cc")

ADD_CUSTOM_COMMAND(
        OUTPUT "${dst_parser}"
        DEPENDS "${src_parser}"
        COMMAND
        ${BISON_EXECUTABLE} -o${dst_parser} ${src_parser}
        )

add_custom_target(typy_grammar DEPENDS "${dst_parser}")

##########################
#          FLEX          #
##########################

SET(src_lexer "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/lexer.ll")
SET(dst_lexer "${CMAKE_CURRENT_SOURCE_DIR}/src/parser/lexer.cc")

ADD_CUSTOM_COMMAND(
        OUTPUT "${dst_lexer}"
        DEPENDS "${src_lexer}"
        COMMAND
        ${FLEX_EXECUTABLE} -o${dst_lexer} ${src_lexer}
        )

add_custom_target(typy_lexer DEPENDS "${dst_lexer}")

add_executable(typy
               src/parser/parser.cc
               src/parser/lexer.cc
               src/parser/driver.cc
               src/parser/tasks.cc

               src/ast/ast.cc
               src/ast/stmt.cc
               src/ast/expr.cc
               src/ast/if-stmt.cc
               src/ast/while-stmt.cc
               src/ast/pass-stmt.cc
               src/ast/break-stmt.cc
               src/ast/continue-stmt.cc
               src/ast/expr-stmt.cc
               src/ast/assign-expr.cc
               src/ast/unary-expr.cc
               src/ast/op-expr.cc
               src/ast/numeral-expr.cc
               src/ast/string-expr.cc
               src/ast/var.cc
               src/ast/id-var.cc
               src/ast/function-var.cc
               src/ast/pretty-printer.cc
               src/ast/tasks.cc

               src/tasks/task-invoker.cc
               src/tasks/task-register.cc
               src/tasks/basic-task.cc
               src/tasks/callback-task.cc

               src/typy.cc)

target_link_libraries(typy typy_lib)

add_dependencies(typy typy_grammar)
add_dependencies(typy typy_lexer)

LIST(APPEND extra_clean_files
     src/parser/parser.hh
     src/parser/location.hh
     src/parser/position.hh
     src/parser/stack.hh
)

SET_DIRECTORY_PROPERTIES(PROPERTIES
                         ADDITIONAL_MAKE_CLEAN_FILES
                         "${extra_clean_files}")

#######################
#######################
##    CLEAR RULE     ##
#######################
#######################

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_clear.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(distclean
  COMMAND ${CMAKE_BUILD_TOOL} clean
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake")
