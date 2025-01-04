#include "MyTest.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(Cpp_Constructor, "MyTest.Cpp.Constructor", TEST_FILTER)

int32 G_BaseConstructCallCount = 0;
int32 G_BaseDestructCallCount = 0;
int G_DerivedConstructCallCount = 0;
int G_DerivedDestructCallCount = 0;

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

bool Cpp_Constructor::RunTest(const FString& Parameters)
{
	G_BaseConstructCallCount = 0;
	G_BaseDestructCallCount = 0;
	G_DerivedConstructCallCount = 0;
	G_DerivedDestructCallCount = 0;
	
	const FBase *Base = new FDerived();
	delete Base;

	TestEqual("G_BaseConstructCallCount must be 1", G_BaseConstructCallCount, 1);
	TestEqual("G_BaseDestructCallCount must be 1", G_BaseDestructCallCount, 1);
	TestEqual("G_DerivedConstructCallCount must be 1", G_DerivedConstructCallCount, 1);
	TestEqual("G_DerivedDestructCallCount must be 1", G_DerivedDestructCallCount, 1);
	
	return true;
}
