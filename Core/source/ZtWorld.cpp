#include "Zinet/Core/ZtWorld.h"
#include <imgui.h>

void ZtWorld::BeginPlay()
{
	Logger->info("{}", __FUNCTION__);

    Level.BeginPlay();
}

void ZtWorld::Tick(float DeltaTime)
{
    Level.Tick(DeltaTime);
}

void ZtWorld::EndPlay()
{
	Logger->info("{}", __FUNCTION__);

    Level.EndPlay();
}

ZtLevel& ZtWorld::GetLevel()
{
	return Level;
}

#ifdef ZINET_DEBUG_UI
void ZtWorld::ImGuiChildren() const
{
    if (ImGui::TreeNode("World"))
    {
        ImGui::Separator();
        ImGui::Text("Placeholder");
        ImGui::NewLine();

        ImGui::TreePop();
    }

    Level.ImGuiChildren();
}
#endif
