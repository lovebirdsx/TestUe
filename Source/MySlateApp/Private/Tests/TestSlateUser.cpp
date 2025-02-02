#include "DeclarativeSyntaxSupport.h"
#include "TestSlateUser.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/SlateUser.h"
#include "Log.h"
#include "SButton.h"
#include "Widgets/SBoxPanel.h"

#define LOCTEXT_NAMESPACE "MySlateApp"

class FTestSlateUserImpl : public FUiTestBase, public TSharedFromThis<FTestSlateUserImpl>
{
public:
	virtual FName GetName() const override
	{
		return FName(TEXT("Test Slate User"));
	}

	virtual TSharedRef<SWidget> CreateWidget() const override
	{
        return SNew(SVerticalBox)
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10)
            [
                SNew(SButton)
				.Text(LOCTEXT("MyButtonText1", "Set Mouse Pos to (400, 400)"))
				.OnClicked_Lambda([]() -> FReply
				{
					LOG("Set Mouse Pos to (400, 400)");
					FSlateApplication& App = FSlateApplication::Get();
					TSharedPtr<FSlateUser> User = App.GetUser(App.GetUserIndexForMouse());
					if (User.IsValid())
					{
						User->SetCursorPosition(400, 400);
					}

					return FReply::Handled();
				})
            ]

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(10)
            [
				SNew(SButton)
				.Text(LOCTEXT("MyButtonText2", "Print Mouse Pos"))
				.OnClicked_Lambda([]() -> FReply
				{
					FSlateApplication& App = FSlateApplication::Get();
					TSharedPtr<FSlateUser> User = App.GetUser(App.GetUserIndexForMouse());
					if (User.IsValid())
					{
						FVector2D MousePos = User->GetCursorPosition();
						LOG("Mouse Pos: (%f, %f)", MousePos.X, MousePos.Y);
					}

					return FReply::Handled();
				})
            ];
	}
};

FTestSlateUser::FTestSlateUser()
{
	Impl = MakeShared<FTestSlateUserImpl>();
}

FTestSlateUser::~FTestSlateUser()
{
}

FName FTestSlateUser::GetName() const
{
	return Impl->GetName();
}

TSharedRef<SWidget> FTestSlateUser::CreateWidget() const
{
	return Impl->CreateWidget();
}

#undef LOCTEXT_NAMESPACE
