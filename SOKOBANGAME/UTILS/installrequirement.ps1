echo "Menginstall Chocolatey (Package manager untuk windows)"
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
choco install cmake.install
choco install make
choco install mingw
echo "Instalasi Requirement Build/Compile Berhasil!"
