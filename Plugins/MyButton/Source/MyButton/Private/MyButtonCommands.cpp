// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MyButtonCommands.h"

#define LOCTEXT_NAMESPACE "FMyButtonModule"

void FMyButtonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MyButton", "Execute MyButton action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
