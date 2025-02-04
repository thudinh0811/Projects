cmake_minimum_required(VERSION 3.15)

project (ShaderFun LANGUAGES C)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS src/*.c src/*.h)
if (EMSCRIPTEN)
    message("${CMAKE_CURRENT_LIST_DIR}")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
endif()

add_executable(App ${SOURCE_FILES})
if (MSVC)
	target_compile_options(App PRIVATE /W4 -D_CRT_SECURE_NO_WARNINGS)
else()
	target_compile_options(App PRIVATE -Wall -Wextra -g)
endif()

if(EMSCRIPTEN)
    set_target_properties(App PROPERTIES LINK_FLAGS "-sUSE_GLFW=3 --preload-file ./assets -sUSE_WEBGL2 -sFULL_ES3")
else()
    target_link_libraries(App glfw)
    target_link_libraries(App OpenGL::GL)
endif()

find_library(MATH_LIB m)
if (MATH_LIB)
   target_link_libraries(App ${MATH_LIB})
endif()

target_include_directories(App PUBLIC include)
set_target_properties(App PROPERTIES C_STANDARD 17)
