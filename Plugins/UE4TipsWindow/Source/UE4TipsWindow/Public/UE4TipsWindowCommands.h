// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "UE4TipsWindowStyle.h"

class FUE4TipsWindowCommands : public TCommands<FUE4TipsWindowCommands>
{
public:

	FUE4TipsWindowCommands()
		: TCommands<FUE4TipsWindowCommands>(TEXT("UE4TipsWindow"), NSLOCTEXT("Contexts", "UE4TipsWindow", "UE4TipsWindow Plugin"), NAME_None, FUE4TipsWindowStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};