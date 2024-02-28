#include "Camera.hpp"

glm::mat4 Camera::createOrthographic() {
    float x1 = 2.0f / (m_right - m_left);
    float x4 = -(m_right + m_left) / (m_right - m_left);
    float y2 = 2.0f / (m_top - m_bottom);
    float y4 = -(m_top + m_bottom) / (m_top - m_bottom);
    float z3 = -2.0f / (m_far - m_near);
    float z4 = -(m_far + m_near) / (m_far - m_near);

    glm::mat4 orthographic;
    orthographic[0] = glm::vec4(x1, 0.0f, 0.0f, x4);
    orthographic[1] = glm::vec4(0.0f, y2, 0.0f, y4);
    orthographic[2] = glm::vec4(0.0f, 0.0f, z3, z4);
    orthographic[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    return orthographic;
}

glm::mat4 Camera::createPerspective() {
    float z3 = -(m_far + m_near) / (m_far - m_near);
    float z4 = -2.0f * m_far * m_near / (m_far - m_near);
    float angle = 3.14159f * field_of_view / 2;
    float fov = glm::tan(angle);
    float scale = 1.0f / (fov != 3.14159f / 2 ? fov : 1.0f);

    glm::mat4 perspective;
    perspective[0] = glm::vec4(scale, 0.0f, 0.0f, 0.0f);
    perspective[1] = glm::vec4(0.0f, scale, 0.0f, 0.0f);
    perspective[2] = glm::vec4(0.0f, 0.0f, z3, z4);
    perspective[3] = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

    return perspective;
}

glm::mat4 Camera::createViewMatrix() {
    glm::vec3 dir = glm::normalize(m_direction);
    glm::vec3 right = glm::normalize(glm::cross(m_up, dir));
    glm::vec3 up = glm::normalize(glm::cross(dir, right));

    glm::mat4 rotation;
    rotation[0] = glm::vec4(right, 0.0f);
    rotation[1] = glm::vec4(up, 0.0f);
    rotation[2] = glm::vec4(dir, 0.0f);
    rotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    glm::mat4 translation;
    translation[0] = glm::vec4(1.0f, 0.0f, 0.0f, -m_eye.x);
    translation[1] = glm::vec4(0.0f, 1.0f, 0.0f, -m_eye.y);
    translation[2] = glm::vec4(0.0f, 0.0f, 1.0f, -m_eye.z);
    translation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    return translation * rotation;
}

Camera::Camera() {
    m_eye = glm::vec3(0.0f, 0.0f, 7.0f);
    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_direction = glm::normalize(m_eye - m_target);

    resetProjection();
    resetView();
}

Camera::Camera(glm::vec3 e, glm::vec3 t, glm::vec3 u) {
    m_eye = e;
    m_target = t;
    m_up = glm::normalize(u);
    m_direction = glm::normalize(m_eye - m_target);

    resetProjection();
    resetView();
}

void Camera::moveForward(float speed) {
    m_eye += m_direction * speed;
}

void Camera::moveRight(float speed) {
    glm::vec3 dir = glm::normalize(m_direction);
    glm::vec3 right = glm::normalize(glm::cross(m_up, dir));

    m_eye += right * speed;
}

void Camera::moveUp(float speed) {
    glm::vec3 dir = glm::normalize(m_direction);
    glm::vec3 right = glm::normalize(glm::cross(m_up, dir));
    glm::vec3 up = glm::normalize(glm::cross(dir, right));

    m_eye += up * speed;
}

void Camera::rotate(float angle) {
    Quaternion r = Quaternion(glm::vec3(0.0f, 1.0f, 0.0f), angle).normalize();
    Quaternion rc = r.conjugate().normalize();
    Quaternion d = Quaternion(m_direction);
    d = (r * d * rc).normalize();
    m_direction = glm::vec3(d.x, d.y, d.z);
}

void Camera::setUniforms(const GpuProgram& program) {
    program.bind();
    program.setMat4("P", m_projection);
    program.setMat4("V", m_view);
    program.setVec3("eye", m_eye);
}   


