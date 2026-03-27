// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class OnlineMultiPlayerEditorTarget : TargetRules
{
	public OnlineMultiPlayerEditorTarget(TargetInfo Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.V5;
		bLegacyParentIncludePaths = false;
		bValidateFormatStrings = true;
		WindowsPlatform.bStrictConformanceMode = true;
		Type = TargetType.Editor;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		CppStandard = CppStandardVersion.Cpp20;
		ExtraModuleNames.Add("OnlineMultiPlayer");
	}
}
