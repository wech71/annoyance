# Introduction #
This project attempts to prevent applications from performing certain annoying methods. Namely stealing your focus or un-hiding your taskbar.

It does so by loading a DLL into every process and hooking certain Windows API functions.

Currently, the only tested method to achieve the DLL injection is through the [AppInit mechanism](http://support.microsoft.com/kb/197571) in Windows.
Please note, on modern versions of Windows the AppInit process is disabled by default and even if enabled should only be used to load signed DLLs. The current builds of this project are not signed and, thus, enabling the AppInit process is strongly discouraged. The current version should be considered for testing purposes only.

# Installation #
For pre Win7-tech systems the following keys need to be set:
```
LoadAppInit_DLLs(REG_DWORD) = 0x1
```
This will simply enable the AppInit DLL loading process.
```
AppInit_DLLs(REG_SZ) = <path to StopThat.dll>
```
This is a space delimited list of DLLs that should be loaded when a process starts. The path must not contain spaces.

For Win7-tech systems the following key needs to be set as well:
```
RequireSignedAppInit_DLLs(REG_DWORD) = 0x0
```
This will disable checks for signed DLLs.

These keys are located in these registry branches:
## x64 Systems ##
### for x64 processes ###
Note: `AppInit_DLLs` should point to the x64 version of `StopThat.dll`.
```
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows
```
### for x86 processes ###
Note: `AppInit_DLLs` should point to the x86 version of `StopThat.dll`.
```
HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Microsoft\Windows NT\CurrentVersion\Windows
```
## x86 Systems ##
Note: `AppInit_DLLs` should point to the x86 version of `StopThat.dll`.
```
HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows
```

The project was inspired by [this article](http://www.apriorit.com/our-experience/articles/9-sd-articles/160-apihooks) and uses the [mhook library](http://codefromthe70s.org/mhook22.aspx).