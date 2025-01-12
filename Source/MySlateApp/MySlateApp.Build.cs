// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MySlateApp : ModuleRules
{
    public MySlateApp(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePathModuleNames.Add("Launch");

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "AppFramework",
                "Core",
                "ApplicationCore",
                "Projects",
                "Slate",
                "SlateCore",
                "StandaloneRenderer",
                "ToolWidgets",
            }
        );
    }
}
