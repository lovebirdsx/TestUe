#include "Misc/AutomationTest.h"
#include "TestUe/Test/MyObject.h"
#include "DataRegistryId.h"
#include "DataRegistry.h"
#include "DataRegistrySubsystem.h"
#include "DataRegistrySource_DataTable.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestDataRegistry_FDataRegistryId, "TestUe.DataRegistry.FDataRegistryId", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestDataRegistry_FDataRegistryId::RunTest(const FString &Parameters)
{
    // 测试构造函数
    FDataRegistryId DefaultId;
    TestFalse("DefaultId.IsValid()", DefaultId.IsValid());

    // Type:Name格式
    FDataRegistryId ConstructId(FName("MyRegistryType"), FName("MyItemName"));
    TestTrue("ConstructId.IsValid()", ConstructId.IsValid());
    TestEqual("ConstructId.RegistryType", ConstructId.RegistryType.GetName(), FName("MyRegistryType"));
    TestEqual("ConstructId.ItemName", ConstructId.ItemName, FName("MyItemName"));

    // ==操作符
    FDataRegistryId EqualId(FName("MyRegistryType"), FName("MyItemName"));
    TestTrue("ConstructId == EqualId", ConstructId == EqualId);

    FDataRegistryId NotEqualId(FName("MyRegistryType"), FName("MyItemName2"));
    TestFalse("ConstructId == NotEqualId", ConstructId == NotEqualId);

    // Type:Name字符串
    FDataRegistryId ParseId(FString(TEXT("MyRegistryType:MyItemName")));
    TestTrue("ParseId.IsValid()", ParseId.IsValid());
    TestEqual("ParseId.RegistryType", ParseId.RegistryType.GetName(), FName("MyRegistryType"));
    TestEqual("ParseId.ItemName", ParseId.ItemName, FName("MyItemName"));

    // ToString
    TestEqual("ConstructId.ToString()", ConstructId.ToString(), FString(TEXT("MyRegistryType:MyItemName")));

    return true;
}
