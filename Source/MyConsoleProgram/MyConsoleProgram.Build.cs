using UnrealBuildTool;
using System.IO;

public class MyConsoleProgram : ModuleRules
{
	public MyConsoleProgram(ReadOnlyTargetRules Target) : base(Target)
	{
		// 指定这是一个 "Program" 模块
		// Type = ModuleType.Program;

		// 只依赖最基本的 Core 模块
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);

		// 如果你需要使用到一些平台抽象函数（如 FPlatformMisc），
		// 可以把 "ApplicationCore" 也加上
		// PublicDependencyModuleNames.Add("ApplicationCore");

		// 默认情况下，Program 类型的模块不会启用很多 UE 特性。
		// 如果需要异常支持或 RTTI，可以手动启用：
		bUseRTTI = true;
		bEnableExceptions = true;
	}
}
