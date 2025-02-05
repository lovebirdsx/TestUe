#include "MyEventManager.h"
#include "ILiveCodingModule.h"

UMyEventManager* UMyEventManager::GetInstance()
{	
	static UMyEventManager* Instance = nullptr;
	if (!Instance)
	{
		Instance = NewObject<UMyEventManager>();
		Instance->AddToRoot();

		Instance->Init();
	}
	
	return Instance;
}

void UMyEventManager::TriggerLiveCodingComplete()
{
	OnLiveCodingComplete.Broadcast();
}

void UMyEventManager::Init()
{	
	if (FModuleManager::Get().IsModuleLoaded("LiveCoding"))
	{
		ILiveCodingModule& LiveCoding = FModuleManager::LoadModuleChecked<ILiveCodingModule>("LiveCoding");
		LiveCoding.GetOnPatchCompleteDelegate().AddUObject(this, &UMyEventManager::TriggerLiveCodingComplete);
	}
}
