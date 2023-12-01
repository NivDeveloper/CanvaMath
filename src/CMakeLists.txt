add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    core/main.cpp
    core/Window.cpp
    utils/stb_image/stb_image.cpp
    utils/glad/src/glad.c
    )

target_include_directories(${PROJECT_NAME} PUBLIC vendor
    utils/stb_image/
    utils/glad/include/
    )
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)