#include "DeclarativeSyntaxSupport.h"
#include "TestModalWindow.h"
#include "Log.h"
#include "MyConfig.h"
#include "SButton.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/Input/SSlider.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/SWindow.h"


#define LOCTEXT_NAMESPACE "MySlateApp"

class FTestModalWindowImpl : public FUiTestBase, public TSharedFromThis<FTestModalWindowImpl>
{
public:
    virtual FName GetName() const override
    {
        return FName(TEXT("Test ModalWindow"));
    }

    virtual TSharedRef<SWidget> CreateWidget() const override
    {
        return SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("ModalWindowTitle", "测试 ModalWindow"))
                .Font(FCoreStyle::Get().GetFontStyle("LargeFont"))
            ]
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10)
            [
                SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(5)
                [
                    SNew(SButton)
                    .Text(LOCTEXT("Display1ModalWindow", "显示1个ModalWindow"))
                    .OnClicked_Lambda([this]() -> FReply
                    {
						this->ShowModalWindowByCount(TEXT("1"), 1);
                        return FReply::Handled();
                    })
                ]
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(5)
                [
                    SNew(SButton)
                    .Text(LOCTEXT("Display2ModalWindow", "显示2个ModalWindow"))
                    .OnClicked_Lambda([this]() -> FReply
                    {
						this->ShowModalWindowByCount(TEXT("2"), 2);
                        return FReply::Handled();
                    })
                ]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(5)
				[
					SNew(SButton)
					.Text(LOCTEXT("Display3ModalWindow", "显示3个ModalWindow"))
					.OnClicked_Lambda([this]()->FReply
					{
						this->ShowModalWindowByCount(TEXT("3"), 3);
						return FReply::Handled();
					})
                ]
            ];
    }

    void ShowModalWindowByCount(const FString& Prefix, int Count) const
    {
        for (int i = 0; i < Count; ++i)
        {
            TSharedRef<SWindow> ModalWindow = SNew(SWindow)
                .Title(FText::Format(LOCTEXT("ModalWindowTitle", "Modal Window {0}-{1}"), FText::FromString(Prefix), i + 1))
                .ClientSize(FVector2D(400, 300))
                .SupportsMinimize(false)
                .SupportsMaximize(false)
                .SizingRule(ESizingRule::Autosized);

            ModalWindow->SetContent(
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(10)
                [
                    SNew(STextBlock)
                    .Text(FText::Format(LOCTEXT("ModalWindowContent", "This is the {0}-{1} modal window."), FText::FromString(Prefix), i + 1))
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(10)
                [
                    SNew(SButton)
                    .Text(LOCTEXT("ShowAnotherModalWindow", "Show Another Modal Window"))
                    .OnClicked_Lambda([this, &Prefix, i, ModalWindow]()->FReply
                    {
                        this->ShowModalWindowByCount(FString::Printf(TEXT("%s-%d"), *Prefix, i + 1), 1);
                        return FReply::Handled();
                    })
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(10)
                [
                    SNew(SButton)
                    .Text(LOCTEXT("CloseButton", "Close"))
                    .OnClicked_Lambda([ModalWindow]()
                    {
                        ModalWindow->RequestDestroyWindow();
                        return FReply::Handled();
                    })
                ]
            );

            FSlateApplication::Get().AddModalWindow(
                ModalWindow,
                FSlateApplication::Get().GetActiveTopLevelWindow()
            );
        }
    }
};

FTestModalWindow::FTestModalWindow()
{
    Impl = MakeShared<FTestModalWindowImpl>();
}

FTestModalWindow::~FTestModalWindow()
{
}

FName FTestModalWindow::GetName() const
{
    return Impl->GetName();
}

TSharedRef<SWidget> FTestModalWindow::CreateWidget() const
{
    return Impl->CreateWidget();
}

#undef LOCTEXT_NAMESPACE
