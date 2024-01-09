cmake_minimum_required(VERSION 3.5)

project(sample_smart_server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(sample_smart_server
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        device/devicefan.h device/devicefan.cpp device/devicefan.ui
        device/devicelamp.h device/devicelamp.cpp device/devicelamp.ui
        device/devicecurtain.h device/devicecurtain.cpp device/devicecurtain.ui
        device/deviceac.h device/deviceac.cpp device/deviceac.ui
        tcp/tcpserver.h tcp/tcpserver.cpp
        custom/sliderbutton.h custom/sliderbutton.cpp
        custom/digitalscroller.h custom/digitalscroller.cpp custom/digitalscroller.ui
        res.qrc
        custom/global.h custom/global.cpp
        custom/SetWindowCompositionAttribute.h
        tcp/tcpserverthread.h tcp/tcpserverthread.cpp
        tcp/tcpsocket.h tcp/tcpsocket.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET sample_smart_server APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(sample_smart_server SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(sample_smart_server
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(sample_smart_server PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.sample_smart_server)
endif()
set_target_properties(sample_smart_server PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_link_libraries(sample_smart_server PRIVATE Qt6::Network)
target_link_libraries(sample_smart_server PRIVATE Qt6::Core)
target_link_libraries(sample_smart_server PRIVATE Qt6::Gui)
include(GNUInstallDirs)
install(TARGETS sample_smart_server
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(sample_smart_server)
endif()
