cmake_minimum_required(VERSION 3.12)
project(LR_2)

find_package(MPI REQUIRED)

set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/matrix.cpp
        src/Random.cpp
        src/MPI_calculations.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC ${MPI_INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} PUBLIC ${MPI_LIBRARIES})

include_directories(${PROJECT_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE include)
