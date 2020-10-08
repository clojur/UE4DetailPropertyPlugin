// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MyButtonStyle.h"

class FMyButtonCommands : public TCommands<FMyButtonCommands>
{
public:

	FMyButtonCommands()
		: TCommands<FMyButtonCommands>(TEXT("MyButton"), NSLOCTEXT("Contexts", "MyButton", "MyButton Plugin"), NAME_None, FMyButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
