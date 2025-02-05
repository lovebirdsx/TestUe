#pragma once

#include "DrawDebugHelpers.h"

inline void Print(const FString& Message)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, Message);
    }
}

#define PRINT(MSG, ...) Print(FString::Printf(TEXT(MSG), __VA_ARGS__))

inline void DrawSphere(const UWorld* World, const FVector& Center, const bool bPersistent = true)
{
    if (World)
    {
        DrawDebugSphere(World, Center, 20, 16, FColor::Blue, bPersistent);
    }
}

inline void DrawSphereTick(const UWorld* World, const FVector& Center)
{
    if (World)
    {
        DrawDebugSphere(World, Center, 20, 16, FColor::Green, false);
    }
}

inline void DrawLine(const UWorld* World, const FVector& Start, const FVector& End, bool bPersistent = true)
{
    if (World)
    {
        DrawDebugLine(World, Start, End, FColor::Blue, bPersistent);
    }
}

inline void DrawLineTick(const UWorld* World, const FVector& Start, const FVector& End)
{
    if (World)
    {
        DrawDebugLine(World, Start, End, FColor::Green, false);
    }
}
