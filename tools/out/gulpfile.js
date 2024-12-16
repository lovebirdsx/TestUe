"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const gulp = require("gulp");
const path = require("path");
const gulp_util_1 = require("gulp-util");
const util_1 = require("./common/util");
const workingDir = path.resolve(__dirname, '../..');
gulp.task('clean', (cb) => {
    (0, gulp_util_1.log)(`Cleaning pwd: ${workingDir}`);
    (0, util_1.cleanDir)(path.join(workingDir, 'node_modules'));
    (0, util_1.cleanDir)(path.join(workingDir, 'tools', 'node_modules'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Binaries'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Intermediate'));
    (0, util_1.cleanDir)(path.join(workingDir, 'Saved'));
    (0, util_1.cleanDir)(path.join(workingDir, 'DerivedDataCache'));
    cb();
});
//# sourceMappingURL=gulpfile.js.map