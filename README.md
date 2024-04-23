# Rad-s-datotekama
U ovom će projektu biti prikazan rad s datotekama (kreiranje, brisanje, čitanje) te rad s podacima unutar njih (dodavanje, brisanje, ažuriranje, sortiranje). Aplikacija služi za praćenje osoba koliko su puta darovale krv.

FUNKCIONALNOSTI APLIKACIJE:
KREIRANJE DATOTEKE:
- odabire se opcija '1'
- unosi se naziv datoteke
- moguće je u istom trenutku biti kreirno samo jedna datoteka, a ukoliko se želi ponovno kreirati nova, potrebno je izbrisati postojeću

BRISANJE DATOTEKE:
- odabire se opcija '2'
- briše se kreirana datoteka

DODAVANJE OSOBA U DATOTEKU:
- odabire se opcija '3'
- unosi se OIB, ime, prezime, datum rođenja, krvna grupa, broj darivanja
- nije moguće unijeti osobu s OIB-om ukoliko taj OIB već postoji u datoteci

BRISANJE OSOBA IZ DATOTEKE:
- odabire se opcija '4'
- unosi se OIB osobe
- ukoliko je OIB ispravan, osoba se briše iz datoteke, a ukoliko ne postoji osoba s traženim OIB-om, ispisuje se pripadajuća poruka

ZABILJEŽAVANJE DARIVANJA KRVI:
- odabire se opcija '5'
- unosi se OIB osobe
- ukoliko je OIB ispravan, osobi se povećava broj darivanja krvi za 1, a ukoliko ne postoji osoba s traženim OIB-om, ispisuje se pripadajuća poruka

ISPIS SADRŽAJA DATOTEKE:
- odabire se opcija '6'
- prikazuju se sve osobe upisane u datoteci s pripadajućim podacima

SORTIRANJE OSOBA PREMA BROJU DARIVANJA KRVI:
- odabire se opcija '7'
- prikazuju se osobe prema broju koliko su puta darovale krv (od najvećeg broja prema najmanjem)

IZLAZ IZ PROGRAMA:
- odabire se opcija '9'
- izlazi se iz programa
