#pragma once

#include "IDetailCustomization.h"

class MYASSETEDITOR_API FMyCustomAssetDetails : public IDetailCustomization
{
public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static TSharedRef<IDetailCustomization> MakeInstance();
};
