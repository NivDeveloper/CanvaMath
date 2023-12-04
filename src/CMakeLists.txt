add_executable(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES
    core/*.cpp
    utils/*.cpp
    RenderAPI/*.cpp
)

target_sources(${PROJECT_NAME} PRIVATE
    core/main.cpp
    core/Window.cpp
    utils/stb_image/stb_image.cpp
    utils/glad/src/glad.c
    ${SOURCES}
    )

target_include_directories(${PROJECT_NAME} PUBLIC vendor
    utils/stb_image/
    utils/glad/include/
    )
target_link_libraries(${PROJECT_NAME} PRIVATE
    vendor
    ${GLAD_LIBRARIES})