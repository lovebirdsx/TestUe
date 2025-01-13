#pragma once

#include "CoreMinimal.h"
#include "MyConfig.generated.h"

USTRUCT()
struct FMyConfig
{
    GENERATED_BODY()

    UPROPERTY()
    FString SelectedTest;
    
    UPROPERTY()
    float SliderValue;
};

class FMyConfigGetter
{
public:
    static FMyConfigGetter& Get();
    static void Destroy();

    FMyConfigGetter(const FMyConfigGetter&) = delete;
    FMyConfigGetter& operator=(const FMyConfigGetter&) = delete;

    TSharedPtr<FMyConfig> GetConfig();
    bool Save();

private:
    FMyConfigGetter() = default;
    ~FMyConfigGetter() = default;
    
    static FMyConfigGetter *Instance;
    TSharedPtr<FMyConfig> Config;
};
