# Transaction-X

### Build

#### VCPKG

`trx-app` currently uses `vcpkg` to download and install external libraries.

Download VCPKG:

```
git clone https://github.com/microsoft/vcpkg.git
```

Configure VCPKG:

```
cd vcpkg/

./bootstrap-vcpkg.bat
```

Clone `trx-app` repository:

```
git clone https://github.com/denny0754/trx-app.git
```

Open the `trx-app` folder with your IDE of choice (e.g.: VS Code or Visual Studio).

Create a new file on the root of the project and call it: `CMakeUserPresets.json` and copy the content below:

```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "vcpkg-env",
      "hidden": true,
      "environment": {
        "VCPKG_ROOT": "C:\\vcpkg"
      }
    },
    {
      "name": "user-windows-base",
      "hidden": true,
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/out/build/${presetName}",
      "installDir": "${sourceDir}/out/install/${presetName}",
      "inherits": "vcpkg-env",
      "cacheVariables": {
        "CMAKE_C_COMPILER": "cl.exe",
        "CMAKE_CXX_COMPILER": "cl.exe",
        "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      },
      "condition": {
        "type": "equals",
        "lhs": "${hostSystemName}",
        "rhs": "Windows"
      }
    },
    {
      "name": "user-x64-debug",
      "displayName": "(User)x64 Debug",
      "inherits": "user-windows-base",
      "architecture": {
        "value": "x64",
        "strategy": "external"
      },
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug",
        "TRX_DEVELOPER_BUILD": true
      }
    },
    {
      "name": "user-x64-release",
      "displayName": "(User)x64 Release",
      "inherits": "user-x64-debug",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release",
        "TRX_DEVELOPER_BUILD": false
      }
    }
  ]
}
```

Note: `VCPKG_ROOT` should be changed to the directory in which you downloaded VCPKG.

The project is now ready to be built.