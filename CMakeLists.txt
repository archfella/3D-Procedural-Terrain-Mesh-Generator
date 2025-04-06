cmake_minimum_required(VERSION 3.10)
project(TerrainGenerator)

set(CMAKE_CXX_STANDARD 17)

# Set the path to third-party libraries
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/ImGui)
set(GLFW_DIR /usr/local/opt/glfw)
# Set the path to third-party libraries
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/vendor/ImGui)
set(GLFW_DIR /usr/local/opt/glfw)

add_executable(TerrainGenerator main.cpp
                h/Assertion.h
                src/Assertion.cpp
                h/Camera.h
                src/Camera.cpp
                h/EBO.h
                src/EBO.cpp
                h/Shader.h
                src/Shader.cpp
                h/Texture.h
                src/Texture.cpp
                h/VAO.h
                src/VAO.cpp
                h/VBLayout.h
                src/VBLayout.cpp
                h/VBO.h
                src/VBO.cpp
                terrain/Triangles.h
                terrain/Triangles.cpp
                terrain/Terrain.h
                terrain/Terrain.cpp
                utils/utils.h
                utils/utils.cpp
                utils/Array2D.h
                vendor/stb_image/stb_image.cpp
                vendor/STBImage.h
                vendor/STBImage.cpp
                )

# Find GLEW include dirs.
find_path(GLEW_INCLUDE_DIRS GL/glew.h)
include_directories(${GLEW_INCLUDE_DIRS})

# Defines the 'imgui' library.
add_library(imgui STATIC
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ImguiWindow/CustomizationWindow.cpp
        ImguiWindow/CustomizationWindow.h
        h/Assertion.h
        src/Assertion.cpp
)

# Include directories from 'imgui' library, including the backends.
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_include_directories(imgui PUBLIC ${IMGUI_DIR}/backends)


# Include directories for GLFW, needed by ImGui backend
target_include_directories(imgui PRIVATE ${GLFW_DIR}/include)

# Add ImGui and GLFW
    # This tells CMake to:
        # 1. Enter the GLFW directory.
        # 2. Find its CMakeLists.txt
        # 3. Build GLFW as part of our project.
    # *Find GLFW - This automatically finds the installed GLFW3 package, as it is installed system-wide (via: brew install glfw)
find_package(GLFW3 REQUIRED)

# Add GLEW for OpenGL function loading
find_library(GLEW_LIBRARIES NAMES GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Link OpenGL (since it's required for your project)
find_library(OpenGL_LIBRARY OpenGL)

# Link the libraries (ImGui, GLFW, OpenGL and GLEW)
target_link_libraries(TerrainGenerator PRIVATE imgui glfw ${OpenGL_LIBRARY} ${GLEW_LIBRARIES})

# Include directories for FileExplorerMacOS
target_include_directories(TerrainGenerator PRIVATE ${GLFW_DIR}/include)