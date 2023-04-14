{
  "targets": [
    {
      "target_name": "voicevox",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "voicevox.cc",
        "voicevox_core/voicevox_core.h"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      "libraries": [
        "<(module_root_dir)/voicevox_core/voicevox_core.lib"
      ]
    }
  ]
}