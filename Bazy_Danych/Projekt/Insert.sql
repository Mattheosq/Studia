-- 1. KUPON
create sequence seq_id_kuponu
increment by 1
start with 1
maxvalue 9999999999999999999999999
minvalue 1
cache 20;

insert into KUPON
values (seq_id_kuponu.nextval,'2021/08/13','2021/10/12',43245,0.30);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/07/04','2022/07/11',49845,0.15);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/07/01','2021/07/08',87546,0.20);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/01/01','2022/03/01',12345,0.15);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/02/15','2022/05/15',67890,0.25);

insert into KUPON
values (seq_id_kuponu.nextval,'2021/12/01','2022/02/28',56789,0.10);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/05/01','2022/08/01',34567,0.30);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/07/01','2022/10/01',01234,0.40);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/08/15','2022/11/15',23456,0.50);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/09/01','2022/12/01',34567,0.60);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/10/01','2022/12/31',67890,0.70);

insert into KUPON
values (seq_id_kuponu.nextval,'2022/10/12','2022/12/12',63490,0.33);

-- 2. USLUGI
create sequence seq_id_uslugi
increment by 1
start with 1
maxvalue 9999999999999999999999999
minvalue 1
cache 20;

insert into USLUGI
values
(seq_id_uslugi.nextval, 'skladanie komputerow', 189.99, '5 dni','mozliwa do wyboru obudowa PC');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'skladanie komputerow gamingowych', 239.99, '7 dni','mozliwy wybor koloru swiatel LED');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'naprawa laptopow', 120, '4 dni','profesjonalna pomoc eksperta');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'skladanie komputerow', 159.99, '5 dni','');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'doradztwo technologiczne', 100, '1 dzien','wybor najlepszych czesci w stosunku do budzetu klienta');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'ochrona antywirusowa', 100, '1 dzien','');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'instalacja oprogramowania', 100, '','m.in. Windows, Mac');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'tworzenie kopii zapasowych danych', 60, '','');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'projektowanie stron internetowych', 289.99, '','');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'hosting stron internetowych', 289.99, '','');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'serwis drukarek', 80, '','');
insert into USLUGI
values
(seq_id_uslugi.nextval, 'utrzymanie sieci komputerowych', 140, '','');

-- 3. KLIENT
create sequence seq_id_klient
increment by 1
start with 1
maxvalue 9999999999999999999999999
minvalue 1
cache 20;

insert into KLIENT values (seq_id_klient.nextval, 'Mateusz', 'Grabowski','ul.Konopnicka 5/29, Warszawa','501409500');
insert into KLIENT values (seq_id_klient.nextval, 'Katarzyna', 'Kowalczyk', 'ul. Gdañska 4/20, Gdañsk', '');
insert into KLIENT values (seq_id_klient.nextval, 'Piotr', 'Kwiatkowski', 'ul. Poznañska 30, Poznañ', '506579515');
insert into KLIENT values (seq_id_klient.nextval, 'Agnieszka', 'Kaczmarek', '', '787409520');
insert into KLIENT values (seq_id_klient.nextval, 'Adam', 'Mazur', 'ul. £ódzka 6/40, £ódŸ', '506589525');
insert into KLIENT values (seq_id_klient.nextval, 'Ewa', 'Wojciechowska', 'ul. Katowicka 50, Katowice', '');
insert into KLIENT values (seq_id_klient.nextval, 'Zofia', 'Krawczyk', 'ul. Opolska 60, Opole', '506709530');
insert into KLIENT values (seq_id_klient.nextval, 'Mateusz', 'Piotrowski', '', '501409535');
insert into KLIENT values (seq_id_klient.nextval, 'Dariusz', 'Grabowski', 'ul. Bielska 70, Bielsko-Bia³a', '507765940');
insert into KLIENT values (seq_id_klient.nextval, 'Jolanta', 'Nowakowska', 'ul. Czêstochowska 80, Czêstochowa', '');
insert into KLIENT values (seq_id_klient.nextval, 'Sylwia', 'Koz³owska', '', '');
insert into KLIENT values (seq_id_klient.nextval, 'Zbigniew', 'Adamski', '', '');

-- 4. ZAMOWIENIE
create sequence seq_id_zamowienie
increment by 1
start with 1
maxvalue 9999999999999999999999999
minvalue 1
cache 20;

insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 3048, 'zrealizowano','na miejscu','2022/07/05', 2,7,1);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 4119, 'zrealizowano','wysylka','2022/09/11', 8,1,1);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 4120, 'anulowano','wysylka','2022/09/11', 8,'',1);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 3928, 'zrealizowano','na miejscu','2022/07/02', 8,6,12);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 5137, 'zrealizowano','wysylka','2022/09/11', '',6,2);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 5218, 'zrealizowano','paczkomat','2022/10/24', 11,6,3);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 5370, 'zrealizowano','na miejscu','2022/11/24', 11,'',4);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 1112, 'zrealizowano','paczkomat','2021/08/15', 1,4,4);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 1001, 'anulowano','na miejscu','2020/04/17', '','',5);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 1012, 'zrealizowano','paczkomat','2020/07/02', '','',6);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 1076, 'anulowano','na miejscu','2021/11/11', '','',7);
insert into ZAMOWIENIE
values
(seq_id_zamowienie.nextval, 1089, 'zrealizowano','wysylka','2022/05/10', '','',8);


-- 5. FEEDBACK
create sequence seq_id_feedback
increment by 1
start with 1
maxvalue 9999999999999999999999999
minvalue 1
cache 20;

insert into FEEDBACK values (seq_id_feedback.nextval, 10, 'bardzo szybko zrealizowano zamowienie', '2022/07/12', 'Dziekujemy za pozytywna ocene', 1, 1); 
insert into FEEDBACK values (seq_id_feedback.nextval, 6, 'dlugi czas oczekiwania', '2022/09/24', 'Dziekujemy za pozytywna ocene', 2, 1); 
insert into FEEDBACK values (seq_id_feedback.nextval, 10, 'wyrozumiala obsluga', '2022/09/11', '', 3, 1); 
insert into FEEDBACK values (seq_id_feedback.nextval, 8, 'wszystko dziala', '2022/07/07', 'Dziekujemy za pozytywna ocene', 4, 12); 
insert into FEEDBACK values (seq_id_feedback.nextval, 2, 'dlugi czas oczekiwania', '2022/10/01', 'Przepraszamy za niedogodnosci', 5, 2); 
insert into FEEDBACK values (seq_id_feedback.nextval, 4, '', '2022/10/28', 'Przepraszamy za niedogodnosci', 6, 3); 
insert into FEEDBACK values (seq_id_feedback.nextval, 9, 'bardzo mila obsluga', '2022/11/29', '', 7, 4); 
insert into FEEDBACK values (seq_id_feedback.nextval, 7, '', '2021/08/20', '', 8, 4); 
insert into FEEDBACK values (seq_id_feedback.nextval, 10, 'wyrozumiala obsluga', '2022/08/06', '', 9, 5); 
insert into FEEDBACK values (seq_id_feedback.nextval, 8, '', '2020/07/06', '', 10, 6); 
insert into FEEDBACK values (seq_id_feedback.nextval, 10, 'wyrozumiale podejscie do klienta', '2021/11/12', '', 11, 7); 
insert into FEEDBACK values (seq_id_feedback.nextval, 9, 'szybko dotarla przesylka', '2022/05/12', '', 12, 8);

-- 6. PRODUCENT

insert into PRODUCENT values ('Firma A', 'karty graficzne', 'Polska', '2000/04/15', 9);
insert into PRODUCENT values ('Firma B', 'procesory', 'Niemcy', '1997/06/23', 10);
insert into PRODUCENT values ('Firma C', 'monitory', 'Stany Zjednoczone', '1989/01/20', 10);
insert into PRODUCENT values ('Firma D', 'klawiatury', 'Stany Zjednoczone', '2007/06/18', '');
insert into PRODUCENT values ('Firma E', 'sluchawki', 'Stany Zjednoczone', '2004/11/23', 9);
insert into PRODUCENT values ('Firma F', 'karty graficzne', 'Stany Zjednoczone', '1996/03/13', 6);
insert into PRODUCENT values ('Firma G', 'komputery', 'Stany Zjednoczone', '2005/07/02', '');
insert into PRODUCENT values ('Firma H', 'laptopy', 'Stany Zjednoczone', '2005/04/15', 6);
insert into PRODUCENT values ('Firma I', 'karty graficzne', 'Chiny', '2017/10/09', 5);
insert into PRODUCENT values ('Firma J', 'procesory', 'Stany Zjednoczone', '2000/05/12', 8);
insert into PRODUCENT values ('Firma K', 'procesory', 'Francja', '2002/07/23', 4);
insert into PRODUCENT values ('Firma L', 'monitory', 'Francja', '2000/04/15', 3);

-- 7. PRODUKT

insert into PRODUKT values ('GTX 1080', 1799.99, 'karta graficzna', 'wypuszczona na rynek w 2016 roku', 'Firma A');
insert into PRODUKT values ('RTX 2060', 3299.99, 'karta graficzna', 'wypuszczona na rynek w 2020 roku', 'Firma A');
insert into PRODUKT values ('RTX 4090', 3899.79, 'karta graficzna', '', 'Firma A');
insert into PRODUKT values ('i5-8400', 684.99, 'procesor', 'wypuszczony na rynek w 2017 roku', 'Firma J');
insert into PRODUKT values ('RX 7900 XTX', 2799, 'karta graficzna', '', 'Firma F');
insert into PRODUKT values ('i5-13600KF', 1529, 'procesor', '', 'Firma J');
insert into PRODUKT values ('i7-13700K', 2169, 'procesor', '', 'Firma J');
insert into PRODUKT values ('i9-13900KF', 2849, 'procesor', '', 'Firma J');
insert into PRODUKT values ('Acer EK240YCbi', 479, 'monitor', 'dobrej jakosci monitor', 'Firma C');
insert into PRODUKT values ('G4M3R HERO', 7800, 'komputer', '', 'Firma G');
insert into PRODUKT values ('Logitech G PRO X GAMING', 499, 'sluchawki', '', 'Firma E');
insert into PRODUKT values ('HP X24ih Gaming', 479, 'monitor', '', 'Firma L');

-- 8. POZYCJE_ZAMOWIEN

insert into POZYCJE_ZAMOWIEN values ('RTX 2060', 1, 1, 'czerwony', 'tak');
insert into POZYCJE_ZAMOWIEN values ('HP X24ih Gaming', 1, 1, 'czarny', 'nie');
insert into POZYCJE_ZAMOWIEN values ('Logitech G PRO X GAMING', 1, 2, '', 'tak');

insert into POZYCJE_ZAMOWIEN values ('GTX 1080', 2, 5, '', 'nie');

insert into POZYCJE_ZAMOWIEN values ('GTX 1080', 3, 5, '', 'nie');

insert into POZYCJE_ZAMOWIEN values ('GTX 1080', 4, 1, 'zielony', 'tak');
insert into POZYCJE_ZAMOWIEN values ('HP X24ih Gaming', 4, 1, '', 'nie');
insert into POZYCJE_ZAMOWIEN values ('Acer EK240YCbi', 4, 1, 'czarny', 'tak');

insert into POZYCJE_ZAMOWIEN values ('i9-13900KF', 5, 1, '', 'tak');
insert into POZYCJE_ZAMOWIEN values ('Acer EK240YCbi', 5, 2, '', 'nie');

insert into POZYCJE_ZAMOWIEN values ('RX 7900 XTX', 6, 1, '', 'tak');

insert into POZYCJE_ZAMOWIEN values ('i7-13700K', 7, 2, 'zloty', 'nie');

insert into POZYCJE_ZAMOWIEN values ('RTX 2060', 8, 1, '', 'nie');

insert into POZYCJE_ZAMOWIEN values ('RTX 4090', 9, 3, '', 'tak');

insert into POZYCJE_ZAMOWIEN values ('i5-8400', 10, 12, '', 'tak');

insert into POZYCJE_ZAMOWIEN values ('G4M3R HERO', 11, 1, 'srebrny', 'nie');

insert into POZYCJE_ZAMOWIEN values ('G4M3R HERO', 12, 3, '', 'tak');

-- 9. ODDZIAL

insert into ODDZIAL values ('Sklep_Katowice','ul. Fronczewska 26, Katowice','301200300','sklep_katowice@gmail.com','Adam Niemiec');
insert into ODDZIAL values ('Sklep_Krakow', 'ul. Karmelicka 34, Krakow', '302200310', 'sklep_krakow@gmail.com', 'Anna Nowak');
insert into ODDZIAL values ('Sklep_Gdansk', 'ul. Nowe Ogrody 12, Gdansk', '303300320', 'sklep_gdansk@gmail.com', '');
insert into ODDZIAL values ('Sklep_Szczecin', 'ul. Wojska Polskiego 78, Szczecin', '304400330', 'sklep_szczecin@gmail.com', 'Magdalena Kowalska');
insert into ODDZIAL values ('Sklep_Lodz', 'ul. Piotrkowska 45, Lodz', '305500340', '', 'Tomasz Nowak');
insert into ODDZIAL values ('Sklep_Wroclaw', 'ul. Grunwaldzka 32, Wroclaw', '306600350', 'sklep_wroclaw@gmail.com', 'Ewa Kowalska');
insert into ODDZIAL values ('Sklep_Poznan', 'ul. Stary Rynek 12, Poznan', '307700360', 'sklep_poznan@gmail.com', 'Marek Zielinski');
insert into ODDZIAL values ('Sklep_Gdynia', 'ul. Wielkopolska 12, Gdynia', '308800370', '', 'Agata Nowak');
insert into ODDZIAL values ('Sklep_Bydgoszcz', 'ul. Fordonska 12, Bydgoszcz', '309900380', 'sklep_bydgoszcz@gmail.com', 'Jan Kowalski');
insert into ODDZIAL values ('Sklep_Lublin', 'ul. Krakowska 12, Lublin', '301000390', '', '');
insert into ODDZIAL values ('Sklep_Rzeszow', 'ul. Kolejowa 12, Rzeszow', '302000400', 'sklep_rzeszow@gmail.com', 'Mariusz Kowalski');
insert into ODDZIAL values ('Sklep_Opole', 'ul. Gliwicka 12, Opole', '303000410', 'sklep_opole@gmail.com', 'Katarzyna Nowak');

-- 10. MAGAZYN
create sequence seq_id_magazyn
increment by 1
start with 1
maxvalue 9999999999999999999999999
minvalue 1
cache 20;

insert into MAGAZYN values (seq_id_magazyn.nextval, '2000 m^3', '500 m^2', 'Magazyn nr 1','Sklep_Katowice');
insert into MAGAZYN values (seq_id_magazyn.nextval, '2550 m^3', '600 m^2', 'Magazyn nr 2','Sklep_Katowice');
insert into MAGAZYN values (seq_id_magazyn.nextval, '1800 m^3', '400 m^2', 'Magazyn nr 3','Sklep_Katowice');

insert into MAGAZYN values (seq_id_magazyn.nextval, '1550 m^3', '420 m^2', 'Magazyn nr 1','Sklep_Krakow');
insert into MAGAZYN values (seq_id_magazyn.nextval, '3000 m^3', '700 m^2', 'Magazyn nr 2','Sklep_Krakow');

insert into MAGAZYN values (seq_id_magazyn.nextval, '1800 m^3', '400 m^2', '','Sklep_Gdansk');

insert into MAGAZYN values (seq_id_magazyn.nextval, '1800 m^3', '400 m^2', '','Sklep_Szczecin');

insert into MAGAZYN values (seq_id_magazyn.nextval, '4000 m^3', '500 m^2', '','Sklep_Lodz');

insert into MAGAZYN values (seq_id_magazyn.nextval, '5000 m^3', '1000 m^2', '','Sklep_Wroclaw');

insert into MAGAZYN values (seq_id_magazyn.nextval, '2300 m^3', '700 m^2', '','Sklep_Poznan');

insert into MAGAZYN values (seq_id_magazyn.nextval, '2700 m^3', '700 m^2', '','Sklep_Gdynia');

insert into MAGAZYN values (seq_id_magazyn.nextval, '1800 m^3', '550 m^2', '','Sklep_Bydgoszcz');

insert into MAGAZYN values (seq_id_magazyn.nextval, '1800 m^3', '400 m^2', '','Sklep_Lublin');

insert into MAGAZYN values (seq_id_magazyn.nextval, '1800 m^3', '400 m^2', '','Sklep_Rzeszow');

insert into MAGAZYN values (seq_id_magazyn.nextval, '1000 m^3', '380 m^2', '','Sklep_Opole');

-- 11. REGAL
--katowice 1
insert into REGAL values ('GTX 1080', 1, '1A', 200, '2022/07/04');
insert into REGAL values ('RTX 2060', 1, '2A', 450, '2022/04/04');
insert into REGAL values ('RTX 4090', 1, '2B', 200, '2022/07/04');
-- katowice 2
insert into REGAL values ('i5-13600KF', 2, '1D', 376, '2022/03/11');
insert into REGAL values ('i7-13700K', 2, '3A', 874, '2021/03/28');
insert into REGAL values ('i9-13900KF', 2, '4F', 937, '2022/09/09');
-- katowice 3
insert into REGAL values ('Acer EK240YCbi', 3, '1A', 510, '2021/03/28');
insert into REGAL values ('HP X24ih Gaming', 3, '1C', 124, '2022/09/08');
-- krakow 1
insert into REGAL values ('GTX 1080', 4, '1A', 873, '2022/10/19');
insert into REGAL values ('RTX 2060', 4, '2D', 431, '2022/04/14');
insert into REGAL values ('i9-13900KF', 4, '1D', 785, '2022/06/30');
-- krakow 2
insert into REGAL values ('G4M3R HERO', 5, '1A', 430, '2022/05/29');

-- gdansk
insert into REGAL values ('G4M3R HERO', 6, '6D', 108, '2022/02/14');

-- szczecin
insert into REGAL values ('G4M3R HERO', 7, '1A', 1400, '2022/11/03');
insert into REGAL values ('Logitech G PRO X GAMING', 7, '1B', 2600, '2021/12/24');

-- lodz
insert into REGAL values ('HP X24ih Gaming', 8, '2A', 320, '2020/10/21');

-- reszta
insert into REGAL values ('HP X24ih Gaming', 9, '1C', 632, '2020/10/18');
insert into REGAL values ('GTX 1080', 10, '2A', 2100, '2020/10/21');
insert into REGAL values ('RTX 2060', 11, '5A', 3000, '2020/10/18');
insert into REGAL values ('RTX 4090', 12, '3B', 3900, '2021/04/18');
insert into REGAL values ('i5-8400', 13, '4G', 282, '2022/08/30');
insert into REGAL values ('Logitech G PRO X GAMING', 14, '1H', 876, '2021/02/03');
insert into REGAL values ('i9-13900KF', 15, '1B', 512, '2021/12/09');

-- 12. PRACOWNIK
create sequence seq_id_pracownik
increment by 1
start with 1
maxvalue 9999999999999999999999999
minvalue 1
cache 20;
-- katowice
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Maks', 'Ratigowski', 'ul.Odkryta 4/28, Warszawa', 3200, 1);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Anna', 'Nowak', 'ul. Stroma 2, Warszawa', 3400, 1);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Adam', 'Michalski', 'ul. S³oneczna 3, Katowice', 3320, 1);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Dorian', 'Kowalczyk', 'ul. Kwiatowa 4, Katowice', 2729, 2);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Mieszko', 'Kowalczyk', 'ul. D³uga 5/23, Katowice', 3200, 2);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Anastazy', 'Szulc', 'ul. Zielona 5/2, Katowice', 4878, 3);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Ariel', 'Czerwiñski', 'ul. Spokojna 3/18, Krakow', 3200, 3);
-- krakow
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Kacper', 'Wójcik', 'ul.B³otna 10, Krakow', 3200, 4);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Jaros³aw', 'W³odarczyk', 'ul.Aluzyjna 21, Krakow', 3200, 4);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Cezary', 'Kowalski', 'ul.Dworcowa 15, Krakow', 4993, 5);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Marcel', 'Laskowski', 'ul.Kopernika 5/16, Opole', 4195, 5);
-- reszta
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Florian', 'Lis', 'ul.Tulipanowa 2, Gdansk', 4344, 6);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Maks', 'Soko³owski', 'ul.Porannej Rosy 4, Gdansk', 4966, 6);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Mateusz', 'Baran', 'ul.Lesna 2/43, Szczecin', 2588, 7);
insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Roman', 'Górski', 'ul.Dworkowa 10, Szczecin', 2604, 7);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Andrzej', 'Mróz', 'ul.Prosta 19, Lodz', 2770, 8);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Andrzej', 'Kalinowski', 'ul.Koszykowa 2/13, Wroclaw', 3424, 9);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Boles³aw', 'Kalinowski', 'ul.Milenijna 20, Warszawa', 2514, 10);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Alan', 'Kalinowski', 'ul.Osiedle Mlodych 1/14, Gdynia', 4351, 11);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Janusz', 'Szulc', 'ul.Krakowska 32, Bydgoszcz', 5293, 12);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Olaf', 'Szymañski', 'ul.Warszawska 45, Lublin', 4023, 13);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Mateusz', 'Urbañski', 'ul.Perlowa 19, Rzeszow', 3770, 14);

insert into PRACOWNIK values (seq_id_pracownik.nextval, 'Dawid', 'Pawlak', 'ul.Krolowej Jadwigi 3/20, Opole', 2609, 15);





















