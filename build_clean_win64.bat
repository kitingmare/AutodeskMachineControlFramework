echo off


set GO111MODULE=off

set basepath=%~dp0
echo %basepath%
set builddir=%basepath%build_win64
set outputdir=%builddir%\Output

if not exist "%builddir%" (mkdir "%builddir%")
if not exist "%outputdir%" (mkdir "%outputdir%")
if not exist "%outputdir%\data" (mkdir "%outputdir%\data")
if not exist "%builddir%\Artifacts" (mkdir "%builddir%\Artifacts")
if not exist "%builddir%\DevPackage" (mkdir "%builddir%\DevPackage")
if not exist "%builddir%\DevPackage\Framework" (mkdir "%builddir%\DevPackage\Framework")
if not exist "%builddir%\DevPackage\Framework\HeadersDev" (mkdir "%builddir%\DevPackage\Framework\HeadersDev")
if not exist "%builddir%\DevPackage\Framework\HeadersDev\CppDynamic" (mkdir "%builddir%\DevPackage\Framework\HeadersDev\CppDynamic")
if not exist "%builddir%\DevPackage\Framework\HeadersDriver" (mkdir "%builddir%\DevPackage\Framework\HeadersDriver")
if not exist "%builddir%\DevPackage\Framework\HeadersDriver\CppDynamic" (mkdir "%builddir%\DevPackage\Framework\HeadersDriver\CppDynamic")
if not exist "%builddir%\DevPackage\Framework\InterfacesDev" (mkdir "%builddir%\DevPackage\Framework\InterfacesDev")
if not exist "%builddir%\DevPackage\Framework\PluginCpp" (mkdir "%builddir%\DevPackage\Framework\PluginCpp")
if not exist "%builddir%\DevPackage\Framework\Dist" (mkdir "%builddir%\DevPackage\Framework\Dist")
if not exist "%builddir%\DevPackage\Framework\ClientSource" (mkdir "%builddir%\DevPackage\Framework\ClientSource")
if not exist "%builddir%\Framework" (mkdir "%builddir%\Framework")
if not exist "%builddir%\Framework\HeadersDev" (mkdir "%builddir%\Framework\HeadersDev")
if not exist "%builddir%\Framework\HeadersDev\CppDynamic" (mkdir "%builddir%\Framework\HeadersDev\CppDynamic")
if not exist "%builddir%\Framework\HeadersDriver" (mkdir "%builddir%\Framework\HeadersDriver")
if not exist "%builddir%\Framework\HeadersDriver\CppDynamic" (mkdir "%builddir%\Framework\HeadersDriver\CppDynamic")
if not exist "%builddir%\Framework\InterfacesDev" (mkdir "%builddir%\Framework\InterfacesDev")
if not exist "%builddir%\Framework\PluginCpp" (mkdir "%builddir%\Framework\PluginCpp")
if not exist "%builddir%\Framework\ClientSource" (mkdir "%builddir%\Framework\ClientSource")

copy /y "%basepath%\Framework\PluginCpp\*.*" "%builddir%\Framework\PluginCpp"
if "%ERRORLEVEL%" neq "0" (
	goto ERROR
)

copy /y  "%basepath%\Framework\InterfacesDev\*.*" "%builddir%\Framework\InterfacesDev"
if "%ERRORLEVEL%" neq "0" (
	goto ERROR
)

git rev-parse --verify --short HEAD >"%builddir%\githash.txt"
SET /p GITHASH=<"%builddir%\githash.txt"
echo git hash: %GITHASH%

git rev-parse --verify HEAD >"%builddir%\longgithash.txt"
SET /p LONGGITHASH=<"%builddir%\longgithash.txt"
echo long git hash: %LONGGITHASH%

git log -n 1 --format="%%H" -- "%basepath%\Client" >"%builddir%\clientdirhash.txt"
SET /p CLIENTDIRHASH=<"%builddir%\clientdirhash.txt"
SET /p CLIENTDISTHASH=<"%basepath%\Artifacts\clientdist\_githash_client.txt"

REM Trim Strings
for /f "tokens=* delims= " %%a in ("%CLIENTDIRHASH%") do set CLIENTDIRHASH=%%a
for /l %%a in (1,1,100) do if "!CLIENTDIRHASH:~-1!"==" " set CLIENTDIRHASH=!CLIENTDIRHASH:~0,-1! 
for /f "tokens=* delims= " %%a in ("%CLIENTDISTHASH%") do set CLIENTDISTHASH=%%a
for /l %%a in (1,1,100) do if "!CLIENTDIRHASH:~-1!"==" " set CLIENTDIRHASH=!CLIENTDIRHASH:~0,-1! 

echo client hash: %CLIENTDIRHASH%
echo client dist hash: %CLIENTDISTHASH%

if "%CLIENTDIRHASH%" neq "%CLIENTDISTHASH%" (
	echo "Please rebuild client!"
	goto ERROR
)

cd /d "%basepath%"

echo "Building Resource builder (Win64)..."
set GOARCH=amd64
set GOOS=windows
go build -o "%builddir%/DevPackage/Framework/buildresources.exe" -ldflags="-s -w" "%basepath%/BuildScripts/buildresources.go"

REM echo "Building Resource builder (Linux64)..."
REM set GOARCH=amd64
REM set GOOS=linux
REM go build -o "%builddir%/DevPackage/Framework/buildresources.linux" -ldflags="-s -w" "%basepath%/BuildScripts/buildresources.go"

REM echo "Building Resource builder (LinuxARM)..."
REM set GOARCH=arm
REM set GOOS=linux
REM set GOARM=5
REM go build -o "%builddir%/DevPackage/Framework/buildresources.arm" -ldflags="-s -w" "%basepath%/BuildScripts/buildresources.go"

copy /y "%basepath%Artifacts\clientdist\clientpackage.zip" "%builddir%\Output\%GITHASH%_core.client"
if "%ERRORLEVEL%" neq "0" (
	goto ERROR
)

go run "%basepath%\BuildScripts\createPackageXML.go" "%builddir%\Output" %GITHASH% win64

cd "%builddir%"

echo "Building Core Modules"
call cmake ..
REM call cmake -G "MinGW Makefiles" ..
call cmake --build . --config Release


echo "Building Developer Package"
cd "%builddir%\DevPackage"

copy "%basepath%\Artifacts\clientdist\clientsourcepackage.zip" Framework\ClientSource\%GITHASH%_client_source.zip
if "%ERRORLEVEL%" neq "0" (
	goto ERROR
)

copy ..\githash.txt Framework\Dist\disthash.txt
copy ..\Output\amc_win32.exe Framework\Dist\
copy ..\Output\amc_server.exe Framework\Dist\
copy ..\Output\amc_server.xml Framework\Dist\
copy ..\Output\%GITHASH%_core_libmc.dll Framework\Dist\
copy ..\Output\%GITHASH%_core_lib3mf.dll Framework\Dist\
copy ..\Output\%GITHASH%_core_libmcdata.dll Framework\Dist\
copy ..\Output\%GITHASH%_core.client Framework\Dist\
copy ..\Output\%GITHASH%_*.data Framework\Dist\
copy ..\Output\%GITHASH%_package.xml Framework\Dist\
copy ..\Output\%GITHASH%_driver_*.dll Framework\Dist\
copy ..\..\Framework\HeadersDev\CppDynamic\*.* Framework\HeadersDev\CppDynamic
copy ..\..\Framework\InterfacesDev\*.* Framework\InterfacesDev
copy ..\..\Framework\PluginCpp\*.* Framework\PluginCpp
del Framework\Dist\%GITHASH%_core.data

cd %builddir%
go run "%basepath%/BuildScripts/createDevPackage.go" .\DevPackage\Framework .\DevPackage\ %LONGGITHASH% win64

copy "%builddir%\DevPackage\amcf_win64_%LONGGITHASH%.zip" "%builddir%\Artifacts\devpackage_win64.zip" /Y

echo "Build done!"

goto END

:ERROR
echo "------------------------------------------------------------"
echo "FATAL BUILD ERROR!"
echo "------------------------------------------------------------"

:END
if "%1" neq "NOPAUSE" (
	pause
)

exit 0
