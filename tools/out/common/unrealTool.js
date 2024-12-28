"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getToolPath = getToolPath;
exports.execUnrealTool = execUnrealTool;
const fs = require("fs");
const exec_1 = require("./exec");
const util_1 = require("./util");
const INSTALL_PATHS = [
    "E:/UE_5.5",
    "F:/UE_5.5",
];
function getVaildUnrealTool(tool) {
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
};
const toolPaths = {};
function getToolPath(tool) {
    if (toolPaths[tool]) {
        return toolPaths[tool];
    }
    const toolPath = getVaildUnrealTool(TOOLS[tool]);
    toolPaths[tool] = toolPath;
    return toolPath;
}
const unrealErrors = [
    "LogAutomationController: Error:",
];
function formatUnrealOutput(data, isError) {
    if (unrealErrors.some((error) => data.includes(error))) {
        return (0, util_1.red)(data);
    }
    return isError ? (0, util_1.red)(data) : data;
}
async function execUnrealTool(options) {
    const toolPath = getToolPath(options.type);
    const cmd = `"${toolPath}" ${options.args.join(" ")}`;
    await (0, exec_1.exec)(cmd, {
        logPrefix: options.logPrefix,
        workingDir: options.workingDir,
        formatText: formatUnrealOutput,
        verbose: options.verbose,
    });
}
//# sourceMappingURL=unrealTool.js.map