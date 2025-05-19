# Processor and architecture-specific flags
set(CMAKE_C_FLAGS_INIT "-g -D__STATIC_INLINE='static inline' -DconfigUSE_POSIX_ERRNO=1 -DPOSIX=1 -DCMAKE_BUILD=1 -DCOMMAND_SOCKET -pthread" CACHE STRING "")
set(CMAKE_CXX_FLAGS_INIT "-g -D__STATIC_INLINE='static inline' -DconfigUSE_POSIX_ERRNO=1 -DPOSIX=1 -DCMAKE_BUILD=1 -DCOMMAND_SOCKET -pthread" CACHE STRING "")
set(CMAKE_ASM_FLAGS_INIT "-g" CACHE STRING "")

if(APPLE)
	set(CMAKE_C_COMPILER /opt/local/bin/gcc-mp-14)
	set(CMAKE_CXX_COMPILER /opt/local/bin/g++-mp-14)
	set(CMAKE_ASM_COMPILER /opt/local/bin/gcc-mp-14)
	set(CMAKE_C_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -D__APPLE__")
	set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -D__APPLE__")
else()
	set(CMAKE_C_COMPILER /usr/bin/gcc)
	set(CMAKE_CXX_COMPILER /usr/bin/g++)
	set(CMAKE_ASM_COMPILER /usr/bin/gcc)
endif()

# Adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment and search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Print out C flags for visibility
# message(STATUS "CMAKE_C_FLAGS_INIT: ${CMAKE_C_FLAGS_INIT}")

