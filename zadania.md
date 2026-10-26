# Czas w C++20 - zadania

Pięć zadań prowadzi od jednostek i pomiaru czasu do kalendarza oraz stref czasowych.

Do każdego zadania przygotowano osobny projekt CMake i plik startowy `main.cpp`: [zadanie 1](zadanie1), [zadanie 2](zadanie2), [zadanie 3](zadanie3), [zadanie 4](zadanie4), [zadanie 5](zadanie5). Sposób budowania opisuje [instrukcja projektów startowych](README.md).

## Zanim zaczniesz

**Wymagany jest C++20 oraz biblioteka standardowa obsługująca kalendarz i strefy czasowe z `std::chrono`.** Samo włączenie `-std=c++20` nie gwarantuje dostępności wszystkich tych funkcji. Zadanie 5 wymaga również dostępnej w środowisku bazy stref czasowych IANA. Przed zajęciami sprawdź poniższy program w swoim środowisku.

```cpp
#include <chrono>
#include <exception>
#include <iostream>

int main() {
    using namespace std::chrono;
    const year_month_day data{year{2026}, month{10}, day{26}};
    if (!data.ok()) return 1;
    try {
        for (const char* nazwa : {"Europe/Warsaw", "America/New_York", "Asia/Tokyo"}) {
            const zoned_time<seconds> czas{nazwa, sys_seconds{sys_days{data}}};
            std::cout << czas.get_time_zone()->name() << '\n';
        }
    } catch (const std::exception& blad) {
        std::cerr << blad.what() << '\n';
        return 1;
    }
}
```

Przykładowe polecenie kompilacji: `c++ -std=c++20 sprawdz_chrono.cpp -o sprawdz_chrono`. Po uruchomieniu program powinien wypisać trzy nazwy stref. Nie potrzebujesz `std::format` ani `std::chrono::parse` do rozwiązania zadań: daty i godziny możesz składać z wartości liczbowych, a wypisywać za pomocą `std::cout` i manipulatorów z `<iomanip>`.

## 1. „Jeszcze tylko pięć minut...”

**Najprostsze.** Budzik dzwoni, a student włącza drzemkę: raz, drugi i trzeci. Każda trwa pięć minut. Potem leży jeszcze przez 90 sekund, zanim w końcu wstanie. Oblicz, ile czasu minęło od pierwszego alarmu.

Przedstaw pojedynczą drzemkę jako `std::chrono::minutes`, a dodatkowy czas jako `std::chrono::seconds`. Oblicz łączny czas trzech drzemek i dodatkowych 90 sekund, korzystając z działań na obiektach `duration`. Wypisz:

- łączny czas w pełnych sekundach;
- liczbę pełnych minut i pozostałych sekund;
- łączny czas w minutach z częścią ułamkową.

Dla tych danych wynik wynosi **990 sekund**, czyli **16 minut i 30 sekund** oraz **16,5 minuty**. Dopuszczalny zapis liczby dziesiętnej to np. `16.5`.

Sprawdź też brak drzemek i dodatkowe 45 sekund: wynik to `45`, `0 min 45 s` oraz `0.75 min`. Załóż nieujemne czasy o niewielkich wartościach.

**Wskazówka:** przydadzą się `duration_cast`, `.count()` i `duration<double, std::ratio<60>>`. Przeliczenia wykonuj na obiektach czasu; wartości liczbowe pobieraj dopiero do wypisania. W komentarzu wyjaśnij, dlaczego konwersja `990` sekund do całkowitych minut daje `16`, a nie `17`.

## 2. „Dlaczego to tak długo trwa?”

**Najprostsze.** Student klika „Wyślij wiadomość” i czeka na odpowiedź serwera. Chce sprawdzić, ile trwa oczekiwanie. Na potrzeby zadania nie łączymy się z siecią: odpowiedź serwera zastępujemy funkcją, która wstrzymuje program na 120 ms.

Do programu wstaw poniższą funkcję i wywołaj ją dokładnie raz pomiędzy dwoma odczytami zegara. Potrzebne nagłówki to `<chrono>` i `<thread>`.

```cpp
void symulujOdpowiedzSerwera() {
    std::this_thread::sleep_for(std::chrono::milliseconds{120});
}
```

Do pomiaru użyj `std::chrono::steady_clock`. Oblicz różnicę odczytów i wypisz czas jako całkowitą liczbę mikrosekund oraz jako liczbę milisekund z częścią ułamkową. Wypisz tylko oba wyniki pomiaru, poza mierzonym fragmentem.

Uruchom program trzy razy. **Nie oczekuj dokładnie 120 ms ani identycznych wyników:** funkcja symuluje czekanie, a jego rzeczywista długość zależy także od systemu. Sprawdź, czy oba wypisane wyniki opisują ten sam pomiar; przykładowo `120500 us` odpowiada `120.5 ms`.

**Wskazówka:** odejmowanie dwóch punktów czasu daje czas trwania. Dla wyniku ułamkowego możesz użyć `duration<double, std::milli>`. W komentarzu wyjaśnij, dlaczego do mierzenia odstępu wybrano `steady_clock` oraz czy ten program mierzy czas pracy procesora, czy czas, który upłynął podczas wywołania.

## 3. „Kiedy wypada piątek trzynastego?”

**Konkretne.** Student sprawdza, czy egzamin przypadkiem nie wypada w piątek trzynastego. Nie jest przesądny, ale wolałby wiedzieć wcześniej. Przygotuj program, który dla podanej daty wyszuka trzy najbliższe piątki trzynastego i poda, ile dni zostało do każdego z nich.

Datę początkową przedstaw jako `std::chrono::year_month_day`. Sprawdź jej poprawność przez `.ok()`; błędną datę odrzuć czytelnym komunikatem. W wyszukiwaniu uwzględnij także datę początkową: jeśli sama jest piątkiem trzynastego, pierwszy wynik ma wskazywać `0` dni.

Dla każdego znalezionego terminu wypisz datę w formacie `RRRR-MM-DD` oraz liczbę dni od daty początkowej. Korzystaj z `year_month_day`, `sys_days`, `days` i `weekday`. Nie obliczaj dnia tygodnia własnym wzorem ani nie wpisuj znalezionych dat na stałe. Załóż rok początkowy z zakresu `2000–2100`; wyniki mogą przypadać w późniejszych latach.

Sprawdź:

- początek `2026-01-01` -> `2026-02-13` (43 dni), `2026-03-13` (71 dni), `2026-11-13` (316 dni);
- początek `2026-03-13` -> `2026-03-13` (0 dni), `2026-11-13` (245 dni), `2027-08-13` (518 dni);
- początek `2026-12-31` -> `2027-08-13` (225 dni), `2028-10-13` (652 dni), `2029-04-13` (834 dni);
- początek `2026-02-30` oraz `2026-04-31` -> odrzucenie daty.

**Wskazówka:** po sprawdzeniu poprawności zamień datę na `sys_days`. Możesz przechodzić po kolejnych dniach za pomocą `days{1}` i sprawdzać jednocześnie dzień miesiąca oraz dzień tygodnia. Różnica dwóch wartości `sys_days` daje liczbę dni między datami. Nie zakładaj, że w każdym roku znajdziesz trzy pasujące terminy.

## 4. „Paczka dostarczona wczoraj”

**Praktyczne.** Sklep „Już prawie u Ciebie” obiecuje dostawę w trzy dni robocze. Jego dotychczasowy kalkulator dodawał trzy do numeru dnia miesiąca, więc pod koniec grudnia przewidywał dostawę na 34 grudnia. Zastąp go czymś, czemu można zaufać.

Przygotuj funkcję wyznaczającą datę dostawy na podstawie daty zamówienia i liczby dni roboczych. Przyjmij jednoznaczne reguły:

- dzień zamówienia nie jest liczony; pierwszy kandydat to następny dzień kalendarzowy;
- dni robocze to poniedziałek–piątek; soboty i niedziele pomijamy;
- **nie uwzględniamy świąt**
- dla `0` dni roboczych zwróć niezmienioną datę zamówienia, również gdy to weekend;
- niepoprawną datę lub ujemną liczbę dni odrzuć czytelnym komunikatem.

Wykorzystaj `year_month_day`, `sys_days`, `days` i `weekday`. Nie przechowuj własnej tabeli długości miesięcy ani nie obliczaj ręcznie dnia tygodnia. Sposób zgłaszania błędów przez funkcję wybierz samodzielnie; program główny ma pokazać zarówno udane obliczenia, jak i odrzucenie błędnych danych. Załóż lata zamówień `2000–2100` i najwyżej `1000` dni roboczych.

Sprawdź:

- `2026-10-23` (piątek), `1` dzień -> `2026-10-26`;
- `2026-10-23`, `3` dni -> `2026-10-28`;
- `2026-10-24` (sobota), `1` dzień -> `2026-10-26`;
- `2026-10-24`, `0` dni -> `2026-10-24`;
- `2026-12-31`, `1` dzień -> `2027-01-01` zgodnie z uproszczeniem dotyczącym świąt;
- `2024-02-28`, `2` dni -> `2024-03-01`;
- `2026-02-30` albo liczba dni `-1` -> odrzucenie danych.

**Wskazówka:** najpierw sprawdź poprawność daty, potem zamień ją na `sys_days`. Na tej reprezentacji możesz przechodzić po dniach za pomocą `days{1}` i sprawdzać `weekday`. Wynik zamień z powrotem na `year_month_day`. W tym zadaniu operujemy na datach kalendarzowych, bez godzin i stref czasowych.

## 5. „U profesora jest jeszcze wczoraj”

**Praktyczne.** Profesor Kemilk wyjechał do Nowego Jorku i ogłosił konsultacje online: „Piątek, 18:00, według mojego zegarka”. Studenci w Krakowie i na erasmusie w Tokio muszą ustalić, kiedy dołączyć i którą datę wpisać w kalendarzu.

Dla terminu określonego przez datę oraz godzinę i minutę w strefie `America/New_York` wypisz lokalną datę i godzinę w trzech strefach:

- `America/New_York` - zegarek profesora;
- `Europe/Warsaw` - studenci w Polsce;
- `Asia/Tokyo` - studenci w Japonii.

Wykorzystaj `std::chrono::zoned_time` i bazę stref IANA. Najpierw powiąż lokalny termin profesora z jego strefą, następnie pobierz wspólny punkt czasu przez `get_sys_time()` i na jego podstawie utwórz widoki w pozostałych strefach. **Nie wpisuj na stałe różnic godzin ani reguł zmiany czasu.** Wynik ma zawierać nazwę strefy, datę `RRRR-MM-DD` i godzinę `GG:MM`; skróty takie jak CET i EST nie są wymagane.

Sprawdź trzy terminy; każdy oznacza godzinę **18:00 w Nowym Jorku**:

```text
Termin 1:
America/New_York  2026-03-06 18:00
Europe/Warsaw    2026-03-07 00:00
Asia/Tokyo       2026-03-07 08:00

Termin 2:
America/New_York  2026-03-20 18:00
Europe/Warsaw    2026-03-20 23:00
Asia/Tokyo       2026-03-21 07:00

Termin 3:
America/New_York  2026-04-03 18:00
Europe/Warsaw    2026-04-04 00:00
Asia/Tokyo       2026-04-04 07:00
```

W komentarzu wyjaśnij na podstawie wyników, dlaczego Warszawa i Nowy Jork nie mają zawsze tej samej różnicy godzin.

Zakładamy poprawne daty, godziny `0–23`, minuty `0–59` i lokalne terminy, które istnieją oraz są jednoznaczne w strefie profesora. Nie trzeba obsługiwać powtórzonej ani pominiętej godziny przy przestawianiu zegarków. Błąd dostępu do bazy stref zgłoś czytelnym komunikatem zamiast zastępować obliczenia stałymi przesunięciami.

**Wskazówka:** lokalny termin możesz złożyć jako `local_days{data} + hours{godzina} + minutes{minuta}`, gdzie `data` ma typ `year_month_day`. Z `get_local_time()` wyodrębnij początek dnia przez `floor<days>`, datę przez `year_month_day`, a godzinę przez `hh_mm_ss` dla różnicy względem początku dnia. Nazwa `local_time` sama w sobie nie oznacza ani strefy profesora, ani strefy komputera - strefę przypisujesz osobno.

## Pomocne źródła

### Artykuły z przykładami

- [C++ Stories: Exploring C++20 std::chrono - Calendar Types](https://www.cppstories.com/2025/chrono-calendar-types/) - wprowadzenie do `year_month_day`, `weekday`, tworzenia dat, `.ok()` i konwersji na `sys_days`. Pomoc do zadań 3–4. Uwaga: do wypisywania autor używa też `std::print` z C++23; w naszych zadaniach wystarczy `std::cout`.
- [Modernes C++: Time Zones: Details](https://www.modernescpp.com/index.php/time-zones-details/) - wprowadzenie do stref czasowych w C++20, `zoned_time`, czasu systemowego i lokalnego oraz odczytu przesunięcia względem UTC. Pomoc do zadania 5.
- [C++ Stories: What is the current time around the world?](https://www.cppstories.com/2024/chrono_dates_zones/) - przykład wyświetlania dat i godzin w Warszawie, Nowym Jorku i Tokio oraz omówienie czasu letniego. Pomoc do zadania 5. Artykuł łączy strefy z C++20 z `std::print` z C++23; korzystaj z części o strefach, a wypisywanie wykonaj przez `std::cout`.

### Dokumentacja do sprawdzania szczegółów

- [Przegląd biblioteki daty i czasu - cppreference](https://en.cppreference.com/w/cpp/chrono) - mapa pojęć i odnośniki do typów używanych w zadaniach.
- [Czasy trwania: `duration`](https://en.cppreference.com/w/cpp/chrono/duration) oraz [konwersje: `duration_cast`](https://en.cppreference.com/w/cpp/chrono/duration/duration_cast) - zadania 1–2.
- [Zegar monotoniczny: `steady_clock`](https://en.cppreference.com/w/cpp/chrono/steady_clock) oraz [oczekiwanie: `sleep_for`](https://en.cppreference.com/w/cpp/thread/sleep_for) - zadanie 2.
- [Daty kalendarzowe: `year_month_day`](https://en.cppreference.com/w/cpp/chrono/year_month_day) i [sprawdzanie poprawności: `ok`](https://en.cppreference.com/w/cpp/chrono/year_month_day/ok) - zadania 3–4.
- [Punkty czasu systemowego: `sys_time`, w tym `sys_days`](https://en.cppreference.com/w/cpp/chrono/sys_time) oraz [dzień tygodnia: `weekday`](https://en.cppreference.com/w/cpp/chrono/weekday) - zadania 3–4.
- [Czas ze strefą: `zoned_time`](https://en.cppreference.com/w/cpp/chrono/zoned_time), [lokalny punkt czasu: `local_time`](https://en.cppreference.com/w/cpp/chrono/local_t), [podział czasu na godziny, minuty i sekundy: `hh_mm_ss`](https://en.cppreference.com/w/cpp/chrono/hh_mm_ss) - zadanie 5.
- [Baza stref czasowych IANA](https://www.iana.org/time-zones) - skąd pochodzą nazwy stref i dane o zmianach czasu.
