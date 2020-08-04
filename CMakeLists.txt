cmake_minimum_required(VERSION 3.0)

project(openexr-bind)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

set(PYTHON_VERSION 2.7 CACHE STRING "Major/Minor verison of Python. The default is  2.7. You may need to install python-dev")
STRING ( REGEX REPLACE "[.]" "" PYTHON_VERSION_NUMERIC ${PYTHON_VERSION} )
message (STATUS "Using Python: ${PYTHON_VERSION}")

set(BUILD_BOOST_PYTHON OFF CACHE BOOL "Build Boost - required if package manager does not ship specific version of boost-python bindings")

set(USE_CUSTOM_PYTHON ""  CACHE STRING "")

set(OFFLINE 0 CACHE BOOL "Skips download and uses tarballs downloaded into the root of the project")
set(EXR_VERSION 2.2.0 CACHE STRING "Major/Minor/Patch version of OpenEXR dependencies")

### Python - Custom / System version

if (NOT (USE_CUSTOM_PYTHON STREQUAL ""))
  set(CUSTOM_PYTHON_ROOT ${USE_CUSTOM_PYTHON})

  message(STATUS "Using custom python from :" ${CUSTOM_PYTHON_ROOT})

  if (NOT (EXISTS ${CUSTOM_PYTHON_ROOT}/bin/python${PYTHON_VERSION}))
     message (FATAL_ERROR "File does not exists:${CUSTOM_PYTHON_ROOT}/bin/python${PYTHON_VERSION} ")
  endif()

  # these have to be set before cmake starts
  # set (ENV{LD_LIBRARY_PATH} ${CUSTOM_PYTHON_ROOT}/lib:$ENV{LD_LIBRARY_PATH})
  # set (ENV{PATH} ${CUSTOM_PYTHON_ROOT}/bin:$ENV{PATH})
  # set (ENV{PYTHON} ${CUSTOM_PYTHON_ROOT}/bin/python${PYTHON_VERSION})

  # Check if custom Python has been added to PATH and LD_LIBRARY_PATH
  exec_program("python${PYTHON_VERSION} -c ''"  RETURN_VALUE  result)
  if ( ${result} GREATER 0)
    message(FATAL_ERROR "Set  Python${PYTHON_VERSION} in your environment before running CMake:
      export PATH=${CUSTOM_PYTHON_ROOT}/bin/:$PATH
      export LD_LIBRARY_PATH=${CUSTOM_PYTHON_ROOT}/lib:$LD_LIBRARY_PATH
     ")
  endif()

  # Pyilmbase ./configure is patched to detect custom version of Python but that
  # test requires includes and lib to be set up externally.
  if (NOT (EXISTS $ENV{PYTHON_INC_DIR}))
    message (FATAL_ERROR "Pyilmbase requires PYTHON_INC_DIR:
    export PYTHON_INC_DIR=${CUSTOM_PYTHON_ROOT}/include/python${PYTHON_VERSION}")
  endif()
  if (NOT (EXISTS $ENV{PYTHON_LIB_DIR}))
    message (FATAL_ERROR "Pyilmbase requires  PYTHON_LIB_DIR:
    export PYTHON_LIB_DIR=${CUSTOM_PYTHON_ROOT}/lib")
  endif()

else()
  find_package (Python ${PYTHON_VERSION} REQUIRED COMPONENTS Development )
  # On some systems libpythonX.X.so is missing, link it with existing libpythonX.Xm.so
  set(system_lib_path /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/)
  message (STATUS "Checking ${system_lib_path}/libpython${PYTHON_VERSION}.so")

  if (NOT (EXISTS ${system_lib_path}/libpython${PYTHON_VERSION}.so))
    message (WARNING "missing symlink to ${system_lib_path}/libpython${PYTHON_VERSION}.so")
  endif()

endif()

if (BUILD_BOOST_PYTHON)
  message (STATUS "Building Boost")
else()
  message (STATUS "Using system Boost")
  find_package(Boost REQUIRED COMPONENTS system python)
endif()

## Split version into major/minor components
string(REPLACE "." " " VERSION_LIST ${EXR_VERSION})
separate_arguments(VERSION_LIST)
list(GET VERSION_LIST 0 MAJOR)
list(GET VERSION_LIST 1 MINOR)
list(GET VERSION_LIST 2 PATCH)
set(DSO_VERSION "${MAJOR}_${MINOR}")
message(STATUS "EXR_VERSION: " ${MAJOR}.${MINOR}.${PATCH})
message(STATUS "DSO_VERSION: " ${DSO_VERSION})

if (OFFLINE)
  if (NOT (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ilmbase-${EXR_VERSION}.tar.gz))
    message(FATAL ERROR "
    In the OFFLINE mode download the following dependencies first:
    wget -P ${CMAKE_CURRENT_SOURCE_DIR} http://download.savannah.nongnu.org/releases/openexr/ilmbase-${EXR_VERSION}.tar.gz
    wget -P ${CMAKE_CURRENT_SOURCE_DIR} http://download.savannah.nongnu.org/releases/openexr/openexr-${EXR_VERSION}.tar.gz
    wget -P ${CMAKE_CURRENT_SOURCE_DIR} http://download.savannah.nongnu.org/releases/openexr/pyilmbase-${EXR_VERSION}.tar.gz
    wget -P ${CMAKE_CURRENT_SOURCE_DIR} https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.tar.gz 
    git clone  https://github.com/pybind/pybind11.git --branch v2.3.0 ${CMAKE_CURRENT_SOURCE_DIR}/pybind_src
    ")
  endif()
endif()
if(OFFLINE EQUAL 0)
  set (TAR_LOCATION http://download.savannah.nongnu.org/releases/openexr/)
  set (TAR_LOCATION_BOOST https://dl.bintray.com/boostorg/release/1.71.0/source/)
  set (PYBIND_REPO GIT_REPOSITORY https://github.com/pybind/pybind11.git)
else()
  set (TAR_LOCATION ${CMAKE_CURRENT_SOURCE_DIR})
  set (TAR_LOCATION_BOOST ${CMAKE_CURRENT_SOURCE_DIR})
  set (PYBIND_REPO URL ${CMAKE_CURRENT_SOURCE_DIR}/pybind_src)

endif()

### Boost-Python

if ( BUILD_BOOST_PYTHON )
ExternalProject_Add(
  "boost"
  PREFIX "external"
  URL ${TAR_LOCATION_BOOST}/boost_1_71_0.tar.gz
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/boost_download
  SOURCE_DIR ${CMAKE_BINARY_DIR}/boost_src
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_IN_SOURCE  1
  CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/boost_src/bootstrap.sh  --with-libraries=python --with-libraries=filesystem --with-libraries=system --with-python-version=${PYTHON_VERSION} --prefix=${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_COMMAND ${CMAKE_BINARY_DIR}/boost_src/b2
  INSTALL_COMMAND ${CMAKE_BINARY_DIR}/boost_src/b2 install
  )
endif()

### IlmBase

ExternalProject_Add(
  "ilmbase"
  PREFIX "external"
  URL ${TAR_LOCATION}/ilmbase-${EXR_VERSION}.tar.gz
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/ilmbase_download
  SOURCE_DIR ${CMAKE_BINARY_DIR}/ilmbase_src
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_COMMAND ""
  CMAKE_ARGS
  "-DCMAKE_BUILD_TYPE=Release"
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
)

# Create symlinks so that PyIlmbase does not complain.
add_custom_command(TARGET ilmbase POST_BUILD
  COMMAND ln -fs libIlmThread-${DSO_VERSION}.so.12 libIlmThread.so
  COMMAND ln -fs libImath-${DSO_VERSION}.so libImath.so
  COMMAND ln -fs libIexMath-${DSO_VERSION}.so libIexMath.so
  COMMAND ln -fs libIex-${DSO_VERSION}.so libIex.so
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/install_dir/lib/)

### OpenEXR

ExternalProject_Add(
  "openexr"
  PREFIX "external"
  URL ${TAR_LOCATION}/openexr-${EXR_VERSION}.tar.gz
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/openexr_download
  SOURCE_DIR ${CMAKE_BINARY_DIR}/openexr_src
  INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
  BUILD_COMMAND ""
  CMAKE_ARGS
  "-DCMAKE_BUILD_TYPE=Release"
  "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
  "-DILMBASE_PACKAGE_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
  )

# Arm (aarch64) is not handled at the moment by openexr_src/config.guess
# Ideally this should be patched but for now we handle this ourselves.
set(host_architecture ${CMAKE_HOST_SYSTEM_PROCESSOR})
if ((${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "aarch64") OR # jetson nano
    (${CMAKE_HOST_SYSTEM_PROCESSOR} STREQUAL "armv7l"))    # rpi 3B+
  set (host_architecture "x86_64-unknown-linux-gnu")
  message (STATUS "openexr build arch: ${host_architecture} (instead of ${CMAKE_HOST_SYSTEM_PROCESSOR})")
endif()

### PyIlmBase

# # Set PyilmBase commands
# set (PYILMBASE_PATCH_CMD "")
# set (PYILMBASE_CONFIGURE_CMD   CONFIGURE_COMMAND ${CMAKE_BINARY_DIR}/pyilmbase_src/./configure   --prefix=${CMAKE_CURRENT_SOURCE_DIR}/install_dir PKG_CONFIG_PATH=../../install_dir/lib/pkgconfig --build=${CMAKE_HOST_SYSTEM_PROCESSOR}-unknown-linux-gnu )
# if ( BUILD_BOOST_PYTHON )
#   ExternalProject_Add_StepDependencies(ilmbase build boost)

#   if (NOT (USE_CUSTOM_PYTHON STREQUAL ""))
#     set (PYILMBASE_PATCH_CMD sed -i -r s/^PYTHON_[A-Z]+_DIR=/\#&/ ${CMAKE_BINARY_DIR}/pyilmbase_src/configure)
#   endif()

#   set (PYILMBASE_CONFIGURE_CMD LD_LIBRARY_PATH=${CMAKE_CURRENT_SOURCE_DIR}/install_dir/lib:${CUSTOM_PYTHON_ROOT}/lib ${CMAKE_BINARY_DIR}/pyilmbase_src/./configure   --prefix=${CMAKE_CURRENT_SOURCE_DIR}/install_dir PKG_CONFIG_PATH=../../install_dir/lib/pkgconfig    --with-boost-include-dir=${CMAKE_CURRENT_SOURCE_DIR}/install_dir/include --with-boost-lib-dir=${CMAKE_CURRENT_SOURCE_DIR}/install_dir/lib  --with-boost-python-libname=boost_python${PYTHON_VERSION_NUMERIC}    --build=${CMAKE_HOST_SYSTEM_PROCESSOR}-unknown-linux-gnu )
# endif()

# ExternalProject_Add_StepDependencies(openexr build ilmbase)

# ExternalProject_Add(
#   "pyilmbase"
#   PREFIX "external"
#   URL ${TAR_LOCATION}/pyilmbase-${EXR_VERSION}.tar.gz
#   DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/pyilmbase_download
#   SOURCE_DIR ${CMAKE_BINARY_DIR}/pyilmbase_src
#   INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
#   PATCH_COMMAND ${PYILMBASE_PATCH_CMD}
#   CONFIGURE_COMMAND ${PYILMBASE_CONFIGURE_CMD}
#   BUILD_COMMAND "make"
#   )

# ExternalProject_Add_StepDependencies(pyilmbase build ilmbase openexr)

# Disable pyilmbase as it does not work for python3

ExternalProject_Add_StepDependencies( ilmbase openexr)

# ### Pybind11

# ExternalProject_Add(
#   "pybind11"
#   PREFIX "external"
#   ${PYBIND_REPO}
#   GIT_TAG "v2.3.0"
#   DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/pybind_download
#   SOURCE_DIR ${CMAKE_BINARY_DIR}/pybind_src
#   INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_dir
#   BUILD_COMMAND ""
#   CMAKE_ARGS
#   "-DCMAKE_BUILD_TYPE=Release"
#   "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install_dir"
#   "-DPYBIND11_TEST=0"
#  )

# ### Openexr-bind

add_library(example SHARED src/example.cpp)         # sources
# SET_TARGET_PROPERTIES(example PROPERTIES PREFIX "") # remove lib from library prefix
# set(CMAKE_CXX_FLAGS "-fno-strict-aliasing -fwrapv")
# # add_dependencies(example pybind11 pyilmbase )
# add_dependencies(example pybind11)

# FIXME: Two python includes Python_INCLUDE_DIR fro find_package PYTHON_INCLUDE_DIR from custom python build
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/install_dir/include/ ${CMAKE_CURRENT_SOURCE_DIR}/install_dir/include/OpenEXR ${PYTHON_INCLUDE_DIR} ${Python_INCLUDE_DIR})

# Add the to already built libraries
# TODO: find a better way to discover link path
target_link_libraries(example -L/${CMAKE_CURRENT_SOURCE_DIR}/install_dir/lib/)
# Adding explicit 2_2 to IlmImf (libIlmImf.so not created on Arm)
target_link_libraries(example Imath Half Iex IexMath IlmThread IlmImf-${DSO_VERSION} z pthread dl util m )

install(TARGETS example DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install_dir/lib/python${PYTHON_VERSION}/site-packages/)
