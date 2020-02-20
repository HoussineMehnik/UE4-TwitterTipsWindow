// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4TipsWindowCommands.h"

#define LOCTEXT_NAMESPACE "FUE4TipsWindowModule"

void FUE4TipsWindowCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "UE4 Tips", "Bring up UE4 Tips Window window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
