#include "Zinet/Core/ZtLevel.h"
#include <imgui.h>

void ZtLevel::BeginPlay()
{
}

void ZtLevel::Tick(float DeltaTime)
{
}

void ZtLevel::EndPlay()
{
}

#ifdef ZINET_DEBUG_UI
void ZtLevel::ImGuiChildren() const
{
    if (ImGui::TreeNode("Level"))
    {
        ImGui::Separator();
        ImGui::Text("Placeholder");
        ImGui::NewLine();

        ImGui::TreePop();
    }
}
#endif
