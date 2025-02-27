#include "CQTest.h"
#include "GameplayTagContainer.h"

TEST_CLASS(GameplayTag, "TestUe")
{
    TEST_METHOD(BasicTest)
    {
        FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
        FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));

        ASSERT_THAT(IsTrue(TagA.IsValid()));
        ASSERT_THAT(IsTrue(TagB.IsValid()));

        ASSERT_THAT(IsTrue(TagB.MatchesTag(TagA)));
        ASSERT_THAT(IsFalse(TagA.MatchesTag(TagB)));
    }
    
    TEST_METHOD(TagMatchTest)
    {
        FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
        FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));

        ASSERT_THAT(IsTrue(TagB.MatchesTag(TagA)));
        ASSERT_THAT(IsTrue(TagB.MatchesTagExact(TagB)));
        ASSERT_THAT(IsFalse(TagB.MatchesTagExact(TagA)));

        FGameplayTagContainer TagContainer1;
        TagContainer1.AddTag(TagA);
        ASSERT_THAT(IsTrue(TagB.MatchesAny(TagContainer1)));

        FGameplayTagContainer TagContainer2;
        TagContainer2.AddTag(TagB);
        ASSERT_THAT(IsFalse(TagA.MatchesAny(TagContainer2)));
    }

    TEST_METHOD(TagContainerTest)
    {
        FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
        FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));
        FGameplayTagContainer TagContainer;
        TagContainer.AddTag(TagB);

        ASSERT_THAT(IsTrue(TagContainer.HasTag(TagA)));
        ASSERT_THAT(IsTrue(TagContainer.HasTag(TagB)));

        ASSERT_THAT(IsFalse(TagContainer.HasTagExact(TagA)));
        ASSERT_THAT(IsTrue(TagContainer.HasTagExact(TagB)));
    }

    TEST_METHOD(TagQueryTest)
    {
        FGameplayTag TagA = FGameplayTag::RequestGameplayTag(FName("Test.TagA"));
        FGameplayTag TagB = FGameplayTag::RequestGameplayTag(FName("Test.TagA.SubTagB"));

        {
            FGameplayTagContainer TagContainer1;
            TagContainer1.AddTag(TagA);
            TagContainer1.AddTag(TagB);

            FGameplayTagQuery Query = FGameplayTagQuery::MakeQuery_MatchAnyTags(TagContainer1);
            ASSERT_THAT(IsTrue(TagContainer1.MatchesQuery(Query)));

            FGameplayTagContainer TagContainer2;
            TagContainer2.AddTag(TagA);
            ASSERT_THAT(IsTrue(TagContainer2.MatchesQuery(Query)));
        }

        {
            FGameplayTagContainer TagContainer1;
            TagContainer1.AddTag(TagA);

            FGameplayTagQuery Query = FGameplayTagQuery::MakeQuery_MatchAnyTags(TagContainer1);
            ASSERT_THAT(IsTrue(TagContainer1.MatchesQuery(Query)));

            FGameplayTagContainer TagContainer2;
            TagContainer2.AddTag(TagB);
            ASSERT_THAT(IsTrue(TagContainer2.MatchesQuery(Query)));
        }
    }
};
