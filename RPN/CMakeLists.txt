project(RPN)

add_library(RPN
        RPN.cpp
        exception.cpp)


target_link_libraries(${PROJECT_NAME}
        Token
        )