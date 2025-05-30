CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

# Name of the project
PROJECT(Assignment6)

# Get the list of all files.
FILE(GLOB_RECURSE SOURCES "src/*.cpp")
FILE(GLOB_RECURSE HEADERS "src/*.h")
FILE(GLOB_RECURSE GLSL "shaders/*.glsl")

# Set the executable.
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS} ${GLSL}
		src/Triangle.h
		src/Triangle.cpp
		src/BVH.cpp
		src/BoundingBox.cpp)

# Setup GLM
SET(GLM_INCLUDE_DIR "$ENV{GLM_INCLUDE_DIR}")
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIR})

# Get the GLFW environment variable. There should be a CMakeLists.txt in the 
# specified directory.
set(GLFW_DIR "$ENV{GLFW_DIR}")
if(NOT GLFW_DIR)
	message(FATAL_ERROR "Please point the environment variable GLFW_DIR to the root directory of your GLFW3 installation.")
endif()
option(GLFW_BUILD_EXAMPLES "GLFW_BUILD_EXAMPLES" OFF)
option(GLFW_BUILD_TESTS "GLFW_BUILD_TESTS" OFF)
option(GLFW_BUILD_DOCS "GLFW_BUILD_DOCS" OFF)
if(CMAKE_BUILD_TYPE MATCHES Release)
	add_subdirectory(${GLFW_DIR} ${GLFW_DIR}/release)
else()
	add_subdirectory(${GLFW_DIR} ${GLFW_DIR}/debug)
endif()
include_directories(${GLFW_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw ${GLFW_LIBRARIES})

# Get the GLEW environment variable.
set(GLEW_DIR "$ENV{GLEW_DIR}")
if(NOT GLEW_DIR)
	message(FATAL_ERROR "Please point the environment variable GLEW_DIR to the root directory of your GLEW installation.")
endif()
include_directories(${GLEW_DIR}/include)
IF(WIN32)
	# With prebuilt binaries
	# Check for 32 vs 64 bit generator
	IF(NOT CMAKE_CL_64)
		MESSAGE(STATUS "Using 32Bit")
		TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${GLEW_DIR}/lib/Release/Win32/glew32s.lib)
	ELSE()
		MESSAGE(STATUS "Using 64Bit")
		TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${GLEW_DIR}/lib/Release/x64/glew32s.lib)
	ENDIF()
ELSE()
	TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${GLEW_DIR}/lib/libGLEW.a)
ENDIF()

# Use c++17
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# OS specific options and libraries
IF(WIN32)
	# -Wall produces way too many warnings.
	# -pedantic is not supported.
	# Disable warning 4996.
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
	TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} opengl32.lib)
	SET_PROPERTY(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CMAKE_PROJECT_NAME})
ELSE()
	# Enable all pedantic warnings.
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
	IF(APPLE)
		# Add required frameworks for GLFW.
		TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} "-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo")
	ELSE()
		#Link the Linux OpenGL library
		TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} "GL")
	ENDIF()
ENDIF()
