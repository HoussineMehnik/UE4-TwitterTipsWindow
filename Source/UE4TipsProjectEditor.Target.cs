// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UE4TipsProjectEditorTarget : TargetRules
{
	public UE4TipsProjectEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "UE4TipsProject" } );
	}
}
