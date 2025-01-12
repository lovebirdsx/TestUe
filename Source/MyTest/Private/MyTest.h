#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyTest, Log, All);

#define LOG(Format, ...) UE_LOG(LogMyTest, Display, TEXT(Format), ##__VA_ARGS__)
#define ERR(Format, ...) UE_LOG(LogMyTest, Error, TEXT(Format), ##__VA_ARGS__)
#define TEST_FILTER EAutomationTestFlags::ProgramContext | EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
