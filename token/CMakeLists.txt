project(Token)

add_subdirectory(operator)
add_subdirectory(operand)

add_library(Token
        Token.cpp)

target_link_libraries(${PROJECT_NAME}
        Operand
        Operator)

target_link_directories(${PROJECT_NAME}
        PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/operand"
        "${PROJECT_SOURCE_DIR}/operator")