#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMySlateApp, Verbose, All);

#define LOG(Format, ...) UE_LOG(LogMySlateApp, Display, TEXT(Format), ##__VA_ARGS__)
#define ERR(Format, ...) UE_LOG(LogMySlateApp, Error, TEXT(Format), ##__VA_ARGS__)