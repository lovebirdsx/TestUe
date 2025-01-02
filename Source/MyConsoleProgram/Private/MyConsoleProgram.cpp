#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FMyConsoleProgramModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        // 在UE模块加载时会执行此处。
        // 如果想在这里就执行你的逻辑，也可以把主逻辑写在这里面。
    }

    virtual void ShutdownModule() override
    {
        // 模块卸载时执行的清理操作。
    }
};

IMPLEMENT_MODULE(FMyConsoleProgramModule, MyConsoleProgram);
