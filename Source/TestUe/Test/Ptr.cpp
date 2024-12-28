#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_SharedRef, "TestUe.Ptr.SharedRef", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_SharedRef::RunTest(const FString& Parameters)
{
	struct FTest
    {
        int32 Value = 123;
    };

    // 访问 SharedRef 的对象
    const TSharedRef<FTest> Test1 = MakeShared<FTest>();
    TestEqual(TEXT("Test Value must be 123"), Test1->Value, 123);
	Test1->Value = 456;
    TestEqual(TEXT("Test Value must be 456"), Test1->Value, 456);

    // 测试 SharedRef 的引用计数
	TestTrue(TEXT("Test1 is unique"), Test1.IsUnique());
	TestEqual(TEXT("GetSharedReferenceCount should be 1"), Test1.GetSharedReferenceCount(), 1);
    {
        const TSharedRef<FTest> Test2 = Test1;
        TestEqual(TEXT("Test2 Value must be 456"), Test2->Value, 456);
        TestFalse(TEXT("Test2 is unique"), Test1.IsUnique());
		TestEqual(TEXT("GetSharedReferenceCount should be 2"), Test1.GetSharedReferenceCount(), 2);
    }

    TestTrue(TEXT("Test1 is unique"), Test1.IsUnique());

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_SharedPtr, "TestUe.Ptr.SharedPtr", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_SharedPtr::RunTest(const FString& Parameters)
{
	// TSharedPtr
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_WeakPtr, "TestUe.Ptr.WeakPtr", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_WeakPtr::RunTest(const FString& Parameters)
{
	// TWeakPtr
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_UniquePtr, "TestUe.Ptr.UniquePtr", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_UniquePtr::RunTest(const FString& Parameters)
{
	// TUniquePtr
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_RefCountPtr, "TestUe.Ptr.RefCountPtr", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_RefCountPtr::RunTest(const FString& Parameters)
{
	// TRefCountPtr
	return true;
}
