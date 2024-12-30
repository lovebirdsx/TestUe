using UnrealBuildTool;

public class MyAssetEditor : ModuleRules
{
    public MyAssetEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
        });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "InputCore",
            "UnrealEd",
            "AssetDefinition",
            "MyAsset",
        });
    }
}