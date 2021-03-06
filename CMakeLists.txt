cmake_minimum_required(VERSION 2.8)

project(RePy CXX)

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

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -std=c++11 -I${CMAKE_CURRENT_SOURCE_DIR}/src -I${CMAKE_CURRENT_SOURCE_DIR}/lib -O0 -g -ggdb")

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -std=c++11 -I${CMAKE_CURRENT_SOURCE_DIR}/src -I${CMAKE_CURRENT_SOURCE_DIR}/lib -O2 -s -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")

ADD_LIBRARY(repy_lib STATIC
            lib/repy/builtin.cc
            )

SET_TARGET_PROPERTIES(
    repy_lib
    PROPERTIES
    VERSION 0.0.1
    OUTPUT_NAME repy
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

add_custom_target(repy_grammar DEPENDS "${dst_parser}")

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

add_custom_target(repy_lexer DEPENDS "${dst_lexer}")

add_executable(repy
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
               src/ast/return-stmt.cc
               src/ast/module-stmt.cc
               src/ast/function-dec.cc
               src/ast/class-dec.cc
               src/ast/assign-expr.cc
               src/ast/unary-expr.cc
               src/ast/op-expr.cc
               src/ast/numeral-expr.cc
               src/ast/string-expr.cc
               src/ast/yield-expr.cc
               src/ast/star-expr.cc
               src/ast/double-star-expr.cc
               src/ast/var.cc
               src/ast/id-var.cc
               src/ast/function-var.cc
               src/ast/field-var.cc
               src/ast/method-var.cc
               src/ast/pretty-printer.cc
               src/ast/typed.cc
               src/ast/tasks.cc

               src/bind/tasks.cc
               src/bind/binder.cc

               src/type/tasks.cc
               src/type/type.cc
               src/type/void.cc
               src/type/int.cc
               src/type/string.cc
               src/type/function.cc
               src/type/polymorphic.cc
               src/type/tuple.cc
               src/type/class.cc
               src/type/type-checker.cc

               src/builtin/builtin-library.cc

               src/cloner/tasks.cc
               src/cloner/ast-cloner.cc

               src/desugar/tasks.cc
               src/desugar/declaration-generator.cc
               src/desugar/global-desugar.cc

               src/cpp/tasks.cc
               src/cpp/code-generator.cc
               src/cpp/header-generator.cc

               src/tasks/task-invoker.cc
               src/tasks/task-register.cc
               src/tasks/basic-task.cc
               src/tasks/callback-task.cc
               src/tasks/boolean-task.cc

               src/misc/error.cc
               src/misc/indent.cc

               src/repy.cc)

add_dependencies(repy repy_grammar)
add_dependencies(repy repy_lexer)

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
