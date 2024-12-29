#include "MyObject.h"

int32 UMyObject::FreeCount = 0;
int32 UMyObject::NewCount = 0;

void UMyObject::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);

	if (Ar.IsLoading() || Ar.IsSaving())
	{
		Ar << SelfSerialNumber;
	}
}
