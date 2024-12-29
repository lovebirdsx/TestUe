using UnrealBuildTool;

public class MyAsset : ModuleRules
{
	public MyAsset(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[]{});

		PrivateIncludePaths.AddRange(new string[]{});			
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",		
		});			
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
		});		
		
		DynamicallyLoadedModuleNames.AddRange(new string[] {});
	}
}
