import * as fs from "fs";
import * as path from 'path';
import * as WinReg from 'winreg';

import { exec } from "./exec";
import { red } from "./util";

const INSTALL_PATHS = [
    "F:/UE_5.5_Source",
    "E:/UE_5.5_Source",
    "E:/UE_5.5",
    "F:/UE_5.5",
]

let unrealEnginePath: string | undefined;

/**
 * 获得 Unreal Engine 的安装路径
 */
export function getUnrealEnginePath(): string {
    if (unrealEnginePath) {
        return unrealEnginePath;
    }

    for (const path of INSTALL_PATHS) {
        if (fs.existsSync(path)) {
            unrealEnginePath = path;
            return path;
        }
    }
    throw new Error("Cannot find valid Unreal Engine path");
}

function getVaildUnrealTool(tool: string): string {
    const enginePath = getUnrealEnginePath();
    return path.join(enginePath, tool);
}

const TOOLS = {
    unrealBuildTool: "Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.exe",
    unrealEditorCmd: "Engine/Binaries/Win64/UnrealEditor-Cmd.exe",
    unrealEditor: "Engine/Binaries/Win64/UnrealEditor.exe",
    build: "Engine/Build/BatchFiles/Build.bat",
    runuat: "Engine/Build/BatchFiles/RunUAT.bat",
    generateProjectFiles: "Engine/Build/BatchFiles/GenerateProjectFiles.bat",
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
    "error LNK",
    "error C",
    "Error:",
]

export function formatUnrealOutput(data: string, isError: boolean): string {
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

/**
 * 使用提供的 GUID 将 Unreal Engine 构建与系统注册表关联。
 *
 * @param engineDir - Unreal Engine 的源码目录
 * @param guid - Unreal Engine 构建的唯一标识符
 */
export async function associateUnrealBuildInRegistry(engineDir: string, guid: string): Promise<void> {
    const enginePathNormed = path.normalize(engineDir);

    const regKey = new WinReg({
        hive: WinReg.HKCU,
        key: '\\Software\\Epic Games\\Unreal Engine\\Builds'
    });

    const items = await new Promise<WinReg.RegistryItem[]>((resolve, reject) => {
        regKey.values((err, result) => {
            if (err) reject(err);
            else resolve(result);
        });
    });

    for (const item of items) {
        if (path.normalize(item.value) === enginePathNormed) {
            await new Promise<void>((resolve, reject) => {
                regKey.remove(item.name, err => (err ? reject(err) : resolve()));
            });
        }
    }

    await new Promise<void>((resolve, reject) => {
        regKey.set(guid, WinReg.REG_SZ, engineDir, err => (err ? reject(err) : resolve()));
    });
}
