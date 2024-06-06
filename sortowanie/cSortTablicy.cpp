#include "cSortTablicy.h"
#include <ctime>
#include <cstdlib>
//#include <stdexcept>
#include "myExceptions.h"

cSortTablicy::~cSortTablicy() {
    delete tablica;
}

void cSortTablicy::wprowadzZKlawiatury(int n) {
    std::vector<int> tab(n);
    std::cout << "Wprowadz " << n << " elementow: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> tab[i];
    }
    tablica = new cTablica(tab);
}

void cSortTablicy::losujElementy(int n) {
    std::vector<int> tab(n);
    std::srand(std::time(0));

    switch (rTab)
    {
        // 
    case cSortTablicy::los:
        for (int i = 0; i < n; ++i) {
            tab[i] = std::rand() % 1000; // losowe liczby od 0 do 999
        }
        tablica = new cTablica(tab);
        break;
    case cSortTablicy::uporz:
        tab[0] = std::rand() % 1000;
        for (int i = 1; i < n; ++i) {
            tab[i] = std::rand() % 1000 + tab[i - 1]; // losowe liczby uporzadkowane od 0 do 999
        }
        tablica = new cTablica(tab);
        break;
    case cSortTablicy::odwr:
        tab[0] = std::rand() % 1000;
        for (int i = 1; i < n; ++i) {
            tab[i] = tab[i - 1] - std::rand() % 1000; // losowe liczby uporzadkowane od 0 do 999
        }
        tablica = new cTablica(tab);
        break;
    case cSortTablicy::prawie:
        // pierwsze 90% elementow jest posortowanych
        tab[0] = std::rand() % 1000;
        int ostPosort = 0.9 * n - 1;
        for (int i = 1; i <= ostPosort; ++i) {
            tab[i] = tab[i - 1] - std::rand() % 1000; // losowe liczby uporzadkowane od 0 do 999
        }
        // pozostale 10% jest losowych
        for (int i = ostPosort + 1; i < n; ++i) {
            tab[i] = std::rand() % 1000 + tab[ostPosort]; // losowe liczby uporzadkowane od 0 do 999
        }
        tablica = new cTablica(tab);
        break;
    default:
        throw MyExceptions("Niewiadomy rodzaj tablicy.\n");
        break;
    }

}

void cSortTablicy::ustawElementy(const std::vector<int>& tab) {
    tablica = new cTablica(tab);
}

std::vector<int> cSortTablicy::getElements() const {
    if (tablica == nullptr) throw std::runtime_error("Tablica jest pusta");
    return tablica->getElements();
}

void cSortTablicy::sortujShakerSort() {
    if (tablica == nullptr) throw std::runtime_error("Tablica jest pusta");
    tablica->shakerSort();
}

void cSortTablicy::sortujQuickSortLomuto() {
    if (tablica == nullptr) throw std::runtime_error("Tablica jest pusta");
    tablica->quickSortLomuto(0, tablica->size() - 1);
}

void cSortTablicy::sortujQuickSortHoare() {
    if (tablica == nullptr) throw std::runtime_error("Tablica jest pusta");
    tablica->quickSortHoare(0, tablica->size() - 1);
}

void cSortTablicy::sortujHeapSort() {
    if (tablica == nullptr) throw std::runtime_error("Tablica jest pusta");
    tablica->heapSort();
}
void cSortTablicy::zapiszWyniki(ofstream& write)
{
    // Zapisz nazwe metody
    switch (alg)
    {
    case cSortTablicy::shaker:
        write << "Shaker sort\t";
        break;
    case cSortTablicy::qHoare:
        write << "Quick sort z podzialem Hoare'a\t";
        break;
    case cSortTablicy::qLomuto:
        write << "Quick sort z podzialem Lomuto\t";
        break;
    case cSortTablicy::heap:
        write << "Sortowanie przez kopcowanie\t";
        break;
    default:
        throw MyExceptions("Niewiadomy rodzaj sortowania\n");
        break;
    }

    // Zapisz dlugosz tablicy
    write << tablica->size() << '\t';

    // Zapisz rodzaj tablicy
    switch (rTab)
    {
    case cSortTablicy::los:
        write << "tablica uzupelniona losowymi liczbami\t";
        break;
    case cSortTablicy::uporz:
        write << "tablica uzupelniona liczbami posortowanymi rosnaco\t";
        break;
    case cSortTablicy::odwr:
        write << "tablica uzupelniona liczbami posortowanymi malejaco\t";
        break;
    case cSortTablicy::prawie:
        write << "tablica czesciowo uporzadkowana (10 % elementow jest na zlej pozycji)\t";
        break;
    default:
        throw MyExceptions("Niewiadomy rodzaj tablicy.\n");
        break;
    }

    // Zapisz liczbe porownan
    write << tablica->getPorownania() << '\t';

    // Zapisz liczbe przestawien
    write << tablica->getPrzestawienia() << '\t';
}

void cSortTablicy::pokazWyniki() const {
    if (tablica == nullptr) throw std::runtime_error("Tablica jest pusta");
    std::cout << "Tablica po sortowaniu: ";
    tablica->print();
    std::cout << "Liczba porownan: " << tablica->getPorownania() << std::endl;
    std::cout << "Liczba przestawien: " << tablica->getPrzestawienia() << std::endl;
}


