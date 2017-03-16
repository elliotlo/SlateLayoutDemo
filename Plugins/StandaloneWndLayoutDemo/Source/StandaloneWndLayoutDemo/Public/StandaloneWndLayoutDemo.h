// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LayoutDemoLog, Log, All);

class FToolBarBuilder;
class FMenuBuilder;

class FStandaloneWndLayoutDemoModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	
	// create a new text block with text
	TSharedRef<class STextBlock> NewTextBlock(FString String);
	// create new title
	TSharedRef<class SBox> NewTitleBox(FString Title);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};