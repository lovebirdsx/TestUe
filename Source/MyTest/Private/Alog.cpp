#include "MyTest.h"
#include "Misc/AutomationTest.h"
#include "Algo/TopologicalSort.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAlog_Sort, "MyTest.Alog.Sort", TEST_FILTER)

bool TestAlog_Sort::RunTest(const FString &Parameters)
{
    // 根据依赖关系来排序
    TArray<int32> Array = {1, 2, 3, 4, 5};
    TMap<int32, TArray<int32>> Dependencies;
    Dependencies.Add(1, {2, 3});
    Dependencies.Add(2, {4});
    Dependencies.Add(3, {4, 5});

    Algo::TopologicalSort(
        Array,
        [&Dependencies](const int32 &Element) -> TArray<int32>
        {
            const TArray<int32> *Deps = Dependencies.Find(Element);
            return Deps ? *Deps : TArray<int32>{};
        });

    TestEqual("Array[0] should be 1", Array[0], 4);
    TestEqual("Array[1] should be 2", Array[1], 5);
    TestEqual("Array[2] should be 3", Array[2], 2);
    TestEqual("Array[3] should be 4", Array[3], 3);
    TestEqual("Array[4] should be 5", Array[4], 1);

    return true;
}