#include "MyTest.h"
#include "RequiredProgramMainCPPInclude.h"

DEFINE_LOG_CATEGORY(LogMyTest);

IMPLEMENT_APPLICATION(MyTest, "MyTest");

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

	if (const int32 Ret = GEngineLoop.PreInit(ArgC, ArgV))
	{
		return Ret;
	}	

	FAutomationTestFramework& TestFramework = FAutomationTestFramework::Get();
	TestFramework.SetRequestedTestFilter(EAutomationTestFlags::ProgramContext | EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter);
	
	TArray<FAutomationTestInfo> TestInfos;
	TestFramework.GetValidTestNames(TestInfos);	
	for (const FAutomationTestInfo& Test : TestInfos)
	{
		if (Test.GetDisplayName().StartsWith(TEXT("MyTest")))
		{
			TestFramework.StartTestByName(Test.GetTestName(), 0);
			if (FAutomationTestExecutionInfo TestExecutionInfo; TestFramework.StopTest(TestExecutionInfo))
			{				
				UE_LOG(LogMyTest, Display, TEXT("Pass: %s (%3fms)"), *Test.GetDisplayName(), TestExecutionInfo.Duration * 1000);
			}
			else
			{
				UE_LOG(LogMyTest, Error, TEXT("Fail: %s (%3fms)"), *Test.GetDisplayName(), TestExecutionInfo.Duration * 1000);
				for (const FAutomationExecutionEntry& Entry : TestExecutionInfo.GetEntries())
				{
					GLog->Flush();
					UE_LOG(LogMyTest, Error, TEXT("%s"), *Entry.Event.Message);
				}
			}
            GLog->Flush();
		}
	}	

	return 0;
}
