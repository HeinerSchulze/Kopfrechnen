#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <limits>

int main() {
    srand(time(0));
    
    // Schwierigkeitsgrad auswählen
    int schwierigkeit;
    std::cout << "Wähle den Schwierigkeitsgrad:\n";
    std::cout << "1. Leicht (Zahlen 1-10)\n";
    std::cout << "2. Mittel (Zahlen 10-50)\n";
    std::cout << "3. Schwer (Zahlen 50-100)\n";
    std::cout << "Deine Wahl: ";
    std::cin >> schwierigkeit;
    
    int minZahl, maxZahl;
    switch (schwierigkeit) {
        case 1: minZahl = 1; maxZahl = 10; break;
        case 2: minZahl = 10; maxZahl = 50; break;
        case 3: minZahl = 50; maxZahl = 100; break;
        default:
            std::cout << "Ungültige Auswahl. Standardmäßig wird 'Leicht' gewählt.\n";
            minZahl = 1; maxZahl = 10;
    }
    
    int anzahlAufgaben;
    std::cout << "Wie viele Aufgaben möchtest du üben? ";
    std::cin >> anzahlAufgaben;
    
    int richtige = 0;
    
    for (int i = 1; i <= anzahlAufgaben; i++) {
        int a = rand() % (maxZahl - minZahl + 1) + minZahl;
        int b = rand() % (maxZahl - minZahl + 1) + minZahl;
        int ergebnis;
        char op;
        
        // Zufällige Operation auswählen
        int opWahl = rand() % 4;
        switch (opWahl) {
            case 0: op = '+'; ergebnis = a + b; break;
            case 1: op = '-'; ergebnis = a - b; break;
            case 2: op = '*'; ergebnis = a * b; break;
            case 3: op = '/'; 
                    // Division: a muss durch b teilbar sein
                    b = rand() % (maxZahl - minZahl + 1) + minZahl;
                    a = b * (rand() % (maxZahl / b) + 1); 
                    ergebnis = a / b;
                    break;
        }
        
        std::cout << "\nAufgabe " << i << ": " << a << " " << op << " " << b << " = ";
        
        // Zeitlimit von 10 Sekunden
        auto startZeit = std::chrono::steady_clock::now();
        int benutzerAntwort;
        bool zeitAbgelaufen = false;
        
        // Warte auf Eingabe oder Zeitablauf
        while (!std::cin.eof() && !zeitAbgelaufen) {
            // Prüfe, ob Eingabe verfügbar ist
            if (std::cin >> benutzerAntwort) {
                break;
            } else {
                // Fehlgeschlagene Eingabe (z. B. Buchstaben)
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                // Prüfe, ob Zeit abgelaufen ist
                auto aktuelleZeit = std::chrono::steady_clock::now();
                auto vergangeneZeit = std::chrono::duration_cast<std::chrono::seconds>(aktuelleZeit - startZeit).count();
                
                if (vergangeneZeit >= 10) {
                    zeitAbgelaufen = true;
                    break;
                }
                
                // Kurze Pause, um CPU-Last zu reduzieren
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        
        if (zeitAbgelaufen) {
            std::cout << "\nZeit abgelaufen! Das richtige Ergebnis ist " << ergebnis << "\n";
        } else {
            if (benutzerAntwort == ergebnis) {
                std::cout << "Richtig!\n";
                richtige++;
            } else {
                std::cout << "Falsch! Das richtige Ergebnis ist " << ergebnis << "\n";
            }
        }
    }
    
    std::cout << "\n\nZusammenfassung: " << richtige << " von " << anzahlAufgaben << " richtig.";
    double prozent = (double(richtige) / anzahlAufgaben) * 100;
    std::cout << " (" << prozent << "%)\n";
    
    return 0;
}
