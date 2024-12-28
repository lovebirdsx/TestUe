import './packages/testUe';

import { getConfig } from './config';
import { setExecVerbose } from './common/exec';

function init() {
    const config = getConfig();
    if (config.verbose) {
        setExecVerbose(true);
    }
}

init();
