#include "Misc/AutomationTest.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestGameplayTag_Basic, "TestUe.GameplayTag.Basic", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestGameplayTag_Basic::RunTest(const FString &Parameters)
{
    // 两个Tag在DefaultGameplayTags.ini中定义
    FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
    FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));

    TestTrue("TagA.IsValid()", TagA.IsValid());
    TestTrue("TagB.IsValid()", TagB.IsValid());

    TestTrue("TagB.MatchesTag(TagA)", TagB.MatchesTag(TagA));
    TestFalse("TagA.MatchesTag(TagB)", TagA.MatchesTag(TagB));

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestGameplayTag_Match, "TestUe.GameplayTag.Match", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestGameplayTag_Match::RunTest(const FString &Parameters)
{
    FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
    FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));

    TestTrue("TagB.MatchesTag(TagA)", TagB.MatchesTag(TagA));
    TestTrue("TagB.MatchesTagExact(TagB)", TagB.MatchesTagExact(TagB));
    TestFalse("TagB.MatchesTagExact(TagA)", TagB.MatchesTagExact(TagA));

    FGameplayTagContainer TagContainer1;
    TagContainer1.AddTag(TagA);

    TestTrue("TagB.MatchesAny(TagContainer1)", TagB.MatchesAny(TagContainer1));

    FGameplayTagContainer TagContainer2;
    TagContainer2.AddTag(TagB);

    TestFalse("TagA.MatchesAny(TagContainer2)", TagA.MatchesAny(TagContainer2));

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestGameplayTag_Container, "TestUe.GameplayTag.Container", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestGameplayTag_Container::RunTest(const FString &Parameters)
{
    FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
    FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));
    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(TagB);

    // HasTag可以兼容继承关系
    TestTrue("TagContainer.HasTag(TagA)", TagContainer.HasTag(TagA));
    TestTrue("TagContainer.HasTag(TagB)", TagContainer.HasTag(TagB));

    // HasTagExact只能匹配完全相同的Tag
    TestFalse("TagContainer.HasTagExact(TagA)", TagContainer.HasTagExact(TagA));
    TestTrue("TagContainer.HasTagExact(TagB)", TagContainer.HasTagExact(TagB));

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestGameplayTag_Query, "TestUe.GameplayTag.Query", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestGameplayTag_Query::RunTest(const FString &Parameters)
{
    FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
    FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));

    {
        FGameplayTagContainer TagContainer1;
        TagContainer1.AddTag(TagA);
        TagContainer1.AddTag(TagB);

        FGameplayTagQuery Query = FGameplayTagQuery::MakeQuery_MatchAnyTags(TagContainer1);
        TestTrue("TagContainer1.MatchesQuery(Query)", TagContainer1.MatchesQuery(Query));

        FGameplayTagContainer TagContainer2;
        TagContainer2.AddTag(TagA);

        TestTrue("TagContainer2.MatchesQuery(Query)", TagContainer2.MatchesQuery(Query));
    }

    {
        FGameplayTagContainer TagContainer1;
        TagContainer1.AddTag(TagA);

        FGameplayTagQuery Query = FGameplayTagQuery::MakeQuery_MatchAnyTags(TagContainer1);
        TestTrue("TagContainer1.MatchesQuery(Query)", TagContainer1.MatchesQuery(Query));

        FGameplayTagContainer TagContainer2;
        TagContainer2.AddTag(TagB);

        TestTrue("TagContainer2.MatchesQuery(Query)", TagContainer2.MatchesQuery(Query));
    }

    return true;
}