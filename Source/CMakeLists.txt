## Create the library.

# Define private and public directories.

set(SGF_PRIVATE_DIR ${PROJECT_SOURCE_DIR}/Source)
set(SGF_PUBLIC_DIR ${PROJECT_SOURCE_DIR}/Include)

# Include public headers.

set(SGF_CORE_HEADERS
    ${SGF_PUBLIC_DIR}/SGF/Defines.h
)

source_group(Include FILES ${SGF_CORE_HEADERS})

set(SGF_WINDOW_HEADERS
    ${SGF_PUBLIC_DIR}/SGF/Window/WindowManager.h
)

source_group(Include\\Window FILES ${SGF_WINDOW_HEADERS})

# Include sources.

set(SGF_PLATFORM_SDL2_SOURCES
        ${SGF_PRIVATE_DIR}/Platform/SDL2/SDL2WindowManager.h
        ${SGF_PRIVATE_DIR}/Platform/SDL2/SDL2WindowManager.cpp
)

source_group(Source\\Platform\\SDL2 FILES ${SGF_PLATFORM_SDL2_SOURCES})

# Add files to library.

add_library(${PROJECT_NAME}
    SHARED
        ${SGF_CORE_HEADERS}
        ${SGF_WINDOW_HEADERS}
        ${SGF_PLATFORM_SDL2_SOURCES}
)

## Create an alias.

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

## Specify private include directories.

target_include_directories(${PROJECT_NAME} PRIVATE ${SGF_PRIVATE_DIR})

## Specify public include directories.

target_include_directories(${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${SGF_PUBLIC_DIR}>
    $<INSTALL_INTERFACE:include>)

## Create tests.

# Include sources.

set(SGF_WINDOW_TEST_SOURCES
    ${SGF_PRIVATE_DIR}/Test/WindowTest.cpp
)

source_group(Source\\Test ${SGF_WINDOW_TEST_SOURCES})

# Create the executables.

add_executable(WindowTest ${SGF_WINDOW_TEST_SOURCES})

# Link the library to the executables.

target_link_libraries(WindowTest PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})

## Specify install directories.

# Library general config (*.dll will go to "bin" folder).

install(TARGETS ${PROJECT_NAME} 
    EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION include
    ARCHIVE DESTINATION lib 
    LIBRARY DESTINATION lib 
    RUNTIME DESTINATION bin)

# Install header files to "include" folder.

install(DIRECTORY ${SGF_PUBLIC_DIR}/${PROJECT_NAME}
    DESTINATION include)

# Install library files to "lib" folder.

install(TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION lib)

# Export cmake config to "cmake" folder.

install(EXPORT ${PROJECT_NAME}-targets
    NAMESPACE ${PROJECT_NAME}::
    FILE ${PROJECT_NAME}-config.cmake
    DESTINATION cmake)

# Tests (will go to "bin" folder).

install(TARGETS WindowTest 
    DESTINATION bin)