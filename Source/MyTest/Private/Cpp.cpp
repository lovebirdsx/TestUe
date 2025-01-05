#include "MyTest.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Cpp_Constructor, "MyTest.Cpp.Constructor", TEST_FILTER)

bool Cpp_Constructor::RunTest(const FString& Parameters)
{
	static int32 G_BaseConstructCallCount;
	static int32 G_BaseDestructCallCount;
	static int32 G_DerivedConstructCallCount;
	static int32 G_DerivedDestructCallCount;

	G_BaseConstructCallCount = 0;
	G_BaseDestructCallCount = 0;
	G_DerivedConstructCallCount = 0;
	G_DerivedDestructCallCount = 0;

	class FBase
	{
	public:		
		FBase()
		{
			G_BaseConstructCallCount++;			
		}

		virtual ~FBase()
		{
			G_BaseDestructCallCount++;			
		}
	};

	class FDerived : public FBase
	{
	public:
		FDerived()
		{
			G_DerivedConstructCallCount++;
		}

		virtual ~FDerived() override
		{
			G_DerivedDestructCallCount++;
		}
	};
	
	const FBase *Base = new FDerived();
	delete Base;

	TestEqual("G_BaseConstructCallCount must be 1", G_BaseConstructCallCount, 1);
	TestEqual("G_BaseDestructCallCount must be 1", G_BaseDestructCallCount, 1);
	TestEqual("G_DerivedConstructCallCount must be 1", G_DerivedConstructCallCount, 1);
	TestEqual("G_DerivedDestructCallCount must be 1", G_DerivedDestructCallCount, 1);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Cpp_RValueParameter, "MyTest.Cpp.RValueParameter", TEST_FILTER)

bool Cpp_RValueParameter::RunTest(const FString& Parameters)
{
    class FTest 
    {
    public:
        bool Print1Called = false;
        bool Print2Called = false;
        bool Print3Called = false;

        void Print(const FString& InString)
        {
            Print1Called = true;
        }

        void Print(FString&& InString)
        {
            Print2Called = true;
        }

        void Print(FString& InString)
        {
            Print3Called = true;
        }
    };

    FTest Test;

    FString TestString = TEXT("TestString");
    Test.Print(TestString);
    TestTrue("Print3Called must be true", Test.Print3Called);
    Test.Print3Called = false;

    const FString TestString2 = TEXT("TestString2");
    Test.Print(TestString2);
    TestTrue("Print1Called must be true", Test.Print1Called);
    Test.Print1Called = false;

    Test.Print(MoveTemp(TestString));
    TestTrue("Print2Called must be true", Test.Print2Called);
    Test.Print2Called = false;

    Test.Print(TEXT("TestString"));
    TestTrue("Print2Called must be true", Test.Print2Called);
    Test.Print2Called = false;

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Cpp_MoveConstructor, "MyTest.Cpp.MoveConstructor", TEST_FILTER)

bool Cpp_MoveConstructor::RunTest(const FString& Parameters)
{
	class FTest
	{
	public:
		FString String;

		explicit FTest(FString&& InString): String(MoveTemp(InString))
		{
		}
		
		explicit FTest(FTest&& InTest): String(MoveTemp(InTest.String))
		{
		}

		FTest& operator=(FTest&& InTest)
		{
			String = MoveTemp(InTest.String);
			return *this;
		}
	};

	{
		FString TestString = TEXT("TestString");
		FTest Test(MoveTemp(TestString));
		TestEqual("TestString.Len() must be 0", TestString.Len(), 0);
		TestGreaterThan("Test.String.Len() must > 0", Test.String.Len(), 0);

		FTest Test2(MoveTemp(Test));
		TestEqual("Test.String.Len() must be 0", Test.String.Len(), 0);
		TestGreaterThan("Test2.String.Len() must > 0", Test2.String.Len(), 0);

		FTest &&Test3 = FTest(MoveTemp(Test2));
		TestEqual("Test2.String.Len() must be 0", Test2.String.Len(), 0);
		TestGreaterThan("Test3.String.Len() must > 0", Test3.String.Len(), 0);		
	}

	static int32 DeConstructorCallCount;
	static int32 AllocCount;
	static int32 FreeCount;
	
	class FTest2
	{
	public:
		static void Reset()
		{
			DeConstructorCallCount = 0;
			AllocCount = 0;
			FreeCount = 0;
		}

		FTest2() : Length(0), Data(nullptr)
		{
		
		}
		
		explicit FTest2(const char *InString) : Length(strlen(InString)), Data(new char[Length + 1])
		{
			strcpy_s(Data, Length + 1, InString);
			++AllocCount;
		}

		FTest2(FTest2&& InTest) noexcept : Length(InTest.Length), Data(InTest.Data)
		{
			InTest.Data = nullptr;
			InTest.Length = 0;
		}		

		explicit FTest2(const FTest2& InTest) : Length(InTest.Length), Data(new char[Length + 1])
		{
			strcpy_s(Data, Length + 1, InTest.Data);
			++AllocCount;
		}

		virtual ~FTest2()
		{
			++DeConstructorCallCount;
			if (Data)
			{
				++FreeCount;

				delete[] Data;
				Data = nullptr;
				Length = 0;
			}
		}

		FTest2& operator=(const FTest2& InTest)
		{
			if (this != &InTest)
			{
				if (Data)
				{
					delete[] Data;					
					++FreeCount;					
				}

				Length = InTest.Length;
				Data = new char[Length + 1];
				strcpy_s(Data, Length + 1, InTest.Data);
				++AllocCount;
			}

			return *this;
		}

		FTest2& operator=(FTest2&& InTest)
		{
			if (this != &InTest)
			{
				if (Data)
				{
					delete[] Data;					
					++FreeCount;
				}

				Length = InTest.Length;
				Data = InTest.Data;
				InTest.Data = nullptr;
				InTest.Length = 0;
			}

			return *this;
		}

		const char* GetData() const
		{
			return Data;
		}

		size_t GetLength() const
		{
			return Length;
		}

	private:
		size_t Length;
		char *Data;
	};

	{
		FTest2::Reset();

		const FTest2 Test1;
		TestNull("Test1.Data must be null", Test1.GetData());
		TestEqual("Test1.Length must be 0", Test1.GetLength(), 0);
	}

	{
		FTest2::Reset();
		
		FTest2 Test1("TestString");
		FTest2 Test2(MoveTemp(Test1));
		TestNull("Test1.Data must be null", Test1.GetData());
		TestNotNull("Test2.Data must not be null", Test2.GetData());

		FTest2 Test3(MoveTemp(Test2));
		TestNull("Test2.Data must be null", Test2.GetData());
		TestNotNull("Test3.Data must not be null", Test3.GetData());
		
		FTest2 &&Test4 = FTest2(MoveTemp(Test3));
		TestNull("Test3.Data must be null", Test3.GetData());
		TestNotNull("Test4.Data must not be null", Test4.GetData());		
	}	

	TestEqual("DeConstructorCallCount must be 3", DeConstructorCallCount, 4);
	TestEqual("AllocCount must be 3", AllocCount, 1);
	TestEqual("FreeCount must be 3", FreeCount, 1);	
	
	return true;
}
