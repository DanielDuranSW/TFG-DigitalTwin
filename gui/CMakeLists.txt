cmake_minimum_required(VERSION 3.5)

project(gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ManagerGUI.cpp
        ManagerGUI.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        assert.qrc
        ../resources/DMA.cpp
        ../resources/DMA.h
        ../resources/Flash.cpp
        ../resources/Flash.h
        ../resources/RAM.cpp
        ../resources/RAM.h
        ../resources/Resource.cpp
        ../resources/Resource.h
        ../resources/RTC.cpp
        ../resources/RTC.h
        ../resources/SPI.cpp
        ../resources/SPI.h
        ../resources/CSVReader.h
        ../resources/CSVReader.cpp
        ../resources/ClassifierFeatures.h
        ../resources/ClassifierFeatures.cpp
        ../resources/ClassifierModel.h
        ../resources/ClassifierModel.cpp
        ../threads/BLE_Stack_Operation.cpp
        ../threads/BLE_Stack_Operation.h
        ../threads/Custom_Event_Handler.cpp
        ../threads/Custom_Event_Handler.h
        ../threads/Energy_Saving.cpp
        ../threads/Energy_Saving.h
        ../threads/FSR_Acquisition.cpp
        ../threads/FSR_Acquisition.h
        ../threads/IMU_Acquisition.cpp
        ../threads/IMU_Acquisition.h
        ../threads/RAM_Operation.cpp
        ../threads/RAM_Operation.h
        ../threads/LowLevelActivityClassifier.h
        ../threads/LowLevelActivityClassifier.cpp
        ../Makefile
        ../State.cpp
        ../State.h
        ../ThreadsData.h
        ../StateSignalHandler.cpp
        ../StateSignalHandler.h
        ../config.h
        ../config.cpp
        ../DataPacket.h
        ../DataPacket.cpp
        ../data/data1.csv
        ../data/data2.csv
        ../data/data3.csv
        ../data/marcha.csv
    )

# Include path for fft3.h
set(FFTW_ROOT /usr/local)
find_path(FFTW_INCLUDE_DIR fftw3.h PATHS ${FFTW_ROOT}/include)
find_library(FFTW_LIBRARY fftw3 PATHS ${FFTW_ROOT}/lib)
target_include_directories(gui PRIVATE ${FFTW_INCLUDE_DIR})
target_link_libraries(gui PRIVATE ${FFTW_LIBRARY})

# Include path for ONNX Runtime
set(ONNXRUNTIME_ROOT /usr/local/onnxruntime)
find_path(ONNXRUNTIME_INCLUDE_DIR onnxruntime_cxx_api.h PATHS ${ONNXRUNTIME_ROOT}/include)
find_library(ONNXRUNTIME_LIBRARY onnxruntime PATHS ${ONNXRUNTIME_ROOT}/lib)
target_include_directories(gui PRIVATE ${ONNXRUNTIME_INCLUDE_DIR})
target_link_libraries(gui PRIVATE ${ONNXRUNTIME_LIBRARY})


# Define target properties for Android with Qt 6 as:
#    set_property(TARGET gui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(gui SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(gui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Ruta a la carpeta que contiene tus archivos de encabezado
target_include_directories(gui PRIVATE
    /home/daniduran/ws/TFG-DigitalTwin
)

target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.gui)
endif()
set_target_properties(gui PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS gui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gui)
endif()
