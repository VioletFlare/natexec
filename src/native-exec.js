const exec = require('bindings')('exec.node');

const _callbackWrapper = (output, cb) => {
    cb(output.toString('utf8'));
}

const execWrapper = (cmd, cb = () => {}) => {
    return exec.exec(cmd, (output) => _callbackWrapper(output, cb));
};

module.exports = {
    exec: execWrapper
};