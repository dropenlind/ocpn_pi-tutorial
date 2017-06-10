##---------------------------------------------------------------------------
## Author:      Mohamed Saad Ibn Seddik
## Copyright:
## License:     wxWidgets License
##---------------------------------------------------------------------------

# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(MINIMAL_pi)

SET(PACKAGE_NAME MINIMAL_pi)
SET(VERBOSE_NAME MINIMAL)
SET(TITLE_NAME MINIMAL)
SET(CPACK_PACKAGE_CONTACT "Mohamed Saad Ibn Seddik")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "1")

#SET(CMAKE_BUILD_TYPE Debug)
SET( wxWidgets_USE_DEBUG OFF)
SET( wxWidgets_USE_UNICODE ON)
SET( wxWidgets_USE_UNIVERSAL OFF)
SET( wxWidgets_USE_STATIC OFF)

INCLUDE("cmake/PluginConfigure.cmake")

SET(SRC_MINIMAL
        src/ocpn_plugin.h
        src/icons.cpp
        src/minimalgui.cpp
        src/minimalwindow.cpp
        src/minimal_pi.cpp
  )


ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_MINIMAL})

INCLUDE("cmake/PluginInstall.cmake")
# INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
