const { exec } = require('../src/native-exec');

exec('ls -la', (output) => {
    console.log(output);
});