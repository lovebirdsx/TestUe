#include "MyObject.h"

int32 UMyObject::FreeCount = 0;
int32 UMyObject::NewCount = 0;

UMyObject::UMyObject(): PlayerLocation(), PlayerHealth(0)
{
	NewCount++;
	SetFlags(RF_Transactional);
}

void UMyObject::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);

	if (Ar.IsLoading() || Ar.IsSaving())
	{
		Ar << SelfSerialNumber;
	}
}
