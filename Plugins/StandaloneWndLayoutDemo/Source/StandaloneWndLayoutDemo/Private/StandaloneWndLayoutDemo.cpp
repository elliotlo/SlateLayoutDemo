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
		FText::FromString(TEXT("FTestEditorStandaloneWndModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TestEditorStandaloneWnd.cpp"))
	);



	TSharedRef<SDockTab> DockTab =
		SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// 建立一個 ScrollBox 
			SNew(SScrollBox)
			// 一開始先來個 VerticalBox
			+ SScrollBox::Slot()
			[
				SNew(SBox)
				.HAlign(EHorizontalAlignment::HAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString("--- VerticalBox ---"))
				]
			]
			+ SScrollBox::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				[

					// 靠左對齊
					SNew(STextBlock)
					.Text(FText::FromString("Vertical1 Align Left"))
				]
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				[
					// 置中對齊
					SNew(STextBlock)
					.Text(FText::FromString("Vertical2 Align Center"))
				]
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Right)
				[
					// 靠右對齊
					SNew(STextBlock)
					.Text(FText::FromString("Vertical3 Align Right"))
				]
			]
			// 再來個 HorizontalBox
			+ SScrollBox::Slot()
			[
				// 
				SNew(SBox)
				.HAlign(EHorizontalAlignment::HAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString("--- HorizontalBox ---"))
				]
			]
			+ SScrollBox::Slot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Horizontal1"))
				]
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.ColorAndOpacity(FSlateColor(FLinearColor(0.5f, 0.7f, 0.3f)))	// 測試換顏色
					.Text(FText::FromString("Horizontal2"))
				]
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Horizontal3"))
				]
			]
			// WrapBox
			+ SScrollBox::Slot()
			[
				// 
				SNew(SBox)
				.HAlign(EHorizontalAlignment::HAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString("--- WrapBox ---"))
				]
			]
			+ SScrollBox::Slot()
			[
				SNew(SWrapBox)
				.PreferredWidth(200)	// 超過多少寬度就自動wrap
				+ SWrapBox::Slot()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Wrap1"))
				]
				+ SWrapBox::Slot()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Wrap2"))
				]
				+ SWrapBox::Slot()
				[
					SNew(STextBlock)
					.Text(FText::FromString("Wrap3"))
				]
			]
			// UniformGridBox
			+ SScrollBox::Slot()
			[
				SNew(SBox)
				.HAlign(EHorizontalAlignment::HAlign_Center)
				[
					SNew(STextBlock)
					.Text(FText::FromString("--- UniformGridPanel ---"))
				]
			]
			+ SScrollBox::Slot()
			[
				SNew(SUniformGridPanel)
				.ForceVolatile(true)
				+ SUniformGridPanel::Slot(0, 0)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Grid (0,0)"))
				]
				+ SUniformGridPanel::Slot(0, 1)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Grid (0,1)"))
				]
				+ SUniformGridPanel::Slot(0, 2)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Grid (0,2)"))
				]
				+ SUniformGridPanel::Slot(1, 0)
				[
					SNew(SEditableText)
					.HintText(FText::FromString("Grid(1,0) editable"))
				]
				+ SUniformGridPanel::Slot(1, 2)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Grid (1,2)"))
				]
				+ SUniformGridPanel::Slot(2, 0)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Grid (2,0)"))
				]
				+ SUniformGridPanel::Slot(2, 1)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Grid (2,1)"))
				]
				+ SUniformGridPanel::Slot(2, 2)
				[
					/*FSlateBrush*/
					SNew(SCheckBox)
				]
			]
		];

	//SNew(SDockTab)
	//.TabRole(ETabRole::NomadTab)
	//[
	//	// Put your tab content here!
	//	SNew(SBox)
	//	.HAlign(HAlign_Center)
	//.VAlign(VAlign_Center)
	//[
	//	SNew(STextBlock)
	//	.Text(WidgetText)
	//]
	//];


	return DockTab;
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