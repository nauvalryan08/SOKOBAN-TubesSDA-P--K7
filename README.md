# Sokoban SDA
[![GitHub license](https://img.shields.io/github/license/nauvalryan08/SOKOBAN-TubesSDA-P--K7?logo=opensourceinitiative&logoColor=white&style=flat-square)](https://github.com/nauvalryan08/SOKOBAN-TubesSDA-P--K7/blob/main/LICENSE)
[![GitHub contributors](https://img.shields.io/github/contributors/nauvalryan08/SOKOBAN-TubesSDA-P--K7?logo=github&style=flat-square)](https://github.com/nauvalryan08/SOKOBAN-TubesSDA-P--K7/graphs/contributors)
[![GitHub top language](https://img.shields.io/github/languages/top/nauvalryan08/SOKOBAN-TubesSDA-P--K7?logo=c&logoColor=white&style=flat-square)](https://github.com/nauvalryan08/SOKOBAN-TubesSDA-P--K7)
[![GitHub commit activity](https://img.shields.io/github/commit-activity/m/nauvalryan08/SOKOBAN-TubesSDA-P--K7?logo=git&logoColor=white&style=flat-square)](https://github.com/nauvalryan08/SOKOBAN-TubesSDA-P--K7/commits)
[![GitHub stars](https://img.shields.io/github/stars/nauvalryan08/SOKOBAN-TubesSDA-P--K7?logo=github&style=social)](https://github.com/nauvalryan08/SOKOBAN-TubesSDA-P--K7/stargazers)

Sebuah implementasi game Sokoban berbasis terminal yang dikembangkan sebagai tugas besar mata kuliah Struktur Data dan Algoritma.

## Deskripsi

Sokoban SDA adalah sebuah game berbasis terminal yang dikembangkan sebagai tugas besar mata kuliah Struktur Data dan Algoritma. Game ini mengimplementasikan berbagai struktur data seperti **Linked List**, **Stack**, **Queue**, dan **Tree** dalam sistem permainan Sokoban — sebuah permainan klasik di mana pemain harus mendorong kotak ke lokasi tujuan dengan strategi dan urutan langkah yang tepat.

## Fitur Utama

- **Interface Terminal**: Game berjalan langsung di terminal/command line
- **Implementasi Struktur Data**: Menggunakan berbagai struktur data fundamental:
  - Array (2 dimensi)
  - Linked List
  - Stack
  - Queue
  - Tree

## Cara Bermain

1. Gunakan tombol arrow keys untuk menggerakkan karakter
2. Dorong kotak-kotak (biasanya ditandai dengan simbol tertentu) ke posisi tujuan
3. Selesaikan level dengan menempatkan semua kotak di lokasi yang tepat

### Kontrol Permainan
- **↑** - Bergerak ke atas
- **↓** - Bergerak ke bawah
- **←** - Bergerak ke kiri
- **→** - Bergerak ke kanan
- **U** - Undo langkah terakhir
- **R** - Restart level
- **Q** - Keluar dari permainan

## Instalasi [![Windows](https://custom-icon-badges.demolab.com/badge/Windows-0078D6?logo=windows11&logoColor=white&style=flat-square)](#) [![PSH](https://img.shields.io/badge/Powershell-2CA5E0?style=flat-square&logo=powershell&logoColor=white)](#) [![Cmake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=flat-square&logo=cmake&logoColor=white)](#)

```bash
# Clone repository
git clone https://github.com/nauvalryan08/SOKOBAN-TubesSDA-P--K7.git
cd .\SOKOBAN-TubesSDA-P--K7\SOKOBANGAME

# Compile Cmake & make
cd .\UTILS\build.ps1
# Compile GCC
cd .\UTILS\compilewithoutcmake.bat
```
### Requirement / Kebutuhan Instalasi
- Cmake
- make
- gcc

## Compile Menggunakan [![Dev C++](https://img.shields.io/badge/Dev%20C++-FF2B22?style=flat-square)](#)
Jika Mingw64 sudah tersedia di perangkat skip saja langkah 1 - 8, lanjut ke bagian proses pengaturan compiler Dev C++
1. Download Mingw64 menggunakan [Installer Berikut](https://github.com/Vuniverse0/mingwInstaller/releases/download/1.2.1/mingwInstaller.exe)
2. Buka aplikasi installer lalu pilih versi yang terbaru(15.1.0), lalu klik next
3. Pilih arsitektur pada installer sesuai dengan laptop yang digunakan untuk instalasi (Biasanya 64-bit), lalu klik next
4. Pilih Posix untuk opsi thread model, lalu klik next
5. Pilih build revision rev0 dan klik next
6. Pilih msvcrt untuk C runtime (dikarenakan microsoft C runtime)
7. Pilih path untuk instalasi Mingw64 sesuai keinginan (PATH HARUS DI INGAT KARENA PENTING UNTUK SETTING COMPILER DEV C++!), lalu klik process
8. Tunggu process download
---
### Proses Pengaturan Compiler Dev C++
Untuk Dev C++ menggunakan versi [berikut](https://github.com/Embarcadero/Dev-Cpp/releases/download/v6.3/Embarcadero_Dev-Cpp_6.3_No_Compiler_Setup.exe)
1. Buka Dev C++ dan Buka opsi berikut: Tools > Compiler Options
2. -
3. -

## Tim Pengembang
- **[Johan Muhammad Avicenna]** dengan NIM 241524013
- **[Muhamad Sopiana Argiansah]** dengan NIM 241524016
- **[Naufal Khairiyan]** dengan NIM 241524021

## Lisensi

Project ini dilisensikan di bawah MIT License - lihat file [LICENSE](LICENSE) untuk detail lengkap.

---

*Dikembangkan sebagai tugas besar mata kuliah Struktur Data dan Algoritma*
