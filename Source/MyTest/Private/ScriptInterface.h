#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScriptInterface.generated.h"

UINTERFACE(Blueprintable)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

class IInteractable
{
    GENERATED_BODY()

public:
    virtual void InteractNative() = 0;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
    void Interact();
};

UINTERFACE(Blueprintable)
class UDamageable : public UInterface
{
    GENERATED_BODY()
};

class IDamageable
{
    GENERATED_BODY()

public:
    virtual void TakeDamageNative(int Damage) = 0;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
    void TakeDamage(int Damage);
};

UCLASS()
class MYTEST_API UDoor : public UObject, public IInteractable, public IDamageable
{
    GENERATED_BODY()

public:
    virtual void InteractNative() override
    {
        bIsOpen = !bIsOpen;
        InteractNativeCount++;
    }

    virtual void Interact_Implementation() override
    {
        bIsOpen = !bIsOpen;
        InteractBlueprintCount++;
    }

    virtual void TakeDamageNative(int Damage) override
    {
        Health -= Damage;
        DamageNativeCount++;
    }

    virtual void TakeDamage_Implementation(int Damage) override
    {
        Health -= Damage;
        DamageBlueprintCount++;
    }

    bool bIsOpen = false;
    int Health = 100;
    int InteractNativeCount = 0;
    int InteractBlueprintCount = 0;
    int DamageNativeCount = 0;
    int DamageBlueprintCount = 0;
};

UCLASS()
class MYTEST_API UButton : public UObject, public IInteractable
{
    GENERATED_BODY()

public:
    virtual void InteractNative() override
    {
        bIsPressed = !bIsPressed;
        InteractNativeCount++;
    }

    virtual void Interact_Implementation() override
    {
        bIsPressed = !bIsPressed;
        InteractBlueprintCount++;
    }

    bool bIsPressed = false;
    int InteractNativeCount = 0;
    int InteractBlueprintCount = 0;
};

UCLASS()
class MYTEST_API UInteractor : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
    TScriptInterface<IInteractable> InteractableTarget;

    UFUNCTION(BlueprintCallable, Category = "Interac")
    void PerformInteract()
    {
        if (InteractableTarget.GetInterface() != nullptr)
        {
            InteractableTarget->InteractNative();
        }
        else if (InteractableTarget.GetObject() != nullptr)
        {
            UObject *Target = InteractableTarget.GetObject();
            if (Target->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
            {
                IInteractable::Execute_Interact(Target);
            }
        }
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    TScriptInterface<IDamageable> DamageableTarget;

    UFUNCTION(BlueprintCallable, Category = "Damage")
    bool PerformDamage(int Damage)
    {
        if (DamageableTarget.GetInterface() != nullptr)
        {
            IDamageable::Execute_TakeDamage(DamageableTarget.GetObject(), Damage);
            return true;
        }
        else if (DamageableTarget.GetObject() != nullptr)
        {
            UObject *Target = DamageableTarget.GetObject();
            if (Target->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
            {
                IDamageable::Execute_TakeDamage(Target, Damage);
                return true;
            }
        }

        return false;
    }
};
