file(GLOB_RECURSE HSRC ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

include_directories(${CMAKE_SOURCE_DIR}/src/public)

add_executable(${CMAKE_PROJECT_NAME}-example ${SRC} ${HSRC})
target_link_libraries(${CMAKE_PROJECT_NAME}-example ${CMAKE_PROJECT_NAME})
