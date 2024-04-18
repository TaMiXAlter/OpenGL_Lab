cmake_minimum_required(VERSION 3.16)
project(ComputerGraph)


set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# this two line don't work new.
set(INCLUDE_FILE)
set(SRC_FILES)
add_subdirectory(Thirdparty/freeglut)

# you need pre-install OpenGL, GLU, please google
add_executable(${PROJECT_NAME} ${SRC_DIR}/Midterm.cpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} freeglut_static)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Thirdparty/freeglut/include/GL)


target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resourse/OBJs4/")


