cmake_minimum_required(VERSION 3.21)
project(Reverse_Polish_notation)

set(CMAKE_CXX_STANDARD 14)

include_directories("${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}")

add_executable(Reverse_Polish_notation main.cpp
        #        token/operator/Operator.cpp
        #        token/operator/UnaryOperator.cpp
        #        token/operator/BinocularOperator.cpp
        #        token/operator/NegativeOperator.cpp
        #        token/operator/PlusOperator.cpp
        #        token/operator/SubtractionOperator.cpp
        #        token/operator/MultiplicationOperator.cpp
        #        token/operator/DivisionOperator.cpp
        #        token/operator/LeftBracket.cpp
        #        token/operator/RightBracket.cpp
        #        ./token/Token.cpp
        #        ./token/operand/Number.cpp
        #        ./token/operand/Operand.cpp
        )

add_subdirectory(Google_tests)
add_subdirectory(token)
add_subdirectory(RPN)
add_subdirectory(common)
add_subdirectory(BigNumberCalculation)

target_link_libraries(${PROJECT_NAME} PUBLIC Token RPN BigNumberCalculation)

# add the binary tree to the search path for include files
target_include_directories(Reverse_Polish_notation PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/Token"
        "${PROJECT_SOURCE_DIR}/RPN"
        )