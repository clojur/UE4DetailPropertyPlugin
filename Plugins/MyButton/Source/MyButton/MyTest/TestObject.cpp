#include "TestObject.h"
//#include "Internationalization/Internationalization.h"
#include "PropertyEditor/Private/DetailPropertyRow.h"
#include "PropertyEditor/Private/ObjectPropertyNode.h"
#define LOCTEXT_NAMESPACE "TestObject"
TSharedRef<IDetailCustomization> FMyClassCustomization::MakeInstance()
{
    return MakeShareable(new FMyClassCustomization());
}

void FMyClassCustomization::CustomizeDetails(IDetailLayoutBuilder & DetailBuilder)
{
    const FName DefaultCategoryName = "AuroraSettings";
    IDetailCategoryBuilder& DefaultCategory = DetailBuilder.EditCategory(DefaultCategoryName);
    DetailBuilder.HideCategory("TestObject");

    TArray<TWeakObjectPtr<UObject>> SelObjs;
    SelObjs = DetailBuilder.GetSelectedObjects();
    for (int32 i = 0; i < SelObjs.Num(); ++i)
    {
        UTestObject* pTestObj = Cast<UTestObject>(SelObjs[i]);
        if (pTestObj != nullptr)
        {
            for (TFieldIterator<UProperty> it(pTestObj->GetClass()); it; ++it)
            {
                FString PropertyName = it->GetName();
                TSharedRef<IPropertyHandle> PropertyHandle = DetailBuilder.GetProperty(PropertyName.GetCharArray().GetData());
    
                IDetailPropertyRow& PropertyRow = DefaultCategory.AddProperty(PropertyHandle);
                PropertyHandle->MarkResetToDefaultCustomized();

                TSharedPtr<SWidget> NameWidget;
                TSharedPtr<SWidget> ValueWidget;
                FDetailWidgetRow Row;

                PropertyRow.GetDefaultWidgets(NameWidget, ValueWidget, Row);
                const TCHAR* StrName= PropertyName.GetCharArray().GetData();
                PropertyRow.CustomWidget()
                    .NameContent()
                    .MinDesiredWidth(Row.NameWidget.MinWidth)
                    .MaxDesiredWidth(Row.NameWidget.MaxWidth)
                    [
                        NameWidget.ToSharedRef()
                        //SNew(SHorizontalBox)
                        //+ SHorizontalBox::Slot()
                        //.AutoWidth()
                        //[
                        //    SNew(SCheckBox)
                        //    .OnCheckStateChanged(this,&FMyClassCustomization::PlayGameClicked)
                        //]
                        //+ SHorizontalBox::Slot()
                        //.AutoWidth()
                        //[
                        //    NameWidget.ToSharedRef()
                        //]
                    ]
                    .ValueContent()
                    .MinDesiredWidth(Row.ValueWidget.MinWidth)
                    .MaxDesiredWidth(Row.ValueWidget.MaxWidth)
                    [
                        ValueWidget.ToSharedRef()
                    ];

                    TAttribute<bool> IsParamEnabled = TAttribute<bool>::Create(TAttribute<bool>::FGetter::CreateSP(this,&FMyClassCustomization::IsPropertyRowEnableEdit));
                    PropertyRow.EditCondition(IsParamEnabled, FOnBooleanValueChanged::CreateSP(this, &FMyClassCustomization::OnPropertyRowEnableChanged));
            }
        }
    }
}

void FMyClassCustomization::PlayGameClicked(ECheckBoxState BoxState)
{
    if (BoxState == ECheckBoxState::Checked)
    {
        bPropertyRowEnableEdit = true;
        UE_LOG(LogTemp, Warning, TEXT("Your message"));
    }
    else
    {
        bPropertyRowEnableEdit = false;
    }
}

void FMyClassCustomization::OnPropertyRowEnableChanged(bool NewChange)
{
    bPropertyRowEnableEdit = NewChange;
}

bool FMyClassCustomization::IsPropertyRowEnableEdit()
{
    return bPropertyRowEnableEdit;
}
#undef LOCTEXT_NAMESPACE 