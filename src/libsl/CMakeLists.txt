file(GLOB_RECURSE PHSRC ${PROJECT_SOURCE_DIR}/src/public/libsl/*.h)
file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(sl ${SL_STATIC} ${SRC} ${HSRC} ${PHSRC})
target_link_libraries(sl PUBLIC datatypes)

target_include_directories(sl PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/public/libsl>
        $<INSTALL_INTERFACE:include>
        )
