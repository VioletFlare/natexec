const { exec } = require('../src/native-exec');

exec('ls -la', (output) => {
    console.log(output);
});

//this command has no output
exec('echo > /dev/null 2>&1', (output) => {
    console.log(output)
})