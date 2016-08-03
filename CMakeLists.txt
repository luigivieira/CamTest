# Copyright (C) 2016 Luiz Carlos Vieira (http://www.luiz.vieira.nom.br)
#
# This file is part of CamTest.
#
# CamTest is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CamTest is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.1.0)
project (CamTest)

#############################################
# Configuring
#############################################

set (CT_VERSION_MAJOR 1)
set (CT_VERSION_MINOR 0)
set (CT_VERSION_PATCH 0)
set (CT_VERSION "${CT_VERSION_MAJOR}.${CT_VERSION_MINOR}.${CT_VERSION_PATCH}")
configure_file (
  "${PROJECT_SOURCE_DIR}/version.h.in"
  "${PROJECT_BINARY_DIR}/version.h"
)
include_directories("${PROJECT_BINARY_DIR}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

# Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 REQUIRED Core Gui Widgets)

# OpenCV
find_package(OpenCV REQUIRED core highgui imgproc)
include_directories(${OpenCV_INCLUDE_DIRS})

# Source files
file(GLOB SRC src/*.cpp src/*.h)
file(GLOB RSC src/*.qrc)

# Executable
if(WIN32)
    add_executable(CamTest WIN32 ${SRC} ${RSC})
else()
    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
    add_executable(CamTest ${SRC} ${RSC})
endif()
set_target_properties(CamTest PROPERTIES OUTPUT_NAME camtest)
set_target_properties(CamTest PROPERTIES OUTPUT_NAME_DEBUG camtestd)

# Libraries
list(APPEND Qt5_LIBS Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(CamTest ${Qt5_LIBS} ${OpenCV_LIBS})

#############################################
# Installing (only for Release)
#############################################

get_filename_component(QT_BIN_DIR "${Qt5_DIR}/../../../bin" ABSOLUTE)
get_filename_component(QT_PLUGIN_DIR "${Qt5_DIR}/../../../plugins" ABSOLUTE)

# Executable
install(TARGETS CamTest DESTINATION bin CONFIGURATIONS Release)

# Qt5 dependencies
foreach(LIB_TARGET ${Qt5_LIBS})
	get_target_property(LIB_FILE ${LIB_TARGET} LOCATION_RELEASE)
	install(FILES ${LIB_FILE} DESTINATION bin CONFIGURATIONS Release)
endforeach()

foreach(LIB_TARGET ${Qt5Gui_PLUGINS})
	get_target_property(LIB_FILE ${LIB_TARGET} LOCATION_RELEASE)
	get_filename_component(PLUGIN_NAME ${LIB_FILE} DIRECTORY)
	string(REGEX REPLACE ".*/plugins/" "" PLUGIN_NAME ${PLUGIN_NAME})
	install(FILES ${LIB_FILE} DESTINATION bin/${PLUGIN_NAME} CONFIGURATIONS Release)
endforeach()
   
# OpenCV dependencies
foreach(LIB_TARGET ${OpenCV_LIBS})
	get_target_property(LIB_FILE ${LIB_TARGET} LOCATION_RELEASE)
	install(FILES ${LIB_FILE} DESTINATION bin CONFIGURATIONS Release)
endforeach()
   
# Windows 10 C Runtime dependencies
if(WIN32)
	macro(get_WIN32_VERSION version)
		if(CMAKE_SYSTEM)
			set(ver ${CMAKE_SYSTEM})
			string(REGEX REPLACE "Windows[- ]" "" ver ${ver})
			string(REGEX REPLACE "[.].*" "" ver ${ver})
			set(${version} "${ver}")
		endif()
	endmacro()

	get_WIN32_VERSION(WIN_VERSION)
	if(${WIN_VERSION} EQUAL "10")
		set(WIN10_CRT_REDIST_DIR "C:/Program Files (x86)/Windows Kits/10/Redist/ucrt/DLLs/x86" CACHE STRING "Path of the Windows 10 Universal C Runtime DLLs.")
		file(GLOB CRT_DEPENDENCIES "${WIN10_CRT_REDIST_DIR}/*.dll")
		install(FILES ${CRT_DEPENDENCIES} DESTINATION bin CONFIGURATIONS Release)
	endif()
endif()

# Other system dependencies (i.e. VS redist in Windows)
set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP 1)
include(InstallRequiredSystemLibraries)
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION bin CONFIGURATIONS Release)

#############################################
# Packaging
#############################################

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CamTest - A simple webcam application")
set(CPACK_PACKAGE_VENDOR "Luiz Carlos Vieira (http://www.luiz.vieira.nom.br)")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION "${CT_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CamTest ${CT_VERSION}")
include(CPack)
