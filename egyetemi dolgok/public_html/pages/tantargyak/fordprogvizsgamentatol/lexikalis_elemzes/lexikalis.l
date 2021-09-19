%option noyywrap c++ yylineno

%{
#include <iostream>
#include <stdlib.h>
%}

SZAMJEGY    [0-9]
WS          [ \t\n]
BETU        [a-zA-Z]
VALOS_SZAM	[0-9]+\.[0-9]*
EGESZ_RESZ	egeszresz
TORT_RESZ	tortresz

%%

#.*    // nem kell semmit csinalni

{SZAMJEGY}+ std::cout << "SZAMKONSTANS" << std::endl;

PROGRAM         std::cout << "PROGRAM" << std::endl;
VALTOZOK:       std::cout << "VALTOZOK" << std::endl;
UTASITASOK:     std::cout << "UTASITASOK" << std::endl;
PROGRAM_VEGE    std::cout << "PROGRAM_VEGE" << std::endl; 
HA              std::cout << "HA" << std::endl;
AKKOR           std::cout << "AKKOR" << std::endl;
KULONBEN        std::cout << "KULONBEN" << std::endl;
HA_VEGE         std::cout << "HA_VEGE" << std::endl; 
CIKLUS          std::cout << "CIKLUS" << std::endl;
AMIG            std::cout << "AMIG" << std::endl;
CIKLUS_VEGE     std::cout << "CIKLUS_VEGE" << std::endl;
BE:             std::cout << "BE" << std::endl;
KI:             std::cout << "KI" << std::endl;
EGESZ           std::cout << "EGESZ" << std::endl;
LOGIKAI         std::cout << "LOGIKAI" << std::endl;
IGAZ            std::cout << "IGAZ" << std::endl;
HAMIS           std::cout << "HAMIS" << std::endl;
SKIP            std::cout << "SKIP" << std::endl;
VALOS			std::cout << "VALOS" << std::endl;

":="            std::cout << "ERTEKADAS" << std::endl;
"="             std::cout << "EGYENLO" << std::endl;
"<"             std::cout << "KISEBB" << std::endl;
">"             std::cout << "NAGYOBB" << std::endl;
"<="            std::cout << "KISEBBEGYENLO" << std::endl;
">="            std::cout << "NAGYOBBEGYENLO" << std::endl;
"+"             std::cout << "PLUSZ" << std::endl;
"-"             std::cout << "MINUSZ" << std::endl;
"*"             std::cout << "SZORZAS" << std::endl;
"/"             std::cout << "OSZTAS" << std::endl;
"%"             std::cout << "MARADEK" << std::endl;
ES              std::cout << "ES" << std::endl;
VAGY            std::cout << "VAGY" << std::endl;
NEM             std::cout << "NEM" << std::endl;
"("             std::cout << "BALZAROJEL" << std::endl;
")"             std::cout << "JOBBZAROJEL" << std::endl;

{EGESZ_RESZ}	std::cout << "EGESZ_RESZ" << std::endl;
{TORT_RESZ}		std::cout << "TORT_RESZ" << std::endl;
{VALOS_SZAM}	std::cout << "VALOS_SZAM" << std::endl;
({BETU}|_)({BETU}|{SZAMJEGY}|_)*  std::cout << "AZONOSITO" << std::endl;

{WS}+   // feher szokozok: semmi teendo

. {
    std::cerr << "lexikalis hiba" << std::endl;
    exit(1);
}

%%
