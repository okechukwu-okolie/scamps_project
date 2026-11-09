# Smart Clinic Appointment & Patient Management System (SCAPMS)

## Project Overview
SCAPMS is a modular C++ application developed for university clinic management. It manages patient records (General, Emergency, Follow-Up), appointments, waiting queues, administration undo stacks, recent patient caches, searching/sorting algorithms, exception handling, and file persistence.

## Architecture
- **Model**: `PatientRecord`, `GeneralPatient`, `EmergencyPatient`, `FollowUpPatient`, `Appointable`, `Appointment`, `ClinicDatabase`
- **Controller**: `ClinicManager`, `SearchEngine`
- **GUI Panels**: `MainWindow`, `PatientPanel`, `AppointmentPanel`, `AdminPanel`
- **Utilities**: `IDGenerator`, `FileHandler`, `Exceptions`

## Dependencies
The Windows desktop interface uses the native Win32 API, so there are no third-party library dependencies. It requires:
- CMake 3.10 or newer
- A C++17-compatible C++ compiler
- A build tool supported by the selected CMake generator

On Windows, the build steps below use MinGW-w64/MinGW (`g++` and `mingw32-make`). The current environment has CMake 4.4.5, MinGW GCC 6.3.0, and `mingw32-make` installed; no external libraries need to be installed.

## Build and run on Windows (MinGW)
Run these commands in PowerShell from the `scamps_project` folder:

```powershell
cmake -S . -B build-mingw -G "MinGW Makefiles"
cmake --build build-mingw --parallel
.\build-mingw\SCAPMS.exe
```

Use a new build folder (such as `build-mingw`) when switching generators. The existing `build` folder was configured for the NMake Makefiles generator, which requires Microsoft's NMake toolchain; it cannot be reused for a MinGW build. The application opens as a desktop window (no console menu is required). Use the Dashboard, Patients, Appointments, and Administration buttons to navigate. Patient IDs are generated when a patient is registered; the generated ID is shown in the patient panel.

To launch the program from PowerShell in the `scamps_project` folder:

```powershell
.\build-mingw\SCAPMS.exe
```

From any folder, use the full path:

```powershell
& "C:\Users\ADMIN\Documents\LAB ASSESSMENT FOR COS 202\scamps_project\build-mingw\SCAPMS.exe"
```