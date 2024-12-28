import * as gulp from 'gulp';
import * as path from 'path';

import { execUnrealTool } from '../common/unrealTool';
import { cleanDir } from '../common/util';

const workingDir = path.resolve(__dirname, '../../..');
const uproject = path.join(workingDir, 'TestUe.uproject');

async function build() {
    await execUnrealTool({
        type: 'build',
        args: ['TestUeEditor', 'Win64', 'Development', `-Project="${uproject}"`, '-WaitMutex', '-FromMSBuild'],
        logPrefix: '[build] ',
        workingDir,
    });
}

async function test() {
    await execUnrealTool({
        type: 'unrealEditor',
        args: [`"${uproject}"`, '-execcmds="Automation RunTests StartsWith:TestUe.; Quit"', '-unattended', '-stdout', '-NOSPLASH', '-NullRHI'],
        logPrefix: '[test] ',
        workingDir,
    });
}

async function clean() {
    cleanDir(path.join(workingDir, 'node_modules'));
    cleanDir(path.join(workingDir, 'tools', 'node_modules'));
    cleanDir(path.join(workingDir, 'Binaries'));
    cleanDir(path.join(workingDir, 'Intermediate'));
    cleanDir(path.join(workingDir, 'Saved'));
    cleanDir(path.join(workingDir, 'DerivedDataCache'));
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
    await execUnrealTool({
        type: 'runuat',
        args: ['-Help'],
        logPrefix: '[runuat-help] ',
        workingDir,
        verbose: true,
    });
});
