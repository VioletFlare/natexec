# About

This module wraps the execlp() C++ method and exposes it through a JS interface, allowing
to execute shell commands without passing through Node.JS spawn() or exec().

The documentation says:

> 'pipe': Create a pipe between the child process and the parent process. The parent end of the pipe is exposed to the parent as a property on the child_process object as subprocess.stdio[fd]. Pipes created for fds 0, 1, and 2 are also available as subprocess.stdin, subprocess.stdout and subprocess.stderr, respectively. These are not actual Unix pipes and therefore the child process can not use them by their descriptor files, e.g. /dev/fd/2 or /dev/stdout.

The intention behind executing the shell command at a lower level is to bypass the Node.JS limitation of not being able to interact with /dev/stdout.

# Usage

```
ln -s /dev/stdout pico2wave.wav
```

```
const { exec } = require('../src/native-exec');

exec('pico2wave -w ./tests/pico2wave.wav test!', (output) => {
    console.log(output)
})
```

# Dev

To debug the code in vscodium or vscode, install

https://github.com/vadimcn/codelldb

and then run

"Launch Test" 

from Run And Debug menu.