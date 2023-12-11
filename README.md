# Harjoitustyö
 
Harjoitustyö TAMKin C++ ohjelmointikurssille.

Ohjelma toimii ikään kuin pienenä pelinä, jossa sinun on tarkoitus varata huoneita hotellista ja tehdä töitä, 
jotta ansaitset rahaa. Kaikki koodi on kirjoitettu englanniksi, mutta ohjelman 
tekstit ovat suomeksi. Teksteissä ei kuitenkaan ole ääkkösiä ollenkaan, vaan ”ä” on korvattu ”a”:lla ja ”ö” on 
korvattu ”o”:lla.


Ohjelman perusmekaniikkoihin kuuluu esimerkiksi:
- Varaa huone, jotta voit nukkua ja edistyä seuraavaan päivään
- Joka päivä voit käydä töissä tietyn määrän, työn määrä määräytyy siitä, kuinka monta 
hotellihuonetta omistat (myös huoneen koko vaikuttaa)
- Peli päättyy, kun saavutat 1 000 000 € saldon

# Ohjelman käyttöliittymä
Kaikki mitä pelissä tapahtuu, tapahtuu ns. monivalintakäyttöliittymän ympärillä. Käyttöliittymän eri osioita 
on selitetty alla:

Aloitus 
- Aloitus osiossa selitetään pelin perusmekaniikat lyhyesti. Eteenpäin pääsee 
painamalla Enter-näppäintä.

Hotellin pääaula
- Pääaula on koko pelin perusta. Kaikki tiet vievät aina takaisin pääaulaan. 
Pääaulasta pääset muun muassa varaamaan huoneen, katselemaan 
varaamiasi huoneita, menemään töihin ja nukkumaan seuraavaan päivään.

Huoneen varaus
- Huoneen varaukseen pääsee valitsemalla ”1”. Tämän jälkeen saat vaihtoehdon 
valita haluatko yhden vai kahden henkilön huoneen. Huoneen saat valita 
vapaiden huoneiden listasta käyttämällä numeroita 10-19. Tämän jälkeen 
ohjelma antaa sinun valita kuinka moneksi yöksi haluat valita huoneen.

Huoneiden hallinta
- Valitsemalla ”2” pääset katsomaan mitä huoneita olet varannut. Täältä näet 
monta yötä huoneissasi on jäljellä ja niiden koon.

Työt
- Ohjelmassa voit ansaita rahaa käymällä töissä. Töihin pääset valitsemalla ”3”, 
jokaisena päivänä sinun tarvitsee käydä vähintään kerran töissä, tai muuten et 
voi edistyä seuraavaan päivään. Mahdollisten töiden määrä vaihtelee 
omistamiesi huoneiden perusteella. Jos omistat yhden henkilön huoneen, 
töiden määrä kasvaa yhdellä, jos omistat kahden henkilön huoneen, niin 
töiden määrä kasvaa kahdella.

Nukkuminen
- Kuten edellä mainittiin, voit nukkua vain, jos olet käynyt töissä ainakin kerran. 
Joka kerta kun olet nukkunut, riippuen kuinka pitkäksi ajaksi huone on varattu, 
saatat menettää huoneen varauksen. Muista myös, että tarvitsen ainakin 
yhden huoneen nukkuaksesi.

# Strategia 
Helpoin tapa edistyä pelissä on varata kahden henkilön huoneita mahdollisimman pitkäksi aikaa, tällä takaat 
mahdollisimman monta työkertaa päivän ajalle. Huoneilla on mahdollisuus olla 10-20% alennus, kannattaa 
siis valita näitä huoneita, jotta takaat suurimmat mahdolliset hyödyt huoneesta.
TÄRKEÄ: Testaamista varten ohjelmasta löytyy myös huijjauskomento, kun olet hotellin pääaulassa, käytä 
numeroa 9, ja peli antaa sinulle 999 999 €. Tämä on vapaasti käytettävissä.

# Päivissä edistyminen 
Ohjelman alussa ohjelma arpoo satunnaisen huoneiden määrän välillä 40-300. Noin 30% huoneista on 
valmiiksi varattuja, joten et voi valita näitä huoneita. Päivien edetessä jotkin näistä huoneista saattaa 
kuitenkin vapautua, mutta samaan aikaan jotkin huoneet saattavat muuttua varatuiksi.

# Lähdekoodin sisältö 
Ohjelma on jaettu eri tiedostoihin, joista tärkein on coreApplication.cpp ja coreApplication.h. Näissä 
tiedostoissa on kaikki tärkein ohjelmakoodi. Ohjelmaa on pyritty kommentoimaan mahdollisimman hyvin ja 
selvästi, mutta kuten koodikin, on nämäkin kirjoitettu englanniksi.
Ohjelma toteuttaa kaiken laskennan jokaisen käyttäjän antaman vastauksen jälkeen.
Ohjelma käyttää C++20 standardia ja on käännetty GCC g++ kääntäjällä käyttäen tätä komentoa:
- g++ -o HarjoitusTyo.exe src/*.cpp -Iinclude -static -static-libgcc -std=c++20
