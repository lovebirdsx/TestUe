import * as gulp from 'gulp';
import * as path from 'path';

import './packages/testUe';

import { getConfig } from './config';
import { setExecVerbose } from './common/exec';
import { cleanDir } from './common/util';

const workingDir = path.resolve(__dirname, '../..');

function init() {
    const config = getConfig();
    if (config.verbose) {
        setExecVerbose(true);
    }
}

gulp.task('tool:clean', () => {
    cleanDir(path.join(workingDir, 'node_modules'));
})

init();
