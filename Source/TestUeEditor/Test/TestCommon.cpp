#include "TestCommon.h"
#include "Engine/AssetManager.h"

bool FMyTestCommand_WaitLoadPrimaryAsset::Update()
{
	const UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
	if (!AssetManager)
	{
		return false;
	}

	const UObject* Asset = AssetManager->GetPrimaryAssetObject(PrimaryAssetId);
	return Asset != nullptr;
}
