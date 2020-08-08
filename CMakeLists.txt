cmake_minimum_required(VERSION 3.18.0)

project(SGF)

## Find third party libraries.

find_package(SDL2 REQUIRED)
find_package(tinyobjloader REQUIRED)
find_package(PhysX REQUIRED)
find_package(Vulkan REQUIRED)

## Add framework library source.

add_subdirectory(Source)

## Add dependency includes and libraries.
    
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        SDL2::SDL2
        tinyobjloader::tinyobjloader
        PhysX::PhysX
        PhysX::PhysXCharacterKinematic
        PhysX::PhysXExtensions
        PhysX::PhysXCommon
        Vulkan::Vulkan
)