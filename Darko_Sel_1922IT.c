#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_POINTS 201
#define MAX_ROUNDS 15
int nasumican_broj_od_do(int pocetni, int krajnji)
{
    return pocetni + rand() % (krajnji - pocetni + 1);
}

int koliko_poena_dodati(int sansa, int trenutni, int trenutni_rezultat)
{
    int rezultat;
    // proverava da li je promasaj i da li je input veci ili manji od dozvoljenog
    if (sansa <= 30 || (trenutni > 20 || trenutni < 1))
    {
        rezultat = trenutni * 0;
    }
    else if (sansa <= 50) // x3 polje
    {
        rezultat = trenutni * 3;
    }
    else if (sansa <= 80) // x2 polje
    {
        rezultat = trenutni * 2;
    }
    else
    {
        rezultat = trenutni; // Obican pogodak
    }
    if (MAX_POINTS < (trenutni_rezultat + rezultat))
    { // proverava da li prelazi 201
        rezultat = 0;
    }

    return rezultat;
}

int main()
{
    srand(time(NULL));
    char igrac1[20];
    char igrac2[20];
    int rezultati[] = {0, 0};
    int trenutni_poeni1, trenutni_poeni2, sansa1, sansa2;
    int rezultati_runde_igrac1, rezultati_runde_igrac2, veci;
    int round = 0;
    printf("Naziv 1. igraca:"); // 0. unos imena
    scanf("%[^\n]%*c", &igrac1);
    printf("Naziv 2. igraca:");
    scanf("%[^\n]%*c", &igrac2);

    while (round != MAX_ROUNDS && rezultati[0] != MAX_POINTS && rezultati[1] != MAX_POINTS) // 1 uslovi za trajanje igre
    {
        round++;
        // Generisemo nasumican broj od 0 - 100
        sansa1 = nasumican_broj_od_do(0, 100);
        sansa2 = nasumican_broj_od_do(0, 100);
        printf("Stanje na tabeli:\n");
        printf("%s: %d poena \n", igrac1, rezultati[0]);
        printf("%s: %d poena \n", igrac2, rezultati[1]);

        printf("Unesite poene:\n");
        printf("%s:", igrac1);
        scanf("%d", &trenutni_poeni1);
        printf("%s:", igrac2);
        scanf("%d", &trenutni_poeni2);
        // funkcija racuna rezultate trenutne runde za svakog igraca
        rezultati_runde_igrac1 = koliko_poena_dodati(sansa1, trenutni_poeni1, rezultati[0]);
        rezultati_runde_igrac2 = koliko_poena_dodati(sansa2, trenutni_poeni2, rezultati[1]);
        // sabira rezultat
        rezultati[0] += rezultati_runde_igrac1;
        rezultati[1] += rezultati_runde_igrac2;

        if (rezultati[0] > rezultati[1]) // Proverava koji je veci u svakom trenutku kako bi znali koga da zbacimo na nulu, ukoliko je igrac 1 imao veci rezultat u krugu 1 , a igrac 2 manji.Ukoliko se u sledecem krugu izjednace igrac 1 gubi sve poene.
        {
            veci = 0;
        }
        else if (rezultati[1] > rezultati[0])
        {
            veci = 1;
        }
        else if (rezultati[0] == rezultati[1] && round != 1)
        {
            rezultati[veci] = 0;
        }
    }
    if (rezultati[0] == MAX_POINTS || rezultati[0] > rezultati[1]) // proverava i ispisuje rezultate
    {
        printf("%s je pobedio! Cestitamo!", igrac1);
    }
    else if (rezultati[1] == MAX_POINTS || rezultati[1] > rezultati[0])
    {
        printf("%s je pobedio! Cestitamo!", igrac2);
    }
    else
    {
        printf("Rezultat je neresen!");
    }
}

/*
0.Na pocetku igre unose imena
1.Uslovi za nastavak igre su:
    1.1)Nijedan igrac nema rezultat 201
    1.2)Broj krugova nije preko 15
        Ukoliko se zavrsi i niko nema 201 pobednik je onaj koji ima vise poena
        Ukoliko je rezultat neresen ispisati odgovarajucu poruku
2.Igraci unose poene na pocetku igre od 1 do 20
    Nepravilan unos se racuna kao promasaj  - 0 poena
    U svakom pokusaju igraci imaju:
        30% da omase bacanje - 0 poena
        20% trostruki poeni Pogodjeni X 3
        30% dvostruki poeni Pogodjeni X 2
        20% za pogodjen iznos
3.Gubitak poena
    Ukoliko igrac prebaci 201 ti poeni se ne racunaju
    Ukoliko igrac1 u datom krugu ostvari isti broj poena kao igrac2 , igrac2 gubi sve poene
*/