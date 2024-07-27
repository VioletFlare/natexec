{
  "targets": [
    {
      "target_name": "exec",
      "sources": [ "src/exec.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('node-addon-api').include\")"
      ],
      "dependencies": [
        "<!(node -e \"require('node-addon-api').gyp\")"
      ],
      "cflags_cc": [ "-std=c++17" ]
    }
  ]
}