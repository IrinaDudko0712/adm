cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
project(adm)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file" -G Ninja)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}/bin.relwithdbg)

set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "Vcpkg target triplet")
find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  FiltersSources
  IOGeometry
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  #ImagingOpenGL2
)
#set(VCPKG_ROOT "${CMAKE_CURRENT_SOURCE_DIR}C:\vcpkg")

#set(SFML_DIR "${VCPKG_ROOT}/installed/x64-windows/share/SFML")
#set(SFML_DIR "${VCPKG_ROOT}/installed/x64-windows/share/SFML")

#find_package(libigl CONFIG REQUIRED)
find_package(SFML COMPONENTS graphics REQUIRED)
find_package(Threads)

#find_package(Stb REQUIRED)
 
add_subdirectory(admlib)
add_subdirectory (tester)
add_subdirectory(visualization)
vtk_module_autoinit(
  TARGETS  visualization
  MODULES ${VTK_LIBRARIES}
)
