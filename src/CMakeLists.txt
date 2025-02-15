cmake_minimum_required(VERSION 3.5)
project(Thermus_Application) # Put C,C++ or anything in place of XX 
set(CMAKE_CXX_STANDARD 20)    # Specify standard of language in place of STANDARD  
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()


add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../Thermus-Engine/src/main.cpp)
target_link_libraries(${PROJECT_NAME} raylib)