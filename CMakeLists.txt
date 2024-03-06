cmake_minimum_required(VERSION 3.12)
project(simulation)

# Create Project
add_executable( simulation 
src/glad/glad.c
src/glad/glad.h
src/main.cpp
src/classes/object.h
src/classes/object.cc
src/classes/object_shapes.h
src/classes/object_shapes.cc
)
target_compile_features(simulation PRIVATE cxx_std_17)
target_include_directories( simulation PRIVATE
  src
  include
)
# Set StartUp Project
set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "simulation" )

add_subdirectory(libs/glfw)

target_link_libraries(simulation glfw)

add_subdirectory(libs/glm)

target_link_libraries(simulation glm)



 



