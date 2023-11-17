{
  "targets": [
    {
      "target_name": "swe_addon",
      "sources": [
        "addon/swe.cc",
        "addon/position.cc"
      ],
      # "include_dirs": [
      #     "<!@(node -p \"require('node-addon-api').include\")"
      # ],
      # "libraries": [],
      # 'dependencies': [
      #     "<!(node -p \"require('node-addon-api').gyp\")"
      # ],
      # "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}