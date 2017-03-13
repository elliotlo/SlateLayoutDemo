// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "StandaloneWndLayoutDemo.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "StandaloneWndLayoutDemoStyle.h"
#include "StandaloneWndLayoutDemoCommands.h"

#include "LevelEditor.h"

static const FName StandaloneWndLayoutDemoTabName("StandaloneWndLayoutDemo");

#define LOCTEXT_NAMESPACE "FStandaloneWndLayoutDemoModule"

void FStandaloneWndLayoutDemoModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FStandaloneWndLayoutDemoStyle::Initialize();
	FStandaloneWndLayoutDemoStyle::ReloadTextures();

	FStandaloneWndLayoutDemoCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWndLayoutDemoCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWndLayoutDemoModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FStandaloneWndLayoutDemoModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FStandaloneWndLayoutDemoModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWndLayoutDemoTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWndLayoutDemoModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWndLayoutDemoTabTitle", "StandaloneWndLayoutDemo"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FStandaloneWndLayoutDemoModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FStandaloneWndLayoutDemoStyle::Shutdown();

	FStandaloneWndLayoutDemoCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWndLayoutDemoTabName);
}

TSharedRef<SDockTab> FStandaloneWndLayoutDemoModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FStandaloneWndLayoutDemoModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("StandaloneWndLayoutDemo.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FStandaloneWndLayoutDemoModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(StandaloneWndLayoutDemoTabName);
}

void FStandaloneWndLayoutDemoModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FStandaloneWndLayoutDemoCommands::Get().OpenPluginWindow);
}

void FStandaloneWndLayoutDemoModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FStandaloneWndLayoutDemoCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWndLayoutDemoModule, StandaloneWndLayoutDemo)