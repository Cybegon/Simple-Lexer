file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${PROJECT_SOURCE_DIR}/src/public)
include_directories(${PROJECT_SOURCE_DIR}/src/public/libsl)

add_library(sl ${SL_STATIC} ${SRC} ${HSRC} ${PHSRC})

target_include_directories(sl PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public>
        $<INSTALL_INTERFACE:include>
        )
