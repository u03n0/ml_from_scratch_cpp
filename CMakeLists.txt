cmake_minimum_required(VERSION 3.25.1)
project(naive_bayes_cpp)

# Add include directory to the include path
include_directories(include)
# Create the executables
add_executable(${PROJECT_NAME} src/main.cpp )

# Create libraries
add_library(mylib src/processing.cpp)
add_library(algo_lib src/algo.cpp)

# Link libraries to the executable
target_link_libraries(${PROJECT_NAME} mylib algo_lib)
