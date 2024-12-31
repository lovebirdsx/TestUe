#include "CustomEditor2/MyCustomAsset2Factory.h"
#include "MyCustomAsset2.h"

UMyCustomAsset2Factory::UMyCustomAsset2Factory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMyCustomAsset2::StaticClass();	
}

bool UMyCustomAsset2Factory::ConfigureProperties()
{
	return true;
}

UObject* UMyCustomAsset2Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UMyCustomAsset2>(InParent, InClass, InName, Flags);
}
