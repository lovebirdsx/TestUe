#include "MySlateApp.h"
#include "Log.h"
#include "MainWindow.h"
#include "RequiredProgramMainCPPInclude.h"
#include "StandaloneRenderer.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"

IMPLEMENT_APPLICATION(MySlateApp, "MySlateApp");
DEFINE_LOG_CATEGORY(LogMySlateApp);

#define LOCTEXT_NAMESPACE "MySlateApp"

int RunMySlateApp(const TCHAR* CommandLine)
{
	FTaskTagScope TaskTagScope(ETaskTag::EGameThread);

	// start up the main loop
	GEngineLoop.PreInit(CommandLine);

	// Make sure all UObject classes are registered and default properties have been initialized
	ProcessNewlyLoadedUObjects();

	// Tell the module manager it may now process newly-loaded UObjects when new C++ modules are loaded
	FModuleManager::Get().StartProcessingNewlyLoadedObjects();

	// crank up a normal Slate application using the platform's standalone renderer
	FSlateApplication::InitializeAsStandaloneApplication(GetStandardStandaloneRenderer());

	FSlateApplication::InitHighDPI(true);

	// set the application name
	FGlobalTabmanager::Get()->SetApplicationTitle(LOCTEXT("AppTitle", "My Slate App"));

	FAppStyle::SetAppStyleSetName(FAppStyle::GetAppStyleSetName());

	LOG("MySlateApp started");
	
	FSlateApplication::Get().AddWindow(CreateMainWindow());	

	// new scope to allow TabManager to go out of scope before the Engine is dead
	{
		// loop while the server does the rest
		while (!IsEngineExitRequested())
		{
			BeginExitIfRequested();

			FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
			FStats::AdvanceFrame(false);
			FTSTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
			FSlateApplication::Get().PumpMessages();
			FSlateApplication::Get().Tick();
			FPlatformProcess::Sleep(0.01f);

			GFrameCounter++;
		}
	}

	LOG("MySlateApp shutting down");

	FCoreDelegates::OnExit.Broadcast();
	FSlateApplication::Shutdown();
	FModuleManager::Get().UnloadModulesAtShutdown();

	FEngineLoop::AppPreExit();
	FEngineLoop::AppExit();

	LOG("MySlateApp exited");

	return 0;
}

#undef LOCTEXT_NAMESPACE
