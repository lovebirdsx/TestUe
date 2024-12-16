import * as gulp from 'gulp';
import * as path from 'path';

import { log } from 'gulp-util';

import { cleanDir } from './common/util';

const workingDir = path.resolve(__dirname, '../..');

gulp.task('clean', (cb: () => void): void => {
    log(`Cleaning pwd: ${workingDir}`);
    cleanDir(path.join(workingDir, 'node_modules'));
    cleanDir(path.join(workingDir, 'tools', 'node_modules'));
    cleanDir(path.join(workingDir, 'Binaries'));
    cleanDir(path.join(workingDir, 'Intermediate'));
    cleanDir(path.join(workingDir, 'Saved'));
    cleanDir(path.join(workingDir, 'DerivedDataCache'));

    cb();
});
