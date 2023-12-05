#include "Camera.h"


glm::vec3* Camera::GetPosition() {
    return &m_position;
}

Camera2D::Camera2D(glm::vec3 position, glm::vec3 front) {
    m_position = glm::vec3(0.0f, 0.0f, 1.0f);
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_speed = 0.004f;
    m_sensitivity = 0.01f;
    m_projZoom = glm::mat4(1.0f);
    m_zoom = 1.0f;
    m_scroll = 0.0f;
    m_offset = glm::vec3(0.0f, 0.0f, 0.0f);
    m_aspect = float(m_width)/float(m_height);
    m_proj = glm::mat4(1.0f);
    m_view = glm::mat4(1.0f);
}

void Camera2D::FBcallback(int w, int h) {
    m_width = w;
    m_height = h;
    m_aspect = float(m_width)/float(m_height);

}

int Camera2D::MouseButtoncallback(Uint8 btn, Uint8 state) {
    // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
    if (btn == SDL_BUTTON_LEFT && state == SDL_PRESSED){
        if (!m_inscene){
            m_inscene = true;
            m_lastx = CursPosX;
            m_lasty = CursPosY;
            return 0;
        }
    }
    else if (btn == SDL_BUTTON_LEFT && state == SDL_RELEASED) {
        if (m_inscene) {
            m_inscene = false;
            return 0;
        }
    }
    return 0;
}

void Camera2D::CursorPoscallback(double xpos, double ypos) {

    if (!m_inscene) return;

    if (m_firstmouse)
    {
        m_lastx = xpos;
        m_lasty = ypos;
        m_firstmouse = false;
    }

    float xoffset = xpos - m_lastx;
    float yoffset = m_lasty - ypos; 
    m_lastx = xpos;
    m_lasty = ypos;

    xoffset *= m_aspect;
    xoffset /= m_width/2.0f;
    yoffset /= m_height/2.0f;
    xoffset /= m_zoom;
    yoffset /= m_zoom;

    // std::cout << m_position[0] - xoffset << " "  << m_position[1] - yoffset << std::endl;
    m_position[0] -= xoffset;
    m_position[1] -= yoffset;

}

float Camera2D::GetZoom() const{
    return m_zoom;
}

glm::mat4* Camera2D::GetViewMatrix() {
    m_view = glm::lookAt(m_position, m_position + m_front, glm::vec3(0.0f, 1.0f, 0.0f));
    return &m_view;
    }

glm::mat4* Camera2D::GetProjectionMatrix() {
    m_proj = glm::ortho(-m_aspect, m_aspect, -1.0f, 1.0f, 0.1f, 100.0f) * m_projZoom;
    return &m_proj;
}

void Camera2D::Scrollcallback(double xoffset, double yoffset) {

    m_scroll += (float)yoffset;
    float scale = std::pow(2.0f, yoffset);
    m_zoom = std::pow(2.0f, m_scroll);
    
    glm::vec3 off = glm::vec3(
        m_aspect*((CursPosX-(m_width/2.0f))/(m_width/2.0f)),
        ((-CursPosY+(m_height/2.0f))/(m_height/2.0f)),
        0.0f
        );

    glm::mat4 trans = glm::translate(glm::mat4(1.0f), -off);
    m_projZoom = trans * m_projZoom;
    glm::mat4 sc = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, 1.0f));
    m_projZoom = sc * m_projZoom;
    glm::mat4 invtrans = glm::translate(glm::mat4(1.0f), off);
    m_projZoom = invtrans * m_projZoom;
    
}

void Camera2D::ProcessInput() {

    float velocity = m_speed/m_zoom;
    if (KeyStates[SDL_SCANCODE_W]) {
        m_position[1] += velocity;
    }
    if (KeyStates[SDL_SCANCODE_A]) {
        m_position[0] -= velocity;
    }
    if (KeyStates[SDL_SCANCODE_S]) {
        m_position[1] -= velocity;
    }
    if (KeyStates[SDL_SCANCODE_D]) {
        m_position[0] += velocity;
    }
}

Camera3D::Camera3D(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_speed = SPEED;
    m_sensitivity = SENSITIVITY;
    m_zoom = ZOOM;
    m_position = position;
    m_proj = glm::mat4(1.0f);
    m_view = glm::mat4(1.0f);
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera3D::Camera3D(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) {
    m_speed = SPEED;
    m_sensitivity = SENSITIVITY;
    m_zoom = ZOOM;
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}


glm::mat4* Camera3D::GetViewMatrix() {
    m_view = glm::lookAt(m_position, m_position + m_front, Up);
    return &m_view;
}

glm::mat4* Camera3D::GetProjectionMatrix() {
    m_proj = glm::perspective(glm::radians(GetZoom()), float(m_width)/float(m_height), 0.1f, 100.0f);
    return &m_proj;
}


float Camera3D::GetZoom() const{
    return m_zoom;
}

void Camera3D::ProcessInput() {
    float velocity = m_speed * deltaTime;
    if (KeyStates[SDL_SCANCODE_W]) {
        m_position += m_front * velocity;
    }
    if (KeyStates[SDL_SCANCODE_A]) {
        m_position -= Right * velocity;
    }
    if (KeyStates[SDL_SCANCODE_S]) {
        m_position -= m_front * velocity;
    }
    if (KeyStates[SDL_SCANCODE_D]) {
        m_position += Right * velocity;
    }
}

void Camera3D::CursorPoscallback(double xpos, double ypos) {

    if (!m_inscene) return;

    if (m_firstmouse)
    {
        m_lastx = xpos;
        m_lasty = ypos;
        m_firstmouse = false;
    }

    float xoffset = xpos - m_lastx;
    float yoffset = m_lasty - ypos; 
    m_lastx = xpos;
    m_lasty = ypos;

    float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;


    xoffset *= m_sensitivity;
    yoffset *= m_sensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    // update m_front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera3D::Scrollcallback(double xoffset, double yoffset) {
    m_zoom -= (float)yoffset;
    if (m_zoom < 1.0f)
        m_zoom = 1.0f;
    if (m_zoom > 45.0f)
        m_zoom = 45.0f;
}

int Camera3D::MouseButtoncallback(Uint8 btn, Uint8 state) {
    if (btn == SDL_BUTTON_LEFT && state == SDL_PRESSED){
        if (m_inscene){
            m_inscene = false;
            return 1;
        }
        else{
            m_inscene = true;
            m_lastx = CursPosX;
            m_lasty = CursPosY;
            return -1;
        }
    }
    return 0;
}

void Camera3D::FBcallback(int w, int h) {
    m_width = w;
    m_height = h;
}

void Camera3D::updateCameraVectors(){
    // calculate the new m_front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    m_front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(m_front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, m_front));
}