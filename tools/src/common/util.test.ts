import { getFileModifiedTime } from './util';

describe('util', () => {
    it('get modify time', () => {
        expect(getFileModifiedTime(__filename)).toBeGreaterThan(0);
    });
});
