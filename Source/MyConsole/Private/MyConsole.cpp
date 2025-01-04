#include "CoreMinimal.h"
#include "RequiredProgramMainCPPInclude.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyConsole, Log, All);

IMPLEMENT_APPLICATION(MyConsole, "MyConsole");

INT32_MAIN_INT32_ARGC_TCHAR_ARGV()
{
	FTaskTagScope Scope(ETaskTag::EGameThread);
	ON_SCOPE_EXIT
	{ 
		LLM(FLowLevelMemTracker::Get().UpdateStatsPerFrame());
		RequestEngineExit(TEXT("Exiting"));
		FEngineLoop::AppPreExit();
		FModuleManager::Get().UnloadModulesAtShutdown();
		FEngineLoop::AppExit();
	};

	if (int32 Ret = GEngineLoop.PreInit(ArgC, ArgV))
	{
		return Ret;
	}

	// to run automation tests in MyConsole:
	// * set `bForceCompileDevelopmentAutomationTests` to `true` in `MyConsoleTarget` constructor in "MyConsole.Target.cs"
	// add `FAutomationTestFramework::Get().StartTestByName(TEXT("The name of the test class passed to IMPLEMENT_SIMPLE_AUTOMATION_TEST or TEST_CASE_NAMED"), 0);` right here

	// to link with "CoreUObject" module:
	// * uncomment `PrivateDependencyModuleNames.Add("CoreUObject");` in `MyConsole` constructor in "MyConsole.Build.cs"
	// * set `bCompileAgainstCoreUObject` to `true` in `MyConsoleTarget` constructor in "MyConsole.Target.cs"

	// to enable tracing:
	// * uncomment `AppendStringToPublicDefinition("UE_TRACE_ENABLED", "1");` in `MyConsole` constructor in "MyConsole.Build.cs"
	// * uncomment `GlobalDefinitions.Add("UE_TRACE_ENABLED=1");` in `MyConsoleTarget` constructor in "MyConsole.Target.cs"
	// you may need to enable compilation of a particular trace channel, e.g. for "task" traces:
	// * add `GlobalDefinitions.Add("UE_TASK_TRACE_ENABLED=1");` in `MyConsoleTarget` constructor in "MyConsole.Target.cs"
	// you'll still need to enable this trace channel on cmd-line like `-trace=task,default`

	// to enable LLM tracing, uncomment the following in `MyConsole` constructor in "MyConsole.Build.cs":
	// GlobalDefinitions.Add("LLM_ENABLED_IN_CONFIG=1");
	// GlobalDefinitions.Add("UE_MEMORY_TAGS_TRACE_ENABLED=1");

	UE_LOG(LogMyConsole, Display, TEXT("Hello World, MyConsole!"));

	return 0;
}
