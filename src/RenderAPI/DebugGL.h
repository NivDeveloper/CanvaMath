#pragma once
#include "glad/glad.h"

void    EnableDebugOutput   ();
void    glDebugOutput       (GLenum         source,
                             GLenum         type,
                             unsigned int   id,
                             GLenum         severity, 
                             GLsizei        length,
                             const char     *message,
                             const void     *userParam);