#include "TestUe/Test/MyObject.h"
#include "Misc/AutomationTest.h"
#include "Misc/DataValidation.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestObject_Validation, "TestUe.Object.Validation", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestObject_Validation::RunTest(const FString &Parameters)
{
    // IsA
    UMyObject *MyObject = NewObject<UMyObject>();
    FDataValidationContext Context;
    EDataValidationResult Result = MyObject->IsDataValid(Context);
    TestEqual("Result should be Valid", Result, EDataValidationResult::Valid);
    TestEqual("Context.GetNumErrors() should be 0", Context.GetNumErrors(), 0);

    MyObject->PlayerHealth = -1;
    Result = MyObject->IsDataValid(Context);
    TestEqual("Result should be Invalid", Result, EDataValidationResult::Invalid);
    TestEqual("Context.GetNumErrors() should be 1", Context.GetNumErrors(), 1);

    return true;
}
