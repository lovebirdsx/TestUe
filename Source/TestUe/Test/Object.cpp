#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_StaticClass, "TestUe.Object.StaticClass", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObject_StaticClass::RunTest(const FString& Parameters)
{
	UClass* ObjectClass = UObject::StaticClass();
	TestNotNull(TEXT("UObject::StaticClass should not be null"), ObjectClass);
	TestEqual(TEXT("UObject::StaticClass should be UObject"), ObjectClass, UObject::StaticClass());
	TestTrue(TEXT("ObjectClass is not a child of UObject"), ObjectClass->IsChildOf(UObject::StaticClass()));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_PropIt, "TestUe.Object.PropIt", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObject_PropIt::RunTest(const FString& Parameters)
{
	const int PropCount = UObject::StaticClass()->GetPropertiesSize();
	TestGreaterThan(TEXT("GetPropertiesSize should greater than 0"), PropCount, 0);

	TFieldIterator<FProperty> PropIt(UObject::StaticClass());
	int PropItCount = 0;
	for (; PropIt; ++PropIt)
	{
		++PropItCount;
	}
	TestEqual(TEXT("UObject::StaticClass() PropItCount should be equal to 0"), PropItCount, 0);
	
	return true;
}
