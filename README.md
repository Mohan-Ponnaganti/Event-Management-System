
# Event Scheduling System

## Overview

The **Event Scheduling System** is a C++ program designed to help users manage events, participants, and reminders efficiently. it offers features like scheduling events, checking for conflicts, adding or removing participants, and sending event reminders. The system ensures that no two events conflict in terms of date and time, and provides a menu-driven interface for user interaction.

## Features

- **Add Event**: Users can schedule a new event by providing details such as event name, date, and time.
- **Delete Event**: Allows users to remove an event by its unique ID.
- **Search Event**: Retrieves event details by the event’s unique ID.
- **Add/Remove Participants**: Users can manage participants by adding or removing them from an event.
- **List Participants**: Lists all participants for a specific event.
- **Check Schedule Conflict**: Ensures that no two events overlap on the same date and time.
- **Handle Reminders**: Displays reminders for events happening on the current date.
- **Menu-Driven Interface**: User-friendly interface to easily navigate through the system's features.

## How it Works

- Events are stored in a map, where each event has a unique ID.
- Dates and times are handled using `std::chrono` to ensure proper date-time parsing and comparisons.
- The program prevents scheduling conflicts by checking the date and time before adding an event.
- A priority queue is used for handling event reminders, which are triggered on the event date.
- Multi-word inputs are managed using `getline()` to allow spaces in event names or participant names.

## Data Structures

- **Map (`std::map`)**: Used to store events with their unique IDs as keys.
- **Priority Queue (`std::priority_queue`)**: Manages event reminders, sorted by date.
- **Vector (`std::vector`)**: Stores participants of each event.

## Requirements

- A C++ compiler supporting C++11 or above.
- Basic knowledge of C++ Standard Library components such as maps, queues, and strings.

## Usage

1. **Adding an Event**:
   - Enter the event name, date (`YYYY-MM-DD` format), and time (`HH:MM` format).
   - The program will check for any scheduling conflicts before adding the event.

2. **Deleting an Event**:
   - Input the event’s unique ID to delete it from the schedule.

3. **Adding or Removing Participants**:
   - Input the event ID and the participant’s name to add or remove participants from that event.

4. **Handling Reminders**:
   - The system will automatically handle reminders for events happening on or before the current date.

## Example

```
Event Scheduling System Menu:
1. Add Event
2. Delete Event
3. Search Event
4. Add Participant
5. Remove Participant
6. List Participants
7. Check Schedule Conflict
8. Handle Reminders
9. Exit
Enter your choice: 1
Enter event name: Team Meeting
Enter event date (YYYY-MM-DD): 2024-10-10
Enter event time (HH:MM): 10:00
Event added successfully with ID: 1
```

## Future Improvements

- **Enhanced Reminder System**: Allow customization of reminder times (e.g., 1 hour or 1 day before the event).
- **Event Modification**: Enable users to edit event details like name, date, or time.
- **Recurring Events**: Add support for scheduling recurring events.

## License

This project is licensed under the MIT License. You are free to use, modify, and distribute this project, provided that you retain this license.

