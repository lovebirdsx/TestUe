import * as gulp from 'gulp';
import * as path from 'path';
import * as fs from 'fs';

import { associateUnrealBuildInRegistry, execUnrealTool, getUnrealEnginePath } from '../common/unrealTool';
import { cleanDir } from '../common/util';

const workingDir = path.resolve(__dirname, '../../..');
const uproject = path.join(workingDir, 'TestUe.uproject');
const UNREAL_BUILD_GUID = 'UE5.5-Souce';

async function build() {
    await execUnrealTool({
        type: 'build',
        args: ['TestUeEditor', 'Win64', 'Development', `-Project="${uproject}"`, '-WaitMutex', '-FromMSBuild'],
        logPrefix: '[build] ',
        workingDir,
    });
}

async function buildConsolePrograme() {
    await execUnrealTool({
        type: 'unrealBuildTool',
        args: ['MyConsoleProgram', 'Win64', 'Development', `-Project="${uproject}"`],
        logPrefix: '[build-cp] ',
        workingDir,
    });
}

async function test() {
    await execUnrealTool({
        type: 'unrealEditor',
        args: [`"${uproject}"`, '-execcmds="Automation RunTests StartsWith:TestUe.; Quit"', '-unattended', '-stdout', '-nopause', '-nosound', '-NOSPLASH', '-NullRHI'],
        logPrefix: '[test] ',
        workingDir,
    });
}

async function clean() {
    cleanDir(path.join(workingDir, 'Binaries'));
    cleanDir(path.join(workingDir, 'Intermediate'));
    cleanDir(path.join(workingDir, 'Saved'));
    cleanDir(path.join(workingDir, 'DerivedDataCache'));

    const pluginsDir = path.join(workingDir, 'Plugins');
    if (fs.existsSync(pluginsDir)) {
        fs.readdirSync(pluginsDir).forEach((plugin) => {
            cleanDir(path.join(pluginsDir, plugin, 'Binaries'));
            cleanDir(path.join(pluginsDir, plugin, 'Intermediate'));
            cleanDir(path.join(pluginsDir, plugin, 'Saved'));
            cleanDir(path.join(pluginsDir, plugin, 'DerivedDataCache'));
        });
    }
}

gulp.task('set-guid', async () => {
    associateUnrealBuildInRegistry(getUnrealEnginePath(), UNREAL_BUILD_GUID);
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
    await execUnrealTool({
        type: 'runuat',
        args: ['-Help'],
        logPrefix: '[runuat-help] ',
        workingDir,
        verbose: true,
    });
});
