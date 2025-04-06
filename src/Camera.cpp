//
// Created by filip on 8/7/24.
//

#include "../h/Camera.h"
#include "../vendor/ImGui/backends/imgui_impl_glfw.h"


Camera* Camera::instance = nullptr;

Camera::Camera() :

    cameraPos(glm::vec3(50.0f, 300.0f, 50.0f)),
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
    farPlane(1000.0f)

    {

        instance = this;
        UpdateViewMatrix();
        UpdateProjectionMatrix();

    }

Camera::~Camera() {}

Camera *Camera::GetInstance() {
    if (!instance) {
        instance = new Camera();
    }
    return instance;
}

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

void Camera::SetCameraPos(float yPos) {
    instance->cameraPos.y = yPos;
}

void Camera::SetCameraPos(float xPos, float yPos, float zPos) {
    instance->cameraPos.x = xPos;
    instance->cameraPos.y = yPos;
    instance->cameraPos.z = zPos;
}

void Camera::ImGuiMouseCallback(GLFWwindow *window, double xPos, double yPos) {
    ImGui_ImplGlfw_CursorPosCallback(window, xPos, yPos);
}

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos) {

    // Initialization code that runs on the first mouse move.
    if (instance->firstMouse) {
        instance->lastX = xPos;
        instance->lastY = yPos;
        instance->firstMouse = false;
    }

    float xOffset = xPos - instance->lastX;
    float yOffset = instance->lastY - yPos;

    instance->lastX = xPos;
    instance->lastY = yPos;

    static float sensitivity = 0.08f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    instance->yaw += xOffset;
    instance->pitch += yOffset;

    // Cap the pitch value.
    if (instance->pitch > 89.0f)
        instance->pitch = 89.0f;
    if (instance->pitch < -89.0f)
        instance->pitch = -89.0f;

    // Update the camera direction.
    glm::vec3 direction;
    direction.x = cos(glm::radians(instance->yaw)) * cos(glm::radians(instance->pitch));
    direction.y = sin(glm::radians(instance->pitch));
    direction.z = sin(glm::radians(instance->yaw)) * cos(glm::radians(instance->pitch));
    instance->cameraFront = glm::normalize(direction);

    instance->UpdateViewMatrix();
}

void Camera::scroll_callback(GLFWwindow* window, double xOffset, double yoffset) {

    /* Zoom-in/out on mouse scroll. */
    instance->zoom -= (float)yoffset;

    // Cap the zoom.
    if (instance->zoom < 1.0f)
        instance->zoom = 1.0f;
    if (instance->zoom > 45.0f)
        instance->zoom = 45.0f;

    instance->UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix() {
    /* This function should be called every time any of the following:
     *      [cameraPos, cameraFront, cameraUp]
     * is changed.*/
    viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::UpdateProjectionMatrix() {
    /* This function should be called every time any of the following:
     *      [fov, zoom, aspect, nearPlane, farPlane]
     * is changed.*/
    projectionMatrix = glm::perspective(glm::radians(fov + zoom), aspect, nearPlane, farPlane);
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime) {

    const float cameraSpeed = 25.0f * deltaTime;

    // Handle movement.
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        cameraPos.y += cameraSpeed;
    }


    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {

        // Hide cursor and capture it.
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {

        // Show cursor again.
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetCursorPosCallback(window, ImGuiMouseCallback);
        glfwSetScrollCallback(window, nullptr);

    }

}



