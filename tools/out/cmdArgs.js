"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getCmdArgs = getCmdArgs;
const gulplog_1 = require("gulplog");
let cmdArgs;
function getCmdArgs() {
    if (cmdArgs) {
        return cmdArgs;
    }
    const { argv } = process;
    cmdArgs = {
        verbose: argv.includes('--verbose') || argv.includes('-v'),
    };
    if (cmdArgs.verbose) {
        (0, gulplog_1.info)('cmdArgs:', cmdArgs);
    }
    return cmdArgs;
}
//# sourceMappingURL=cmdArgs.js.map