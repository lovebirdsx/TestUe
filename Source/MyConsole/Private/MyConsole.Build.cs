using UnrealBuildTool;
using System.IO;

public class MyConsole : ModuleRules
{
	public MyConsole(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePathModuleNames.Add("Launch");
		PrivateDependencyModuleNames.Add("Core");
		PrivateDependencyModuleNames.Add("Projects");
	}
}
