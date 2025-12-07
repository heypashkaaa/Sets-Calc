cmake_minimum_required(VERSION 3.23)
project(SETS_CALCULATOR C)

set(CMAKE_C_STANDARD 99)


# looking for bison and flex installed on the computer
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# 2. Configure Bison
BISON_TARGET(
        MyParser
        parser.y
        ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c # path for the generated file
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h # header
)

# 3. Configure Flex
FLEX_TARGET(
        MyScanner
        lexer.l
        ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c     # path for the generated file
)

# 4. Dependency (lexer should compile after the parser)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)


# CMAKE_CURRENT_BINARY_DIR - files
# CMAKE_CURRENT_SOURCE_DIR - headers
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Making an executable
add_executable(SETS_CALCULATOR
        main.c
        set.c
        set.h
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
        )