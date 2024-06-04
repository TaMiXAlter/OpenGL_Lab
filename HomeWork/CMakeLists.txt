cmake_minimum_required(VERSION 3.16)
project(ComputerGraph)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(THIRDPARTY ${CMAKE_SOURCE_DIR}/Thirdparty)
set(OpenGL_GL_PREFERENCE "GLVND")
# this two line don't work new.
set(SRC_FILES
        ${THIRDPARTY}/gltools/src/GLBatch.cpp
        ${THIRDPARTY}/gltools/src/glew.c
        ${THIRDPARTY}/gltools/src/GLShaderManager.cpp
        ${THIRDPARTY}/gltools/src/GLTools.cpp
        ${THIRDPARTY}/gltools/src/GLTriangleBatch.cpp
        ${THIRDPARTY}/gltools/src/math3d.cpp
)
add_subdirectory(Thirdparty/freeglut)

# you need pre-install OpenGL, GLU, please google
# 查找OpenGL库
find_package(OpenGL REQUIRED)
add_executable(${PROJECT_NAME} ${SRC_DIR}/Robot.cpp  ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${OPENGL_glu_LIBRARY})
target_link_libraries(${PROJECT_NAME} freeglut_static)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Thirdparty/freeglut/include/GL ${THIRDPARTY}/gltools/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/texture")
