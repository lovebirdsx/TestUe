#include "MyObject.h"
#include "Misc/DataValidation.h"

int32 UMyObject::FreeCount = 0;
int32 UMyObject::NewCount = 0;

UMyObject::UMyObject() : PlayerLocation(), PlayerHealth(0)
{
    NewCount++;
    SetFlags(RF_Transactional);

    PlayerHealth = 100;
}

void UMyObject::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);

    if (Ar.IsLoading() || Ar.IsSaving())
    {
        Ar << SelfSerialNumber;
    }
}

EDataValidationResult UMyObject::IsDataValid(FDataValidationContext &Context) const
{
    if (PlayerHealth < 0)
    {
        const FString Message = FString::Printf(TEXT("PlayerHealth is %d, should be greater than 0"), PlayerHealth);
        const FText ErrorMsg = FText::FromString(Message);
        Context.AddError(ErrorMsg);
        return EDataValidationResult::Invalid;
    }

    return EDataValidationResult::Valid;
}
