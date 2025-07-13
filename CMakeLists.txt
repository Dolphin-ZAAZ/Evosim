cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

project(Evosim)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib/static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/shared)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

add_library(neural_network 
    src/neural-network/matrix.cpp
    src/neural-network/individual.cpp
    src/neural-network/network.cpp
    src/neural-network/population.cpp
    src/neural-network/species.cpp
)

add_executable(matrix_tests tests/matrix_tests.cpp)
target_link_libraries(matrix_tests neural_network)
add_custom_target(run_matrix_tests
    COMMAND matrix_tests
    DEPENDS matrix_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(individual_tests tests/individual_tests.cpp)
target_link_libraries(individual_tests neural_network)
add_custom_target(run_individual_tests
    COMMAND individual_tests
    DEPENDS individual_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(network_tests tests/network_tests.cpp)
target_link_libraries(network_tests neural_network)
add_custom_target(run_network_tests
    COMMAND network_tests
    DEPENDS network_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(population_tests tests/population_tests.cpp)
target_link_libraries(population_tests neural_network)
add_custom_target(run_population_tests
    COMMAND population_tests
    DEPENDS population_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(species_tests tests/species_tests.cpp)
target_link_libraries(species_tests neural_network)
add_custom_target(run_species_tests
    COMMAND species_tests
    DEPENDS species_tests
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(main src/main.cpp)
target_link_libraries(main neural_network)
add_custom_target(run_main
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)