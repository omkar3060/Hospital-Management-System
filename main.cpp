#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
class Person
{
protected:
    std::string name;
    int age;

public:
    Person() {}
    Person(const std::string &name, int age) : name(name), age(age) {}
    virtual ~Person() {}

    virtual void displayDetails() const
    {
        std::cout << "Name: " << name << ", Age: " << age;
    }
    string getName()
    {
        return name;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setAge(int age)
    {
        this->age = age;
    }
};

class Staff : public Person
{
protected:
    std::string role;
    double salary;
    std::string shifts;

public:
    Staff() : Person() {}
    Staff(const std::string &name, int age, const std::string &role, double salary, const std::string &shifts)
        : Person(name, age), role(role), salary(salary), shifts(shifts) {}

    virtual void displayDetails() const override
    {
        Person::displayDetails();
        std::cout << ", Role: " << role << ", Salary: $" << salary << ", Shifts: " << shifts;
    }
    void setSalary(double sal)
    {
        salary = sal;
    }
    void setShifts(string shift)
    {
        shifts = shift;
    }
    static Staff *createStaff(const std::string &name, int age, const std::string &role, double salary, const std::string &shifts);
};

class Patient : public Person
{
private:
    int patientId;
    std::string condition;
    double medicalExpenses;

public:
    Patient(const std::string &name, int age, int patientId, const std::string &condition)
        : Person(name, age), patientId(patientId), condition(condition)
    {
        medicalExpenses = 0;
    }

    void displayDetails() const override
    {
        Person::displayDetails();
        std::cout << ", Patient ID: " << patientId << ", Condition: " << condition;
    }

    void updateMedicalExpenses(double expenses)
    {
        medicalExpenses += expenses;
    }

    double getBill() const
    {
        return medicalExpenses;
    }
    int getpid()
    {
        return patientId;
    }
};

class Doctor : public Staff
{
    std::vector<Patient *> patients;

public:
    Doctor(const std::string &name, int age, double salary, const std::string &shifts)
        : Staff(name, age, "Doctor", salary, shifts) {}

    void displayDetails() const override
    {
        Staff::displayDetails();
        std::cout << ", Specialty: " << getSpecialty();
    }

    virtual std::string getSpecialty() const
    {
        return "General Medicine";
    }

    void prescribeMedicine(Patient *patient, const std::string &medicineName)
    {
        std::cout << "Prescribing " << medicineName << " to " << patient->getName() << std::endl;
    }

    void addPatient(Patient *patient)
    {
        patients.push_back(patient);
    }
};

class Nurse : public Staff
{
public:
    Nurse(const std::string &name, int age, double salary, const std::string &shifts)
        : Staff(name, age, "Nurse", salary, shifts) {}

    void recordVitalSigns(Patient *patient, double temperature, int heartRate, int bloodPressure)
    {
        std::cout << "Recording vital signs for patient " << patient->getName() << ":\n";
        std::cout << "Temperature: " << temperature << " C\n";
        std::cout << "Heart Rate: " << heartRate << " bpm\n";
        std::cout << "Blood Pressure: " << bloodPressure << " mmHg\n";
    }
    void display()
    {
    Staff:
        displayDetails();
    }
};
class Observer
{
public:
    virtual void update(const std::string &message) = 0;
};

class Subject
{
private:
    std::vector<Observer *> observers;

public:
    void addObserver(Observer *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer)
    {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
        }
    }

    void notifyObservers(const std::string &message)
    {
        for (const auto &observer : observers)
        {
            observer->update(message);
        }
        cout << message << " " << endl;
    }
    void display()
    {
        for (int i = 0; i < observers.size(); i++)
        {
            cout << observers[i] << " ";
        }
        cout << endl;
    }
};
class Hospital : public Subject
{
private:
    std::vector<Person *> staffMembers;
    std::vector<Patient *> patients;

public:
    Hospital() {}

    void addStaffMember(Person *staffMember)
    {
        staffMembers.push_back(staffMember);
    }

    void addPatient(Patient *patient)
    {
        patients.push_back(patient);
    }

    void displayAllStaffDetails() const
    {
        std::cout << "Hospital Staff Details:\n";
        for (const auto &staffMember : staffMembers)
        {
            staffMember->displayDetails();
            std::cout << '\n';
        }
    }

    void displayAllPatientsDetails() const
    {
        std::cout << "Hospital Patient Details:\n";
        for (const auto &patient : patients)
        {
            patient->displayDetails();
            std::cout << '\n';
        }
    }

    void displayTotalBill() const
    {
        double totalBill = 0;
        for (const auto &patient : patients)
        {
            totalBill += patient->getBill();
        }
        std::cout << "Total Bill for all patients: $" << totalBill << std::endl;
    }

    Person *getStaffMembersByName(const std::string &name) const
    {
        for (const auto &staffMember : staffMembers)
        {
            if (staffMember->getName() == name)
            {
                return staffMember;
            }
        }
        return nullptr;
    }

    Patient *getPatientsByName(const std::string &name) const
    {
        for (const auto &patient : patients)
        {
            if (patient->getName() == name)
            {
                return patient;
            }
        }
        return nullptr;
    }

    void removeStaffMember(Person *staffMember)
    {
        auto it = std::find(staffMembers.begin(), staffMembers.end(), staffMember);
        if (it != staffMembers.end())
        {
            staffMembers.erase(it);
            delete staffMember;
            std::cout << "Staff member removed from the hospital." << std::endl;
        }
        else
        {
            std::cout << "Staff member not found in the hospital." << std::endl;
        }
    }
    bool searchPatientByID(Patient &p)
    {
        for (const auto &patient : patients)
        {
            if (patient->getpid() == p.getpid())
            {
                return true;
            }
        }
        return false;
    }
    ~Hospital()
    {
        for (const auto &staffMember : staffMembers)
        {
            delete staffMember;
        }

        for (const auto &patient : patients)
        {
            delete patient;
        }
    }
    void removePatient(Patient *patient)
    {
        auto it = find(patients.begin(), patients.end(), patient);
        if (it != patients.end())
        {
            patients.erase(it);
            delete patient;
            std::cout << "Patient discharged from the hospital." << std::endl;
        }
        else
        {
            std::cout << "Patient  not found in the hospital." << std::endl;
        }
    }
    void dischargePatient(const string &patientName)
    {
        Patient *patient = getPatientsByName(patientName);
        if (patient)
        {
            removePatient(patient);
            std::cout << "Patient " << patientName << " has been discharged.\n";
            std::cout << "Final Bill: $" << patient->getBill() << std::endl;
        }
        else
        {
            std::cout << "Patient with name " << patientName << " not found.\n";
        }
    }
};
class Receptionist : public Staff, public Observer, public Subject
{
public:
    Receptionist(const std::string &name, int age, double salary, const std::string &shifts)
        : Staff(name, age, "Receptionist", salary, shifts) {}

    void addPatientToDoctor(Hospital &hospital, const std::string &patientName, int patientAge, int patientId, const std::string &patientCondition, const std::string &doctorName)
    {
        Patient *newPatient = new Patient(patientName, patientAge, patientId, patientCondition);
        hospital.addPatient(newPatient);

        Doctor *doctor = dynamic_cast<Doctor *>(hospital.getStaffMembersByName(doctorName));
        if (doctor)
        {
            doctor->addPatient(newPatient);
            std::cout << "Patient " << patientName << " assigned to Doctor " << doctorName << std::endl;
            hospital.notifyObservers("New patient added: " + patientName);
        }
        else
        {
            std::cout << "Doctor with name " << doctorName << " not found. Patient not assigned." << std::endl;
            delete newPatient;
        }
    }
    void update(const std::string &message) override
    {
        std::cout << "Notification for Receptionist: " << message << std::endl;
    }
    void display()
    {
        Staff::displayDetails();
    }
};

Staff *Staff::createStaff(const std::string &name, int age, const std::string &role, double salary, const std::string &shifts)
{
    if (role == "Doctor")
    {
        return new Doctor(name, age, salary, shifts);
    }
    else if (role == "Nurse")
    {
        return new Nurse(name, age, salary, shifts);
    }
    else if (role == "Receptionist")
    {
        return new Receptionist(name, age, salary, shifts);
    }
    else
    {
        return nullptr;
    }
}

class Admin : public Staff, public Observer
{
    static Admin *instance;
    Admin() : Staff()
    {
    }
    Admin(const std::string &name, int age, const std::string &role, double salary, const std::string &shifts)
        : Staff(name, age, role, salary, shifts) {}

public:
    static Admin *getinstance()
    {
        if (!instance)
        {
            instance = new Admin("Sampreet",25,"Admin",25000,"morning");
        }
        return instance;
    }

    void addStaffMember(Hospital &hospital, const std::string &name, int age, const std::string &role, double salary, const std::string &shifts)
    {
        Staff *newStaffMember = Staff::createStaff(name, age, role, salary, shifts);
        if (newStaffMember)
        {
            hospital.addStaffMember(newStaffMember);
            std::cout << "New " << role << " named " << name << " added to the hospital." << std::endl;
        }
        else
        {
            std::cout << "Invalid role. Staff member not added to the hospital." << std::endl;
        }
    }
    void updateStaffMember(Hospital &hospital, const std::string &name, int age, double salary, const std::string &shifts)
    {
        Person *staffMember = hospital.getStaffMembersByName(name);
        if (staffMember)
        {
            staffMember->setName(name);
            staffMember->setAge(age);

            if (Doctor *doctor = dynamic_cast<Doctor *>(staffMember))
            {
                doctor->setSalary(salary);
                doctor->setShifts(shifts);
            }
            else if (Nurse *nurse = dynamic_cast<Nurse *>(staffMember))
            {
                nurse->setSalary(salary);
                nurse->setShifts(shifts);
            }
            else if (Receptionist *receptionist = dynamic_cast<Receptionist *>(staffMember))
            {
                receptionist->setSalary(salary);
                receptionist->setShifts(shifts);
            }
            std::cout << "Staff member details updated successfully." << std::endl;
        }
        else
        {
            std::cout << "Staff member with name " << name << " not found." << std::endl;
        }
    }

    void removeStaffMember(Hospital &hospital, const std::string &name)
    {
        Person *staffMember = hospital.getStaffMembersByName(name);
        if (staffMember)
        {
            hospital.removeStaffMember(staffMember);
            std::cout << "Staff member with name " << name << " removed from the hospital." << std::endl;
        }
        else
        {
            std::cout << "Staff member with name " << name << " not found." << std::endl;
        }
    }
    void update(const std::string &message) override
    {
        std::cout << "Notification for Admin: " << message << std::endl;
    }
    void display()
    {
        Staff::displayDetails();
    }
};
Admin *Admin::instance = NULL;

class StaffNotFoundException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Staff member not found in the hospital.";
    }
};

class PatientNotFoundException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Patient not found in the hospital.";
    }
};

int main()
{
    Hospital hospital;
    Admin *admin = Admin::getinstance();
    string name, name1;
    double temperature;
    int heartRate;
    int bloodPressure;
    int choice;
    do
    {
        cout << "\n===== Hospital Management System =====\n";
        cout << "\n=========== MENU =========\n";
        cout << "1. Add Staff Member\n";
        cout << "2. Display the details of a particular patient\n";
        cout << "3. Display the details of a particular staff member\n";
        cout << "4. Add Patient\n";
        cout << "5. Update Staff Member Details\n";
        cout << "6. Update Patient Medical Expenses\n";
        cout << "7. Display All Staff Details\n";
        cout << "8. Display All Patient Details\n";
        cout << "9. Display Total Bill for All Patients\n";
        cout << "10. Prescribe medicine to a patient from a doctor\n";
        cout << "11. Record vital signs of a patient\n";
        cout << "12. Notify admin from receptionist" << endl;
        cout << "13.Search patient by id" << endl;
        cout << "14. Discharge Patient" << endl;
        cout << "15. Exit\n";
        cout << "Enter your choice (1-14): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, role, shifts;
            int age;
            double salary;

            cout << "Enter staff member name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter staff member age: ";
            cin >> age;
            cout << "Enter staff member role (Doctor/Nurse/Receptionist): ";
            cin.ignore();
            getline(cin, role);
            cout << "Enter staff member salary: ";
            cin >> salary;
            cout << "Enter staff member shifts: ";
            cin.ignore();
            getline(cin, shifts);

            admin->addStaffMember(hospital, name, age, role, salary, shifts);
            break;
        }
        case 2:
            cout << "Enter patient name:" << endl;
            cin >> name;
            try
            {
                Patient *patient = hospital.getPatientsByName(name);
                if (!patient)
                {
                    throw PatientNotFoundException();
                }
                else
                {
                    patient->displayDetails();
                }
            }
            catch (const PatientNotFoundException &e)
            {
                std::cerr << "Exception caught: " << e.what() << std::endl;
            }
            break;
        case 3:
            try
            {
                cout << "Enter the name of the staff:" << endl;
                cin >> name;
                Person *staffMember = hospital.getStaffMembersByName(name);
                if (!staffMember)
                {
                    throw StaffNotFoundException();
                }
                else
                {
                    staffMember->displayDetails();
                }
            }
            catch (const StaffNotFoundException &e)
            {
                std::cerr << "Exception caught: " << e.what() << std::endl;
            }

            break;
        case 4:
        {
            string name, condition;
            int age, patientId;

            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter patient age: ";
            cin >> age;
            cout << "Enter patient ID: ";
            cin >> patientId;
            cout << "Enter patient condition: ";
            cin.ignore();
            getline(cin, condition);

            hospital.addPatient(new Patient(name, age, patientId, condition));
            break;
        }
        case 5:
        {
            string name, shifts;
            int age;
            double salary;

            cout << "Enter staff member name to update details: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter staff member age: ";
            cin >> age;
            cout << "Enter staff member salary: ";
            cin >> salary;
            cout << "Enter staff member shifts: ";
            cin.ignore();
            getline(cin, shifts);

            admin->updateStaffMember(hospital, name, age, salary, shifts);
            break;
        }
        case 6:
        {
            string name;
            double expenses;

            cout << "Enter patient name to update medical expenses: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter additional medical expenses: ";
            cin >> expenses;

            Patient *patient = hospital.getPatientsByName(name);
            if (patient)
            {
                patient->updateMedicalExpenses(expenses);
            }
            else
            {
                cout << "Patient with name " << name << " not found." << endl;
            }
            break;
        }
        case 7:
            hospital.displayAllStaffDetails();
            break;
        case 8:
            hospital.displayAllPatientsDetails();
            break;
        case 9:
            hospital.displayTotalBill();
            break;
        case 10:
            cout << "Enter patient name: ";
            cin >> name;
            cout << "Enter doctor name: ";
            cin >> name1;

            try
            {
                Doctor *doctor = dynamic_cast<Doctor *>(hospital.getStaffMembersByName(name1));
                Patient *patient = dynamic_cast<Patient *>(hospital.getPatientsByName(name));
                if (!patient)
                    throw PatientNotFoundException();
                if (!doctor)
                    throw StaffNotFoundException();

                if (doctor && patient)
                {
                    doctor->prescribeMedicine(patient, "Antibiotics");
                }
            }
            catch (const PatientNotFoundException &e)
            {
                std::cerr << "Exception caught: " << e.what() << std::endl;
            }
            break;
        case 11:

            cout << "Enter patient name: ";
            cin >> name;
            cout << "Enter the name of the nurse: ";
            cin >> name1;
            try
            {
                Nurse *nurse = dynamic_cast<Nurse *>(hospital.getStaffMembersByName(name1));
                Patient *patient = hospital.getPatientsByName(name);
                if (!nurse)
                    throw StaffNotFoundException();

                else if (!nurse)
                {
                    throw PatientNotFoundException();
                }
                if (patient)
                {
                    cout << "Enter the bloodPressure,temperature,heartRate of the patient" << endl;
                    cin >> bloodPressure >> temperature >> heartRate;
                    nurse->recordVitalSigns(patient, bloodPressure, temperature, heartRate);
                }
            }
            catch (const StaffNotFoundException &e)
            {
                std::cerr << "Exception caught: " << e.what() << std::endl;
            }
            catch (const PatientNotFoundException &e)
            {
                std::cerr << "Exception caught: " << e.what() << std::endl;
            }
            break;
        case 12:
            try
            {
                Receptionist *receptionist = dynamic_cast<Receptionist *>(hospital.getStaffMembersByName("Mike Johnson"));
                if (!receptionist)
                    throw StaffNotFoundException();
                else
                {
                    receptionist->addObserver(admin);
                    receptionist->notifyObservers("hello");
                }
            }
            catch (const StaffNotFoundException &e)
            {
                std::cerr << "Exception caught: " << e.what() << std::endl;
            }
            break;
        case 13:
            try
            {
                string name, condition;
                int age, patientId;

                cout << "Enter patient name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter patient age: ";
                cin >> age;
                cout << "Enter patient ID: ";
                cin >> patientId;
                cout << "Enter patient condition: ";
                cin.ignore();
                getline(cin, condition);
                Patient p(name, age, patientId, condition);
                if (hospital.searchPatientByID(p))
                {
                    cout << "Patient found" << endl;
                }
                else
                    throw PatientNotFoundException();
            }
            catch (const PatientNotFoundException &e)
            {
                std::cerr << "Exception caught: " << e.what() << std::endl;
            }
            break;
        case 14:
            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);
            hospital.dischargePatient(name);
            break;

        case 15:
            cout << "Thankyou!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 15);

    return 0;
}
