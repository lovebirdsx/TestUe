#include "MyObject.h"
#include "MyTest.h"
#include "UObject/Package.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObjectInitializer_Basic, "MyTest.ObjectInitializer.Basic", TEST_FILTER)

bool TestObjectInitializer_Basic::RunTest(const FString& Parameters)
{
	const UOiObject2* Object2 = NewObject<UOiObject2>();
	TestNotNull("Object2 should not be null", Object2);

	TestNotNull("Null", Object2->Object1);
	const UObject* Outer = Object2->Object1->GetOuter();
	TestTrue("Outer is a UOiObject2", Outer->IsA(UOiObject2::StaticClass()));
	TestTrue("Outer should be Object2", Outer == Object2);

	const UPackage* Package = Object2->GetPackage();
	TestNotNull("Package should not be null", Package);
	TestEqual("Package name", Package->GetName(), TEXT("/Engine/Transient"));

	return true;
}

