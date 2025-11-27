#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>
#include <string>

typedef enum {
    STATE_OBEN = 0,
    STATE_UNTEN,
    STATE_FAHRE_HOCH,
    STATE_FAHRE_RUNTER,
    STATE_STOP_AUF_WEG_HOCH,
    STATE_STOP_AUF_WEG_RUNTER
} Garagen_States;

typedef enum {
    EVENT_NONE = 0,
    EVENT_TASTER,       // Fernbedienung Taste gedrückt
    EVENT_ENDSCHALTER_OBEN,
    EVENT_ENDSCHALTER_UNTEN
} Garagen_Events;

// Hilfsfunktion: State-Name als String
const char* stateName(Garagen_States s) {
    switch (s) {  
        case STATE_OBEN: return "OBEN (Tor offen)";
        case STATE_UNTEN: return "UNTEN (Tor zu)";
        case STATE_FAHRE_HOCH: return "FAHRE_HOCH (Tor fährt hoch)";
        case STATE_FAHRE_RUNTER: return "FAHRE_RUNTER (Tor fährt runter)";
        case STATE_STOP_AUF_WEG_HOCH: return "STOP_AUF_WEG_HOCH (Stop beim Hochfahren)";
        case STATE_STOP_AUF_WEG_RUNTER: return "STOP_AUF_WEG_RUNTER (Stop beim Runterfahren)";
        default: return "UNBEKANNT";
    }
}

// Aktionen (nur zur Anzeige; in embedded würde hier Motorsteuerung erfolgen)
void motor_stop() { fmt::print("[AKTION] Motor stoppen\n"); }
void motor_up()   { fmt::print("[AKTION] Motor: hochfahren\n"); }
void motor_down() { fmt::print("[AKTION] Motor: runterfahren\n"); }

// Die State-Maschine: verarbeitet ein Ereignis und ändert ggf. den Zustand.
// Gibt true zurück, wenn Zustand geändert wurde.
bool stateMachine(Garagen_States &state, Garagen_Events event)
{
    bool changed = false;

    switch (state)
    {
        case STATE_OBEN:
            if (event == EVENT_TASTER) {
                // Von Oben -> Fahre runter
                motor_down();
                fmt::print("Übergang: OBEN -> FAHRE_RUNTER\n");
                state = STATE_FAHRE_RUNTER;
                changed = true;
            } else {
                // keine Aktion sonst
            }
            break;

        case STATE_UNTEN:
            if (event == EVENT_TASTER) {
                // Von Unten -> Fahre hoch
                motor_up();
                fmt::print("Übergang: UNTEN -> FAHRE_HOCH\n");
                state = STATE_FAHRE_HOCH;
                changed = true;
            } else {
                // keine Aktion sonst
            }
            break;

        case STATE_FAHRE_RUNTER:
            if (event == EVENT_ENDSCHALTER_UNTEN) {
                // erreicht unten
                motor_stop();
                fmt::print("Übergang: FAHRE_RUNTER -> UNTEN\n");
                state = STATE_UNTEN;
                changed = true;
            } else if (event == EVENT_TASTER) {
                // Stop auf dem Weg nach unten
                motor_stop();
                fmt::print("Übergang: FAHRE_RUNTER -> STOP_AUF_WEG_RUNTER\n");
                state = STATE_STOP_AUF_WEG_RUNTER;
                changed = true;
            } else if (event == EVENT_ENDSCHALTER_OBEN) {
                // Sicherheitsfall: falls irrtümlich Endschalter oben kommt -> stoppe
                motor_stop();
                fmt::print("FAHRE_RUNTER: Endschalter oben aktiviert (ungewöhnlich) -> STOP_AUF_WEG_RUNTER\n");
                state = STATE_STOP_AUF_WEG_RUNTER;
                changed = true;
            }
            break;

        case STATE_FAHRE_HOCH:
            if (event == EVENT_ENDSCHALTER_OBEN) {
                motor_stop();
                fmt::print("Übergang: FAHRE_HOCH -> OBEN\n");
                state = STATE_OBEN;
                changed = true;
            } else if (event == EVENT_TASTER) {
                // Stop auf dem Weg nach oben
                motor_stop();
                fmt::print("Übergang: FAHRE_HOCH -> STOP_AUF_WEG_HOCH\n");
                state = STATE_STOP_AUF_WEG_HOCH;
                changed = true;
            } else if (event == EVENT_ENDSCHALTER_UNTEN) {
                // Sicherheitsfall
                motor_stop();
                fmt::print("FAHRE_HOCH: Endschalter unten aktiviert (ungewöhnlich) -> STOP_AUF_WEG_HOCH\n");
                state = STATE_STOP_AUF_WEG_HOCH;
                changed = true;
            }
            break;

        case STATE_STOP_AUF_WEG_RUNTER:
            if (event == EVENT_TASTER) {
                // Taste gedrückt: umkehren -> fahre hoch
                motor_up();
                fmt::print("Übergang: STOP_AUF_WEG_RUNTER -> FAHRE_HOCH\n");
                state = STATE_FAHRE_HOCH;
                changed = true;
            } else if (event == EVENT_ENDSCHALTER_UNTEN) {
                // Falls während Stop doch Endschalter unten aktiv wird -> gehe in UNDEN Zustand
                motor_stop();
                fmt::print("Übergang: STOP_AUF_WEG_RUNTER -> UNTEN\n");
                state = STATE_UNTEN;
                changed = true;
            }
            break;

        case STATE_STOP_AUF_WEG_HOCH:
            if (event == EVENT_TASTER) {
                // Taste gedrückt: umkehren -> fahre runter
                motor_down();
                fmt::print("Übergang: STOP_AUF_WEG_HOCH -> FAHRE_RUNTER\n");
                state = STATE_FAHRE_RUNTER;
                changed = true;
            } else if (event == EVENT_ENDSCHALTER_OBEN) {
                // Falls während Stop doch Endschalter oben aktiv wird -> gehe in OBEN Zustand
                motor_stop();
                fmt::print("Übergang: STOP_AUF_WEG_HOCH -> OBEN\n");
                state = STATE_OBEN;
                changed = true;
            }
            break;

        default:
            // unbekannter Zustand -> stoppen
            motor_stop();
            fmt::print("[FEHLER] Unbekannter Zustand -> Stopping und setze auf UNTEN\n");
            state = STATE_UNTEN;
            changed = true;
            break;
    }

    return changed;
}

int main(int argc, char** argv)
{
    fmt::print("Garagentor State Machine Demo\n");
    fmt::print("Steuerbefehle: b = Taster, t = Endschalter Oben, n = Endschalter Unten, s = Status, q = quit\n\n");

    Garagen_States state = STATE_OBEN; // Start: Tor offen
    fmt::print("Startzustand: {}\n\n", stateName(state));

    std::string line;
    while (true) {
        fmt::print("> ");
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;

        char c = line[0];
        Garagen_Events ev = EVENT_NONE;

        if (c == 'b' || c == 'B') ev = EVENT_TASTER;
        else if (c == 't' || c == 'T') ev = EVENT_ENDSCHALTER_OBEN;
        else if (c == 'n' || c == 'N') ev = EVENT_ENDSCHALTER_UNTEN;
        else if (c == 's' || c == 'S') {
            fmt::print("Aktueller Zustand: {}\n", stateName(state));
            continue;
        }
        else if (c == 'q' || c == 'Q') {
            fmt::print("Beende Programm.\n");
            break;
        } else {
            fmt::print("Unbekannter Befehl: '{}'\n", c);
            continue;
        }

        bool changed = stateMachine(state, ev);
        if (!changed) {
            // Wenn kein Übergang, zeige trotzdem aktuelle Aktion / Info
            fmt::print("Keine Zustandsänderung. Aktueller Zustand: {}\n", stateName(state));
        } else {
            fmt::print("Neuer Zustand: {}\n", stateName(state));
        }
    }

    return 0;
}