add_subdirectory(SDL)
add_subdirectory(SDL_image)
add_subdirectory(glm)

add_library(vendor INTERFACE)

target_sources(vendor INTERFACE ${SOURCES})

target_link_libraries(vendor INTERFACE
    SDL3::SDL3
    SDL3_image::SDL3_image
    glm::glm)