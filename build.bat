pushd %~dp0\build
"C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe" -G "Visual Studio 14 2015 Win64" -DMAYA_VERSION=2018 ../
"C:\Program Files\JetBrains\CLion 2018.3.1\bin\cmake\win\bin\cmake.exe" --build . --config Release