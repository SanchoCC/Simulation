cmake_minimum_required(VERSION 3.12)
project(Simulation)

# Create Project
add_executable( simulation 
src/glad/glad.c
src/glad/glad.h
src/main.cc
src/classes/object.h
src/classes/object.cc
src/classes/object_shapes.h
src/classes/object_shapes.cc
src/classes/object_handler.h
src/classes/object_handler.cc
src/classes/color.h
src/classes/color.cc
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



 



