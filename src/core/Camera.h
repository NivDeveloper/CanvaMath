#pragma once
#include "Window.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <iostream>
#include <numbers>
#include <cmath>


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  0.01f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera: public IEventListener {
protected:
    glm::mat4 m_proj;
    glm::mat4 m_view;
    glm::vec3 m_position;
    glm::vec3 m_front;
    float m_speed;
    float m_sensitivity;
    float m_zoom;
    int m_width = 1200;
    int m_height = 900;
    bool m_inscene = false;
    double m_lastx = 600, m_lasty = 450;
    bool m_firstmouse = true;
public:
    virtual glm::mat4* GetViewMatrix() = 0;
    virtual glm::mat4* GetProjectionMatrix() = 0;
    glm::vec3* GetPosition();
};




class Camera2D: public Camera {
public:

    Camera2D(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f)
    );

    glm::mat4* GetViewMatrix() override;
    glm::mat4* GetProjectionMatrix() override;

private:
    glm::vec3 m_offset;
    glm::mat4 m_projZoom;
    double m_scroll;
    float m_aspect;
    float GetZoom() const;
    int MouseButtoncallback(Uint8 btn, Uint8 state) override;
    void Scrollcallback(double xoffset, double yoffset) override;
    void CursorPoscallback(double xpos, double ypos) override;
    void FBcallback(int width, int height) override;
    void ProcessInput() override;

};

class Camera3D: public Camera {
private:
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    float Yaw;
    float Pitch;
    float deltaTime = 0.1f;

    float GetZoom() const;
    void FBcallback(int width, int height) override;
    void CursorPoscallback(double xpos, double ypos) override;
    void Scrollcallback(double xoffset, double yoffset) override;
    int MouseButtoncallback(Uint8 btn, Uint8 state) override;
    void ProcessInput() override;
    void updateCameraVectors();

public:
    Camera3D(glm::vec3 position = glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH);
    // constructor with scalar values
    Camera3D(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    glm::mat4* GetViewMatrix() override;
    glm::mat4* GetProjectionMatrix() override;
    // calculates the front vector from the Camera's (updated) Euler Angles
};