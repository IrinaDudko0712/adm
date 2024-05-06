add_library(admlib admlib.cpp include/admlib/admlib.hpp)
set_property(TARGET admlib PROPERTY CXX_STANDARD 20)
target_include_directories(admlib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
include_directories(${LIBIGL_INCLUDE_DIRS})
#target_link_libraries( admlib igl::igl_core igl_copyleft::igl_copyleft_core)
#include_directories(nvolib ${STB_INCLUDE_DIRS})
#target_link_libraries( nvolib ${STB_INCLUDE_DIRS})
include_directories( "${VCPKG_ROOT}/installed/x64-windows/include")

 target_link_libraries(admlib sfml-graphics)

 install(TARGETS admlib)


