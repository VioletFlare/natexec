{
  "targets": [
    {
      "target_name": "exec",
      "sources": [ "src/exec.cpp" ],
      "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
      "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
      "cflags_cc": [ "-std=c++17" ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}