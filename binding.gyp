{
  "targets": [
    {
      "target_name": "swe_addon",
      "sources": [
        "src/swe.cc",
        "src/position.cc"
      ],
      "include_dirs": [
          "/home/ss/gsync/web-server/src/ephm/",
          "/home/ss/gsync/web-server/lib/boost_1_82_0"
      ],
      "libraries": [
        "/home/ss/gsync/web-server/src/ephm/swedate.o",
        "/home/ss/gsync/web-server/src/ephm/swehel.o",
        "/home/ss/gsync/web-server/src/ephm/swehouse.o",
        "/home/ss/gsync/web-server/src/ephm/swejpl.o",
        "/home/ss/gsync/web-server/src/ephm/swemmoon.o",
        "/home/ss/gsync/web-server/src/ephm/swemplan.o",
        "/home/ss/gsync/web-server/src/ephm/sweph.o",
        "/home/ss/gsync/web-server/src/ephm/swephlib.o",
      ],
      "conditions": [
          [ "OS=='linux'", {
              "cflags+": [ "-std=c++17", "-fexceptions" ],
              "cflags_c+": [ "-std=c++17", "-fexceptions" ],
              "cflags_cc+": [ "-std=c++17", "-fexceptions" ],
          }],
          [ "OS=='mac'", {
              "cflags+": [ "-stdlib=libc++" ],
              "xcode_settings": {
                  "OTHER_CPLUSPLUSFLAGS" : [ "-std=c++17", "-stdlib=libc++", "-pthread" ],
                  "OTHER_LDFLAGS": [ "-stdlib=libc++" ],
                  "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                  "CLANG_CXX_LANGUAGE_STANDARD":"c++17",
                  "CLANG_CXX_LIBRARY": "libc++"
              },
          }],
      ]
    }
  ]
}