"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const util_1 = require("./util");
describe('util', () => {
    it('get modify time', () => {
        expect((0, util_1.getFileModifiedTime)(__filename)).toBeGreaterThan(0);
    });
});
//# sourceMappingURL=util.test.js.map