#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMyTest, Log, All);

#define TEST_FILTER EAutomationTestFlags::ProgramContext | EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter
