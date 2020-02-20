// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4TipsWindow.h"
#include "UE4TipsWindowStyle.h"
#include "UE4TipsWindowCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "SWebBrowser.h"

static const FName UE4TipsWindowTabName("UE4TipsWindow");

#define LOCTEXT_NAMESPACE "FUE4TipsWindowModule"

void FUE4TipsWindowModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FUE4TipsWindowStyle::Initialize();
	FUE4TipsWindowStyle::ReloadTextures();

	FUE4TipsWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUE4TipsWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FUE4TipsWindowModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FUE4TipsWindowModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FUE4TipsWindowModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(UE4TipsWindowTabName, FOnSpawnTab::CreateRaw(this, &FUE4TipsWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FUE4TipsWindowTabTitle", "UE4 Tips"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FUE4TipsWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FUE4TipsWindowStyle::Shutdown();

	FUE4TipsWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(UE4TipsWindowTabName);
}

TSharedRef<SDockTab> FUE4TipsWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SWebBrowser)
				.ShowErrorMessage(true)
				.SupportsTransparency(false)
				.ShowControls(false)
				.ShowInitialThrobber(false)
				.ShowAddressBar(false)
				.InitialURL(FString("https://twitter.com/hashtag/ue4tips?src=hashtag_click&f=live"))
			]
		];
}

void FUE4TipsWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(UE4TipsWindowTabName);
}

void FUE4TipsWindowModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FUE4TipsWindowCommands::Get().OpenPluginWindow);
}

void FUE4TipsWindowModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FUE4TipsWindowCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUE4TipsWindowModule, UE4TipsWindow)