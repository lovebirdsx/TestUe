"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const gulp = require("gulp");
const path = require("path");
const fs = require("fs");
const unrealTool_1 = require("../common/unrealTool");
const util_1 = require("../common/util");
const exec_1 = require("../common/exec");
const workingDir = path.resolve(__dirname, '../../..');
const uproject = path.join(workingDir, 'TestUe.uproject');
const UNREAL_BUILD_GUID = 'UE5.5-Souce';
async function build() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'build',
        args: ['TestUeEditor', 'Win64', 'Development', `-Project="${uproject}"`, '-WaitMutex', '-FromMSBuild'],
        logPrefix: '[build] ',
        workingDir,
    });
}
async function buildConsoleProgram() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealBuildTool',
        args: ['MyConsole', 'Win64', 'Debug', `-Project="${uproject}"`],
        logPrefix: '[build-cp] ',
        workingDir,
    });
}
async function buildMySlateApp() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealBuildTool',
        args: ['MySlateApp', 'Win64', 'Debug', `-Project="${uproject}"`],
        logPrefix: '[build-slate] ',
        workingDir,
    });
}
async function buildTestProgram() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealBuildTool',
        args: ['MyTest', 'Win64', 'Debug', `-Project="${uproject}"`],
        logPrefix: '[build-test] ',
        workingDir,
    });
}
async function runEditor() {
    const uproject = path.join(workingDir, 'TestUe.uproject');
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealEditor',
        args: [`"${uproject}"`],
        logPrefix: '[editor] ',
        workingDir,
    });
}
async function runEditorTest() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealEditor',
        args: [`"${uproject}"`, '-execcmds="Automation RunTests StartsWith:TestUe.; Quit"', '-unattended', '-stdout', '-nopause', '-nosound', '-NOSPLASH', '-NullRHI'],
        logPrefix: '[test] ',
        workingDir,
    });
}
async function runTest() {
    const exe = path.join(workingDir, 'Binaries', 'Win64', 'MyTest-Win64-Debug.exe');
    await (0, exec_1.exec)(exe, {
        logPrefix: '[test] ',
        workingDir,
        formatText: unrealTool_1.formatUnrealOutput,
    });
}
async function runConsoleProgram() {
    const exe = path.join(workingDir, 'Binaries', 'Win64', 'MyConsole-Win64-Debug.exe');
    await (0, exec_1.exec)(exe, {
        logPrefix: '[console] ',
        workingDir,
        formatText: unrealTool_1.formatUnrealOutput,
    });
}
async function runMySlateApp() {
    const exe = path.join(workingDir, 'Binaries', 'Win64', 'MySlateApp-Win64-Debug.exe');
    await (0, exec_1.exec)(exe, {
        logPrefix: '[slate] ',
        workingDir,
        formatText: unrealTool_1.formatUnrealOutput,
    });
}
async function runClean() {
    (0, util_1.cleanDir)(path.join(workingDir, 'Binaries'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Intermediate'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Saved'));
    (0, util_1.cleanDir)(path.join(workingDir, 'DerivedDataCache'));
    const pluginsDir = path.join(workingDir, 'Plugins');
    if (fs.existsSync(pluginsDir)) {
        fs.readdirSync(pluginsDir).forEach((plugin) => {
            (0, util_1.cleanDir)(path.join(pluginsDir, plugin, 'Binaries'));
            (0, util_1.cleanDir)(path.join(pluginsDir, plugin, 'Intermediate'));
            (0, util_1.cleanDir)(path.join(pluginsDir, plugin, 'Saved'));
            (0, util_1.cleanDir)(path.join(pluginsDir, plugin, 'DerivedDataCache'));
        });
    }
}
gulp.task('set-guid', async () => {
    (0, unrealTool_1.associateUnrealBuildInRegistry)((0, unrealTool_1.getUnrealEnginePath)(), UNREAL_BUILD_GUID);
});
gulp.task('build', build);
gulp.task('build:watch', async () => {
    await build();
    const watchDirGlobs = [
        path.join(workingDir, 'Source', 'TestUe', '**/*'),
        path.join(workingDir, 'Plugins', '**/Source/**/*'),
    ];
    gulp.watch(watchDirGlobs, gulp.series('build'));
});
gulp.task('editor', runEditor);
gulp.task('editor:watch', async () => {
    await build();
    await runEditor();
    const watchDirGlobs = [
        path.join(workingDir, 'Source', 'TestUe', '**/*'),
        path.join(workingDir, 'Plugins', '**/Source/**/*'),
    ];
    gulp.watch(watchDirGlobs, gulp.series('build', 'editor'));
});
gulp.task('build-console', buildConsoleProgram);
gulp.task('build-test', buildTestProgram);
gulp.task('editor-test', async () => {
    await build();
    await runEditorTest();
});
gulp.task('editor-test:watch', async () => {
    await build();
    await runEditorTest();
    const watchDirGlobs = [
        path.join(workingDir, 'Source', 'TestUe', '**/*'),
        path.join(workingDir, 'Source', 'TestUeEditor', '**/*'),
        path.join(workingDir, 'Plugins', '**/Source/**/*'),
    ];
    gulp.watch(watchDirGlobs, gulp.series('editor-test'));
});
gulp.task('console', async () => {
    await buildConsoleProgram();
    await runConsoleProgram();
});
gulp.task('console:watch', async () => {
    await buildConsoleProgram();
    await runConsoleProgram();
    const watchDirGlob = path.join(workingDir, 'Source', 'MyConsole') + '/**/*';
    gulp.watch(watchDirGlob, gulp.series('console'));
});
gulp.task('slate', async () => {
    await buildMySlateApp();
    await runMySlateApp();
});
gulp.task('slate:watch', async () => {
    await buildMySlateApp();
    await runMySlateApp();
    const watchDirGlob = path.join(workingDir, 'Source', 'MySlateApp') + '/**/*';
    gulp.watch(watchDirGlob, gulp.series('slate'));
});
gulp.task('test', async () => {
    await buildTestProgram();
    await runTest();
});
gulp.task('test:watch', async () => {
    await buildTestProgram();
    await runTest();
    const watchDirGlob = path.join(workingDir, 'Source', 'MyTest') + '/**/*';
    gulp.watch(watchDirGlob, gulp.series('test'));
});
gulp.task('clean', runClean);
gulp.task('runuat-help', async () => {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'runuat',
        args: ['-Help'],
        logPrefix: '[runuat-help] ',
        workingDir,
        verbose: true,
    });
});
//# sourceMappingURL=testUe.js.map