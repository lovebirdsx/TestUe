#include "CustomEditor3/MyCustomAsset3Factory.h"
#include "MyCustomAsset3.h"

UMyCustomAsset3Factory::UMyCustomAsset3Factory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMyCustomAsset3::StaticClass();	
}

bool UMyCustomAsset3Factory::ConfigureProperties()
{
	return true;
}

UObject* UMyCustomAsset3Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UMyCustomAsset3>(InParent, InClass, InName, Flags);
}
