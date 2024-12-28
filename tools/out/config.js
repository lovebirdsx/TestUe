"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getConfig = getConfig;
const cmdArgs_1 = require("./cmdArgs");
const config = {
    verbose: false,
};
let isInit = false;
function init() {
    if (isInit) {
        return;
    }
    const cmdArgs = (0, cmdArgs_1.getCmdArgs)();
    Object.keys(cmdArgs).forEach((key) => {
        const k = key;
        if (cmdArgs[k] !== undefined) {
            config[k] = cmdArgs[k];
        }
    });
    isInit = true;
}
function getConfig() {
    init();
    return config;
}
//# sourceMappingURL=config.js.map