#include <fmt/chrono.h>
#include <fmt/format.h>

#include "config.h"

int static globalVar = 2;
int globalVar2 = 0;
int globalVar3 = 5;
int const globalVar4 = 78 ;


void foo() { fmt::print("Hello from foo!\\n"); }


int main(int argc, char **argv) {

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", tea::PROJECT_NAME);

    /* INSERT YOUR CODE HERE */

    /// Teil 1 Globale Variable
    fmt::print("Adresse, {}\n", fmt::ptr(&globalVar)); // Adresse Verändert sich, wenn Programm neu ausgeführt wird
    fmt::print("Adresse, {}\n", fmt::ptr(&globalVar2));
    fmt::print("Adresse, {}\n", fmt::ptr(&globalVar3));
    fmt::print("Adresse, {}\n", fmt::ptr(&globalVar4));
                                                        /** 
                                                         * Hello, exercise-001!
                                                         * Adresse, 0x5d1ce6338020
                                                         * Adresse, 0x5d1ce633802c
                                                         * Adresse, 0x5d1ce6338024
                                                         * Adresse, 0x5d1ce6338030
                                                        */

                                                        /** Adressen mit static und const (static braucht viel mehr Speicherplatz etwa 8kb)
                                                         * Hello, exercise-001!
                                                         * Adresse, 0x5ecf95996024
                                                         * Adresse, 0x5ecf9599402c
                                                         * Adresse, 0x5ecf95996020
                                                         * Adresse, 0x5ecf9599602c
                                                        */

    
    /// Teil 2 Lokale Variablen
    int localVar = 2;
    int localVar2 = 3;
    int localVar3 = 4;
    int static localVar4 = 5;
    int const localVar5 = 6;

    fmt::print("Adresse LocalVar, {}\n", fmt::ptr(&localVar));
    fmt::print("Adresse LocalVar2, {}\n", fmt::ptr(&localVar2));
    fmt::print("Adresse LocalVar3, {}\n", fmt::ptr(&localVar3));
    fmt::print("Adresse LocalVar4, {}\n", fmt::ptr(&localVar4));
    fmt::print("Adresse LocalVar5, {}\n", fmt::ptr(&localVar5));

                                                        /** Adressen mit static und const (static braucht viel mehr Speicherplatz etwa 8kb)
                                                         *Adresse LocalVar, 0x7ffcbe5b0f3c
                                                         *Adresse LocalVar2, 0x7ffcbe5b0f38
                                                         *Adresse LocalVar3, 0x7ffcbe5b0f34
                                                         *Adresse LocalVar4, 0x640face43028
                                                         *Adresse LocalVar5, 0x7ffcbe5b0f30
                                                        */
                                                       /**Erkenntnis: Neue lokale Variablen werden auf niedriger Adressen als vorherige gelegt.
                                                         * Stack wächst nach unten.
                                                         * Globale Variablen liegen auf dem Datasegment und nicht auf dem Segment
                                                         */
                                            
                                                        
    /// Teil 3 Dynamisch allozierte Variablen (Heap)

    int* heapVar = new int(3);
    fmt::print("Adresse heapVar, {}\n", fmt::ptr(&heapVar));
    fmt::print("Inhalt heapVar, {}\n", *heapVar);

                                                        /**Erkenntnis: New int reserviert Speicher für den int auf dem Heap
                                                         * Ausgabe:
                                                         * Adresse heapVar, 0x7ffc99028ca0
                                                         * Inhalt heapVar, 3
                                                         * Der Heap speichert es bis man mit einem Befehl es wieder herauslöscht.
                                                         */
    delete heapVar;     // Speicher wieder freigeben                                      


    /// Teil 4 Funktionen (Code-Segment)
    fmt::print("Adresse von foo: {}\\n", fmt::ptr(&foo));

    /// Zusatz

/*
Fazit Speicher und Variablen

1. Speicherorte:

- Globale Variablen: Datensegment (existieren während der gesamten Programmlaufzeit)
- Lokale Variablen: Stack (werden beim Funktionsaufruf erzeugt und nach Rückkehr gelöscht)
- Dynamische Variablen (new): Heap (müssen mit delete freigegeben werden)
- Funktionen: Code-Segment (Programmcode)

2. Stack vs. Heap:

- Stack: schnell, automatisch verwaltet
- Heap: flexibel, manuell verwaltet, fehleranfällig (Memory Leaks, doppelte Freigabe)

3. Zeiger:

- Speichern Adressen von Variablen (Stack, Heap, global)
- Ermöglichen Zugriff auf dynamische Daten und flexible Speicherverwaltung

4. Skizze Arbeitsspeicher:

+---------------------+  <- hohe Adressen
| Stack               |  -> lokale Variablen
|  localVar, ...      |
+---------------------+
| Heap                |  -> dynamisch allozierte Variablen
|  heapVar            |
+---------------------+
| Datensegment        |  -> globale & static Variablen
|  globalVar, ...     |
+---------------------+
| Code-Segment        |  -> ausführbarer Programmcode
|  foo(), main(), ... |
+---------------------+  <- niedrige Adressen
*/



    return 0; /* exit gracefully*/
}


