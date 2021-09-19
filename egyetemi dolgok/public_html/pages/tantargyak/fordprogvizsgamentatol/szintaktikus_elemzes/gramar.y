%baseclass-preinclude <iostream>

%lsp-needed

%token SZAMKONSTANS
%token PROGRAM
%token VALTOZOK
%token UTASITASOK
%token PROGRAM_VEGE
%token HA
%token AKKOR
%token KULONBEN
%token HA_VEGE
%token CIKLUS
%token AMIG
%token CIKLUS_VEGE
%token BE
%token KI
%token EGESZ
%token LOGIKAI
%token ERTEKADAS
%token BALZAROJEL
%token JOBBZAROJEL
%token AZONOSITO
%token IGAZ
%token HAMIS
%token SKIP
%token VALOS
%token VALOS_SZAM
%token EGESZ_RESZ
%token TORT_RESZ

%left VAGY
%left ES
%left NEM
%left EGYENLO
%left KISEBB NAGYOBB KISEBBEGYENLO NAGYOBBEGYENLO
%left PLUSZ MINUSZ
%left SZORZAS OSZTAS MARADEK

%%

start:
    kezdes deklaraciok utasitasok befejezes
    {
        std::cout << "start -> kezdes deklaraciok utasitasok befejezes" << std::endl;
    }
;

kezdes:
    PROGRAM AZONOSITO
    {
        std::cout << "kezdes -> PROGRAM AZONOSITO" << std::endl;
    }
;

befejezes:
    PROGRAM_VEGE
    {
        std::cout << "befejezes -> PROGRAM_VEGE" << std::endl;
    }
;

deklaraciok:
    // ures
    {
        std::cout << "deklaraciok -> epszilon" << std::endl;
    }
|
    VALTOZOK valtozolista
    {
        std::cout << "deklaraciok -> VALTOZOK valtozolista" << std::endl;
    }
;

valtozolista:
    deklaracio
    {
        std::cout << "valtozolista -> deklaracio" << std::endl;
    }
|
    deklaracio valtozolista
    {
        std::cout << "valtozolista -> deklaracio valtozolista" << std::endl;
    }
;

deklaracio:
    EGESZ AZONOSITO
    {
        std::cout << "deklaracio -> EGESZ AZONOSITO" << std::endl;
    }
|
    LOGIKAI AZONOSITO
    {
        std::cout << "deklaracio -> LOGIKAI AZONOSITO" << std::endl;
    }
|
    VALOS AZONOSITO
    {
        std::cout << "deklaracio -> VALOS AZONOSITO" << std::endl;
    }
;

utasitasok:
    UTASITASOK utasitas utasitaslista
    {
        std::cout << "utasitasok -> UTASITASOK utasitaslista" << std::endl;
    }
;

utasitaslista:
    // epsilon
    {
        std::cout << "utasitaslista -> utasitas" << std::endl;
    }
|
    utasitas utasitaslista
    {
        std::cout << "utasitaslista -> utasitas utasitaslista" << std::endl;
    }
;

utasitas:
    SKIP
    {
        std::cout << "utasitas -> SKIP" << std::endl;
    }
|
    ertekadas
    {
        std::cout << "utasitas -> ertekadas" << std::endl;
    }
|
    be
    {
        std::cout << "utasitas -> be" << std::endl;
    }
|
    ki
    {
        std::cout << "utasitas -> ki" << std::endl;
    }
|
    elagazas
    {
        std::cout << "utasitas -> elagazas" << std::endl;
    }
|
    ciklus
    {
        std::cout << "utasitas -> ciklus" << std::endl;
    }
;

ertekadas:
    AZONOSITO ERTEKADAS kifejezes
    {
        std::cout << "ertekadas -> AZONOSITO ERTEKADAS kifejezes" << std::endl;
    }
;

be:
    BE AZONOSITO
    {
        std::cout << "be -> BE AZONOSITO" << std::endl;
    }
;

ki:
    KI kifejezes
    {
        std::cout << "ki -> KI kifejezes" << std::endl;
    }
;

elagazas:
    HA kifejezes AKKOR utasitas utasitaslista HA_VEGE
    {
        std::cout << "elagazas -> HA kifejezes AKKOR utasitaslista HA_VEGE" << std::endl;
    }
|
    HA kifejezes AKKOR utasitas utasitaslista KULONBEN utasitas utasitaslista HA_VEGE
    {
        std::cout << "elagazas -> HA kifejezes AKKOR utasitaslista KULONBEN utasitaslista HA_VEGE" << std::endl;
    }
;

ciklus:
    CIKLUS AMIG kifejezes utasitas utasitaslista CIKLUS_VEGE
    {
        std::cout << "ciklus -> CIKLUS AMIG kifejezes utasitaslista CIKLUS_VEGE" << std::endl;
    }
;

kifejezes:
    SZAMKONSTANS
    {
        std::cout << "kifejezes -> SZAMKONSTANS" << std::endl;
    }
|
	VALOS_SZAM
    {
        std::cout << "kifejezes -> VALOS_SZAM" << std::endl;
    }
|
    IGAZ
    {
        std::cout << "kifejezes -> IGAZ" << std::endl;
    }
|
    HAMIS
    {
        std::cout << "kifejezes -> HAMIS" << std::endl;
    }
|
    AZONOSITO
    {
        std::cout << "kifejezes -> AZONOSITO" << std::endl;
    }
|
    kifejezes PLUSZ kifejezes
    {
        std::cout << "kifejezes -> kifejezes PLUSZ kifejezes" << std::endl;
    }
|
    kifejezes MINUSZ kifejezes
    {
        std::cout << "kifejezes -> kifejezes MINUSZ kifejezes" << std::endl;
    }
|
    kifejezes SZORZAS kifejezes
    {
        std::cout << "kifejezes -> kifejezes SZORZAS kifejezes" << std::endl;
    }
|
    kifejezes OSZTAS kifejezes
    {
        std::cout << "kifejezes -> kifejezes OSZTAS kifejezes" << std::endl;
    }
|
    kifejezes MARADEK kifejezes
    {
        std::cout << "kifejezes -> kifejezes MARADEK kifejezes" << std::endl;
    }
|
    kifejezes KISEBB kifejezes
    {
        std::cout << "kifejezes -> kifejezes KISEBB kifejezes" << std::endl;
    }
|
    kifejezes NAGYOBB kifejezes
    {
        std::cout << "kifejezes -> kifejezes NAGYOBB kifejezes" << std::endl;
    }
|
    kifejezes KISEBBEGYENLO kifejezes
    {
        std::cout << "kifejezes -> kifejezes KISEBB kifejezes" << std::endl;
    }
|
    kifejezes NAGYOBBEGYENLO kifejezes
    {
        std::cout << "kifejezes -> kifejezes NAGYOBB kifejezes" << std::endl;
    }
|
    kifejezes EGYENLO kifejezes
    {
        std::cout << "kifejezes -> kifejezes EGYENLO kifejezes" << std::endl;
    }
|
    kifejezes ES kifejezes
    {
        std::cout << "kifejezes -> kifejezes ES kifejezes" << std::endl;
    }
|
    kifejezes VAGY kifejezes
    {
        std::cout << "kifejezes -> kifejezes VAGY kifejezes" << std::endl;
    }
|
    NEM kifejezes
    {
        std::cout << "kifejezes -> NEM kifejezes" << std::endl;
    }
|
    BALZAROJEL kifejezes JOBBZAROJEL
    {
        std::cout << "kifejezes -> BALZAROJEL kifejezes JOBBZAROJEL" << std::endl;
    }
|
	EGESZ_RESZ BALZAROJEL kifejezes JOBBZAROJEL
    {
        std::cout << "kifejezes -> EGESZ_RESZ BALZAROJEL kifejezes JOBBZAROJEL" << std::endl;
    }
|
	TORT_RESZ BALZAROJEL kifejezes JOBBZAROJEL
    {
        std::cout << "kifejezes -> EGESZ_RESZ BALZAROJEL kifejezes JOBBZAROJEL" << std::endl;
    }
;
