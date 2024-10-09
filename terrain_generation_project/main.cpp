#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "./h/Renderer.h"
#include "./h/Camera.h"
#include "./h/Texture.h"

#include "imgui_windows/ImGuiWin.h"

#include "terrain/BaseTerrain.h"
#include "terrain/MidpointDisplacement.h"


/* -------------- callback functions -------------- */

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}



/* -------- Create the graphics context && window -------- */

GLFWwindow* CreateWindowInitContext(int width, int height) {
    /* -------------- GLFW initialization -------------- */
    /*window, initial OpenGL context*/

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);


    /* -------------- GLAD initialization -------------- */
    /*OpenGL function pointers*/
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    /*size of the rendering window*/
    GLCall(glViewport(0, 0, width, height));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}


// global variables
Camera camera;

float deltaTime = 0.0f; //  Time between last frame and current frame
float lastFrame = 0.0f; //  Time of last frame

/* -------------- process user input -------------- */


void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        if(camera.IsFPSCamera()) {
            camera.SetFPSCamera(false);
        }
        else {
            camera.SetFPSCamera(true);
        }
    }
    camera.ProcessInput(window, deltaTime);
}

int terrainSize = 256;
float roughness;
float minH;
float maxH;

void initAlps(BaseTerrain* terrain, Shader* shader) {
    roughness = 1.0f;

    float worldScale = 1.0f;

    float textureScale = 4.0f;

    minH = 0.0f;

    maxH = 250.0f;

    std::vector<std::string> textureFilenames;

    textureFilenames.push_back("../resources/terrainTextures/alps/IMGP5525_seamless.jpg");
    textureFilenames.push_back("../resources/terrainTextures/alps/IMGP5487_seamless.jpg");
    textureFilenames.push_back("../resources/terrainTextures/alps/grass.png");
    textureFilenames.push_back("../resources/terrainTextures/alps/ice.jpg");


    terrain->InitTerrain(worldScale, textureScale, textureFilenames);



    ((MidpointDisplacement*)terrain)->CreateMidpointdDisplacement(terrainSize, roughness, minH, maxH, *shader);
}

void initRockyMountains(BaseTerrain* terrain, Shader* shader) {
    roughness = 1.0f;

    float worldScale = 1.0f;

    float textureScale = 4.0f;

    minH = 50.0f;

    maxH = 250.0f;

    std::vector<std::string> textureFilenames;

    textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/IMGP5525_seamless.jpg");
    textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/orangeRock.jpg");
    textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/gravel.jpg");
    textureFilenames.push_back("../resources/terrainTextures/rocky_mountains/yellowRock.jpg");


    terrain->InitTerrain(worldScale, textureScale, textureFilenames);

    ((MidpointDisplacement*)terrain)->CreateMidpointdDisplacement(terrainSize, roughness, minH, maxH, *shader);
}

void initFlatlands(BaseTerrain* terrain, Shader* shader) {
    roughness = 1.0f;

    float worldScale = 1.0f;

    float textureScale = 4.0f;

    minH = 150.0f;

    maxH = 200.0f;

    std::vector<std::string> textureFilenames;

    textureFilenames.push_back("../resources/terrainTextures/flatlands/gravel.jpg");
    textureFilenames.push_back("../resources/terrainTextures/flatlands/dirt.jpg");
    textureFilenames.push_back("../resources/terrainTextures/flatlands/mudgrass.jpg");
    textureFilenames.push_back("../resources/terrainTextures/flatlands/grass.jpg");


    terrain->InitTerrain(worldScale, textureScale, textureFilenames);

    ((MidpointDisplacement*)terrain)->CreateMidpointdDisplacement(terrainSize, roughness, minH, maxH, *shader);
}

void initDesert(BaseTerrain* terrain, Shader* shader) {
    roughness = 1.0f;

    float worldScale = 1.0f;

    float textureScale = 4.0f;

    minH = 150.0f;

    maxH = 200.0f;

    std::vector<std::string> textureFilenames;

    textureFilenames.push_back("../resources/terrainTextures/desert/bumpyRock.jpg");
    textureFilenames.push_back("../resources/terrainTextures/desert/sandStone.jpg");
    textureFilenames.push_back("../resources/terrainTextures/desert/sandStone.jpg");
    textureFilenames.push_back("../resources/terrainTextures/desert/sand.jpg");


    terrain->InitTerrain(worldScale, textureScale, textureFilenames);

    ((MidpointDisplacement*)terrain)->CreateMidpointdDisplacement(terrainSize, roughness, minH, maxH, *shader);
}

void initTundra(BaseTerrain* terrain, Shader* shader) {
    roughness = 1.0f;

    float worldScale = 1.0f;

    float textureScale = 4.0f;

    minH = 75.0f;

    maxH = 200.0f;

    std::vector<std::string> textureFilenames;

    textureFilenames.push_back("../resources/terrainTextures/tundra/asphalt.jpg");
    textureFilenames.push_back("../resources/terrainTextures/tundra/moss.jpg");
    textureFilenames.push_back("../resources/terrainTextures/tundra/snow.jpg");
    textureFilenames.push_back("../resources/terrainTextures/tundra/ice.jpg");


    terrain->InitTerrain(worldScale, textureScale, textureFilenames);

    ((MidpointDisplacement*)terrain)->CreateMidpointdDisplacement(terrainSize, roughness, minH, maxH, *shader);
}


/* -------------- main function (game loop) -------------- */

int terrainGeneration() {
    GLFWwindow* window = CreateWindowInitContext(1200, 800);
    if(!window) return -1;

    glEnable(GL_DEPTH_TEST);

    Shader diffuseShader("../resources/shaders/TerrainTextured.shader");
    Shader cartoonShader("../resources/shaders/TerrainTexturedCartoon.shader");

    Shader* currentShader = &diffuseShader;

    currentShader->Bind();

    //  Midpoint displacement
    MidpointDisplacement terrain;

    initAlps(&terrain, currentShader);

    //  ImGUI init
    ImGuiWin imGuiWindow;
    imGuiWindow.Init(window);

    float gHeight0 = 50.0;
    float gHeight1 = 100.0;
    float gHeight2 = 150.0;
    float gHeight3 = 200.0;

    currentShader->SetUniform1f("gHeight0", gHeight0);
    currentShader->SetUniform1f("gHeight1", gHeight1);
    currentShader->SetUniform1f("gHeight2", gHeight2);
    currentShader->SetUniform1f("gHeight3", gHeight3);

    int currShaderSelection = 0;
    int currBiomeSelection = 0;

    while(!glfwWindowShouldClose(window)) { //checks if the window is instructed to close


        GLCall(glClearColor(0.3f, 0.3f, 0.3f, 1.0f));
        processInput(window);       //process keys
        /* ---------- Rendering ---------- */

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        //  Calculating delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::vec3 lightDir = glm::normalize(glm::vec3(sin(currentFrame), -1.0f, cos(currentFrame)));
        currentShader->SetUniform3f("gReversedLightDir", lightDir.x, -1.0f, lightDir.z);

        currentShader->Bind();

        camera.UpdateViewMatrix();
        currentShader->SetUniformMat4f("view", camera.GetViewMatrix());

        camera.UpdateProjectionMatrix();
        currentShader->SetUniformMat4f("projection", camera.GetProjectionMatrix());

        terrain.Render(*currentShader);

        imGuiWindow.Update();

        glm::vec3 cameraPos = camera.GetCameraPos();

        {
            ImGui::Begin("Settings:");

            ImGui::SliderFloat("Height0", &gHeight0, 0.0f, 250.0f);
            ImGui::SliderFloat("Height1", &gHeight1, 0.0f, 250.0f);
            ImGui::SliderFloat("Height2", &gHeight2, 0.0f, 250.0f);
            ImGui::SliderFloat("Height3", &gHeight3, 0.0f, 250.0f);

            if(ImGui::Button("Apply")) {
                currentShader->SetUniform1f("gHeight0", gHeight0);
                currentShader->SetUniform1f("gHeight1", gHeight1);
                currentShader->SetUniform1f("gHeight2", gHeight2);
                currentShader->SetUniform1f("gHeight3", gHeight3);

            }

            ImVec2 space(0.0f, 10.0f);  // 10 pixels of space in both directions
            ImGui::Dummy(space);

            // Lighting combo-box
            {

                std::vector<const char*> items = {"Diffuse", "Cartoon"};
                if (ImGui::BeginCombo("Lighting", items[currShaderSelection]))
                {
                    for (int i = 0; i < items.size(); i++)
                    {
                        bool isSelected = (currShaderSelection == i); // Check if the item is selected
                        if (ImGui::Selectable(items[i], isSelected)) // If the item is clicked
                        {
                            currentShader->Unbind();
                            currShaderSelection = i; // Update the selected item index
                            switch (i) {
                                case 0:
                                    currentShader = &diffuseShader;
                                    break;
                                case 1:
                                    currentShader = &cartoonShader;
                                    break;
                            }
                            currentShader->Bind();
                            currentShader->SetUniform1f("maxHeight", minH);
                            currentShader->SetUniform1f("minHeight", maxH);
                            currentShader->SetUniform1f("gHeight0", gHeight0);
                            currentShader->SetUniform1f("gHeight1", gHeight1);
                            currentShader->SetUniform1f("gHeight2", gHeight2);
                            currentShader->SetUniform1f("gHeight3", gHeight3);
                        }

                        // Set the initial focus when opening the combo box
                        if (isSelected)
                            ImGui::SetItemDefaultFocus(); // Ensure the currently selected item is focused
                    }
                    ImGui::EndCombo();
                }
            }


            // Biome
            {

                std::vector<const char*> items = {"Alps", "Rocky mountains", "Flatlands", "Desert", "Tundra"};
                if (ImGui::BeginCombo("Biome", items[currBiomeSelection]))
                {
                    for (int i = 0; i < items.size(); i++)
                    {
                        bool isSelected = (currBiomeSelection == i); // Check if the item is selected
                        if (ImGui::Selectable(items[i], isSelected)) // If the item is clicked
                        {
                            currBiomeSelection = i; // Update the selected item index
                            switch (i) {
                                case 0:
                                    initAlps(&terrain, currentShader);
                                   break;
                                case 1:
                                    initRockyMountains(&terrain, currentShader);
                                    break;
                                case 2:
                                    initFlatlands(&terrain, currentShader);
                                    break;
                                case 3:
                                    initDesert(&terrain, currentShader);
                                    break;
                                case 4:
                                    initTundra(&terrain, currentShader);
                                break;
                            }
                        }

                        // Set the initial focus when opening the combo box
                        if (isSelected)
                            ImGui::SetItemDefaultFocus(); // Ensure the currently selected item is focused
                    }
                    ImGui::EndCombo();
                }
            }

            ImGui::Dummy(space);

            ImGui::Text("Camera:");

            ImGui::Text("X: %.2f", cameraPos.x);
            ImGui::Text("Y: %.2f", cameraPos.y);
            ImGui::Text("Z: %.2f", cameraPos.z);

            ImGui::End();
        }

        imGuiWindow.Render();

        glfwSwapBuffers(window);    //shows contains of the color buffer to the screen (double [front:end] buffer)
        glfwPollEvents();
    }

    imGuiWindow.End();
    glfwTerminate();
    return 0;
}

/* ---------------------------------------------- */


int main() {
    return terrainGeneration();
}
