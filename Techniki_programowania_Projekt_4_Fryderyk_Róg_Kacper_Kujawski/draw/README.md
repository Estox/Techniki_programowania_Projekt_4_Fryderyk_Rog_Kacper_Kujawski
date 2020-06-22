# Symulator windy

Symulator został napisany w języku c++ z wykorzystaniem GUI w WinApi. 
Środowisko: Microsoft Visual Studio 2019;
Kompilator: Microsoft C/C++;
Autorzy: Kacper Kujawski, Fryderyk Róg;

## Sposób działania

Winda transportuje pasażerów na wybrane przez użytkownika poziomy. Użytkownik dokonuje wyboru pięter poprzez klikanie odpowiednich przycisków. Winda jeździ pomiędzy pięcioma piętrami, więc na każdym z nich znajdują się 4 przyciski. Winda startuje po naciśnięciu przycisku "Start". 
Każda osoba, która wsiada do windy waży 70kg, a maksymalny udźwig windy wynosi 600kg. Winda może maksymalnie udźwignąć 8 osób.

### Ważne informacje
Do poprawnego działania programu należy załączyć poniższe Header Files:

- Resource.h
- stdafx.h
- targetver.h
- draw2.h

oraz pliki .ccp:

- draw2.cpp
- stdfax.cpp

Na koniec należy zawrzeć poniższe pliki .jpg żeby widać było animacje:

- person_1.jpg
- person_2.jpg
- person_3.jpg
- person_4.jpg
- person_5.jpg
- person_blank.jpg


