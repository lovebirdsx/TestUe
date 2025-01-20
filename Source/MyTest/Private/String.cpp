#include "MyTest.h"

#include "Misc/AutomationTest.h"

#define LOCTEXT_NAMESPACE "MyTest"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestString_FName, "MyTest.String.FName", TEST_FILTER)

bool TestString_FName::RunTest(const FString& Parameters)
{
	const FName Name1 = "Tom";
	const FName Name2 = "Tom";

	TestTrue("Name1 == Name2", Name1 == Name2);
	TestEqual("Name1.GetComparisonIndex() == Name2.GetComparisonIndex()", Name1.GetComparisonIndex(), Name2.GetComparisonIndex());

	// 作为查找键
	TMap<FName, int32> NameToAge;
	NameToAge.Add(Name1, 20);
	TestTrue("NameToAge.Contains(Name1)", NameToAge.Contains(Name1));	 
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestString_FString, "MyTest.String.FString", TEST_FILTER)

bool TestString_FString::RunTest(const FString& Parameters)
{
	// + 运算符
	{
		FString Name = TEXT("Tom");
		Name += TEXT("Jerry");
		TestEqual("Name must be TomJerry", Name, TEXT("TomJerry"));		
	}

	// Append
	{
		FString Name = TEXT("Tom");
		Name.Append(TEXT("Jerry"));
		TestEqual("Name must be TomJerry", Name, TEXT("TomJerry"));
	}

	// FindChar
	{
		const FString Name = TEXT("TomJerry");
		int32 Index = 0;
		const bool bFind = Name.FindChar('J', Index);
		TestTrue("FindChar must be true", bFind);
		TestEqual("Index must be 3", Index, 3);
	}

	// FindString
	{
		const FString Name = TEXT("TomJerry");
		const int32 Index = Name.Find(TEXT("Jerry"));
		TestEqual("Index must be 3", Index, 3);
	}

	// Replace
	{
		FString Name = TEXT("TomJerry");
		Name.ReplaceInline(TEXT("Jerry"), TEXT("Jack"));
		TestEqual("Name must be TomJack", Name, TEXT("TomJack"));
	}

	// Split
	{
		const FString Name = TEXT("Tom.Jerry");
		FString Left;
		FString Right;
		Name.Split(TEXT("."), &Left, &Right);
		TestEqual("Left must be Tom", Left, TEXT("Tom"));
		TestEqual("Right must be Jerry", Right, TEXT("Jerry"));
	}

	// ParseIntoArray
	{
		const FString Name = TEXT("Apple, Banana, Orange");
		TArray<FString> Array;
		Name.ParseIntoArray(Array, TEXT(","), true);
		
		TestEqual("Array.Num() must be 3", Array.Num(), 3);
		TestEqual("Array[0] must be Apple", Array[0].TrimStart(), TEXT("Apple"));
		TestEqual("Array[1] must be Banana", Array[1].TrimStart(), TEXT("Banana"));
		TestEqual("Array[2] must be Orange", Array[2].TrimStart(), TEXT("Orange"));
	}

	// Printf
	{
		const FString Name = FString::Printf(TEXT("Tom %d"), 20);
		TestEqual("Name must be Tom 20", Name, TEXT("Tom 20"));
	}
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestString_FText, "MyTest.String.FText", TEST_FILTER)

bool TestString_FText::RunTest(const FString& Parameters)
{
	// Localized
	{
		const FText Text = LOCTEXT("MyKey", "Tom");
		TestEqual("Text must be Tom", Text.ToString(), TEXT("Tom"));
	}

	// Namespace Localized
	{
		const FText Text = NSLOCTEXT("MyNamespace", "MyKey", "Tom");
		TestEqual("Text must be Tom", Text.ToString(), TEXT("Tom"));
	}

	// Contains Var
	{
		const FText Text = FText::Format(NSLOCTEXT("MyNamespace", "MyKey", "Tom {0}"), FText::AsNumber(20));
		TestEqual("Text must be Tom 20", Text.ToString(), TEXT("Tom 20"));
	}

	return true;
}

#undef LOCTEXT_NAMESPACE
