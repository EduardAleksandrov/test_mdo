cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SimpleHttpServer)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# COPY FILES START
# Specify the source directory you want to copy
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/files)

# Specify the destination directory (e.g., the path folder in the build directory)
set(DESTINATION_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Create the destination directory if it doesn't exist
file(MAKE_DIRECTORY ${DESTINATION_DIR})

# Copy the entire folder to the destination directory
file(COPY ${SOURCE_DIR} DESTINATION ${DESTINATION_DIR})

message(STATUS "Source directory: ${SOURCE_DIR}")
# COPY FILES END

# Add the executable
add_executable(http_server main.c)