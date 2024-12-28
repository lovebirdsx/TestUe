import { getCmdArgs, ICmdArgs } from './cmdArgs';

interface IConfig extends ICmdArgs {
}

const config: IConfig = {
    verbose: false,
};

let isInit = false;
function init() {
    if (isInit) {
        return;
    }

    const cmdArgs = getCmdArgs();
    Object.keys(cmdArgs).forEach((key) => {
        const k = key as keyof ICmdArgs;
        if (cmdArgs[k] !== undefined) {
            config[k] = cmdArgs[k];
        }
    });

    isInit = true;
}

export function getConfig(): IConfig {
    init();

    return config;
}
