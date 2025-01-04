"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const gulp = require("gulp");
const path = require("path");
const fs = require("fs");
const unrealTool_1 = require("../common/unrealTool");
const util_1 = require("../common/util");
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
async function buildConsolePrograme() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealBuildTool',
        args: ['MyConsoleProgram', 'Win64', 'Development', `-Project="${uproject}"`],
        logPrefix: '[build-cp] ',
        workingDir,
    });
}
async function test() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealEditor',
        args: [`"${uproject}"`, '-execcmds="Automation RunTests StartsWith:TestUe.; Quit"', '-unattended', '-stdout', '-nopause', '-nosound', '-NOSPLASH', '-NullRHI'],
        logPrefix: '[test] ',
        workingDir,
    });
}
async function clean() {
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
gulp.task('build-cp', buildConsolePrograme);
gulp.task('test', async () => {
    await build();
    await test();
});
gulp.task('test:watch', async () => {
    await build();
    await test();
    const watchDir = path.join(workingDir, 'Source');
    gulp.watch(watchDir, gulp.series('test'));
});
gulp.task('clean', clean);
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