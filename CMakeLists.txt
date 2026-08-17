cmake_minimum_required(VERSION 3.21)

project(PCDMIS_Qt_Test VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
add_compile_definitions(NOMINMAX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core Widgets Network OpenGLWidgets AxContainer)

set(KINEMATICS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/kinematics")
set(PCL_ROOT "D:/PCL1.12.1" CACHE PATH "PCL installation root used to locate VTK 9.1")
set(VTK_ROOT "${PCL_ROOT}/3rdParty/VTK")

if(NOT EXISTS "${VTK_ROOT}/include/vtk-9.1/vtkSmartPointer.h")
    message(FATAL_ERROR "VTK 9.1 was not found. Set PCL_ROOT; current value: ${PCL_ROOT}")
endif()

add_library(HK_Kinematics SHARED IMPORTED)
set_target_properties(HK_Kinematics PROPERTIES
    IMPORTED_IMPLIB "${KINEMATICS_DIR}/HK_Kinematics.lib"
    IMPORTED_LOCATION "${KINEMATICS_DIR}/HK_Kinematics.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${KINEMATICS_DIR}"
)

qt_add_executable(PCDMIS_Qt_Test WIN32
    features/testpoints/testpoints.cpp
    features/testpoints/testpoints.h
    features/testpoints/testpoints.ui
    geometrycalculator.cpp
    geometrycalculator.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    pcdmisclient.cpp
    pcdmisclient.h
    pcdmisworker.cpp
    pcdmisworker.h
    robotkinematics.cpp
    robotkinematics.h
    tcpserverworker.cpp
    tcpserverworker.h
)

target_include_directories(PCDMIS_Qt_Test PRIVATE
    "${VTK_ROOT}/include/vtk-9.1"
)

target_link_directories(PCDMIS_Qt_Test PRIVATE
    "${VTK_ROOT}/lib"
)

target_link_libraries(PCDMIS_Qt_Test PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::OpenGLWidgets
    Qt6::AxContainer
    HK_Kinematics
    vtkGUISupportQt-9.1
    vtkRenderingOpenGL2-9.1
    vtkInteractionStyle-9.1
    vtkRenderingAnnotation-9.1
    vtkRenderingCore-9.1
    vtkFiltersSources-9.1
    vtkIOGeometry-9.1
    vtkFiltersModeling-9.1
    vtkCommonExecutionModel-9.1
    vtkCommonDataModel-9.1
    vtkCommonCore-9.1
)

set_target_properties(PCDMIS_Qt_Test PROPERTIES
    WIN32_EXECUTABLE TRUE
)

add_custom_command(TARGET PCDMIS_Qt_Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:HK_Kinematics>"
        "$<TARGET_FILE_DIR:PCDMIS_Qt_Test>"
    COMMENT "Copying HK_Kinematics.dll"
)
