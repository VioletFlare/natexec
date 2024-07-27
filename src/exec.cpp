#include <napi.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace Napi;

class CommandWorker : public AsyncWorker {
public:
    CommandWorker(Function& callback, const std::string& command)
        : AsyncWorker(callback), command_(command) {}

    void Execute() override {
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            SetError("Failed to create pipe");
            return;
        }

        pid_t pid = fork();
        if (pid == -1) {
            SetError("Failed to fork process");
            return;
        }

        if (pid == 0) {
            // Child process
            close(pipefd[0]); // Close reading end of the pipe

            // Redirect stdout and stderr to the pipe
            dup2(pipefd[1], STDOUT_FILENO);
            dup2(pipefd[1], STDERR_FILENO);
            close(pipefd[1]);

            
            // Execute the command in the shell
            execl("/bin/sh", "/bin/sh", "-c", command_.c_str(), nullptr);

            // If execlp fails
            _exit(EXIT_FAILURE);
        } else {
            // Parent process
            close(pipefd[1]); // Close writing end of the pipe

            // Read from the pipe
            char buffer[4096];
            ssize_t bytesRead;
            while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
                outputData_.insert(outputData_.end(), buffer, buffer + bytesRead);
            }

            close(pipefd[0]);
            waitpid(pid, nullptr, 0);
        }
    }

    void OnOK() override {
        Callback().Call({Env().Undefined(), Buffer<char>::Copy(Env(), outputData_.data(), outputData_.size())});
    }

private:
    std::string command_;
    std::vector<char> outputData_;
};

Value RunCommand(const CallbackInfo& info) {
    Env env = info.Env();

    if (info.Length() < 2 || !info[0].IsString() || !info[1].IsFunction()) {
        TypeError::New(env, "Expected a string and a callback function").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string command = info[0].As<String>().Utf8Value();
    Function callback = info[1].As<Function>();

    CommandWorker* worker = new CommandWorker(callback, command);
    worker->Queue();

    return env.Null();
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "exec"), Function::New(env, RunCommand));
    return exports;
}

NODE_API_MODULE(addon, Init)