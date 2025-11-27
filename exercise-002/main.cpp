#include <fmt/chrono.h>
#include <fmt/format.h>
#include "graveyard.h"


/* .bss Segment */
int foo;
int foo2 = 0;

/* .data Segment */
int data = 45;
int data2 = 43; 
int undead = 7;


/* .rodata Segment */
const int rodata = 45;
const int rodata2 = 43;



void doSomething(int value)
{
    value = value + 1;
    fmt::print("doSomething, value {}\n", value);
}

void doSomethingPtr(int* ptr)
{
    *ptr = *ptr + 1;
    fmt::print("doSomethingPtr, value {}\n", *ptr);
}

int* doReturnAPtr()
{
    int value = 4711;
    fmt::print("doReturnAPtr, value {}\n", value);
    return &value;
}

void doSomethingStatic()
{
    static int value = 56;
    value = value + 1;
    fmt::print("doSomethingStatic, value {}\n", value);
}
auto main(int argc, char** argv) -> int
{
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", argv[0]);
    /** Aufgabe 1)
     * Frage 1: a)
     * Frage 2: b)
     * Frage 3: a) 
     * Frage 4: a)
     */

    /** Aufgabe 2)
     * Beispiel 1)
     * Was passiert technisch? 
     * Funktionsaufruf für Anzahl an SOULS; 
     * In Funktion wird einem char Pointer jedes mal Speicher zugewiesen;
     * Dann wird der Wert in dem der Pointer steht beschrieben -> dann ausgegeben;
     * In Main aufgerufen
     * Welcher Fluch entsteht? 
     * Der Speicher wird nie frei gegeben.
     * Wie kann man ihn bannen? 
     * Mit der free() Funktion direkt nach der Ausgabe 
     * 
     * Beispiel 2)
     * Was passiert technisch?
     * Im Main wird einem Pointer Speicher zugewiesen.
     * Dann wird der Wert der im Pointer steht beschrieben; 
     * dann gelöscht dann ausgegeben
     * Welcher Fluch entsteht?
     * Ich gebe dem Speicher frei -> es steht was drin, was ich nicht erwarte
     * Wie kann man ihn bannen?
     * speicher nach dem ausgeben freigeben
     * Was passiert, wenn Sie anschließend erneut Speicher allokieren?
     * Es zeigt vielleicht auf die gleiche Adresse
     * 
     * Beispiel 3)
     * Was passiert technisch?
     * Es wird unendlich oft 1024 byte Speicher zugewiesen.
     * Welcher Fluch entsteht?
     * Stack overflow / es crashed
     * Wie kann man ihn bannen?
     * Speicher freigeben, es nicht unendlich machen
     */

    /** Aufgabe 4)
     * Wann tritt ein Stack Overflow auf?
     *  Wenn der Aufrufstack eines Programms die Größe des dafür vorgesehen Speicherbereichs überschreitet.
     * Warum entstehen Memory Leaks?
     *  Wenn Programme reservierten SPeicher nicht wieder freigeben, nachdem er nicht mehr benötigt wird.
     * Was ist gefährlicher: Ein Zombie-Pointer oder ein Leak?
     *  Leak ist schlimmer, da auch andere Speicherbereiche verändert werden können
     * Wie kann man solche Fehler frühzeitig erkennen?
     *  Code lesen können und verstehen
     */


    /** Aufgabe 5)
     * Wann tritt ein Stack Overflow auf?
     *  Wenn der Aufrufstack eines Programms die Größe des dafür vorgesehen Speicherbereichs überschreitet.
     * Warum entstehen Memory Leaks?
     *  Wenn Programme reservierten SPeicher nicht wieder freigeben, nachdem er nicht mehr benötigt wird.
     * Was ist gefährlicher: Ein Zombie-Pointer oder ein Leak?
     *  Leak ist schlimmer, da auch andere Speicherbereiche verändert werden können
     * Wie kann man solche Fehler frühzeitig erkennen?
     *  Code lesen können und verstehen
     */


     /** Aufgabe 6)
     * Wie unterscheiden sich die Adressen der drei undead- Variablen?
     * 
     */
    doSomething(42);
    int bar = 42;
    doSomething(bar);
    fmt::print("The value of bar is: {}\n", bar);

    doSomethingPtr(&bar);
    fmt::print("The value of bar after doSomethingPtr is: {}\n", bar);

    int* returnedPtr = doReturnAPtr();
    fmt::print("The value of returnedPtr content  after doReturnAPtr is: {}\n", *returnedPtr);
    doSomething(42);
    fmt::print("The value of returnedPtr content  after doReturnAPtr is: {}\n", *returnedPtr);

    doSomethingStatic();
    doSomethingStatic();
    doSomethingStatic();
    doSomethingStatic();

    fmt::print("Value of foo {} address of foo {}\n", foo, fmt::ptr(&foo));
    fmt::print("Value of foo2 {} address of foo2 {}\n", foo2, fmt::ptr(&foo2));
    fmt::print("Value of data {} address of data {}\n", data, fmt::ptr(&data));
    fmt::print("Value of data2 {} address of data2 {}\n", data2, fmt::ptr(&data2));
    fmt::print("Value of rodata {} address of rodata {}\n", rodata, fmt::ptr(&rodata));
    fmt::print("Value of rodata2 {} address of rodata2 {}\n", rodata2, fmt::ptr(&rodata2));

    int var;
    static int var2;
    fmt::print("Value of var {} address of var {}\n", var, fmt::ptr(&var));
    fmt::print("Value of var2 {} address of var2 {}\n", var2, fmt::ptr(&var2));


    fmt::println("🪦 Globale Variable sagt: {}", undead);
    awaken();
    persistent();
    persistent();
    fmt::println("🪦 Globale Variable nach Aufruf: {}", undead);

    return 0; /* exit gracefully*/

}
