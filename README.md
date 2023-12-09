# Projektityo
 
Harjoitustyö TAMKin C++ ohjelmointikurssille.

Ohjelma toimii ikään kuin pienenä pelinä, jossa sinun on tarkoitus varata huoneita hotellista ja tehdä töitä, 
jotta ansaitset rahaa. 
Arvosana tavoitteeni on 5. Uskon, että ansaitsen arvosanani lisäyksieni ja yleisen laadun takia. Ohjelma 
myös noudattaa 4-5 arvosanan tehtävänantoa. Kaikki koodi on kirjoitettu englanniksi, mutta ohjelman 
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
