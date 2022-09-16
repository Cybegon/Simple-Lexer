file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE PHSRC ${CMAKE_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_SOURCE_DIR}/src/public)
include_directories(${CMAKE_SOURCE_DIR}/src/public/libsl)

add_library(${CMAKE_PROJECT_NAME} STATIC ${SRC} ${HSRC} ${PHSRC})
