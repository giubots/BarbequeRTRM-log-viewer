cmake_minimum_required(VERSION 3.12)

project(BarbequeRTRM-LogViewer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SRC_FOLDER src/)
set(HEADERS_FOLDER headers/)
set(FORMS_FOLDER forms/)

set(SRC main.cpp mainwindow.cpp entriesModel.cpp filter.cpp parser.cpp)
set(HEADERS mainwindow.h entriesModel.h filter.h parser.h)
set(FORMS mainwindow.ui)
set(RESOURCES resources.qrc)

list(TRANSFORM SRC PREPEND ${SRC_FOLDER})
list(TRANSFORM HEADERS PREPEND ${HEADERS_FOLDER})
list(TRANSFORM FORMS PREPEND ${FORMS_FOLDER})

set(CMAKE_AUTOUIC_SEARCH_PATHS ${FORMS_FOLDER})

add_executable(BarbequeRTRM-LogViewer ${SRC} ${HEADERS} ${FORMS} ${RESOURCES})

target_link_libraries(BarbequeRTRM-LogViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(BarbequeRTRM-LogViewer PRIVATE ${HEADERS_FOLDER})