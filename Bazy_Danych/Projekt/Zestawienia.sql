-- Z³¹czenie wewnêtrzne 4 tabel z klauzul¹ HAVING
-- Zestawienie wypisuje klientow, ktorzy wystawili wiecej niz jedno zamowienie
-- oraz srednia ocene z tych zamowien

SELECT klient.id_klient, ROUND(AVG(feedback.ocena),2) as "Œrednia ocena", COUNT(zamowienie.id_zamowienie) as "Liczba zamówieñ"
FROM zamowienie
INNER JOIN klient
ON zamowienie.klient_id_klient = klient.id_klient
INNER JOIN feedback
ON zamowienie.id_zamowienie = feedback.zamowienie_id_zamowienie
INNER JOIN kupon
ON zamowienie.kupon_id_kuponu = kupon.id_kuponu
GROUP BY klient.id_klient
HAVING AVG(feedback.ocena) >= 4 AND COUNT(zamowienie.id_zamowienie) >= 2;

-- Podzapytanie nieskorelowane z u¿yciem operatora IN
-- Wykaz wszystkich zamowien w ktorych jeden z produktow ma kolor czerwony
SELECT *
FROM zamowienie
WHERE id_zamowienie IN (SELECT zamowienie_id_zamowienie
                        FROM pozycje_zamowien
                        WHERE kolor = 'czarny');
-- Podzapytanie skorelowane z u¿yciem operatora ALL
-- Wykaz firm tworz¹cych karty graficzne, które istniej¹ na rynku krócej ni¿ wszystkie firmy z pozosta³ych dziedzin
SELECT *
FROM producent x
WHERE x.dziedzina = 'karty graficzne' AND extract (year from sysdate) - extract (year from x.data_zalozenia) <  ALL 
(select extract (year from sysdate) - extract (year from y.data_zalozenia)
FROM producent y
WHERE y.dziedzina != x.dziedzina);

--Operacja agreguj¹ca z klauzul¹ GROUP
-- Wykaz wszystkich srednich zarobków z wszytkich magazynow z kazdej filii firmy/miasta
SELECT magazyn.oddzial_nazwa_oddzial, magazyn_id_magazyn, ROUND(AVG(pensja),2) AS œrednia_pensja
FROM pracownik
INNER JOIN magazyn 
ON magazyn.id_magazyn = pracownik.magazyn_id_magazyn 
GROUP BY magazyn_id_magazyn, magazyn.oddzial_nazwa_oddzial
ORDER BY magazyn.oddzial_nazwa_oddzial;

-- Widoki
-- Tworzenie perspektywy na podstawie poprzedniego przykladu
create or replace view perspektywa as
SELECT magazyn.oddzial_nazwa_oddzial, magazyn_id_magazyn, ROUND(AVG(pensja),2) AS œrednia_pensja
FROM pracownik
INNER JOIN magazyn 
ON magazyn.id_magazyn = pracownik.magazyn_id_magazyn 
GROUP BY magazyn_id_magazyn, magazyn.oddzial_nazwa_oddzial
ORDER BY magazyn.oddzial_nazwa_oddzial;

select * from perspektywa;

-- Zmienne zwi¹zane

select * from PRACOWNIK
where pracownik.nazwisko = :nazwisko
order by pracownik.nazwisko;





