#include "CQTest.h"
#include "TestUe/Test/MyObject.h"
#include "Misc/DataValidation.h"

TEST_CLASS(Object, "TestUe")
{
    TEST_METHOD(BaiscTest)
    {
        UMyObject* MyObject = NewObject<UMyObject>();
        FDataValidationContext Context;
        EDataValidationResult Result = MyObject->IsDataValid(Context);
        ASSERT_THAT(AreEqual(Result, EDataValidationResult::Valid));
        ASSERT_THAT(AreEqual(Context.GetNumErrors(), 0));

        MyObject->PlayerHealth = -1;
        Result = MyObject->IsDataValid(Context);
        ASSERT_THAT(AreEqual(Result, EDataValidationResult::Invalid));
        ASSERT_THAT(AreEqual(Context.GetNumErrors(), 1));
    }
};