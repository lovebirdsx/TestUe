using UnrealBuildTool;
using System.Collections.Generic;

public class MyConsoleProgramTarget : TargetRules
{
	public MyConsoleProgramTarget(TargetInfo Target) : base(Target)
	{		
		Type = TargetType.Program;
		
		LaunchModuleName = "MyConsoleProgram";
		BuildEnvironment = TargetBuildEnvironment.Shared;
		bCompileAgainstEngine = false;
		bCompileWithPluginSupport = false;
		bUseLoggingInShipping = true;
		
		ExtraModuleNames.Add("MyConsoleProgram");
	}
}
