#include "MyTest.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestContainer_Array, "MyTest.Container.Array", TEST_FILTER)

bool TestContainer_Array::RunTest(const FString &Parameters)
{
    TArray<int32> Numbers;
    TestTrue("Numbers.Num() must be 0", Numbers.Num() == 0);

    Numbers.Add(1);
    TestTrue("Numbers.Num() must be 1", Numbers.Num() == 1);
    TestTrue("Numbers.Contains(1) must be true", Numbers.Contains(1));

    Numbers.Empty();
    TestTrue("Numbers.Num() must be 0", Numbers.Num() == 0);
    
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestContainer_Map, "MyTest.Container.Map", TEST_FILTER)

bool TestContainer_Map::RunTest(const FString &Parameters)
{
    TMap<FString, int32> NameToAge;
    TestTrue("NameToAge.Num() must be 0", NameToAge.Num() == 0);

    NameToAge.Add("Tom", 20);
    TestTrue("NameToAge.Num() must be 1", NameToAge.Num() == 1);
    TestTrue("NameToAge.Contains(\"Tom\") must be true", NameToAge.Contains("Tom"));
    TestTrue("NameToAge[\"Tom\"] must be 20", NameToAge["Tom"] == 20);

    NameToAge.Empty();
    TestTrue("NameToAge.Num() must be 0", NameToAge.Num() == 0);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestContainer_Set, "MyTest.Container.Set", TEST_FILTER)

bool TestContainer_Set::RunTest(const FString &Parameters)
{
    TSet<int32> Numbers;
    TestTrue("Numbers.Num() must be 0", Numbers.Num() == 0);

    Numbers.Add(1);
    TestTrue("Numbers.Num() must be 1", Numbers.Num() == 1);
    TestTrue("Numbers.Contains(1) must be true", Numbers.Contains(1));

    Numbers.Empty();
    TestTrue("Numbers.Num() must be 0", Numbers.Num() == 0);

    return true;
}
