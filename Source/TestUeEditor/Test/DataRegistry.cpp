#include "CQTest.h"
#include "DataRegistryId.h"
#include "DataRegistry.h"

TEST_CLASS(DataRegistryIdTest, "TestUe.DataRegistry")
{
    TEST_METHOD(RunTest)
    {
        // 测试构造函数
        FDataRegistryId DefaultId;
        ASSERT_THAT(IsFalse(DefaultId.IsValid()));

        // Type:Name格式
        FDataRegistryId ConstructId(FName("MyRegistryType"), FName("MyItemName"));
        ASSERT_THAT(IsTrue(ConstructId.IsValid()));
        ASSERT_THAT(AreEqual(ConstructId.RegistryType.GetName(), FName("MyRegistryType")));
        ASSERT_THAT(AreEqual(ConstructId.ItemName, FName("MyItemName")));

        // ==操作符
        FDataRegistryId EqualId(FName("MyRegistryType"), FName("MyItemName"));
        ASSERT_THAT(IsTrue(ConstructId == EqualId));

        FDataRegistryId NotEqualId(FName("MyRegistryType"), FName("MyItemName2"));
        ASSERT_THAT(IsFalse(ConstructId == NotEqualId));

        // Type:Name字符串
        FDataRegistryId ParseId(FString(TEXT("MyRegistryType:MyItemName")));
        ASSERT_THAT(IsTrue(ParseId.IsValid()));
        ASSERT_THAT(AreEqual(ParseId.RegistryType.GetName(), FName("MyRegistryType")));
        ASSERT_THAT(AreEqual(ParseId.ItemName, FName("MyItemName")));

        // ToString
        ASSERT_THAT(AreEqual(ConstructId.ToString(), FString(TEXT("MyRegistryType:MyItemName"))));
    }
};