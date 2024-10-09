//
// Created by filip on 8/7/24.
//

#include "../h/Camera.h"

#include <../vendor/imgui/imgui_impl_glfw.h>


Camera* Camera::instance = nullptr;

Camera::Camera()
    : cameraPos(glm::vec3(50.0f, 300.0f, 50.0f)),
      cameraFront(glm::vec3(0.0f, -1.0f, 0.0f)),
      cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
      yaw(-90.0f),
      pitch(-15.0f),
      lastX(400.0f),
      lastY(300.0f),
      firstMouse(true),
      zoom(45.0f),
      fov(10.0f),
      aspect(8.0f/5.0f),
      nearPlane(0.1f),
      farPlane(1000.0f) {

    instance = this;
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix() const {
    return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return projectionMatrix;
}

glm::vec3 Camera::GetCameraPos() const {
    return cameraPos;
}

glm::vec3 Camera::GetCameraFront() const {
    return cameraFront;
}

glm::vec3 Camera::SetCameraPos(float ypos) {
    Camera* cam = Camera::instance;
    cam->cameraPos.y = ypos;
}

glm::vec3 Camera::SetCameraPos(float xpos, float ypos, float zpos) {
    Camera* cam = Camera::instance;
    cam->cameraPos.x = xpos;
    cam->cameraPos.y = ypos;
    cam->cameraPos.z = zpos;
}

void Camera::ImGuiMouseCallback(GLFWwindow *window, double xpos, double ypos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Camera* cam = Camera::instance;

    if (cam->firstMouse) {
        cam->lastX = xpos;
        cam->lastY = ypos;
        cam->firstMouse = false;
    }

    float xoffset = xpos - cam->lastX;
    float yoffset = cam->lastY - ypos; // reversed: y ranges bottom to top
    cam->lastX = xpos;
    cam->lastY = ypos;

    const float sensitivity = 0.08f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->yaw += xoffset;
    cam->pitch += yoffset;

    if (cam->pitch > 89.0f)
        cam->pitch = 89.0f;
    if (cam->pitch < -89.0f)
        cam->pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    direction.y = sin(glm::radians(cam->pitch));
    direction.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    cam->cameraFront = glm::normalize(direction);

    cam->UpdateViewMatrix();
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* cam = Camera::instance;

    cam->zoom -= (float)yoffset;
    if (cam->zoom < 1.0f)
        cam->zoom = 1.0f;
    if (cam->zoom > 45.0f)
        cam->zoom = 45.0f;

    cam->UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix() {
    viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::UpdateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov + zoom), aspect, nearPlane, farPlane);
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime) {
    const float cameraSpeed = 25.0f * deltaTime;
    float oldY = cameraPos.y;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        isJump = true;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        cameraPos.y += cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        //  Mouse initialization
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);    //  Hide the cursor and capture it
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);    //  Show cursor again
        glfwSetCursorPosCallback(window, ImGuiMouseCallback);
        glfwSetScrollCallback(window, nullptr);
    }
    if(isFPS) cameraPos.y = oldY;
}



