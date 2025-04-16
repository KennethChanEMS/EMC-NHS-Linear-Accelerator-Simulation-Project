cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(LinacV2)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB macros ${PROJECT_SOURCE_DIR}/macro/*)

foreach(_script ${macros})
    get_filename_component(_script_name ${_script} NAME)
    configure_file(
        ${_script}
        ${PROJECT_BINARY_DIR}/${_script_name}
        COPYONLY
)
endforeach()

add_executable(LinacV2 LinacV2.cc ${sources} ${headers})
target_link_libraries(LinacV2 ${Geant4_LIBRARIES})