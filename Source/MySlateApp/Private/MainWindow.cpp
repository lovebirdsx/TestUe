#include "SWindow.h"
#include "SComboBox.h"
#include "STextBlock.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"

#include "MainWindow.h"

#include "MyConfig.h"
#include "TestManager.h"
#include "Tests/TestButton.h"
#include "Tests/TestSlider.h"

#define LOCTEXT_NAMESPACE "MySlateApp"

class SMyAppWindow : public SWindow
{
public:
	SLATE_BEGIN_ARGS(SWindow)
	{}

	SLATE_END_ARGS()

	virtual ~SMyAppWindow() override = default;

	virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override
	{		
		if (InKeyEvent.GetKey() == EKeys::Escape)
		{
			FSlateApplication::Get().RequestDestroyWindow(SharedThis(this));
			return FReply::Handled();
		}
		
		return FReply::Unhandled();
	}

	void Construct(const FArguments& InArgs)
	{
		SWindow::Construct(
			SWindow::FArguments()
			.Title(LOCTEXT("MyWindowTitle", "My Slate App"))
			.ClientSize(FVector2D(800, 600))
			.SupportsMaximize(true)
			.SupportsMinimize(true)
		);
	}
};

class FMainWindow : public IMainWindow, public TSharedFromThis<FMainWindow>
{
public:
	FMainWindow()
	{
		RegisterAllTests();	
		PopulateTestNameList();
	}

	virtual ~FMainWindow() override = default;
	
	virtual TSharedRef<SWindow> CreateMainWindow() override
	{
		TSharedRef<SMyAppWindow> MyMainWindow = SNew(SMyAppWindow);

		MyMainWindow->SetContent(			
			SNew(SVerticalBox)			
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(5.f)
			[				
				SAssignNew(TestComboBox, SComboBox<TSharedPtr<FName>>)
				.OptionsSource(&AllTestNames)
				.OnGenerateWidget(this, &FMainWindow::HandleGenerateComboItem)
				.OnSelectionChanged(this, &FMainWindow::HandleSelectionChanged)
				[
					// 下拉列表默认显示的内容（未展开时）
					SNew(STextBlock)
					.Text(this, &FMainWindow::GetSelectedTestText)
				]
			]
			
			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			.Padding(5.f)
			[
				SAssignNew(TestContentContainer, SBorder)
				.Padding(10.f)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("NoTestSelected", "尚未选择任何测试"))
				]
			]
		);

		if (SelectedTest.IsValid())
		{
			HandleSelectionChanged(SelectedTest, ESelectInfo::Direct);
		}

		return MyMainWindow;
	}

private:	
	void PopulateTestNameList()
	{
		TArray<FName> Names;
		TestManager.GetAllNames(Names);

		for (const FName& TestName : Names)
		{
			AllTestNames.Add(MakeShared<FName>(TestName));
		}

		if (AllTestNames.Num() > 0)
		{
			if (const FString SelectedTestName = FMyConfigGetter::Get().GetConfig()->SelectedTest; SelectedTestName.Len() > 0)
			{
				SelectedTest = MakeShared<FName>(*SelectedTestName);
			}
			else
			{
				SelectedTest = AllTestNames[0];
			}			
		}
	}
	
	TSharedRef<SWidget> HandleGenerateComboItem(TSharedPtr<FName> InItem) const
	{
		return SNew(STextBlock)
			.Text(FText::FromName(*InItem));
	}
	
	void HandleSelectionChanged(TSharedPtr<FName> NewValue, ESelectInfo::Type SelectInfo)
	{
		SelectedTest = NewValue;

		if (SelectedTest.IsValid())
		{
			if (const TSharedPtr<FUiTestBase> TestObj = TestManager.GetTest(*SelectedTest); TestObj.IsValid())
			{
				FMyConfigGetter::Get().GetConfig()->SelectedTest = SelectedTest->ToString();
				const TSharedRef<SWidget> TestWidget = TestObj->CreateWidget();				
				TestContentContainer->SetContent(TestWidget);
				return;
			}
		}
		
		TestContentContainer->SetContent(
			SNew(STextBlock)
			.Text(LOCTEXT("NoTestSelected", "尚未选择任何测试"))
		);
	}
	
	FText GetSelectedTestText() const
	{
		if (SelectedTest.IsValid())
		{
			return FText::FromName(*SelectedTest);
		}
		return LOCTEXT("SelectTestPrompt", "请选择测试...");
	}

	void RegisterAllTests()
	{
		TestManager.RegisterTest(MakeShared<FTestButton>());
		TestManager.RegisterTest(MakeShared<FTestSlider>());
	}
	
	FTestManager TestManager;
	TArray<TSharedPtr<FName>> AllTestNames;
	TSharedPtr<FName> SelectedTest;
	TSharedPtr<SComboBox<TSharedPtr<FName>>> TestComboBox;	
	TSharedPtr<SBorder> TestContentContainer;
};

TSharedPtr<IMainWindow> IMainWindow::Create()
{
	return MakeShared<FMainWindow>();
}

#undef LOCTEXT_NAMESPACE
