cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SimpleHttpServer)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# COPY FILES START
# Specify the source files you want to copy
set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/files/file1.txt
    ${CMAKE_SOURCE_DIR}/files/file2.html
    ${CMAKE_SOURCE_DIR}/files/file3.json)

# Specify the destination directory (e.g., the path folder in the build directory)
set(DESTINATION_DIR ${CMAKE_CURRENT_BINARY_DIR}/files)

# Create the destination directory if it doesn't exist
file(MAKE_DIRECTORY ${DESTINATION_DIR})

# Copy the file to the destination directory
file(COPY ${SOURCE_FILES} DESTINATION ${DESTINATION_DIR})

message(STATUS "Source files: ${SOURCE_FILES}")
# COPY FILES END

# Add the executable
add_executable(http_server main.c)