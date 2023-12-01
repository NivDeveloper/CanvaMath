add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    core/main.cpp
    core/Window.cpp
    RenderAPI/stb_image/stb_image.cpp
    RenderAPI/glad/src/glad.c
    )

target_include_directories(${PROJECT_NAME} PUBLIC vendor
    RenderAPI/stb_image/
    RenderAPI/glad/include/
    )
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)