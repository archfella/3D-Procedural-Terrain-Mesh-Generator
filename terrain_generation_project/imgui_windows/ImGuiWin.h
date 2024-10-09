//
// Created by filip on 8/11/24.
//

#ifndef IMGUIUSER_H
#define IMGUIUSER_H

#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"


class ImGuiWin {
public:
    ImGuiWin();
    ~ImGuiWin();

    void Init(GLFWwindow* window);
    void Render();
    void Update();
    void End();
private:
    ImGuiIO* io;
};



#endif //IMGUIUSER_H
