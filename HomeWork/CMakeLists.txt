cmake_minimum_required(VERSION 3.16)
project(OpenGl_Lab)

set(OpenGL_GL_PREFERENCE LEGACY)

add_subdirectory(${CMAKE_SOURCE_DIR}/Thirdparty/freeglut)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC_PATH ${CMAKE_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${SRC_PATH}/texture.cpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} freeglut)
target_link_libraries(${PROJECT_NAME}  ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Thirdparty/freeglut/include/GL)