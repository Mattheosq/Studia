--aktualizacja jednego rekordu
--1.
update MAGAZYN
-- dolaczenie notatki do wybranego magazynu
set notatka = 'Magazyn nr 1'
where id_magazyn = 15;
-- aktualizcja grupy rekordów
-- 2.
-- podwyzka dla Mateuszow
update PRACOWNIK
set pensja = 10000
where imie = 'Mateusz';

-- 3.
-- zmiana ceny dla procesorow
update PRODUKT
set cena = cena + 10000
where nazwa like 'i%';
-- 4.
-- zmiana czasu oczekiwania dla wszystkich uslug
update USLUGI
set czas_realizacji = '7 dni';
-- aktualizacja jednego rekordu
-- 5.
-- zmiana nr telefonu wybranej osoby 
update KLIENT
set nr_telefonu = '111222333'
where imie = 'Jolanta' and nazwisko = 'Nowakowska';