# OpenGL ES x SDL3 Template
## About

A basic OpenGL ES and SDL3 template project in C++ to get
started in graphics programming.

## Building
### Prerequisites

- Unix-like system
- Bash
- XMake
- OpenJDK
- Android SDK
- Android NDK

Precompiled dependencies:
- SDL3 (v3.4.14)

Make sure to have `.a` for the listed dependencies, for arm64-v8a
and armeabi-v7a architecture inside `$ANDROID_HOME/lib`. make
sure to also put necessary headers inside `$ANDROID_HOME/include`.

### Building the APK

```shell
xmake f -p android
bash ./scripts/prebuild.bash

xmake build

bash ./scripts/postbuild.bash
```

### Signing the APK

See the [apksigner documentation](https://developer.android.com/tools/apksigner) for
more information.

## License

This template is licensed under the MIT License, this project
also uses some third party libraries, more information can
be found inside `THIRD_PARTY_LICENSE`.

App icon is licensed under CC0 1.0 Universal.
