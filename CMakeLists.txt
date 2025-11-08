cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME Engine)

project(${PROJECT_NAME})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND SOURCES src/main.cpp)

set(LIBS_ROOT "libs")
set(LIBS_FILES)

# GLFW Configuration ======================================================================================
set(GLFW_ROOT "" CACHE PATH "Path to GLFW root directory (should contain include/ and lib/)")
if(NOT EXISTS "${GLFW_ROOT}/include/GLFW/glfw3.h")
    message(FATAL_ERROR "Could not find GLFW in '${GLFW_ROOT}'. Please set GLFW_ROOT to the correct directory.")
endif()
set(GLFW_INCLUDE_DIR "${GLFW_ROOT}/include")
set(GLFW_LIBRARY_DIR "${GLFW_ROOT}/lib")
link_directories(${GLFW_LIBRARY_DIR})
include_directories(${GLFW_INCLUDE_DIR})
# GLFW ====================================================================================================

# GLAD Configuration ======================================================================================
set(GLAD_ROOT "" CACHE PATH "Path to GLAD root directory (should contain include/)")
if(NOT EXISTS "${GLAD_ROOT}/include/glad/glad.h")
    message(FATAL_ERROR "Could not find GLAD in '${GLAD_ROOT}'. Please set GLAD_ROOT to the correct directory.")
endif()
set(GLAD_INCLUDE_DIR "${GLAD_ROOT}/include")
include_directories(${GLAD_INCLUDE_DIR})
configure_file(
    ${GLAD_ROOT}/src/glad.c
    ${CMAKE_SOURCE_DIR}/${LIBS_ROOT}
    COPYONLY)
list(APPEND LIBS_FILES ${CMAKE_SOURCE_DIR}/${LIBS_ROOT}/glad.c)
# GLAD ====================================================================================================

# GLM Configuration ======================================================================================
set(GLM_ROOT "" CACHE PATH "Path to GLM root directory (should contain glm/)")
if(NOT EXISTS "${GLM_ROOT}/glm/glm.hpp")
    message(FATAL_ERROR "Could not find glm in '${GLM_ROOT}'. Please set GLM_ROOT to the correct directory.")
endif()
include_directories(${GLM_ROOT})
# GLAD ====================================================================================================

# IMGUI Configuration ====================================================================================
set(IMGUI_ROOT "${CMAKE_SOURCE_DIR}/libs/imgui")
if(NOT EXISTS "${IMGUI_ROOT}/imgui.h")
    message(FATAL_ERROR "Could not find ImGui in '${CMAKE_SOURCE_DIR}/libs/imgui.h'. Please pull the ImGui submodule 'git pull --recurse-submodules'.")
endif()
include_directories(${IMGUI_ROOT})
file(GLOB IMGUI_FILES ${IMGUI_ROOT}/*.cpp ${IMGUI_ROOT}/*.h
    ${IMGUI_ROOT}/misc/cpp/*.cpp ${IMGUI_ROOT}/misc/cpp/*.h
    ${IMGUI_ROOT}/backends/*_glfw* 
    ${IMGUI_ROOT}/backends/*opengl3*)
list(APPEND LIBS_FILES ${IMGUI_FILES})
# IMGUI ==================================================================================================

# ASSIMP Configuration ====================================================================================
set(ASSIMP_ROOT "" CACHE PATH "Path to ASSIMP root directory (should contain include/ and lib/)")
if(NOT EXISTS "${ASSIMP_ROOT}/include/assimp/config.h")
    message(FATAL_ERROR "Could not find ASSIMP in '${ASSIMP_ROOT}'. Please set ASSIMP_ROOT to the correct directory.")
endif()
set(ASSIMP_INCLUDE_DIR "${ASSIMP_ROOT}/include")

set(ASSIMP_DLLS_DEBUG_PATH  "${ASSIMP_ROOT}/bin/Debug")
set(ASSIMP_DLLS_RELEASE_PATH "${ASSIMP_ROOT}/bin/Release")
# ASSIMP ====================================================================================================

# STB_IMAGE Configuration ====================================================================================
set(STB_ROOT "${CMAKE_SOURCE_DIR}/libs/stb")
if(NOT EXISTS "${STB_ROOT}/stb_image.h")
    message(FATAL_ERROR "Could not find stb_image.h in '${STB_ROOT}/stb'. Please pull the stb submodule 'git pull --recurse-submodules'.")
endif()
include_directories(${LIBS_ROOT}/stb)

# STB_IMAGE ====================================================================================================

set(SRC_ROOT "src")
set(SHADER_ROOT "shaders")

file(GLOB_RECURSE SHADER_FILES ${SHADER_ROOT}/**.frag ${SHADER_ROOT}/*.frag ${SHADER_ROOT}/**.vert ${SHADER_ROOT}/*.vert)
file(GLOB_RECURSE HEADER_FILES ${SRC_ROOT}/**.h ${SRC_ROOT}/*.h)
file(GLOB_RECURSE SOURCE_FILES ${SRC_ROOT}/**.cpp ${SRC_ROOT}/*.cpp)

include_directories(${SRC_ROOT}/engine)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES} ${LIBS_FILES} "README.md" ".clang-format")

source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SHADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${LIBS_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE "${GLFW_LIBRARY_DIR}/glfw3.lib")

# sets the Editor project as the default startup project in Visual Studio
set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/$<CONFIG>/resources)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/$<CONFIG>/shaders)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/shaders)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<$<CONFIG:Debug>:${ASSIMP_DLLS_DEBUG_PATH}>
        $<$<CONFIG:Release>:${ASSIMP_DLLS_RELEASE_PATH}>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)


# TEST=================================================================================================================
enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/tests/)
add_subdirectory(tests)
