//
// Created by filip on 8/7/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <../vendor/glm/glm.hpp>
#include <../vendor/glm/gtc/matrix_transform.hpp>
#include <../vendor/glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera();
    ~Camera();

    void Initialize(GLFWwindow* window);
    void ProcessInput(GLFWwindow* window, float deltaTime);
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    glm::vec3 GetCameraPos() const;
    glm::vec3 GetCameraFront() const;
    glm::vec3 SetCameraPos(float ypos);
    glm::vec3 SetCameraPos(float xpos, float ypos, float zpos);


    inline void SetFPSCamera(bool ok) {
        isFPS = ok;
    }

    inline bool IsFPSCamera() {
        return isFPS;
    }

    //  jumping
    bool isJump = false;
    glm::vec3 cameraPos;

private:
    bool isFPS = false;
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void ImGuiMouseCallback(GLFWwindow* window, double xpos, double ypos);

    static Camera* instance;

    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

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
