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

int GFTestFreeCount = 0;

bool TestPtr_SharedPtr::RunTest(const FString& Parameters)
{
	
	struct FTest
    {
        int32 Value = 123;

		~FTest() { GFTestFreeCount++; }
    };

    // 访问
	{
	    const TSharedPtr<FTest> Test1 = MakeShared<FTest>();
	    TestEqual(TEXT("Test Value must be 123"), Test1->Value, 123);
		Test1->Value = 456;
	    TestEqual(TEXT("Test Value must be 456"), Test1->Value, 456);
	}

    // 引用计数
	{
		const TSharedPtr<FTest> Test1 = MakeShared<FTest>();
		TestTrue(TEXT("Test1 is valid"), Test1.IsValid());
		TestTrue(TEXT("Test1 is unique"), Test1.IsUnique());
		TestEqual(TEXT("GetSharedReferenceCount should be 1"), Test1.GetSharedReferenceCount(), 1);
		
	    {
	        const TSharedPtr<FTest> Test2 = Test1;
	        TestEqual(TEXT("Test2 Value must be 456"), Test2->Value, 123);
	        TestTrue(TEXT("Test1 is valid"), Test1.IsValid());
			TestFalse(TEXT("Test1 is not unique"), Test1.IsUnique());		
	        TestEqual(TEXT("GetSharedReferenceCount should be 2"), Test1.GetSharedReferenceCount(), 2);
	    }

	    TestTrue(TEXT("Test1 is valid"), Test1.IsValid());
		TestTrue(TEXT("Test1 is unique"), Test1.IsUnique());
	}

	// Reset
	{
		TSharedPtr<FTest> Test1 = MakeShared<FTest>();
		Test1.Reset();
		TestFalse(TEXT("Test1 is not valid"), Test1.IsValid());    
	}

	// 从原生指针创建
	{
		{
			GFTestFreeCount = 0;
			FTest* Test = new FTest();
			Test->Value = 456;
			const TSharedPtr<FTest> Test1(Test);
			TestEqual(TEXT("Test1 Value must be 456"), Test1->Value, 456);
		}
		TestEqual(TEXT("GFTestFreeCount should be 1"), GFTestFreeCount, 1);
	}	
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_WeakPtr, "TestUe.Ptr.WeakPtr", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_WeakPtr::RunTest(const FString& Parameters)
{
	struct FTest
	{
		int32 Value = 123;
	};

	// 创建 - 释放
	{		
		TSharedPtr<FTest> SharedPtr = MakeShared<FTest>();
		const TWeakPtr<FTest> WeakPtr = SharedPtr;
		TestTrue(TEXT("WeakPtr is valid"), WeakPtr.IsValid());
		SharedPtr.Reset();
		TestFalse(TEXT("SharedPtr is not valid"), SharedPtr.IsValid());
		TestFalse(TEXT("WeakPtr is not valid"), WeakPtr.IsValid());
	}
	

	// 创建 - 锁定 - 释放
	{
		TSharedPtr<FTest> SharedPtr = MakeShared<FTest>();
		const TWeakPtr<FTest> WeakPtr = SharedPtr;

		const TSharedPtr<FTest> SharedPtr2 = WeakPtr.Pin();
		SharedPtr.Reset();

		TestTrue(TEXT("SharedPtr2 is valid"), SharedPtr2.IsValid());
		TestEqual(TEXT("SharedPtr2->Value should be 123"), SharedPtr2->Value, 123);
	}	
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_UniquePtr, "TestUe.Ptr.UniquePtr", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_UniquePtr::RunTest(const FString& Parameters)
{
	struct FTest
	{
		int Value = 123;
	};

	// 创建
	{
		const TUniquePtr<FTest> UniquePtr = MakeUnique<FTest>();
		TestEqual(TEXT("UniquePtr->Value should be 123"), UniquePtr->Value, 123);
		UniquePtr->Value = 456;
		TestEqual(TEXT("UniquePtr->Value should be 456"), UniquePtr->Value, 456);
	}

	// 移动
	{
		TUniquePtr<FTest> UniquePtr = MakeUnique<FTest>();
		const TUniquePtr<FTest> UniquePtr2 = MoveTemp(UniquePtr);
		TestFalse(TEXT("UniquePtr is not valid"), UniquePtr.IsValid());
		TestTrue(TEXT("UniquePtr2 is valid"), UniquePtr2.IsValid());
	}
	
	// 释放
	{
		TUniquePtr<FTest> UniquePtr = MakeUnique<FTest>();
		UniquePtr.Reset();
		TestFalse(TEXT("UniquePtr is not valid"), UniquePtr.IsValid());
	}
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPtr_RefCountPtr, "TestUe.Ptr.RefCountPtr", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPtr_RefCountPtr::RunTest(const FString& Parameters)
{
	struct FTest : FRefCountBase
	{
		int Value = 123;
	};

	// 创建
	{
		const TRefCountPtr<FTest> RefCountPtr = MakeRefCount<FTest>();
		TestEqual(TEXT("RefCountPtr->Value should be 123"), RefCountPtr->Value, 123);
		RefCountPtr->Value = 456;
		TestEqual(TEXT("RefCountPtr->Value should be 456"), RefCountPtr->Value, 456);
	}

	// 引用计数
	{
		const TRefCountPtr<FTest> RefCountPtr = MakeRefCount<FTest>();
		TestEqual(TEXT("RefCountPtr->GetRefCount() should be 1"), RefCountPtr->GetRefCount(), 1);
		{
			TRefCountPtr<FTest> RefCountPtr2 = RefCountPtr;
			TestEqual(TEXT("RefCountPtr->GetRefCount() should be 2"), RefCountPtr->GetRefCount(), 2);
		}
		TestEqual(TEXT("RefCountPtr->GetRefCount() should be 1"), RefCountPtr->GetRefCount(), 1);
	}	

	// AddRef - Release
	{
		const TRefCountPtr<FTest> RefCountPtr = MakeRefCount<FTest>();
		const int Count1 = RefCountPtr->AddRef();
		TestEqual(TEXT("Count1 should be 2"), Count1, 2);
		TestEqual(TEXT("RefCountPtr->GetRefCount() should be 2"), RefCountPtr->GetRefCount(), 2);
		
		const int Count2 = RefCountPtr->Release();
		TestEqual(TEXT("Count2 should be 1"), Count2, 1);
		TestEqual(TEXT("RefCountPtr->GetRefCount() should be 1"), RefCountPtr->GetRefCount(), 1);

		const int Count3 = RefCountPtr->Release();
		TestEqual(TEXT("Count3 should be 0"), Count3, 0);		
	}

	// SafeRelease
	{
		TRefCountPtr<FTest> RefCountPtr = MakeRefCount<FTest>();
		RefCountPtr.SafeRelease();
		TestFalse(TEXT("RefCountPtr is not valid"), IsValidRef(RefCountPtr));
		TestTrue(TEXT("RefCountPtr is nullptr"), RefCountPtr == nullptr);
	}
	
	return true;
}
