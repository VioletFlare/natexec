const { exec } = require('../src/native-exec');

exec('ls -la', (output) => {
    console.log(output);
});

//this command has no output
exec('echo > /dev/null 2>&1', (output) => {
    console.log(output)
})

//output to file redirected via symlink to /dev/stdout

//ln -s /dev/stdout pico2wave.wav

/*
exec('pico2wave -w ./tests/pico2wave.wav è tutto straordinario', (output) => {
    console.log(output)
})
*/