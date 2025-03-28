"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getToolPath = getToolPath;
exports.execUnrealTool = execUnrealTool;
const fs = require("fs");
const exec_1 = require("./exec");
const util_1 = require("./util");
const gulplog_1 = require("gulplog");
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
    build: "Engine/Build/BatchFiles/Build.bat"
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
function formatUnrealOutput(data, isError) {
    return isError ? (0, util_1.red)(data) : data;
}
async function execUnrealTool(options) {
    const toolPath = getToolPath(options.type);
    const cmd = `"${toolPath}" ${options.args.join(" ")}`;
    (0, gulplog_1.info)(`exec: ${cmd}`);
    await (0, exec_1.exec)(cmd, {
        logPrefix: options.logPrefix,
        workingDir: options.workingDir,
        formatText: formatUnrealOutput,
        verbose: options.verbose,
    });
}
//# sourceMappingURL=unreal.js.map