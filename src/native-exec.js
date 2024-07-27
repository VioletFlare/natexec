const exec = require('bindings')('exec.node');

const execWrapper = (cmd, cb = () => {}) => {
    return exec.exec(cmd, cb);
};

module.exports = {
    exec: execWrapper
};