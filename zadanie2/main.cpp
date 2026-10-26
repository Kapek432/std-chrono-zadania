#include <chrono>
#include <iostream>
#include <thread>

void symulujOdpowiedzSerwera() {
    std::this_thread::sleep_for(std::chrono::milliseconds{120});
}

int main() {
    // Zadanie 2: pełna treść i przypadki do sprawdzenia w ../zadania.md.
    // TODO: Zmierz jedno wywołanie symulujOdpowiedzSerwera() zegarem steady_clock.
    return 0;
}
