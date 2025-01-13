#include "DeclarativeSyntaxSupport.h"
#include "TestButton.h"
#include "Log.h"
#include "SButton.h"

#define LOCTEXT_NAMESPACE "MySlateApp"

class FTestButtonImpl : public FUiTestBase, public TSharedFromThis<FTestButtonImpl>
{
public:
	virtual FName GetName() const override
	{		
		return FName(TEXT("Test Button"));
	}
	
	virtual TSharedRef<SWidget> CreateWidget() const override
	{
		return SNew(SButton)
		.Text(LOCTEXT("MyButtonText", "Click Me!!!"))
		.OnClicked_Lambda([]() -> FReply
		{			
			LOG("Button clicked!");
			return FReply::Handled();
		});	
	}
};

FTestButton::FTestButton()
{
	Impl = MakeShared<FTestButtonImpl>();
}

FTestButton::~FTestButton()
{
}

FName FTestButton::GetName() const
{
	return Impl->GetName();	
}

TSharedRef<SWidget> FTestButton::CreateWidget() const
{
	return Impl->CreateWidget();
}

#undef LOCTEXT_NAMESPACE
