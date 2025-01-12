"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.setExecVerbose = setExecVerbose;
exports.exec = exec;
exports.formatWebpackOutput = formatWebpackOutput;
exports.formatTscCheckOutput = formatTscCheckOutput;
exports.formatLintOutput = formatLintOutput;
exports.formatMochaTestOutput = formatMochaTestOutput;
exports.formatCheckCircularText = formatCheckCircularText;
exports.formatCSharpOutput = formatCSharpOutput;
const child_process_1 = require("child_process");
const gulplog_1 = require("gulplog");
const util_1 = require("./util");
function removeEmptyLines(data) {
    return data
        .split('\n')
        .filter((line) => line.trim() !== '')
        .join('\n');
}
let execVerbose = false;
function setExecVerbose(verbose) {
    execVerbose = verbose;
}
async function exec(cmd, { logPrefix, workingDir, noThrow, formatText, verbose }) {
    const anyVerbose = verbose || execVerbose;
    if (anyVerbose) {
        (0, gulplog_1.info)(`${(0, util_1.blue)(logPrefix)}exec: ${(0, util_1.green)(cmd)}`);
    }
    return new Promise((resolve, reject) => {
        const process = (0, child_process_1.spawn)(cmd, { shell: true, cwd: workingDir });
        process.on('close', (code) => {
            if (code !== 0 && !noThrow) {
                if (code === 0xC0000005) {
                    reject(new Error(`Executing command failed with an Access Violation (0xC0000005). Code: ${code}. Command: ${cmd}`));
                }
                else {
                    reject(new Error(`Executing command (code: ${code}): ${cmd}`));
                }
            }
            else {
                resolve();
            }
        });
        process.on('error', (err) => {
            if (!noThrow) {
                reject(err);
            }
        });
        const realFormatText = formatText ?? ((data, isError) => (isError ? (0, util_1.red)(data) : data));
        const onOutput = (data, isError) => {
            if (!data) {
                return;
            }
            const str = removeEmptyLines(data.toString());
            if (!str) {
                return;
            }
            const formatedText = realFormatText(str, isError);
            if (!anyVerbose && !(0, util_1.isRed)(formatedText)) {
                return;
            }
            (0, gulplog_1.info)(`${(0, util_1.blue)(logPrefix)}${formatedText}`);
        };
        process.stdout?.on('data', (data) => {
            onOutput(data, false);
        });
        process.stderr?.on('data', (data) => {
            onOutput(data, true);
        });
    });
}
function formatWebpackOutput(data, _isError) {
    if (data.includes('errors')) {
        return (0, util_1.red)(data);
    }
    return data;
}
function formatTscCheckOutput(data, isError) {
    if (isError) {
        return (0, util_1.red)(data);
    }
    if (data.includes('error TS')) {
        return (0, util_1.red)(data);
    }
    return data;
}
function formatLintOutput(data, isError) {
    if (isError) {
        return (0, util_1.red)(data);
    }
    if (data.includes('error')) {
        return (0, util_1.red)(data);
    }
    return data;
}
function formatMochaTestOutput(data, isError) {
    if (isError) {
        return (0, util_1.red)(data);
    }
    if (data.includes('ERR_ASSERTION') || data.includes('error:') || data.includes('Error:')) {
        return (0, util_1.red)(data);
    }
    return data;
}
function formatCheckCircularText(text, isError) {
    const normalText = ['Finding files'];
    const greenText = ['No circular dependency found'];
    if (normalText.some((t) => text.includes(t))) {
        return text;
    }
    if (greenText.some((t) => text.includes(t))) {
        return (0, util_1.green)(text);
    }
    if (text.startsWith('1) ')) {
        return (0, util_1.red)(text);
    }
    return isError ? (0, util_1.red)(text) : text;
}
function formatCSharpOutput(data, isError) {
    if (isError) {
        return (0, util_1.red)(data);
    }
    if (data.includes('error')) {
        return (0, util_1.red)(data);
    }
    return data;
}
//# sourceMappingURL=exec.js.map