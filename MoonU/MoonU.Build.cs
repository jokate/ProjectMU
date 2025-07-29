// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MoonU : ModuleRules
{
	public MoonU(ReadOnlyTargetRules Target) : base(Target)
	{
		bEnableUndefinedIdentifierWarnings = false;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG", 
			"GameplayAbilities", "MotionWarping", "NavigationSystem", "AIModule", "GameplayTasks", "NNE"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[] {
			"GameFeatures",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags"
		});
		
		PublicIncludePaths.AddRange(new string[] {"MoonU"});
	}
}
