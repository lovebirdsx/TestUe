"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.cleanDir = cleanDir;
exports.getFileModifiedTime = getFileModifiedTime;
exports.readJsonFile = readJsonFile;
exports.writeJsonFile = writeJsonFile;
exports.green = green;
exports.yellow = yellow;
exports.red = red;
exports.isRed = isRed;
exports.blue = blue;
const fs = require("fs");
const path = require("path");
function cleanDir(dir) {
    if (fs.existsSync(dir)) {
        fs.rmSync(dir, { recursive: true });
    }
}
function getFileModifiedTime(filePath) {
    return fs.statSync(filePath).mtimeMs;
}
function readJsonFile(filePath) {
    if (!fs.existsSync(filePath)) {
        return undefined;
    }
    let content = fs.readFileSync(filePath, 'utf-8');
    if (content.charCodeAt(0) === 0xfeff) {
        content = content.slice(1);
    }
    return JSON.parse(content);
}
function writeJsonFile(filePath, data) {
    if (!fs.existsSync(filePath)) {
        fs.mkdirSync(path.dirname(filePath), { recursive: true });
    }
    fs.writeFileSync(filePath, JSON.stringify(data, undefined, 4));
}
function green(str) {
    return `\x1b[32m${str}\x1b[0m`;
}
function yellow(str) {
    return `\x1b[33m${str}\x1b[0m`;
}
function red(str) {
    return `\x1b[31m${str}\x1b[0m`;
}
function isRed(str) {
    return str.startsWith('\x1b[31m');
}
function blue(str) {
    return `\x1b[34m${str}\x1b[0m`;
}
//# sourceMappingURL=util.js.map