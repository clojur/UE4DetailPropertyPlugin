#pragma once
#include "CoreMinimal.h"
#include "PropertyEditor/Public/PropertyEditing.h"
#include "IDetailCustomization.h"
#include "TestObject.generated.h"
UCLASS()
class UTestObject :public UObject
{
  GENERATED_BODY()

public:

  UPROPERTY(EditAnywhere)
  int32 Count;
};



/**
*
*/
class  FMyClassCustomization : public IDetailCustomization
{
public:
  static TSharedRef<IDetailCustomization> MakeInstance();

  virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

  void PlayGameClicked(ECheckBoxState BoxState);

  void OnPropertyRowEnableChanged(bool NewChange);

  bool IsPropertyRowEnableEdit();

  bool bPropertyRowEnableEdit=false;
};