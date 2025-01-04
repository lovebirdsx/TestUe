using UnrealBuildTool;

public class MyTest : ModuleRules
{
    public MyTest(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePathModuleNames.Add("Launch");

        PrivateDependencyModuleNames.Add("Core");
        PrivateDependencyModuleNames.Add("Projects");
        PrivateDependencyModuleNames.Add("CoreUObject");
    }
}
