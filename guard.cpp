#include <iostream>
#include <string>

// Enum for door outcomes
enum class DoorOutcome {
    SAFE_EXIT,
    TRAP,
    START_POINT
};

// Struct representing a door
struct Door {
    int id;
    std::string label;
    DoorOutcome outcome;
};

// Guard logic: decides which door to recommend based on conditions
int guardDecision(bool hasKeycard, bool alarmActive, bool guardPresent) {
    // Rule 1: If alarm is active, avoid all risk — go back to start (Door 3)
    if (alarmActive) {
        return 3;
    }

    // Rule 2: If guard is present but no keycard — trap risk, go back (Door 3)
    if (guardPresent && !hasKeycard) {
        return 3;
    }

    // Rule 3: If keycard available and no alarm — safe to exit (Door 1)
    if (hasKeycard && !alarmActive) {
        return 1;
    }

    // Rule 4: Default fallback — unknown risk, avoid trap (Door 2), return start
    return 3;
}

// Display door details
void displayDoor(const Door& door) {
    std::cout << "Door " << door.id << " [" << door.label << "]: ";
    switch (door.outcome) {
        case DoorOutcome::SAFE_EXIT:    std::cout << "Safe Exit\n"; break;
        case DoorOutcome::TRAP:         std::cout << "Trap!\n"; break;
        case DoorOutcome::START_POINT:  std::cout << "Back to Start\n"; break;
    }
}

int main() {
    // Define the three doors
    Door doors[3] = {
        {1, "Green Door",  DoorOutcome::SAFE_EXIT},
        {2, "Red Door",    DoorOutcome::TRAP},
        {3, "Blue Door",   DoorOutcome::START_POINT}
    };

    // --- Scenario Input ---
    bool hasKeycard   = true;
    bool alarmActive  = false;
    bool guardPresent = true;

    std::cout << "=== Secured Facility Guard System ===\n\n";
    std::cout << "Conditions:\n";
    std::cout << "  Has Keycard   : " << (hasKeycard   ? "Yes" : "No") << "\n";
    std::cout << "  Alarm Active  : " << (alarmActive  ? "Yes" : "No") << "\n";
    std::cout << "  Guard Present : " << (guardPresent ? "Yes" : "No") << "\n\n";

    std::cout << "Available Doors:\n";
    for (const auto& door : doors) {
        displayDoor(door);
    }

    // Guard makes a decision
    int chosenDoorId = guardDecision(hasKeycard, alarmActive, guardPresent);
    Door& chosen = doors[chosenDoorId - 1];

    std::cout << "\n>> Guard recommends: Door " << chosen.id
              << " (" << chosen.label << ")\n";
    std::cout << ">> Outcome: ";
    switch (chosen.outcome) {
        case DoorOutcome::SAFE_EXIT:   std::cout << "Proceed to Safe Exit. ✓\n"; break;
        case DoorOutcome::TRAP:        std::cout << "WARNING: This is a trap!\n"; break;
        case DoorOutcome::START_POINT: std::cout << "Returning to starting point.\n"; break;
    }

    return 0;
}