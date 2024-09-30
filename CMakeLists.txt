cmake_minimum_required(VERSION 3.10)
project(HTLProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV package

set(OpenCV_DIR "C:/Users/jack/Documents/opencv/build/x64/vc16/lib")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Find GStreamer package
find_package(PkgConfig REQUIRED)
#pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
#pkg_check_modules(GSTREAMER REQUIRED gstreamer-app-1.0)

# Manually specify GStreamer include directories and library paths
set(GSTREAMER_INCLUDE_DIRS "C:/gstreamer/1.0/msvc_x86_64/include/gstreamer-1.0" 
                           "C:/gstreamer/1.0/msvc_x86_64/include/glib-2.0"
                           "C:/gstreamer/1.0/msvc_x86_64/lib/glib-2.0/include")

set(GSTREAMER_LIBRARY_DIRS "C:/gstreamer/1.0/msvc_x86_64/lib")

set(GSTREAMER_LIBRARIES gstreamer-1.0 gobject-2.0 glib-2.0)

include_directories(
    ${GSTREAMER_INCLUDE_DIRS}
    ${GSTREAMER_APP_INCLUDE_DIRS}
)

link_directories(
    ${GSTREAMER_LIBRARY_DIRS} 
    ${GSTREAMER_APP_LIBRARY_DIRS}
)

# Source files
add_executable(HTLProject src/main.cpp)

# Link OpenCV and GStreamer libraries
target_link_libraries(HTLProject
    ${OpenCV_LIBS}
    ${GSTREAMER_LIBRARIES}
    ${GSTREAMER_APP_LIBRARIES}
)