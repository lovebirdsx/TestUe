#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_StaticClass, "Object.TestObject_StaticClass", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObject_StaticClass::RunTest(const FString& Parameters)
{
	UClass* ObjectClass = UObject::StaticClass();
	TestNotNull("UObject::StaticClass should not be null", ObjectClass);
	TestEqual("UObject::StaticClass should be UObject", ObjectClass, UObject::StaticClass());
	TestTrue("ObjectClass is not a child of UObject", ObjectClass->IsChildOf(UObject::StaticClass()));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_PropIt, "Object.TestObject_PropIt", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObject_PropIt::RunTest(const FString& Parameters)
{
	const int PropCount = UObject::StaticClass()->GetPropertiesSize();
	TestGreaterThan("GetPropertiesSize should greater than 0", PropCount, 0);

	TFieldIterator<FProperty> PropIt(UObject::StaticClass());
	int PropItCount = 0;
	for (; PropIt; ++PropIt)
	{
		++PropItCount;
	}
	TestEqual("PropItCount should be equal to PropCount", PropItCount, PropCount);
	
	return true;
}

