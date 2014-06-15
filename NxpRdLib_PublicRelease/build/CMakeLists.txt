cmake_minimum_required (VERSION 2.8)
project (nxprd)

include_directories (
    "${PROJECT_SOURCE_DIR}/../intfs"
    "${PROJECT_SOURCE_DIR}/../types"
    "${PROJECT_SOURCE_DIR}/../comps/phpalSli15693/src/Sw"
)

set(EXT_LIBS  pthread  m)

add_definitions(-g -O0)

file(GLOB_RECURSE SOURCE_TMP "${PROJECT_SOURCE_DIR}/../*.c" )
list(APPEND SOURCE ${SOURCE_TMP})
add_library(${PROJECT_NAME} ${SOURCE})
