cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
project(terrain_generation_project)


#Find the required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

#Add the executable
add_executable(terrain_generation_project main.cpp
        glad/glad.h
        glad/glad.c
        src/Camera.cpp
        h/Camera.h
        src/Texture.cpp
        src/VBO.cpp
        src/VBLayout.cpp
        src/VBLayout.cpp
        h/VBLayout.h
        h/VBLayout.h
        src/VBLayout.cpp
        imgui_windows/ImGuiWin.cpp
        imgui_windows/ImGuiWin.h

        src/EBO.cpp
        src/Renderable.cpp
        h/Renderable.h
        src/Renderer.cpp
        src/Shader.cpp
        src/VAO.cpp
        terrain/BaseTerrain.cpp
        terrain/MidpointDisplacement.cpp
        terrain/Triangles.cpp
        utils/utils.cpp
        glad/glad.c
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl_opengl3.cpp
        vendor/imgui/imgui_tables.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/stb_image/stb_image.cpp
        vendor/STBImage.h
        vendor/STBImage.cpp
        terrain/MidpointDisplacement.h)

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} src)

# Link libraries
target_link_libraries(terrain_generation_project OpenGL::GL glfw)