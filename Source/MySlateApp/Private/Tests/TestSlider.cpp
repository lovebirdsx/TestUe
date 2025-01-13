#include "DeclarativeSyntaxSupport.h"
#include "TestSlider.h"
#include "Log.h"
#include "MyConfig.h"
#include "SButton.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"


#define LOCTEXT_NAMESPACE "MySlateApp"

class FTestSliderImpl : public FUiTestBase, public TSharedFromThis<FTestSliderImpl>
{
public:
    FTestSliderImpl()
    {
        SliderValue = FMyConfigGetter::Get().GetConfig()->SliderValue;
    }

    virtual FName GetName() const override
    {		
        return FName(TEXT("Test Slider"));
    }
    
    virtual TSharedRef<SWidget> CreateWidget() const override
    {        
        return SNew(SVerticalBox)            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("SliderTitle", "测试 Slider 控件"))
                .Font(FCoreStyle::Get().GetFontStyle("LargeFont"))
            ]            
            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10)
            [
                SNew(SSlider)
                .OnValueChanged(this, &FTestSliderImpl::OnSliderValueChanged)
                .Value(this, &FTestSliderImpl::GetSliderValue)
                .ToolTipText(LOCTEXT("SliderTooltip", "拖动滑块以更改值"))
            ]            
            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10)
            [
                SNew(STextBlock)
                .Text(this, &FTestSliderImpl::GetSliderValueText)
            ];
    }

private:    
    mutable TAttribute<float> SliderValue;
    
    float GetSliderValue() const
    {
        return SliderValue.Get();
    }
    
    FText GetSliderValueText() const
    {
        return FText::Format(LOCTEXT("SliderValueFormat", "当前值: {0}"), FText::AsNumber(SliderValue.Get()));
    }
    
    void OnSliderValueChanged(float NewValue) const
    {        
        SliderValue.Set(NewValue);
        FMyConfigGetter::Get().GetConfig()->SliderValue = NewValue;
        
        LOG("Slider 值已更改为: %f", NewValue);
    }
};

FTestSlider::FTestSlider()
{
    Impl = MakeShared<FTestSliderImpl>();
}

FTestSlider::~FTestSlider()
{
}

FName FTestSlider::GetName() const
{
    return Impl->GetName();	
}

TSharedRef<SWidget> FTestSlider::CreateWidget() const
{
    return Impl->CreateWidget();
}

#undef LOCTEXT_NAMESPACE
