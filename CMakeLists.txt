cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME "Database-Technical-Info-Viewer")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
set(TARGET ${PROJECT_NAME})
#-----------#-----------#-----------#

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#-----------#-----------#-----------#

set(MAIN_PATH "${PROJECT_SOURCE_DIR}/main")
set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/src")
set(HEADERS_PATH "${PROJECT_SOURCE_DIR}/headers")
#set(INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include")
#set(LIBS_PATH "${PROJECT_SOURCE_DIR}/libs")
#set(FORMS_PATH "${PROJECT_SOURCE_DIR}/forms")
set(DB_PATH "${PROJECT_SOURCE_DIR}/databases")
#set(CMAKE_AUTOUIC_SEARCH_PATHS "${PROJECT_SOURCE_DIR}/forms")
set(RESOURCES_PATH "${PROJECT_SOURCE_DIR}/resources")
#-----------#-----------#-----------#

#include_directories(${INCLUDE_PATH} ${HEADERS_PATH} ${RESOURCES_PATH})
include_directories(${HEADERS_PATH} ${RESOURCES_PATH} ${DB_PATH})
#link_directories(${LIBS_PATH})
#-----------#-----------#-----------#

file(GLOB_RECURSE CPPM "${MAIN_PATH}/*.cpp")
file(GLOB_RECURSE HS "${HEADERS_PATH}/*.h")
file(GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp")
file(GLOB_RECURSE RES "${RESOURCES_PATH}/*.qrc")
#file(GLOB_RECURSE UIS "${FORMS_PATH}/*.ui")
#set(PROJECT_SOURCES ${CPPM} ${CPPS} ${HS} ${UIS} ${RES})
set(PROJECT_SOURCES ${CPPM} ${CPPS} ${HS} ${RES})
#-----------#-----------#-----------#

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core5Compat Gui Sql SvgWidgets Widgets)
#-----------#-----------#-----------#

add_executable(${TARGET} ${PROJECT_SOURCES})
target_link_libraries(${TARGET}
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::SvgWidgets
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::Core5Compat)
#-----------#-----------#-----------#
