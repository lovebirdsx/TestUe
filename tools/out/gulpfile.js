"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
require("./packages/testUe");
const config_1 = require("./config");
const exec_1 = require("./common/exec");
function init() {
    const config = (0, config_1.getConfig)();
    if (config.verbose) {
        (0, exec_1.setExecVerbose)(true);
    }
}
init();
//# sourceMappingURL=gulpfile.js.map