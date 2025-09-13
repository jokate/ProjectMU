// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MoonUTarget : TargetRules
{
	public MoonUTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		bLegacyParentIncludePaths = false;
		
		CppStandard = CppStandardVersion.Default;     
		WindowsPlatform.bStrictConformanceMode = true;
		bValidateFormatStrings = true;
		
		ExtraModuleNames.Add("MoonU");
		ExtraModuleNames.Add("BTHTN");
	}
}
