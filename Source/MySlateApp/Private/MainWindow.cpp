#include "SButton.h"

#include "MainWindow.h"
#include "Log.h"

#define LOCTEXT_NAMESPACE "MySlateApp"

TSharedRef<SWindow> CreateMainWindow()
{	
	TSharedRef<SWindow> MyMainWindow = SNew(SWindow)
		.Title(LOCTEXT("MyWindowTitle", "My Slate App"))
		.ClientSize(FVector2D(400, 300))
		.SupportsMaximize(false)
		.SupportsMinimize(false);
	
	MyMainWindow->SetContent(
		SNew(SButton)
		.Text(LOCTEXT("MyButtonText", "Click Me!!!"))
		.OnClicked_Lambda([]() -> FReply
		{			
			LOG("Button clicked!");
			return FReply::Handled();
		})
	);

	return MyMainWindow;
}

#undef LOCTEXT_NAMESPACE
