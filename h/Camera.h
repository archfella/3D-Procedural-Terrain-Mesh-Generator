//
// Created by filip on 8/7/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
#include <GLFW/glfw3.h>

class Camera {

public:

    // Processes user input.
    void ProcessInput(GLFWwindow* window, float deltaTime);

    // Getters/Setters.
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;
    glm::vec3 GetCameraPos() const;
    glm::vec3 GetCameraFront() const;
    static Camera* GetInstance();
    void SetCameraPos(float yPos);
    void SetCameraPos(float xPos, float yPos, float zPos);

    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

private:

    Camera();
    ~Camera();

    static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void ImGuiMouseCallback(GLFWwindow* window, double xpos, double ypos);

    static Camera* instance;

    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraPos;

    float yaw;
    float pitch;
    float lastX;
    float lastY;
    bool firstMouse;
    float zoom;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;

};



#endif //CAMERA_H
