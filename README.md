# MicFX dylib build

Add `native/MicFX.c`, `native/pitch.h`, `native/build.sh`, and `.github/workflows/build-micfx.yml` to the root of your existing MicFX repository (preserve the plugin files). If the iPhone Files app hides `.github`, create the workflow using GitHub's Add file > Create new file with the full path `.github/workflows/build-micfx.yml` and paste the YAML. If folders cannot be uploaded, create each file using its full path and paste its content.

On GitHub, open Actions > Build MicFX dylib. The workflow runs on relevant pushes, or select Run workflow on the default branch. Open the successful run and download the MicFX-dylib artifact; extract the ZIP to obtain MicFX.dylib. The workflow builds for iOS arm64 using Apple's iPhoneOS SDK. It has not been run here. No precompiled dylib is included.

Use a backup of your exact Discord 344.1 IPA. Inject the dylib and re-sign the IPA using Feather if supported. This native code is experimental and checks an exact executable UUID; live audio processing is not verified. Keep a clean backup and test in a private call with headphones. The dylib is for the existing Pitch Lab plugin, not a standalone app.
