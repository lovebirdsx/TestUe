import * as fs from 'fs';
import * as path from 'path';

// region 文件操作

export function cleanDir(dir: string): void {
    if (fs.existsSync(dir)) {
        fs.rmSync(dir, { recursive: true });
    }
}

export function getFileModifiedTime(filePath: string): number {
    return fs.statSync(filePath).mtimeMs;
}

// endregion

// region Json 操作

export function readJsonFile<T>(filePath: string): T | undefined {
    if (!fs.existsSync(filePath)) {
        return undefined;
    }

    let content = fs.readFileSync(filePath, 'utf-8');

    // 检查并移除BOM
    if (content.charCodeAt(0) === 0xfeff) {
        content = content.slice(1);
    }

    return JSON.parse(content) as T;
}

export function writeJsonFile<T>(filePath: string, data: T): void {
    if (!fs.existsSync(filePath)) {
        fs.mkdirSync(path.dirname(filePath), { recursive: true });
    }

    fs.writeFileSync(filePath, JSON.stringify(data, undefined, 4));
}

// endregion

// region 日志输出

/**
 * 转换为绿色的字符串，用于日志输出
 */
export function green(str: string): string {
    return `\x1b[32m${str}\x1b[0m`;
}

/**
 * 转换为黄色的字符串，用于日志输出
 */
export function yellow(str: string): string {
    return `\x1b[33m${str}\x1b[0m`;
}

/**
 * 转换为红色的字符串，用于日志输出
 */
export function red(str: string): string {
    return `\x1b[31m${str}\x1b[0m`;
}

export function isRed(str: string): boolean {
    return str.startsWith('\x1b[31m');
}

/**
 * 转换为蓝色的字符串，用于日志输出
 */
export function blue(str: string): string {
    return `\x1b[34m${str}\x1b[0m`;
}

// endregion
