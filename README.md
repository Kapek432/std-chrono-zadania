# Czas w C++20 - projekty startowe

[Treść pięciu zadań, przykłady wyników i pomocne źródła](zadania.md).

Każdy katalog `zadanie1`–`zadanie5` zawiera niezależny projekt: `CMakeLists.txt` oraz `main.cpp` z miejscem na rozwiązanie. W zadaniu 2 przygotowana jest funkcja symulująca oczekiwanie na odpowiedź serwera, podana również w poleceniu.

Wymagane są **CMake 3.16 lub nowszy, kompilator C++20 i odpowiednia biblioteka standardowa**. Projekty wymagają C++20. Dla zadania 2 CMake dołącza obsługę wątków wymaganą przez dane środowisko.

## Budowanie pojedynczego zadania

Z terminala otwartego w katalogu `std-chrono-zadania` wykonaj, na przykład dla zadania 1:

```sh
cmake -S zadanie1 -B zadanie1/build
cmake --build zadanie1/build --config Debug
```

Uruchom program na Linuxie lub macOS przy generatorze takim jak Unix Makefiles lub Ninja:

```sh
./zadanie1/build/program
```

Przy generatorze Visual Studio na Windowsie uruchom w PowerShell:

```powershell
.\zadanie1\build\Debug\program.exe
```

Położenie pliku wykonywalnego zależy od generatora: generatory wielokonfiguracyjne umieszczają go zwykle w podkatalogu konfiguracji, np. `Debug`. W IDE możesz uruchomić cel `program` bez ręcznego wyszukiwania pliku.

Dla innego zadania zamień `zadanie1` na odpowiednią nazwę katalogu. Po edycji `main.cpp` ponownie wykonaj polecenie budowania. Możesz także otworzyć katalog pojedynczego zadania jako projekt CMake w swoim IDE, wybrać kompilator i uruchamiać cel `program`.

## Uwaga - Zadanie 5: sprawdzenie obsługi stref czasowych

Podczas konfiguracji CMake próbuje skompilować i zlinkować mały program korzystający z `std::chrono::zoned_time`. Jeśli próba się nie powiedzie, konfiguracja zatrzyma się z komunikatem o brakującym wsparciu. Pozostałe zadania są niezależne i można je budować osobno.

**CMake nie instaluje kompilatora, nie uzupełnia biblioteki standardowej i nie dostarcza bazy IANA.** Udana konfiguracja zadania 5 potwierdza możliwość kompilacji i linkowania próby; nie potwierdza dostępności bazy stref w czasie działania. Uruchom także program sprawdzający środowisko z początku [treści zadań](zadania.md), który odwołuje się do wszystkich trzech potrzebnych stref.

Jeśli sprawdzenie się nie powiedzie, wybierz kompilator z biblioteką standardową obsługującą strefy czasowe C++20 i skonfiguruj projekt w nowym katalogu budowania. Samo wskazanie nowszego kompilatora może nie wystarczyć, jeśli nadal korzysta on z biblioteki bez obsługi tych funkcji.

Przykład jawnego wyboru kompilatora; zastąp ścieżkę rzeczywistym położeniem wybranego programu:

```sh
cmake -S zadanie5 -B zadanie5/build/alternatywny -DCMAKE_CXX_COMPILER=/sciezka/do/kompilatora
cmake --build zadanie5/build/alternatywny --config Debug
```

Nie zastępuj stref stałymi przesunięciami godzin: przykłady w zadaniu celowo wymagają uwzględnienia reguł zmiany czasu.