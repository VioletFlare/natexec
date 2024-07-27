const exec = require('bindings')('exec.node');

const exec = (cmd) => {
    return exec.exec(cmd);
};

module.exports = {
    exec: exec
};