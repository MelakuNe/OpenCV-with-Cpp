# CMakeList.txt : CMake project for Pract, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
#include(CTest)
#enable_testing()

find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
# Add source to this project's executable.
add_executable (Pract "Pract.cpp" "Pract.h"  "Reserve.h")
target_link_libraries(Pract "${TORCH_LIBRARIES}")
target_link_libraries(Pract "${OpenCV_LIBS}")


# TODO: Add tests and install targets if needed.
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET Pract
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:Pract>)
endif (MSVC)
