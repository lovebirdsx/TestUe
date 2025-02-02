#include "DeclarativeSyntaxSupport.h"
#include "TestCustomWidget.h"
#include "Log.h"
#include "SButton.h"
#include "Widgets/SPanel.h"
#include "Widgets/SWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Layout/ArrangedChildren.h"

#define LOCTEXT_NAMESPACE "MySlateApp"

/**
 * 自定义控件 SMyCustomPanel 继承自 SPanel，用于演示自定义布局与绘制。
 */
class SMyCustomPanel : public SPanel
{
public:
	class FMyCustomPanelSlot : public TSlotBase<FMyCustomPanelSlot>
	{
	public:
		FMyCustomPanelSlot() {}

		SLATE_SLOT_BEGIN_ARGS(FMyCustomPanelSlot, TSlotBase<FMyCustomPanelSlot>)
		SLATE_SLOT_END_ARGS()
	};

	SLATE_BEGIN_ARGS(SMyCustomPanel) {}
		SLATE_ARGUMENT(FText, MyTitle)
		SLATE_SLOT_ARGUMENT(SMyCustomPanel::FMyCustomPanelSlot, Slots)
	SLATE_END_ARGS()

	// 关键：这里把 "this" 作为父面板传入，否则编译报错
	SMyCustomPanel() : ChildrenWidgets(this) 
	{
	}
	
	void Construct(const FArguments& InArgs)
	{
		MyTitle = InArgs._MyTitle;
		TArray<FMyCustomPanelSlot::FSlotArguments>& SlotArguments = const_cast<TArray<FMyCustomPanelSlot::FSlotArguments>&>(InArgs._Slots);
		ChildrenWidgets.AddSlots(MoveTemp(SlotArguments));
	}

	// 注意要封装以下，方便链式调用
	static FMyCustomPanelSlot::FSlotArguments Slot()
	{
		return FMyCustomPanelSlot::FSlotArguments(MakeUnique<FMyCustomPanelSlot>());
	}

	/** SWidget 接口：计算期望尺寸 */
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override
	{
		// 简单的示例：假设想要 300x200 的最小期望尺寸
		// 你也可以先遍历子控件，计算所有子控件期望的宽高，然后再决定自己的期望尺寸
		return FVector2D(300.0f, 200.0f);
	}

	/** SPanel 接口：为子控件安排布局 */
	virtual void OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const override
	{
		// 示例：我们将子控件垂直排列，每个控件高度相同，等分父空间
		// 获取总大小
		const FVector2D PanelSize = AllottedGeometry.GetLocalSize();
		const int32 NumChildren = ChildrenWidgets.Num();

		// 如果没有子控件，直接返回
		if (NumChildren == 0)
		{
			return;
		}

		// 每个子控件的高度
		const float ChildHeight = PanelSize.Y / NumChildren;

		for (int32 ChildIndex = 0; ChildIndex < NumChildren; ++ChildIndex)
		{
			const TSharedRef<SWidget>& ChildWidget = ChildrenWidgets[ChildIndex].GetWidget();

			// 子控件自身的可见性判断(如果是Collapsed就不安排)
			const EVisibility ChildVisibility = ChildWidget->GetVisibility();
			if (ArrangedChildren.Accepts(ChildVisibility))
			{
				const FVector2D ChildPosition(0.0f, ChildHeight * ChildIndex);
				const FVector2D ChildSize(PanelSize.X, ChildHeight);

				// 安排子控件在父几何体内的位置和大小
				ArrangedChildren.AddWidget(
					AllottedGeometry.MakeChild(
						ChildWidget,
						ChildPosition,
						ChildSize
					)
				);
			}
		}
	}

	/** 获取子控件数量 */
	virtual FChildren* GetChildren() override
	{
		return &ChildrenWidgets;
	}

protected:
	/** SWidget 接口：自定义绘制逻辑 */
	virtual int32 OnPaint(const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override 
	{
		// 绘制一个背景矩形
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId, // Layer 层级，如果我们想绘制在子控件后面，可以用更小的LayerId
			AllottedGeometry.ToPaintGeometry(),
			FCoreStyle::Get().GetBrush("WhiteBrush"),
			ESlateDrawEffect::None,
			FLinearColor(0.0f, 0.3f, 0.6f, 1.0f) // 颜色，比如蓝色
		);

		// 绘制线段
		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			TArray<FVector2D>{ FVector2D(0.0f, 0.0f), FVector2D(AllottedGeometry.Size.X, AllottedGeometry.Size.Y) },
			ESlateDrawEffect::None,
			FLinearColor::White,
			false
		);
		

		// 如果我们想让子控件在此背景之上，再增加一个LayerId
		int32 CurrentLayer = LayerId + 1;

		// 绘制子控件
		// 注意: 默认情况下, 子控件的绘制是由父类的 SPanel::OnPaintChildren 调用的
		// 你可以选择自己遍历子控件并调用 OnPaint, 也可以使用自带的 PaintArrangedChildren

		// 获取布局后的子控件信息，调用ArrangeChildren会触发OnArrangeChildren
		FArrangedChildren ArrangedChildren(EVisibility::Visible);
		this->ArrangeChildren(AllottedGeometry, ArrangedChildren);

		// 调用默认的绘制子控件流程
		// 注意: PaintArrangedChildren 返回最后使用的LayerId
		CurrentLayer = PaintArrangedChildren(Args, ArrangedChildren, AllottedGeometry, MyCullingRect, OutDrawElements, CurrentLayer, InWidgetStyle, bParentEnabled);

		// 也可以在子控件之上绘制一些额外的信息，比如调试文字
		{
			const FString DebugString = FString::Printf(TEXT("Title = %s\nCustom Panel Debug Text"), *MyTitle.ToString());
			FSlateDrawElement::MakeText(
				OutDrawElements,
				CurrentLayer,
				AllottedGeometry.ToPaintGeometry(FVector2D(10.0f, 10.0f), AllottedGeometry.GetAccumulatedLayoutTransform()),
				DebugString,
				FCoreStyle::GetDefaultFontStyle("Regular", 16),
				ESlateDrawEffect::None,
				FLinearColor::Yellow
			);
		}

		// 返回最终的 LayerId
		return CurrentLayer;
	}

private:
	TPanelChildren<FMyCustomPanelSlot> ChildrenWidgets;
	FText MyTitle;
};

class FTestCustomWidgetImpl : public FUiTestBase, public TSharedFromThis<FTestCustomWidgetImpl>
{
public:
	virtual FName GetName() const override
	{
		return FName(TEXT("Test Custom Widget"));
	}

	virtual TSharedRef<SWidget> CreateWidget() const override
	{
		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SMyCustomPanel)
				.MyTitle(LOCTEXT("MyCustomPanelTitle", "My Custom Panel"))
				+SMyCustomPanel::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("MyCustomText", "This is a custom panel with custom layout and custom paint."))
				]
				+SMyCustomPanel::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("MyCustomText", "This is a custom panel with custom layout and custom paint."))
				]
				+SMyCustomPanel::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("MyCustomText", "This is a custom panel with custom layout and custom paint."))
				]
				+SMyCustomPanel::Slot()
				[
					SNew(SButton)
					.Text(LOCTEXT("MyCustomButton", "Click Me"))
					.OnClicked_Lambda([]()->FReply
						{
							LOG("Button clicked!");
							return FReply::Handled();
						})
				]
			];
	}
};

FTestCustomWidget::FTestCustomWidget()
{
	Impl = MakeShared<FTestCustomWidgetImpl>();
}

FTestCustomWidget::~FTestCustomWidget()
{
}

FName FTestCustomWidget::GetName() const
{
	return Impl->GetName();
}

TSharedRef<SWidget> FTestCustomWidget::CreateWidget() const
{
	return Impl->CreateWidget();
}

#undef LOCTEXT_NAMESPACE
