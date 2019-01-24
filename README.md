![ObjectARX2019](https://img.shields.io/badge/ObjectARX-2019-brightgreen.svg)
![BuildPassing](https://img.shields.io/badge/build-passing-brightgreen.svg)
![AutoCAD2019](https://img.shields.io/badge/AutoCAD-2019-blue.svg)


# HLRNetSample

This is Managed HLR sample for AutoCAD HLR C++ Program

## Prerequisite
- ObjectARX 2019 SDK
- Visual Studio 2017 Professional or Community
- AutoCAD 2019
## Building Sample
- `git clone https://github.com/MadhukarMoogala/HLRNetSample.git`
- `cd HLRNetSample`
-  edit `*.vcxproj` &` *.csproj`, find `$(OARX2019)` replace with your SDK path
-  launch visual developer command prompt `devenv HlrApiMgd.sln`
- `msbuild HlrApiMgd.sln /t:build /p:Configuration=Debug;Platform=x64`

## License

This sample is licensed under the terms of the [MIT License](http://opensource.org/licenses/MIT).
Please see the [LICENSE](LICENSE) file for full details.

## Written by

Cyrille Fauvel & Madhukar Moogala (Forge Partner Development)
http://forge.autodesk.com
