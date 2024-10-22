#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;

struct Event {
    int id; // Unique identifier for each event
    string name;
    string date; // YYYY-MM-DD
    string time; // HH:MM
    vector<string> participants;

    bool operator<(const Event& other) const {
        return date < other.date || (date == other.date && time < other.time);
    }
};

class EventSchedulingSystem {
private:
    int nextID = 1; // Counter for generating unique IDs
    map<int, Event> events; // Map of event ID to Event
    priority_queue<pair<string, Event>, vector<pair<string, Event>>, greater<>> reminders;

    // Helper function to combine date and time into a single string
    string combineDateTime(const string& date, const string& time) {
        return date + " " + time;
    }

    // Helper function to convert string to chrono::system_clock::time_point
    chrono::system_clock::time_point parseDateTime(const string& date, const string& time) {
        tm t{};
        stringstream ss(date + " " + time);
        ss >> get_time(&t, "%Y-%m-%d %H:%M");
        return chrono::system_clock::from_time_t(mktime(&t));
    }

public:
    void addEvent(const string& name, const string& date, const string& time) {
        string dateTime = combineDateTime(date, time);
        for (const auto& event : events) {
            if (event.second.date == date && event.second.time == time) {
                cout << "Event already exists at this time." << endl;
                return;
            }
        }

        Event newEvent{nextID++, name, date, time};
        events[newEvent.id] = newEvent;

        // Add to priority queue for reminders (assuming reminder is 1 day before)
        reminders.push({date, newEvent});

        cout << "Event added successfully with ID: " << newEvent.id << endl;
    }

    void deleteEvent(int id) {
        auto it = events.find(id);
        if (it != events.end()) {
            events.erase(it);
            cout << "Event with ID " << id << " deleted successfully." << endl;
        } else {
            cout << "Event not found." << endl;
        }
    }

    void searchEvent(int id) {
        auto it = events.find(id);
        if (it != events.end()) {
            cout << "Event found: " << it->second.name << " on " << it->second.date 
                 << " at " << it->second.time << endl;
        } else {
            cout << "Event not found." << endl;
        }
    }

    void addParticipant(int id, const string& participant) {
        auto it = events.find(id);
        if (it != events.end()) {
            it->second.participants.push_back(participant);
            cout << "Participant added successfully." << endl;
        } else {
            cout << "Event not found." << endl;
        }
    }

    void removeParticipant(int id, const string& participant) {
        auto it = events.find(id);
        if (it != events.end()) {
            auto& participants = it->second.participants;
            auto pos = find(participants.begin(), participants.end(), participant);
            if (pos != participants.end()) {
                participants.erase(pos);
                cout << "Participant removed successfully." << endl;
            } else {
                cout << "Participant not found." << endl;
            }
        } else {
            cout << "Event not found." << endl;
        }
    }

    void listParticipants(int id) {
        auto it = events.find(id);
        if (it != events.end()) {
            cout << "Participants for event " << it->second.name << ":" << endl;
            for (const auto& participant : it->second.participants) {
                cout << "- " << participant << endl;
            }
        } else {
            cout << "Event not found." << endl;
        }
    }

    void checkScheduleConflict(const string& date, const string& time) {
        string dateTime = combineDateTime(date, time);
        for (const auto& event : events) {
            if (event.second.date == date && event.second.time == time) {
                cout << "Schedule conflict found for date and time: " << dateTime << endl;
                return;
            }
        }
        cout << "No schedule conflict." << endl;
    }

    void handleReminders(const string& currentDate) {
        // Assuming reminders need to be handled for the current date
        while (!reminders.empty()) {
            auto reminder = reminders.top();
            if (reminder.first <= currentDate) {
                cout << "Reminder: " << reminder.second.name << " on " << reminder.second.date 
                     << " at " << reminder.second.time << endl;
                reminders.pop();
            } else {
                break;
            }
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\nEvent Scheduling System Menu:" << endl;
            cout << "1. Add Event" << endl;
            cout << "2. Delete Event" << endl;
            cout << "3. Search Event" << endl;
            cout << "4. Add Participant" << endl;
            cout << "5. Remove Participant" << endl;
            cout << "6. List Participants" << endl;
            cout << "7. Check Schedule Conflict" << endl;
            cout << "8. Handle Reminders" << endl;
            cout << "9. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            string name, date, time, participant, currentDate;
            int id;
            switch (choice) {
                case 1:
                    cout << "Enter event name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter event date (YYYY-MM-DD): ";
                    cin >> date;
                    cout << "Enter event time (HH:MM): ";
                    cin >> time;
                    addEvent(name, date, time);
                    break;
                case 2:
                    cout << "Enter event ID to delete: ";
                    cin >> id;
                    deleteEvent(id);
                    break;
                case 3:
                    cout << "Enter event ID to search: ";
                    cin >> id;
                    searchEvent(id);
                    break;
                case 4:
                    cout << "Enter event ID: ";
                    cin >> id;
                    cout << "Enter participant name: ";
                    cin.ignore();
                    getline(cin, participant);
                    addParticipant(id, participant);
                    break;
                case 5:
                    cout << "Enter event ID: ";
                    cin >> id;
                    cout << "Enter participant name: ";
                    cin.ignore();
                    getline(cin, participant);
                    removeParticipant(id, participant);
                    break;
                case 6:
                    cout << "Enter event ID to list participants: ";
                    cin >> id;
                    listParticipants(id);
                    break;
                case 7:
                    cout << "Enter event date (YYYY-MM-DD): ";
                    cin >> date;
                    cout << "Enter event time (HH:MM): ";
                    cin >> time;
                    checkScheduleConflict(date, time);
                    break;
                case 8:
                    cout << "Enter current date (YYYY-MM-DD): ";
                    cin >> currentDate;
                    handleReminders(currentDate);
                    break;
                case 9:
                    cout << "Exiting..." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 9);
    }
};

int main() {
    EventSchedulingSystem system;
    system.menu();
    return 0;
}
