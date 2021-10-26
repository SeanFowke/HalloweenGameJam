// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HalloweenGameJam : ModuleRules
{
	public HalloweenGameJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
