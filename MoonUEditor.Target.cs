// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MoonUEditorTarget : TargetRules
{
	public MoonUEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
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
