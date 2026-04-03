@SET VSINSTALLDIR=c:\Arquivos de programas\Microsoft Visual Studio 8
@SET VCINSTALLDIR=c:\Arquivos de programas\Microsoft Visual Studio 8\VC
@SET FrameworkDir=c:\WINDOWS\Microsoft.NET\Framework
@SET FrameworkVersion=v2.0.50727
@SET FrameworkSDKDir=c:\Arquivos de programas\Microsoft Visual Studio 8\SDK\v2.0
@if "%VSINSTALLDIR%"=="" goto error_no_VSINSTALLDIR
@if "%VCINSTALLDIR%"=="" goto error_no_VCINSTALLDIR

@echo Setting environment for using Microsoft Visual Studio 2005 x86 tools.

@rem
@rem Root of Visual Studio IDE installed files.
@rem
@set DevEnvDir=c:\Arquivos de programas\Microsoft Visual Studio 8\Common7\IDE

@set PATH=c:\Arquivos de programas\Microsoft Visual Studio 8\Common7\IDE;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\BIN;c:\Arquivos de programas\Microsoft Visual Studio 8\Common7\Tools;c:\Arquivos de programas\Microsoft Visual Studio 8\Common7\Tools\bin;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\PlatformSDK\bin;c:\Arquivos de programas\Microsoft Visual Studio 8\SDK\v2.0\bin;c:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\VCPackages;%PATH%
@set INCLUDE=c:\Arquivos de programas\Microsoft Visual Studio 8\VC\ATLMFC\INCLUDE;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\INCLUDE;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\PlatformSDK\include;c:\Arquivos de programas\Microsoft Visual Studio 8\SDK\v2.0\include;%INCLUDE%
@set LIB=c:\Arquivos de programas\Microsoft Visual Studio 8\VC\ATLMFC\LIB;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\LIB;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\PlatformSDK\lib;c:\Arquivos de programas\Microsoft Visual Studio 8\SDK\v2.0\lib;%LIB%
@set LIBPATH=c:\WINDOWS\Microsoft.NET\Framework\v2.0.50727;c:\Arquivos de programas\Microsoft Visual Studio 8\VC\ATLMFC\LIB

@goto end

:error_no_VSINSTALLDIR
@echo ERROR: VSINSTALLDIR variable is not set. 
@goto end

:error_no_VCINSTALLDIR
@echo ERROR: VCINSTALLDIR variable is not set. 
@goto end

:end
