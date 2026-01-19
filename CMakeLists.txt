cmake_minimum_required(VERSION 3.16)

project(VRProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    OpenGLWidgets
)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.cpp
    vrbody.cpp
    vrbounce.cpp
    vrcamera.cpp
    vrcube.cpp
    vrcurve.cpp
    vrdice.cpp
    vrhelix.cpp
    vrlight.cpp
    vrplane.cpp
    vrplanet.cpp
    vrscene.cpp
    vrskybox.cpp
    vrspecularcube.cpp
    vrspecularsphere.cpp
    vrspeculartorus.cpp
    vrsphere.cpp
    vrsphericalcamera.cpp
    vrstereocamera.cpp
    vrsurface.cpp
    vrtexcube.cpp
    vrtorus.cpp
    vrwidget.cpp

    mainwindow.h
    vrbody.h
    vrbounce.h
    vrcamera.h
    vrcube.h
    vrcurve.h
    vrdice.h
    vrhelix.h
    vrlight.h
    vrplane.h
    vrplanet.h
    vrscene.h
    vrskybox.h
    vrspecularcube.h
    vrspecularsphere.h
    vrspeculartorus.h
    vrsphere.h
    vrsphericalcamera.h
    vrstereocamera.h
    vrsurface.h
    vrtexcube.h
    vrtorus.h
    vrwidget.h

    mainwindow.ui
    VRResources.qrc
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
