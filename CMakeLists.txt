cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(MyAllocator)
set(CMAKE_CXX_STANTARD 11)

add_compile_options(-O3)

option(A "test channel xww1" OFF)
option(B "test channel xww2" OFF)
option(C "test channel xww3" OFF)
option(D "test channel stl" OFF)


file(GLOB source_files ${PROJECT_SOURCE_DIR}/code/*.cpp)

if (${A})
    add_definitions(-DVERA)
elseif (${B})
    add_definitions(-DVERB)
    set(source_files ${source_files} ${PROJECT_SOURCE_DIR}/code/v2/mem_pool.cpp)
elseif (${C})
    add_definitions(-DVERC)
    set(source_files ${source_files} ${PROJECT_SOURCE_DIR}/code/v2/mem_pool.cpp)
elseif (${D})
    add_definitions(-DVERD)
else ()
    add_definitions(-DVERE)
endif ()

add_executable(MyAllocator
    ${source_files}
)