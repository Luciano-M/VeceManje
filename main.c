#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <wchar.h>
#include <fcntl.h>

/*
    TODO:   SREDITI PROBLEM MENJANJA SIMBOLA VEC IZVUCENIH KARATA

            Ideja za resenje: novi niz koji samo pamti simbol, i indeks
            mu odgovara odigranoj karti tako da se poklapa sa stanjeIgre

            Vrlo verovatno potrebna modifikacija funkcija za ispis karata
            da primaju argument zeljenog simbola za tacan ispis, umesto
            nasumicnog generisanja svaki put kao sto je trenutno implementirano

            Razume se da stanjeIgre[2] i simbolKarte[2] misle na istu kartu

    TODO:   IMPLEMENTIRATI BOLJI ALGORITAM ZA GENERISANJE RANDOM BROJEVA
*/

void IzvlacenjeKarte(char *trenutnoStanje, int *brojOdigranihPoteza)
{
    srand(time(NULL));
    short int vrednostNaredneKarte = (rand() % 13) + 2; // +2 zbog toga sto je min. moguca vr. 0
    switch(vrednostNaredneKarte)                        // a najmanja karta je 2
    {
        case 10:
            trenutnoStanje[*brojOdigranihPoteza] = 'T';
            break;

        case 11:
            trenutnoStanje[*brojOdigranihPoteza] = 'A';
            break;

        case 12:
            trenutnoStanje[*brojOdigranihPoteza] = 'J';
            break;

        case 13:
            trenutnoStanje[*brojOdigranihPoteza] = 'Q';
            break;

        case 14:
            trenutnoStanje[*brojOdigranihPoteza] = 'K';
            break;

        default:
            trenutnoStanje[*brojOdigranihPoteza] = vrednostNaredneKarte + '0';
            break;
    }

    trenutnoStanje[++*brojOdigranihPoteza] = '\0';

    *brojOdigranihPoteza++;
}

void PrikaziInformacije(char *trenutnoStanje)
{
    system("cls");

    wprintf(L"\n\n Trenutno stanje igre:\n\n ");

    for(int i = 0; trenutnoStanje[i] != '\0'; i++)
    {
        if((trenutnoStanje[i] - '0') > 9 && trenutnoStanje[i] != 'T')
            PrikaziKartuStih(trenutnoStanje[i]);
        else if(trenutnoStanje[i] == 'T')
            PrikaziKartuDvocifrena(10);
        else
            PrikaziKartu(trenutnoStanje[i] - '0');
    }

    wprintf(L"\n\n");
}

wchar_t OdrediSimbolKarte()
{
    // ovde koristim wchar_t da bi ova stvar znala kako
    // da prikaze i interpretira unicode karaktere

    //                     ♠        ♥      ♣       ♦
    wchar_t simboli[] = {0x2660, 0x2665, 0x2663, 0x2666};
    short int vrednostSimbola = rand() % 4;

    return simboli[vrednostSimbola];
}

void PrikaziKartu(int brojKarte)
{
    wprintf(L"\n");

    wprintf(L"\n  _________ ");
    wprintf(L"\n |         |");
    wprintf(L"\n | %d       |", brojKarte);
    wprintf(L"\n |         |");
    wprintf(L"\n |    %lc    |", OdrediSimbolKarte());
    wprintf(L"\n |         |");
    wprintf(L"\n |       %d |", brojKarte);
    wprintf(L"\n |_________|");
}

void PrikaziKartuDvocifrena(int brojKarte)
{
    wprintf(L"\n");

    wprintf(L"\n  _________ ");
    wprintf(L"\n |         |");
    wprintf(L"\n | %d      |", brojKarte);
    wprintf(L"\n |         |");
    wprintf(L"\n |    %lc    |", OdrediSimbolKarte());
    wprintf(L"\n |         |");
    wprintf(L"\n |      %d |", brojKarte);
    wprintf(L"\n |_________|");
}

void PrikaziKartuStih(char simbol)
{
    wprintf(L"\n");

    wprintf(L"\n  _________ ");
    wprintf(L"\n |         |");
    wprintf(L"\n | %c       |", simbol);
    wprintf(L"\n |         |");
    wprintf(L"\n |    %lc    |", OdrediSimbolKarte());
    wprintf(L"\n |         |");
    wprintf(L"\n |       %c |", simbol);
    wprintf(L"\n |_________|");
}


void Restart(char *trenutnoStanje, int *brojOdigranihPoteza)
{
    system("cls");
    *brojOdigranihPoteza = 0;
    trenutnoStanje[0] = '\0';
    main();
}

void KrajIgre()
{
    wprintf(L"\n\n ------------------------- \n\n Hvala na igranju!\n Vece/Manje v0.1.0\n\n Luka Mihailovic, 2022 (c)\n\n");
    system("pause");

    exit(0);
}

void Poraz(char *trenutnoStanje, int *brojOdigranihPoteza)
{
    wprintf(L"\n Izgubili ste! :(\n Nova igra? (y/n): ");

    while(1)
    {
        char odluka;
        scanf(" %c", &odluka);

        if(tolower(odluka) == 'y')
            Restart(trenutnoStanje, brojOdigranihPoteza);
        else if(tolower(odluka) == 'n')
            KrajIgre();
        else
            wprintf(L"\n Neispravan izbor! Pokusajte ponovo.\n\n Nova igra? (y/n): ");
    }
}

int Provera(char *trenutnoStanje, int *brojOdigranihPoteza)
{
    // proverava da li je levi element veci od desnog
    int leviElement;
    int desniElement;

    char bukvalnaVrednostLevi = trenutnoStanje[*brojOdigranihPoteza - 2];
    char bukvalnaVrednostDesni = trenutnoStanje[*brojOdigranihPoteza - 1];


    switch(bukvalnaVrednostLevi)
    {
        case 'T':
            leviElement = 10;
            break;
        case 'A':
            leviElement = 11;
            break;
        case 'G':
            leviElement = 12;
            break;
        case 'Q':
            leviElement = 13;
            break;
        case 'K':
            leviElement = 14;
            break;
        default:
            leviElement = bukvalnaVrednostLevi - '0';
    }

    switch(bukvalnaVrednostDesni)
    {
        case 'T':
            desniElement = 10;
            break;
        case 'A':
            desniElement = 11;
            break;
        case 'J':
            desniElement = 12;
            break;
        case 'Q':
            desniElement = 13;
            break;
        case 'K':
            desniElement = 14;
            break;
        default:
            desniElement = bukvalnaVrednostDesni - '0';
    }

    if(leviElement == desniElement)
        return 0;
    else if(leviElement > desniElement)
        return -1;
    else
        return 1;
}

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);  // naglasavam da standardni izlaz koristi UTF-16 karaktere za ispis
                                            // posledica toga je da printf ne radi, i moram koristiti wprintf
    char unos;                              // tj. wide printf (jer je utf16 "siri" od ascii)
    int vrednostNaredneKarte;

    char stanjeIgre[50];
    wchar_t simboliKarti[50];               // dopraviti funkcije da primaju ovaj argument...
    int brojOdigranihPoteza = 0;

    IzvlacenjeKarte(stanjeIgre, &brojOdigranihPoteza);  // pocetna karta
    PrikaziInformacije(stanjeIgre);                     // prikaz pocetne karte

    while(1)
    {
        wprintf(L"\n Izbor (W - vece / S - manje / R - restart / Q - kraj igre): ");
        scanf(" %c", &unos);

        if(tolower(unos) == 'q')
            break;

        if(tolower(unos) == 'r')
            Restart(stanjeIgre, &brojOdigranihPoteza);

        if(tolower(unos) == 'w' || tolower(unos) == 's')
        {
            IzvlacenjeKarte(stanjeIgre, &brojOdigranihPoteza);
            PrikaziInformacije(stanjeIgre);

            if(tolower(unos) == 'w')
            {
                if(Provera(stanjeIgre, &brojOdigranihPoteza) == -1)
                    Poraz(stanjeIgre, &brojOdigranihPoteza);
            }
            else if(tolower(unos) == 's')
            {
                if(Provera(stanjeIgre, &brojOdigranihPoteza) == 1)
                    Poraz(stanjeIgre, &brojOdigranihPoteza);
            }
        }
        else
            wprintf(L"\n Nepravilan unos! Pokusajte ponovo.");

        while((getchar())!='\n');   // malo cistimo tastaturni bafer
    }

    KrajIgre();

    return 0;
}
