#include "ScriptInterface.h"
#include "MyTest.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestScriptInterface_CallNative, "MyTest.ScriptInterface.CallNative", TEST_FILTER)

bool TestScriptInterface_CallNative::RunTest(const FString &Parameters)
{
    UDoor *Door = NewObject<UDoor>();
    UButton *Button = NewObject<UButton>();
    UInteractor *Interactor = NewObject<UInteractor>();

    Interactor->InteractableTarget = Door;
    Interactor->PerformInteract();
    TestTrue("Door should be open", Door->bIsOpen);
    TestEqual("Door InteractNativeCount should be 1", Door->InteractNativeCount, 1);
    TestEqual("Door InteractBlueprintCount should be 0", Door->InteractBlueprintCount, 0);

    Interactor->InteractableTarget = Button;
    Interactor->PerformInteract();
    TestTrue("Button should be pressed", Button->bIsPressed);
    TestEqual("Button InteractNativeCount should be 1", Button->InteractNativeCount, 1);
    TestEqual("Button InteractBlueprintCount should be 0", Button->InteractBlueprintCount, 0);

    TScriptInterface<IInteractable> InteractableDoor = Door;
    Interactor->InteractableTarget = InteractableDoor;
    Interactor->PerformInteract();
    TestFalse("Door should be closed", Door->bIsOpen);
    TestEqual("Door InteractNativeCount should be 2", Door->InteractNativeCount, 2);
    TestEqual("Door InteractBlueprintCount should be 0", Door->InteractBlueprintCount, 0);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestScriptInterface_CallBlueprint, "MyTest.ScriptInterface.CallBlueprint", TEST_FILTER)

bool TestScriptInterface_CallBlueprint::RunTest(const FString &Parameters)
{
    UDoor *Door = NewObject<UDoor>();
    UButton *Button = NewObject<UButton>();
    UInteractor *Interactor = NewObject<UInteractor>();

    TScriptInterface<IInteractable> InteractableButton;
    InteractableButton.SetObject(Button);

    Interactor->InteractableTarget = InteractableButton;
    Interactor->PerformInteract();
    TestTrue("Button should be pressed", Button->bIsPressed);
    TestEqual("Button InteractNativeCount should be 0", Button->InteractNativeCount, 0);
    TestEqual("Button InteractBlueprintCount should be 1", Button->InteractBlueprintCount, 1);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestScriptInterface_DifferentInterface, "MyTest.ScriptInterface.DifferentInterface", TEST_FILTER)

bool TestScriptInterface_DifferentInterface::RunTest(const FString &Parameters)
{
    UDoor *Door = NewObject<UDoor>();
    UButton *Button = NewObject<UButton>();
    UInteractor *Interactor = NewObject<UInteractor>();

    TScriptInterface<IDamageable> ScriptDoor;
    TScriptInterface<IDamageable> ScriptButton;
    ScriptDoor.SetObject(Door);
    ScriptButton.SetObject(Button);

    Interactor->DamageableTarget = ScriptDoor;
    Interactor->PerformDamage(10);
    TestEqual("Door Health should be 90", Door->Health, 90);
    TestEqual("Door DamageNativeCount should be 0", Door->DamageNativeCount, 0);
    TestEqual("Door DamageBlueprintCount should be 1", Door->DamageBlueprintCount, 1);

    Interactor->DamageableTarget = ScriptButton;
    const bool bResult = Interactor->PerformDamage(10);
    TestFalse("bResult should be false", bResult);

    return true;
}
