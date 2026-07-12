#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

int main() {
    srand(time(0));
    
    int anzahlAufgaben;
    std::cout << "Wie viele Aufgaben möchtest du üben? ";
    std::cin >> anzahlAufgaben;
    
    int richtige = 0;
    
    for (int i = 1; i <= anzahlAufgaben; i++) {
        int a = rand() % 10 + 1;
        int b = rand() % 10 + 1;
        int ergebnis;
        char op;
        
        // Zufällige Operation auswählen
        int opWahl = rand() % 4;
        switch (opWahl) {
            case 0: op = '+'; ergebnis = a + b; break;
            case 1: op = '-'; ergebnis = a - b; break;
            case 2: op = '*'; ergebnis = a * b; break;
            case 3: op = '/'; 
                    // Division: a durch b teilen, a muss durch b teilbar sein
                    a = (b * (rand() % 10 + 1)); 
                    ergebnis = a / b;
                    break;
        }
        
        int benutzerAntwort;
        std::cout << "\nAufgabe " << i << ": " << a << " " << op << " " << b << " = ";
        std::cin >> benutzerAntwort;
        
        if (benutzerAntwort == ergebnis) {
            std::cout << "Richtig!";
            richtige++;
        } else {
            std::cout << "Falsch! Das richtige Ergebnis ist " << ergebnis;
        }
    }
    
    std::cout << "\n\nZusammenfassung: " << richtige << " von " << anzahlAufgaben << " richtig.";
    double prozent = (double(richtige) / anzahlAufgaben) * 100;
    std::cout << " (" << prozent << "%)\n";
    
    return 0;
}
