# Smart Clinic Appointment & Patient Management System (SCAPMS)

## Project Overview
SCAPMS is a modular C++ application developed for university clinic management. It manages patient records (General, Emergency, Follow-Up), appointments, waiting queues, administration undo stacks, recent patient caches, searching/sorting algorithms, exception handling, and file persistence.

## Architecture
- **Model**: `PatientRecord`, `GeneralPatient`, `EmergencyPatient`, `FollowUpPatient`, `Appointable`, `Appointment`, `ClinicDatabase`
- **Controller**: `ClinicManager`, `SearchEngine`
- **GUI Panels**: `MainWindow`, `PatientPanel`, `AppointmentPanel`, `AdminPanel`
- **Utilities**: `IDGenerator`, `FileHandler`, `Exceptions`