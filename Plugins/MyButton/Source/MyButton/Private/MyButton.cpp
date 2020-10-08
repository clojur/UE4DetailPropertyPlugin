// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MyButton.h"
#include "MyButtonStyle.h"
#include "MyButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "PropertyEditor/Public/PropertyEditing.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"



#include "LevelEditor.h"

static const FName MyButtonTabName("MyButton");

#define LOCTEXT_NAMESPACE "FMyButtonModule"

void FMyButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMyButtonStyle::Initialize();
	FMyButtonStyle::ReloadTextures();

	FMyButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMyButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMyButtonModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FMyButtonModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FMyButtonModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

  FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
  PropertyModule.RegisterCustomClassLayout("TestObject", FOnGetDetailCustomizationInstance::CreateStatic(&FMyClassCustomization::MakeInstance));
}

void FMyButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FMyButtonStyle::Shutdown();

	FMyButtonCommands::Unregister();
}

void FMyButtonModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
  FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
  UTestObject* MyTestObj = NewObject<UTestObject>();
  MyTestObj->Count = 90;
  this->TestObjectPtr=TSharedPtr<UTestObject>(MyTestObj);
  TArray<UObject*> Objs;
  Objs.Add(MyTestObj);

  TSharedRef<SWindow> PropertyWindow= PropertyModule.CreateFloatingDetailsView(Objs,false);
  PropertyWindow->SetOnWindowClosed(
    FOnWindowClosed::CreateLambda([this](const TSharedRef<SWindow>& Window) 
          {this->TestObjectPtr = nullptr; }
    )
  );
}

void FMyButtonModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FMyButtonCommands::Get().PluginAction);
}

void FMyButtonModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FMyButtonCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyButtonModule, MyButton)