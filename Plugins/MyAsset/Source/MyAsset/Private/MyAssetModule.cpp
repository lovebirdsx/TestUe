#include "MyAssetModule.h"

#define LOCTEXT_NAMESPACE "FMyAssetModule"

void FMyAssetModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("MyAssetModule: Log Started"));
}

void FMyAssetModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyAssetModule, MyAsset)