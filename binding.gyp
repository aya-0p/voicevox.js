{
    "targets": [
        {
            "target_name": "voicevox",
            "cflags!": ["-fno-exceptions", "-ldl"],
            "cflags_cc!": ["-fno-exceptions", "-ldl"],
            "sources": [
                "voicevox.cc",
            ],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "conditions": [
                [
                    "OS=='win'",
                    {
                        "defines": ["_HAS_EXCEPTIONS=1"],
                        "msvs_settings": {
                            "VCCLCompilerTool": {"ExceptionHandling": 1},
                        },
                    },
                ],
                [
                    "OS=='mac'",
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                            "CLANG_CXX_LIBRARY": "libc++",
                            "MACOSX_DEPLOYMENT_TARGET": "10.7",
                        },
                    },
                ],
            ],
        },
        {
            "target_name": "sharevox",
            "cflags!": ["-fno-exceptions", "-ldl"],
            "cflags_cc!": ["-fno-exceptions", "-ldl"],
            "sources": [
                "sharevox.cc",
            ],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "conditions": [
                [
                    "OS=='win'",
                    {
                        "defines": ["_HAS_EXCEPTIONS=1"],
                        "msvs_settings": {
                            "VCCLCompilerTool": {"ExceptionHandling": 1},
                        },
                    },
                ],
                [
                    "OS=='mac'",
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                            "CLANG_CXX_LIBRARY": "libc++",
                            "MACOSX_DEPLOYMENT_TARGET": "10.7",
                        },
                    },
                ],
            ],
        },
    ]
}
