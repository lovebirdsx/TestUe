#include "MyTest.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestGraphInterface_Simple, "MyTest.GraphInterface.Simple", TEST_FILTER)

bool TestGraphInterface_Simple::RunTest(const FString& Parameters)
{
	static int32 GTaskCount = 0;

	GTaskCount = 0;
	FTaskGraphInterface& TaskGraph = FTaskGraphInterface::Get();
	auto Task = TGraphTask<FSimpleDelegateGraphTask>::CreateTask().ConstructAndDispatchWhenReady(
		FSimpleDelegateGraphTask::FDelegate::CreateLambda([]()
		{
			GTaskCount++;
		}),
		GET_STATID(STAT_FSimpleDelegateGraphTask),
		ENamedThreads::AnyThread
	);

	TestEqual("GTaskCount must be 0", GTaskCount, 0);

	TaskGraph.WaitUntilTaskCompletes(Task);

	TestEqual("GTaskCount must be 1", GTaskCount, 1);

	return true;
}
