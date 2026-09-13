# Learning OpenGL ES
## About

Just logs of my OpenGL ES learning journey.

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

This repo is licensed under the MIT License, this project
also usessome third party libraries, more information can
be found inside `THIRD_PARTY_LICENSE`.
