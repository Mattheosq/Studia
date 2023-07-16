
CREATE TABLE feedback (
    id_feedback              INTEGER NOT NULL,
    ocena                    INTEGER NOT NULL,
    komentarz                VARCHAR2(255),
    data_wystawienia         DATE NOT NULL,
    odpowiedz                VARCHAR2(255),
    zamowienie_id_zamowienie INTEGER NOT NULL,
    klient_id_klient         INTEGER NOT NULL
);

CREATE UNIQUE INDEX feedback__idx ON
    feedback (
        zamowienie_id_zamowienie
    ASC );

ALTER TABLE feedback ADD CONSTRAINT feedback_pk PRIMARY KEY ( id_feedback );

CREATE TABLE klient (
    id_klient   INTEGER NOT NULL,
    imie        VARCHAR2(50) NOT NULL,
    nazwisko    VARCHAR2(50) NOT NULL,
    adres       VARCHAR2(100),
    nr_telefonu VARCHAR2(10)
);

ALTER TABLE klient ADD CONSTRAINT klient_pk PRIMARY KEY ( id_klient );

CREATE TABLE kupon (
    id_kuponu  INTEGER NOT NULL,
    od         DATE NOT NULL,
    do         DATE NOT NULL,
    kod_kuponu INTEGER NOT NULL,
    znizka     NUMBER(3, 2) NOT NULL
);

ALTER TABLE kupon ADD CONSTRAINT kupon_pk PRIMARY KEY ( id_kuponu );

CREATE TABLE magazyn (
    id_magazyn            INTEGER NOT NULL,
    pojemnosc             VARCHAR2(20) NOT NULL,
    powierzchnia          VARCHAR2(20) NOT NULL,
    notatka               VARCHAR2(100),
    oddzial_nazwa_oddzial VARCHAR2(50) NOT NULL
);

ALTER TABLE magazyn ADD CONSTRAINT magazyn_pk PRIMARY KEY ( id_magazyn );

CREATE TABLE oddzial (
    nazwa_oddzial VARCHAR2(50) NOT NULL,
    adres         VARCHAR2(100) NOT NULL,
    nr_telefonu   VARCHAR2(10) NOT NULL,
    email         VARCHAR2(30),
    kierownik     VARCHAR2(100)
);

ALTER TABLE oddzial ADD CONSTRAINT oddzial_pk PRIMARY KEY ( nazwa_oddzial );

CREATE TABLE pozycje_zamowien (
    produkt_nazwa            VARCHAR2(50) NOT NULL,
    zamowienie_id_zamowienie INTEGER NOT NULL,
    ilosc                    INTEGER NOT NULL,
    kolor                    VARCHAR2(50),
    dluzsza_gwarancja        VARCHAR2(10) NOT NULL
);

ALTER TABLE pozycje_zamowien ADD CONSTRAINT pozycje_zamowien_pk PRIMARY KEY ( produkt_nazwa,
                                                                              zamowienie_id_zamowienie );

CREATE TABLE pracownik (
    id_pracownik       INTEGER NOT NULL,
    imie               VARCHAR2(50) NOT NULL,
    nazwisko           VARCHAR2(50) NOT NULL,
    adres              VARCHAR2(100) NOT NULL,
    pensja             NUMBER NOT NULL,
    magazyn_id_magazyn INTEGER
);

ALTER TABLE pracownik ADD CONSTRAINT pracownik_pk PRIMARY KEY ( id_pracownik );

CREATE TABLE producent (
    nazwa          VARCHAR2(50) NOT NULL,
    dziedzina      VARCHAR2(100) NOT NULL,
    kraj           VARCHAR2(50) NOT NULL,
    data_zalozenia DATE NOT NULL,
    rating         INTEGER
);

ALTER TABLE producent ADD CONSTRAINT producent_pk PRIMARY KEY ( nazwa );

CREATE TABLE produkt (
    nazwa           VARCHAR2(50) NOT NULL,
    cena            NUMBER(9, 2) NOT NULL,
    kategoria       VARCHAR2(50) NOT NULL,
    opis            VARCHAR2(255),
    producent_nazwa VARCHAR2(50) NOT NULL
);

ALTER TABLE produkt ADD CONSTRAINT produkt_pk PRIMARY KEY ( nazwa );

CREATE TABLE regal (
    produkt_nazwa      VARCHAR2(50) NOT NULL,
    magazyn_id_magazyn INTEGER NOT NULL,
    pozycja            VARCHAR2(20) NOT NULL,
    ilosc              INTEGER NOT NULL,
    ostatnio_dodano    DATE NOT NULL
);

ALTER TABLE regal ADD CONSTRAINT regal_pk PRIMARY KEY ( produkt_nazwa,
                                                        magazyn_id_magazyn );

CREATE TABLE uslugi (
    id_uslugi       INTEGER NOT NULL,
    rodzaj          VARCHAR2(50) NOT NULL,
    cena            NUMBER NOT NULL,
    czas_realizacji VARCHAR2(20),
    notatka         VARCHAR2(100)
);

ALTER TABLE uslugi ADD CONSTRAINT uslugi_pk PRIMARY KEY ( id_uslugi );

CREATE TABLE zamowienie (
    id_zamowienie    INTEGER NOT NULL,
    nr_faktury       INTEGER NOT NULL,
    status           VARCHAR2(100),
    metoda_odbioru   VARCHAR2(100),
    data_utworzenia  DATE NOT NULL,
    kupon_id_kuponu  INTEGER,
    uslugi_id_uslugi INTEGER,
    klient_id_klient INTEGER NOT NULL
);

ALTER TABLE zamowienie ADD CONSTRAINT zamowienie_pk PRIMARY KEY ( id_zamowienie );

ALTER TABLE feedback
    ADD CONSTRAINT feedback_klient_fk FOREIGN KEY ( klient_id_klient )
        REFERENCES klient ( id_klient );

ALTER TABLE feedback
    ADD CONSTRAINT feedback_zamowienie_fk FOREIGN KEY ( zamowienie_id_zamowienie )
        REFERENCES zamowienie ( id_zamowienie );

ALTER TABLE magazyn
    ADD CONSTRAINT magazyn_oddzial_fk FOREIGN KEY ( oddzial_nazwa_oddzial )
        REFERENCES oddzial ( nazwa_oddzial );

ALTER TABLE pozycje_zamowien
    ADD CONSTRAINT pozycje_zamowien_produkt_fk FOREIGN KEY ( produkt_nazwa )
        REFERENCES produkt ( nazwa );

ALTER TABLE pozycje_zamowien
    ADD CONSTRAINT pozycje_zamowien_zamowienie_fk FOREIGN KEY ( zamowienie_id_zamowienie )
        REFERENCES zamowienie ( id_zamowienie );

ALTER TABLE pracownik
    ADD CONSTRAINT pracownik_magazyn_fk FOREIGN KEY ( magazyn_id_magazyn )
        REFERENCES magazyn ( id_magazyn );

ALTER TABLE produkt
    ADD CONSTRAINT produkt_producent_fk FOREIGN KEY ( producent_nazwa )
        REFERENCES producent ( nazwa );

ALTER TABLE regal
    ADD CONSTRAINT regal_magazyn_fk FOREIGN KEY ( magazyn_id_magazyn )
        REFERENCES magazyn ( id_magazyn );

ALTER TABLE regal
    ADD CONSTRAINT regal_produkt_fk FOREIGN KEY ( produkt_nazwa )
        REFERENCES produkt ( nazwa );

ALTER TABLE zamowienie
    ADD CONSTRAINT zamowienie_klient_fk FOREIGN KEY ( klient_id_klient )
        REFERENCES klient ( id_klient );

ALTER TABLE zamowienie
    ADD CONSTRAINT zamowienie_kupon_fk FOREIGN KEY ( kupon_id_kuponu )
        REFERENCES kupon ( id_kuponu );

ALTER TABLE zamowienie
    ADD CONSTRAINT zamowienie_uslugi_fk FOREIGN KEY ( uslugi_id_uslugi )
        REFERENCES uslugi ( id_uslugi );
