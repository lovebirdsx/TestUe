import * as fs from "fs";
import { exec } from "./exec";
import { red } from "./util";

const INSTALL_PATHS = [
    "E:/UE_5.5",
    "F:/UE_5.5",
]

function getVaildUnrealTool(tool: string): string {
    for (const path of INSTALL_PATHS) {
        const toolPath = `${path}/${tool}`;
        if (fs.existsSync(toolPath)) {
            return toolPath;
        }
    }
    throw new Error(`Cannot find valid Unreal tool: ${tool}`);
}

const TOOLS = {
    unrealBuildTool: "Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe",
    unrealEditorCmd: "Engine/Binaries/Win64/UnrealEditor-Cmd.exe",
    unrealEditor: "Engine/Binaries/Win64/UnrealEditor.exe",
    build: "Engine/Build/BatchFiles/Build.bat",
    runuat: "Engine/Build/BatchFiles/RunUAT.bat",
}

const toolPaths: { [key: string]: string } = {};
export function getToolPath(tool: keyof typeof TOOLS): string {
    if (toolPaths[tool]) {
        return toolPaths[tool];
    }

    const toolPath = getVaildUnrealTool(TOOLS[tool]);
    toolPaths[tool] = toolPath;
    return toolPath;
}

const unrealErrors = [
    "LogAutomationController: Error:",
]

function formatUnrealOutput(data: string, isError: boolean): string {
    if (unrealErrors.some((error) => data.includes(error))) {
        return red(data);
    }

    return isError ? red(data) : data;
}

export interface IExecUnrealToolOptions {
    type: keyof typeof TOOLS;
    args: string[];
    logPrefix: string;
    workingDir?: string;
    verbose?: boolean;
}

export async function execUnrealTool(options: IExecUnrealToolOptions): Promise<void> {
    const toolPath = getToolPath(options.type);
    const cmd = `"${toolPath}" ${options.args.join(" ")}`;

    await exec(cmd, {
        logPrefix: options.logPrefix,
        workingDir: options.workingDir,
        formatText: formatUnrealOutput,
        verbose: options.verbose,
    });
}
