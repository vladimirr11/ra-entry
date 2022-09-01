cmake_minimum_required(VERSION 3.10.2)

project(robotics_accelaration_entry LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake_helper/helper.cmake)

set(_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}) 

add_executable(
    ${PROJECT_NAME} 

        ${_BASE_DIR}/utils/CommonDefines.h
        ${_BASE_DIR}/utils/EyePatterns.h
        ${_BASE_DIR}/utils/FileParser.h
        ${_BASE_DIR}/utils/FunctionTracer.h
        ${_BASE_DIR}/utils/Image.h
        ${_BASE_DIR}/utils/Image.cpp
        ${_BASE_DIR}/utils/SolutionEvaluator.h

        ${_BASE_DIR}/FlashedEyeFinder.h
        ${_BASE_DIR}/FlashedEyeFinder.cpp
        
        ${_BASE_DIR}/main.cpp
        ${_BASE_DIR}/Solution.h
)

# file(COPY ${_BASE_DIR}/input.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# file(COPY ${_BASE_DIR}/output.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set_target_cpp_standard(${PROJECT_NAME} 17)

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE 
            ${_BASE_DIR}
)
