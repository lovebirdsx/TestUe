#include "MyBPLib.h"

FString UMyBPLib::GetPackageName(UObject* Object)
{
	return Object->GetOutermost()->GetName();
}
