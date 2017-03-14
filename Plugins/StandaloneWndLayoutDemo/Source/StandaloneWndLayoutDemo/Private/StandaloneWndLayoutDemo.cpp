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

// create a new text block with text
TSharedRef<STextBlock> NewTextBlock(FString String)
{
	return SNew(STextBlock)
		.Text(FText::FromString(String));
}

// create new title
TSharedRef<SBox> NewTitleBox(FString Title)
{
	// Use engine's font
	FString FontPath = FPaths::EngineDir() + TEXT("Content\\Slate\\Fonts\\DroidSansMono.ttf");
	FSlateFontInfo FontInfo(FontPath, 20);

	return SNew(SBox)
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			SNew(STextBlock)
			.Text(FText::FromString(Title))
			.ColorAndOpacity(FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f)))
			.Font(FontInfo)
		];
}

TSharedRef<SDockTab> FStandaloneWndLayoutDemoModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTestEditorStandaloneWndModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TestEditorStandaloneWnd.cpp"))
	);

	// Create DockTab
	TSharedRef<SDockTab> DockTab = SNew(SDockTab)
									.TabRole(ETabRole::NomadTab);

	// Create VerticalBox
	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox);

	VerticalBox->AddSlot()
		.HAlign(EHorizontalAlignment::HAlign_Left)
		[
			NewTextBlock(TEXT("Vertical Align Left"))
		];
	VerticalBox->AddSlot()
		.HAlign(EHorizontalAlignment::HAlign_Right)
		[
			NewTextBlock(TEXT("Vertical Align Right"))
		];
	VerticalBox->AddSlot()
		.HAlign(EHorizontalAlignment::HAlign_Center)
		[
			NewTextBlock(TEXT("Vertical Align Center"))
		];
	VerticalBox->AddSlot()
		.HAlign(EHorizontalAlignment::HAlign_Fill)
		[
			NewTextBlock(TEXT("Vertical Align Fill"))
		];
	VerticalBox->AddSlot()
		[
			SNew(SEditableText)
			.HintText(FText::FromString(TEXT("editable")))
		];
	VerticalBox->AddSlot()
		[
			SNew(SCheckBox)
			.ToolTipText(FText::FromString(TEXT("this is checkbox")))
		];

	// Create HorizontalBox
	TSharedRef<SHorizontalBox> HorizontalBox = SNew(SHorizontalBox);
	HorizontalBox->AddSlot()
		[
			NewTextBlock(TEXT("horizontal1"))
		];
	HorizontalBox->AddSlot()
		[
			SNew(STextBlock)
			.ColorAndOpacity(FSlateColor(FLinearColor(0.5f, 0.7f, 0.3f)))	// Change Color and opacity
			.Text(FText::FromString(TEXT("Horizontal2")))
		];
	HorizontalBox->AddSlot()
		[
			NewTextBlock(TEXT("Horizontal3"))
		];

	// Create WrapBox
	TSharedRef<SWrapBox> WrapBox = SNew(SWrapBox)
									.PreferredWidth(200);	// auto wrap when exceed;
	int i;
	const int WrapWidgetNum = 20;
	for (i = 0; i < WrapWidgetNum; i++)
	{
		WrapBox->AddSlot()
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Wrap") + FString::FromInt(i)))
			];
	}


	// Create UniformGridPanel
	TSharedRef<SUniformGridPanel> UniformGird = SNew(SUniformGridPanel);
	int row, col;
	const int RowNum = 5;
	const int ColNum = 4;
	for (row = 0; row < RowNum; row++)
	{
		for (col = 0; col < ColNum; col++)
		{
			UniformGird->AddSlot(col, row)
				[
					NewTextBlock(TEXT("Gird(") + FString::FromInt(col) + TEXT(",") + FString::FromInt(row) + TEXT(")"))
				];
		}
	}

	// Add widgets to ScrollBox
	TSharedRef<SScrollBox> ScrollBox = SNew(SScrollBox);
	ScrollBox->AddSlot()[ NewTitleBox(TEXT("VerticalBox")) ];
	ScrollBox->AddSlot()[ VerticalBox ];
	ScrollBox->AddSlot()[ NewTitleBox(TEXT("HorizontalBox")) ];
	ScrollBox->AddSlot()[ HorizontalBox ];
	ScrollBox->AddSlot()[ NewTitleBox(TEXT("WrapBox")) ];
	ScrollBox->AddSlot()[ WrapBox ];
	ScrollBox->AddSlot()[ NewTitleBox(TEXT("UniformGridPanel")) ];
	ScrollBox->AddSlot()[ UniformGird ];

	// Set ScrollBox to DockTab
	DockTab->SetContent(ScrollBox);


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