cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(dist_pt2line)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(
  VTK
  COMPONENTS vtkCommonCore vtkCommonDataModel
  QUIET)
if(NOT VTK_FOUND)
  message("Skipping dist_pt2line: ${VTK_NOT_FOUND_MESSAGE}")
  return()
endif()
message(STATUS "VTK_VERSION: ${VTK_VERSION}")
if(VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(dist_pt2line MACOSX_BUNDLE src/dist_pt2line.cc)
  target_link_libraries(dist_pt2line PRIVATE ${VTK_LIBRARIES})
else()
  # include all components
  add_executable(dist_pt2line MACOSX_BUNDLE src/dist_pt2line.cc)
  target_link_libraries(dist_pt2line PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(TARGETS dist_pt2line MODULES ${VTK_LIBRARIES})
endif()
