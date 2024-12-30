"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const gulp = require("gulp");
const path = require("path");
const unrealTool_1 = require("../common/unrealTool");
const util_1 = require("../common/util");
const workingDir = path.resolve(__dirname, '../../..');
const uproject = path.join(workingDir, 'TestUe.uproject');
async function build() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'build',
        args: ['TestUeEditor', 'Win64', 'Development', `-Project="${uproject}"`, '-WaitMutex', '-FromMSBuild'],
        logPrefix: '[build] ',
        workingDir,
    });
}
async function test() {
    await (0, unrealTool_1.execUnrealTool)({
        type: 'unrealEditor',
        args: [`"${uproject}"`, '-execcmds="Automation RunTests StartsWith:TestUe.; Quit"', '-unattended', '-stdout', '-NOSPLASH', '-NullRHI'],
        logPrefix: '[test] ',
        workingDir,
    });
}
async function clean() {
    (0, util_1.cleanDir)(path.join(workingDir, 'node_modules'));
    (0, util_1.cleanDir)(path.join(workingDir, 'tools', 'node_modules'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Binaries'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Intermediate'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Saved'));
    (0, util_1.cleanDir)(path.join(workingDir, 'DerivedDataCache'));
}
gulp.task('build', build);
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