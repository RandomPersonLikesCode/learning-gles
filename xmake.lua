--- @diagnostic disable: undefined-global

local src_root = "app/src/jni"
local arch = "arm64-v8a"
local sdk = os.getenv("ANDROID_HOME")

if is_arch("armeabi-v7a") then
  arch = "armeabi-v7a"
end

local sdl_root = sdk .. "/lib/SDL3/" .. arch

set_project("learn-gles")
set_version("1.0.0")

add_rules("mode.debug", "mode.release")

set_allowedplats("android")
set_allowedarchs({"armeabi-v7a", "arm64-v8a"})
set_defaultplat("android")
set_defaultarchs("arm64-v8a")
set_defaultmode("debug")

set_kind("shared")
set_languages("cxx23")

set_warnings("allextra", "pedantic")

add_cxxflags({
  "-fno-rtti",
  "-fno-exceptions"
})
add_shflags({
  "-Wl,--as-needed",
  "-Wl,--no-undefined",
})

add_sysincludedirs({
  "third_party/include",
  sdk .. "/include"
})
add_linkdirs({
  sdl_root
})

target("main")
  set_objectdir("build/obj")
  set_targetdir("build/lib/" .. arch)

  add_files({
    src_root .. "/**.cc",
    "third_party/lib/**.cpp"
  })

  add_links({
    "c++_static",
    "android",
    "log",
    "EGL",
    "GLESv3",
    "SDL3"
  })

  if is_mode("release") then
    set_strip("all")
    set_symbols("hidden")
    set_optimize("fastest")
    add_defines({
      "SDL_ASSERT_LEVEL=0",
      "NDEBUG"
    })
    add_cxxflags({
      "-ffunction-sections",
      "-fdata-sections",
      "-flto=thin"
    })
    add_shflags({
      "-Wl,--gc-sections",
      "-flto=thin"
    })
  else -- Debug
    set_symbols("debug", "hidden")
    set_optimize("none")
    add_defines("SDL_ASSERT_LEVEL=3")
  end
