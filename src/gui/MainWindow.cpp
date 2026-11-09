#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "gui/MainWindow.h"
#include "controller/SearchEngine.h"
#include "model/Appointment.h"
#include "utils/IDGenerator.h"

#include <exception>
#include <stdexcept>
#include <sstream>

namespace scapms::gui {
namespace {
constexpr char WindowClassName[] = "SCAPMSMainWindow";
constexpr int MainMenuId = 100;
constexpr int PatientMenuId = 101;
constexpr int AppointmentMenuId = 102;
constexpr int AdminMenuId = 103;
constexpr int PatientAddId = 201;
constexpr int PatientDeleteId = 202;
constexpr int PatientRefreshId = 203;
constexpr int AppointmentScheduleId = 301;
constexpr int AppointmentCancelId = 302;
constexpr int AppointmentRefreshId = 303;
constexpr int QueueAddId = 401;
constexpr int QueueCallId = 402;
constexpr int SelectionSortId = 403;
constexpr int InsertionSortId = 404;
constexpr int UndoId = 405;
constexpr int SaveId = 406;
constexpr int LoadId = 407;
constexpr int SearchId = 408;
constexpr int ReportsId = 409;
constexpr int PatientTypeId = 501;
constexpr int PatientNameId = 502;
constexpr int PatientAgeId = 503;
constexpr int PatientContactId = 504;
constexpr int PatientIdId = 505;
constexpr int AppointmentDateId = 506;
constexpr int AppointmentTimeId = 507;
constexpr int SortFieldId = 508;
constexpr int SearchModeId = 509;
constexpr int SearchQueryId = 510;
}

MainWindow::MainWindow() : window(nullptr), output(nullptr), page(Page::Home) {}

void MainWindow::run() {
    HINSTANCE instance = GetModuleHandleA(nullptr);
    WNDCLASSA windowClass{};
    windowClass.lpfnWndProc = windowProcedure;
    windowClass.hInstance = instance;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
    windowClass.lpszClassName = WindowClassName;

    if (!RegisterClassA(&windowClass) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        throw std::runtime_error("Could not register the application window.");
    }

    window = CreateWindowExA(
        0, WindowClassName, "SCAPMS - Clinic Management",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 940, 700,
        nullptr, nullptr, instance, this);
    if (!window) {
        throw std::runtime_error("Could not create the application window.");
    }

    ShowWindow(window, SW_SHOW);
    UpdateWindow(window);

    MSG message{};
    int result;
    while ((result = GetMessageA(&message, nullptr, 0, 0)) > 0) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
    if (result == -1) {
        throw std::runtime_error("The application message loop failed.");
    }
}

LRESULT CALLBACK MainWindow::windowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
    MainWindow* self = reinterpret_cast<MainWindow*>(GetWindowLongPtrA(window, GWLP_USERDATA));
    if (message == WM_NCCREATE) {
        auto createInfo = reinterpret_cast<CREATESTRUCTA*>(lParam);
        self = static_cast<MainWindow*>(createInfo->lpCreateParams);
        self->window = window;
        SetWindowLongPtrA(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
    }

    if (!self) {
        return DefWindowProcA(window, message, wParam, lParam);
    }

    switch (message) {
        case WM_CREATE:
            self->render();
            return 0;
        case WM_COMMAND:
            self->handleCommand(LOWORD(wParam));
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcA(window, message, wParam, lParam);
    }
}

HWND MainWindow::addControl(const char* type, const char* text, DWORD style, int x, int y, int width, int height, int id) {
    HWND control = CreateWindowExA(
        0, type, text, WS_CHILD | WS_VISIBLE | style, x, y, width, height,
        window, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)),
        GetModuleHandleA(nullptr), nullptr);
    if (!control) {
        throw std::runtime_error("Could not create a window control.");
    }
    controls.push_back(control);
    return control;
}

void MainWindow::clearControls() {
    for (HWND control : controls) {
        DestroyWindow(control);
    }
    controls.clear();
    output = nullptr;
}

void MainWindow::render() {
    clearControls();

    addControl("STATIC", "Smart Clinic Appointment & Patient Management System",
               SS_LEFT, 24, 18, 850, 32, 0);
    addControl("BUTTON", "Dashboard", BS_PUSHBUTTON, 24, 60, 130, 32, MainMenuId);
    addControl("BUTTON", "Patients", BS_PUSHBUTTON, 164, 60, 130, 32, PatientMenuId);
    addControl("BUTTON", "Appointments", BS_PUSHBUTTON, 304, 60, 150, 32, AppointmentMenuId);
    addControl("BUTTON", "Administration", BS_PUSHBUTTON, 464, 60, 150, 32, AdminMenuId);

    switch (page) {
        case Page::Home:
            addControl("STATIC", "Clinic overview", SS_LEFT, 24, 112, 850, 24, 0);
            createOutput(24, 144, 850, 470);
            SetWindowTextA(output, dashboardText().c_str());
            break;
        case Page::Patients:
            renderPatients();
            break;
        case Page::Appointments:
            renderAppointments();
            break;
        case Page::Administration:
            renderAdministration();
            break;
    }
}

void MainWindow::renderPatients() {
    addControl("STATIC", "Type", SS_LEFT, 24, 112, 90, 20, 0);
    HWND type = addControl("COMBOBOX", "", CBS_DROPDOWNLIST | WS_VSCROLL, 24, 134, 150, 180, PatientTypeId);
    SendMessageA(type, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("General"));
    SendMessageA(type, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Emergency"));
    SendMessageA(type, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("FollowUp"));
    SendMessageA(type, CB_SETCURSEL, 0, 0);
    addControl("STATIC", "Name", SS_LEFT, 190, 112, 180, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 190, 134, 180, 26, PatientNameId);
    addControl("STATIC", "Age", SS_LEFT, 386, 112, 90, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER, 386, 134, 90, 26, PatientAgeId);
    addControl("STATIC", "Contact", SS_LEFT, 492, 112, 180, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 492, 134, 180, 26, PatientContactId);
    addControl("BUTTON", "Register patient", BS_PUSHBUTTON, 690, 130, 160, 32, PatientAddId);

    addControl("STATIC", "Patient ID to delete", SS_LEFT, 24, 174, 160, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 24, 196, 180, 26, PatientIdId);
    addControl("BUTTON", "Delete patient", BS_PUSHBUTTON, 214, 193, 140, 32, PatientDeleteId);
    addControl("BUTTON", "Refresh list", BS_PUSHBUTTON, 364, 193, 130, 32, PatientRefreshId);
    createOutput(24, 246, 850, 368);
    SetWindowTextA(output, patientList().c_str());
}

void MainWindow::renderAppointments() {
    addControl("STATIC", "Patient ID", SS_LEFT, 24, 112, 150, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 24, 134, 170, 26, PatientIdId);
    addControl("STATIC", "Date (YYYY-MM-DD)", SS_LEFT, 210, 112, 170, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 210, 134, 170, 26, AppointmentDateId);
    addControl("STATIC", "Time (HH:MM)", SS_LEFT, 396, 112, 140, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 396, 134, 140, 26, AppointmentTimeId);
    addControl("BUTTON", "Schedule", BS_PUSHBUTTON, 552, 130, 110, 32, AppointmentScheduleId);
    addControl("BUTTON", "Cancel", BS_PUSHBUTTON, 672, 130, 100, 32, AppointmentCancelId);
    addControl("BUTTON", "Refresh list", BS_PUSHBUTTON, 24, 178, 130, 32, AppointmentRefreshId);
    createOutput(24, 226, 850, 388);
    SetWindowTextA(output, appointmentList().c_str());
}

void MainWindow::renderAdministration() {
    addControl("STATIC", "Patient ID for waiting queue", SS_LEFT, 24, 112, 230, 20, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 24, 134, 190, 26, PatientIdId);
    addControl("BUTTON", "Add to queue", BS_PUSHBUTTON, 226, 130, 130, 32, QueueAddId);
    addControl("BUTTON", "Call next patient", BS_PUSHBUTTON, 366, 130, 150, 32, QueueCallId);

    addControl("STATIC", "Sort patients by", SS_LEFT, 24, 178, 130, 20, 0);
    HWND sortField = addControl("COMBOBOX", "", CBS_DROPDOWNLIST | WS_VSCROLL, 24, 200, 150, 120, SortFieldId);
    SendMessageA(sortField, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Name"));
    SendMessageA(sortField, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("ID"));
    SendMessageA(sortField, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Age"));
    SendMessageA(sortField, CB_SETCURSEL, 0, 0);
    addControl("BUTTON", "Selection sort", BS_PUSHBUTTON, 190, 197, 140, 32, SelectionSortId);
    addControl("BUTTON", "Insertion sort", BS_PUSHBUTTON, 340, 197, 140, 32, InsertionSortId);
    addControl("BUTTON", "Undo last operation", BS_PUSHBUTTON, 490, 197, 170, 32, UndoId);
    addControl("STATIC", "Search", SS_LEFT, 24, 244, 80, 20, 0);
    HWND searchMode = addControl("COMBOBOX", "", CBS_DROPDOWNLIST | WS_VSCROLL, 24, 266, 150, 120, SearchModeId);
    SendMessageA(searchMode, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Patient ID"));
    SendMessageA(searchMode, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Name (recursive)"));
    SendMessageA(searchMode, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Name (binary)"));
    SendMessageA(searchMode, CB_SETCURSEL, 0, 0);
    addControl("EDIT", "", WS_BORDER | ES_AUTOHSCROLL, 190, 266, 190, 26, SearchQueryId);
    addControl("BUTTON", "Find patient", BS_PUSHBUTTON, 390, 263, 120, 32, SearchId);
    addControl("BUTTON", "Save data", BS_PUSHBUTTON, 530, 263, 110, 32, SaveId);
    addControl("BUTTON", "Load data", BS_PUSHBUTTON, 650, 263, 110, 32, LoadId);
    addControl("BUTTON", "Generate reports", BS_PUSHBUTTON, 24, 304, 150, 32, ReportsId);
    createOutput(24, 346, 850, 268);
    SetWindowTextA(output, dashboardText().c_str());
}

void MainWindow::createOutput(int x, int y, int width, int height) {
    output = addControl("EDIT", "", WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL |
                        ES_READONLY | WS_VSCROLL, x, y, width, height, 600);
}

std::string MainWindow::getText(int id) const {
    HWND control = GetDlgItem(window, id);
    if (!control) {
        return {};
    }
    int length = GetWindowTextLengthA(control);
    std::string text(static_cast<size_t>(length) + 1, '\0');
    GetWindowTextA(control, &text[0], length + 1);
    text.resize(static_cast<size_t>(length));
    return text;
}

void MainWindow::setOutput(const std::string& text) {
    if (output) {
        SetWindowTextA(output, text.c_str());
    }
}

std::string MainWindow::patientList() {
    std::ostringstream text;
    text << "PATIENT RECORDS\r\n"
         << "ID\tName\t\tType\tAge\tContact\r\n"
         << "---------------------------------------------------------------\r\n";
    const auto& patients = manager.getDatabase().getPatients();
    if (patients.empty()) {
        text << "No patients are registered.\r\n";
    }
    for (const auto* patient : patients) {
        text << patient->getPatientId() << '\t' << patient->getName() << '\t'
             << patient->getPatientType() << '\t' << patient->getAge() << '\t'
             << patient->getContactInfo() << "\r\n";
    }
    return text.str();
}

std::string MainWindow::appointmentList() {
    std::ostringstream text;
    text << "APPOINTMENTS\r\nID\tPatient ID\tDate\t\tTime\tStatus\r\n"
         << "---------------------------------------------------------------\r\n";
    const auto& appointments = manager.getDatabase().getAppointments();
    if (appointments.empty()) {
        text << "No appointments are scheduled.\r\n";
    }
    for (const auto& appointment : appointments) {
        text << appointment.getAppointmentId() << '\t' << appointment.getPatientId() << '\t'
             << appointment.getDate() << '\t' << appointment.getTime() << '\t'
             << appointment.getStatus() << "\r\n";
    }
    return text.str();
}

std::string MainWindow::dashboardText() {
    std::ostringstream text;
    const auto& patients = manager.getDatabase().getPatients();
    const auto& appointments = manager.getDatabase().getAppointments();
    text << "Welcome to SCAPMS.\r\n\r\n"
         << "Registered patients: " << patients.size() << "\r\n"
         << "Appointments: " << appointments.size() << "\r\n"
         << "Waiting queue: " << manager.getDatabase().getWaitingQueueCopy().size() << "\r\n\r\n"
         << "Use the navigation buttons above to manage patients, appointments, and clinic administration.";
    return text.str();
}

std::string MainWindow::reportText() {
    std::ostringstream text;
    int general = 0;
    int emergency = 0;
    int followUp = 0;
    for (const auto* patient : manager.getDatabase().getPatients()) {
        const std::string type = patient->getPatientType();
        if (type == "General") {
            ++general;
        } else if (type == "Emergency") {
            ++emergency;
        } else if (type == "FollowUp") {
            ++followUp;
        }
    }

    int pending = 0;
    int completed = 0;
    int cancelled = 0;
    text << "CLINIC REPORTS\r\n\r\n"
         << "Patient category distribution\r\n"
         << "General: " << general << "\r\n"
         << "Emergency: " << emergency << "\r\n"
         << "Follow-up: " << followUp << "\r\n"
         << "Total patients: " << (general + emergency + followUp) << "\r\n\r\n"
         << "Appointments\r\n";

    for (const auto& appointment : manager.getDatabase().getAppointments()) {
        if (appointment.getStatus() == "Scheduled") {
            ++pending;
            text << "Pending: " << appointment.getPatientId() << " - "
                 << appointment.getDate() << " " << appointment.getTime() << "\r\n";
        } else if (appointment.getStatus() == "Completed") {
            ++completed;
        } else if (appointment.getStatus() == "Cancelled") {
            ++cancelled;
        }
    }
    text << "\r\nDaily summary\r\n"
         << "Total appointments: " << manager.getDatabase().getAppointments().size() << "\r\n"
         << "Scheduled: " << pending << "\r\n"
         << "Completed: " << completed << "\r\n"
         << "Cancelled: " << cancelled << "\r\n\r\n"
         << "Registered patients\r\n";
    for (const auto* patient : manager.getDatabase().getPatients()) {
        text << patient->getPatientId() << " - " << patient->getName()
             << " (" << patient->getPatientType() << ")\r\n";
    }
    return text.str();
}

void MainWindow::handleCommand(int commandId) {
    try {
        switch (commandId) {
            case MainMenuId:
                page = Page::Home;
                render();
                return;
            case PatientMenuId:
                page = Page::Patients;
                render();
                return;
            case AppointmentMenuId:
                page = Page::Appointments;
                render();
                return;
            case AdminMenuId:
                page = Page::Administration;
                render();
                return;
            case PatientAddId: {
                const std::string name = getText(PatientNameId);
                const std::string ageText = getText(PatientAgeId);
                const std::string contact = getText(PatientContactId);
                const LRESULT typeIndex = SendMessageA(GetDlgItem(window, PatientTypeId), CB_GETCURSEL, 0, 0);
                const char* types[] = {"General", "Emergency", "FollowUp"};
                if (name.empty() || ageText.empty() || contact.empty() || typeIndex < 0) {
                    setOutput("Enter the patient's name, age, and contact details before registering.");
                    return;
                }
                size_t parsed = 0;
                int age = std::stoi(ageText, &parsed);
                if (parsed != ageText.size()) {
                    setOutput("Age must be a whole number.");
                    return;
                }
                const std::string id = utils::IDGenerator::generatePatientId();
                manager.registerPatient(types[typeIndex], id, name, age, contact);
                setOutput("Patient registered. Generated patient ID: " + id + "\r\n\r\n" + patientList());
                return;
            }
            case PatientDeleteId:
                if (getText(PatientIdId).empty()) {
                    setOutput("Enter a patient ID to delete.");
                    return;
                }
                manager.deletePatient(getText(PatientIdId));
                setOutput("Patient deleted.\r\n\r\n" + patientList());
                return;
            case PatientRefreshId:
                setOutput(patientList());
                return;
            case AppointmentScheduleId:
                manager.scheduleAppointment(getText(PatientIdId), getText(AppointmentDateId), getText(AppointmentTimeId));
                setOutput("Appointment scheduled.\r\n\r\n" + appointmentList());
                return;
            case AppointmentCancelId:
                manager.cancelAppointment(getText(PatientIdId));
                setOutput("Appointment cancellation requested.\r\n\r\n" + appointmentList());
                return;
            case AppointmentRefreshId:
                setOutput(appointmentList());
                return;
            case QueueAddId: {
                const std::string id = getText(PatientIdId);
                auto* patient = manager.getDatabase().findPatientById(id);
                if (!patient) {
                    setOutput("Patient ID not found.");
                } else {
                    manager.getDatabase().enqueuePatient(patient);
                    setOutput("Patient added to the waiting queue.\r\n\r\n" + patientList());
                }
                return;
            }
            case QueueCallId: {
                auto* patient = manager.getDatabase().dequeuePatient();
                setOutput(patient ? "Calling next patient: " + patient->getName() + " (" + patient->getPatientId() + ")"
                                  : "The waiting queue is empty.");
                return;
            }
            case SelectionSortId:
            case InsertionSortId: {
                const LRESULT fieldIndex = SendMessageA(GetDlgItem(window, SortFieldId), CB_GETCURSEL, 0, 0);
                if (fieldIndex < 0) {
                    setOutput("Select a field to sort by.");
                    return;
                }
                const int field = static_cast<int>(fieldIndex) + 1;
                if (commandId == SelectionSortId) {
                    manager.sortPatientsBySelection(field);
                } else {
                    manager.sortPatientsByInsertion(field);
                }
                setOutput("Patient records sorted.\r\n\r\n" + patientList());
                return;
            }
            case UndoId:
                setOutput(manager.undoLastOperation() ? "The last operation was undone.\r\n\r\n" + patientList()
                                                      : "There is no operation to undo.");
                return;
            case SaveId:
                manager.saveData("clinic_data.txt");
                setOutput("Clinic data saved to clinic_data.txt.");
                return;
            case LoadId:
                manager.loadData("clinic_data.txt");
                setOutput("Clinic data loaded from clinic_data.txt.\r\n\r\n" + patientList());
                return;
            case SearchId: {
                const std::string query = getText(SearchQueryId);
                const LRESULT mode = SendMessageA(GetDlgItem(window, SearchModeId), CB_GETCURSEL, 0, 0);
                if (query.empty() || mode < 0) {
                    setOutput("Enter a search term and choose a search method.");
                    return;
                }
                const auto& patients = manager.getDatabase().getPatients();
                model::PatientRecord* patient = nullptr;
                if (mode == 0) {
                    patient = controller::SearchEngine::linearSearchById(patients, query);
                } else if (mode == 1) {
                    patient = controller::SearchEngine::recursiveSearchByName(patients, query);
                } else {
                    patient = controller::SearchEngine::binarySearchByName(patients, query);
                }
                if (patient) {
                    std::ostringstream result;
                    result << "Patient found\r\nID: " << patient->getPatientId()
                           << "\r\nName: " << patient->getName()
                           << "\r\nType: " << patient->getPatientType()
                           << "\r\nAge: " << patient->getAge()
                           << "\r\nContact: " << patient->getContactInfo();
                    setOutput(result.str());
                } else {
                    setOutput(mode == 2 ? "Patient not found. Binary name search requires the patient list to be sorted by name."
                                        : "Patient not found.");
                }
                return;
            }
            case ReportsId:
                setOutput(reportText());
                return;
            default:
                return;
        }
    } catch (const std::exception& error) {
        setOutput(std::string("Operation failed: ") + error.what());
    }
}

} // namespace scapms::gui
