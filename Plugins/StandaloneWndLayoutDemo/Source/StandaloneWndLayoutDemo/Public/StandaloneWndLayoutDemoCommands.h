// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "StandaloneWndLayoutDemoStyle.h"

class FStandaloneWndLayoutDemoCommands : public TCommands<FStandaloneWndLayoutDemoCommands>
{
public:

	FStandaloneWndLayoutDemoCommands()
		: TCommands<FStandaloneWndLayoutDemoCommands>(TEXT("StandaloneWndLayoutDemo"), NSLOCTEXT("Contexts", "StandaloneWndLayoutDemo", "StandaloneWndLayoutDemo Plugin"), NAME_None, FStandaloneWndLayoutDemoStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};