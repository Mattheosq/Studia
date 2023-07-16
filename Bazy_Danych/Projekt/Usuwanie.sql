-- usuniecie grupy rekordow
--1. usuniecie kart graficznych z pozycji zamowien o nazwie GTX 1080
delete POZYCJE_ZAMOWIEN
where produkt_nazwa = 'GTX 1080';
-- usuniecie jednego rekordu
--2. usuniecie jednego regalu
delete REGAL
where magazyn_id_magazyn = 15;
--usuniecie grupy rekordow
-- 3. usuniecie wszystkich kuponiow ze znizka inna niz 0,15 0,4 0,7 oraz 0,3
delete KUPON
where znizka NOT IN (0.15, 0.4, 0.7, 0.3);
--usuniecie grupy rekordow
-- 4. usuniecie uslug wiekszych z id wiekszym niz 7
delete USLUGI
where id_uslugi > 7;
-- usuniecie grupy rekordow
-- 5. usuniecie 3 klientow
delete KLIENT
where id_klient between 9 and 11;