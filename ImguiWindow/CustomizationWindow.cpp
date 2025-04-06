//
// Created by Filip Radovic on 4.4.25..
//

#include <imgui.h>
#include <vector>

#include "CustomizationWindow.h"

#include "../h/Camera.h"
#include "../terrain/Terrain.h"
#include "../h/Shader.h"


float CustomizationWindow::gHeight0 = 50.0f;
float CustomizationWindow::gHeight1 = 100.0f;
float CustomizationWindow::gHeight2 = 150.0f;
float CustomizationWindow::gHeight3 = 200.0f;

CustomizationWindow::CustomizationWindow() {
}

void CustomizationWindow::Render() {
    Shader* currentShader = Shader::GetGlobalShader();

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

    // Biome
    {

        static int currBiomeSelection = 0;

        Terrain* terrain = Terrain::GetInstance();

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
                            terrain->InitBiome(Terrain::BiomeType::ALPS);
                            break;
                        case 1:
                            terrain->InitBiome(Terrain::BiomeType::ROCKY);
                            break;
                        case 2:
                            terrain->InitBiome(Terrain::BiomeType::FLAT);
                            break;
                        case 3:
                            terrain->InitBiome(Terrain::BiomeType::DESERT);
                            break;
                        case 4:
                            terrain->InitBiome(Terrain::BiomeType::TUNDRA);
                            break;
                        default:
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

    glm::vec3 cameraPos = Camera::GetInstance()->GetCameraPos();

    ImGui::Text("X: %.2f", cameraPos.x);
    ImGui::Text("Y: %.2f", cameraPos.y);
    ImGui::Text("Z: %.2f", cameraPos.z);

    ImGui::End();

}

