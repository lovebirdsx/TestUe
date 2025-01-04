#include "MyTest.h"
#include "MyObject.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_StaticClass, "MyTest.Object.StaticClass", TEST_FILTER)

bool TestObject_StaticClass::RunTest(const FString &Parameters)
{
    UClass *ObjectClass = UObject::StaticClass();
    TestNotNull(TEXT("UObject::StaticClass should not be null"), ObjectClass);
    TestEqual(TEXT("UObject::StaticClass should be UObject"), ObjectClass, UObject::StaticClass());
    TestTrue(TEXT("ObjectClass is not a child of UObject"), ObjectClass->IsChildOf(UObject::StaticClass()));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_PropIt, "MyTest.Object.PropIt", TEST_FILTER)

bool TestObject_PropIt::RunTest(const FString &Parameters)
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_New, "MyTest.Object.New", TEST_FILTER)

bool TestObject_New::RunTest(const FString &Parameters)
{
    // NewObject不会自动释放，需要调用垃圾回收
    {
        UMyObject::NewCount = 0;
        UMyObject::FreeCount = 0;
        {
            const UMyObject *MyObject = NewObject<UMyObject>();
            TestEqual(TEXT("UMyObject::NewCount should be 1"), UMyObject::NewCount, 1);
            TestEqual(TEXT("UMyObject::FreeCount should be 0"), UMyObject::FreeCount, 0);

            TestNotNull(TEXT("MyObject should not be null"), MyObject);
            TestTrue(TEXT("MyObject is valid"), MyObject->IsValidLowLevel());
        }

        TestEqual(TEXT("UMyObject::FreeCount should be 1"), UMyObject::FreeCount, 0);
        CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);

        TestEqual(TEXT("UMyObject::FreeCount should be 1"), UMyObject::FreeCount, 1);
    }

    return true;
}
