#ifndef HOSPITAL
#define HOSPITAL
using namespace std;
#include <string>
#include <vector>
#include <map>

#include "./doctor.hh"
#include "./patient.hh"
#include "./nurse.hh"
#include "./driver.hh"
#include "./ambulance.hh"
#include "./appointment.hh"
#include "./room.hh"

class hospital
{
private:
    //map<id, object>
    static map<int, doctor> doctorsList;
    static map<int, patient> patientsList;
    static map<int, nurse> nursesList;
    static map<int, driver> driversList;
    static map<int, ambulance> ambulancesList;
    static map<int, appointment> appointmentsList;
    static map<int, room> roomsList;

    static const int doctorsLimit;
    static const int nursesLimit;
    static const int driversLimit;
    static const int ambulancesLimit;
    static const int appointmentsLimit;

    friend class doctor;
    friend class patient;
    friend class nurse;
    friend class driver;
    friend class ambulance;
    friend class appointment;
    friend class room;

public:
    static void printDoctors();
    static void printPatients();
    static void printNurses();
    static void printDrivers();
    static void printAmbulances();
    static void printAppointments();
    static void printRooms();
};

#endif // !HOSPITAL