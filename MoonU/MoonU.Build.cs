// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MoonU : ModuleRules
{
	public MoonU(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "GameplayTags", "UMG" });
        
        PublicIncludePaths.AddRange(new string[] {"MoonU"});
	}
}
