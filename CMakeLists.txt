cmake_minimum_required(VERSION 3.0.2)
project(bs_arm_control)


# if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
#   set(CMAKE_BUILD_TYPE "Release")
#   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
# endif()
# message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")



# ----- Set compiler options -----

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")


# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g -ggdb")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -g -ggdb")

# set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
#     
# else()
#     set(quclib "${PROJECT_SOURCE_DIR}/3rd_lib/libquc.a")
# endif()

if (WIN32)
  message(STATUS "Now is windows")
  add_compile_options(/std:c++17)

elseif (UNIX)

  message(STATUS "Now is UNIX-like OS's.")
  add_compile_options(-std=c++17)

endif ()




# This will autogenerate qt gui stuff
set(CMAKE_AUTOMOC ON)  

# this needs to be on so cmake will know what to do with QT resource Files
set(CMAKE_AUTORCC ON)  

# need this for qt auto generated headers to include!
set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(ROS_DEPENDS
  roscpp
  sensor_msgs
  geometry_msgs
)

set(EXTERNAL_DEPENDS
  Qt5Widgets
  Qt5PrintSupport
  # yaml-cpp
  # fmt
)

set(EXTERNAL_DEPENDS_LIB
  Qt5::Widgets
  Qt5::PrintSupport
  Qt5::Core
  # yaml-cpp
  # fmt::fmt
)

## Add Non ROS dependencies
foreach(DEPEND ${EXTERNAL_DEPENDS})
  find_package(${DEPEND} REQUIRED)
endforeach(DEPEND)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS ${ROS_DEPENDS})

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)



## The catkin_package macro generates cmake config files for your package
catkin_package(
  INCLUDE_DIRS    "include"
  LIBRARIES       ${PROJECT_NAME}
  CATKIN_DEPENDS  ${ROS_DEPENDS}
  DEPENDS         ${EXTERNAL_DEPENDS}
)




include_directories(
  "include"
  "3rd_lib"
  ${catkin_INCLUDE_DIRS}
)


file(GLOB qt_heads "include/*.h" )
file(GLOB qt_cpp_srcs "src/*.cpp" "src/*.hpp" )
file(GLOB_RECURSE qt_ui "res/*.ui" )
file(GLOB qt_qrc "main.qrc" )

qt5_wrap_ui(qt_ui_heads ${qt_ui})
qt5_wrap_cpp(qt_gen_heads ${qt_heads})

add_executable(
  ${PROJECT_NAME} 
  "main.cpp" 
  ${qt_cpp_srcs} 
  ${qt_gen_heads} 
  ${qt_ui} 
  ${qt_ui_heads} 
  ${qt_qrc}
)

target_link_libraries(
  ${PROJECT_NAME}  
  ${catkin_LIBRARIES} 
  ${EXTERNAL_DEPENDS_LIB} 
)
