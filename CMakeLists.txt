cmake_minimum_required(VERSION 3.0)

#TODO: check for zlib, python2.7 and other deps

include(ExternalProject)

ExternalProject_Add(
  "ilmbase"
  PREFIX "external"
  URL http://download.savannah.nongnu.org/releases/openexr/ilmbase-2.2.0.tar.gz
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/ilmbase_download
  SOURCE_DIR ${CMAKE_BINARY_DIR}/ilmbase_src
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_COMMAND ""
  CMAKE_ARGS
  "-DCMAKE_BUILD_TYPE=Release"
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
)

ExternalProject_Add(
  "openexr"
  PREFIX "external"
  URL http://download.savannah.nongnu.org/releases/openexr/openexr-2.2.0.tar.gz
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/openexr_download
  SOURCE_DIR ${CMAKE_BINARY_DIR}/openexr_src
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_COMMAND ""
  CMAKE_ARGS
  "-DCMAKE_BUILD_TYPE=Release"
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
  "-DILMBASE_PACKAGE_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
  )

ExternalProject_Add_StepDependencies(openexr build ilmbase)

ExternalProject_Add(
  "pyilmbase"
  PREFIX "external"
  URL http://download.savannah.gnu.org/releases/openexr/pyilmbase-2.2.0.tar.gz
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/pyilmbase_download
  SOURCE_DIR ${CMAKE_BINARY_DIR}/pyilmbase_src
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/openexr_src/./configure
  --prefix=${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_COMMAND "make"
  )

ExternalProject_Add_StepDependencies(pyilmbase build ilmbase openexr)
