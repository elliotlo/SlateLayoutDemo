// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "StandaloneWndLayoutDemo.h"
#include "StandaloneWndLayoutDemoCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneWndLayoutDemoModule"

void FStandaloneWndLayoutDemoCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "StandaloneWndLayoutDemo", "Bring up StandaloneWndLayoutDemo window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
