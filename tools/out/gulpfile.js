"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const gulp = require("gulp");
const path = require("path");
require("./packages/testUe");
const config_1 = require("./config");
const exec_1 = require("./common/exec");
const util_1 = require("./common/util");
const workingDir = path.resolve(__dirname, '../..');
function init() {
    const config = (0, config_1.getConfig)();
    if (config.verbose) {
        (0, exec_1.setExecVerbose)(true);
    }
}
gulp.task('tool:clean', () => {
    (0, util_1.cleanDir)(path.join(workingDir, 'node_modules'));
});
init();
//# sourceMappingURL=gulpfile.js.map