add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    core/main.cpp
    core/Window.cpp
    )
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)