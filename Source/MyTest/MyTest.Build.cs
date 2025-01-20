using UnrealBuildTool;

public class MyTest : ModuleRules
{
    public MyTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePathModuleNames.Add("Launch");

        PrivateDependencyModuleNames.Add("Core");
        PrivateDependencyModuleNames.Add("Projects");
        PrivateDependencyModuleNames.Add("CoreUObject");

        DefaultBuildSettings = BuildSettingsVersion.V5;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/MyTest.h";

        bLegacyPublicIncludePaths = false;
        bLegacyParentIncludePaths = false;

        CppStandard = CppStandardVersion.Cpp20;

        bValidateFormatStrings = true;
    }
}
