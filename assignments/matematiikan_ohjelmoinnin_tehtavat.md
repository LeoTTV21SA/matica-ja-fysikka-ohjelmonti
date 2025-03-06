# Tehtävä 1: Fuktioiden kuvaajien piirtäminen:
Palautustiedosto: **submissions/t1/test_draw_functions.cpp, submissions/t1/vastaukset.md ja screenshotit submissions/t1/xxx.png**

Tee sovellus, joka piirtää seuraavanlaisia funktioita ruudulle: 
- Polynomeja, kuten: 
    - x*x
    - x*x
    - 2*x*x*x + 5*x*x + 6*x + 2. sin(x)
    - cos(x)
    - e^x
    - ln(x)
    - sqrt(x)
    - sin(x)*cos(x)
    - 2.3*sin(x)*1.2*cos(x)
    - 2.3*sin(x)+1.2*cos(x)
    - x^x 
    - jne (keksi itse loput funktiot ja kokeile! :)).
- Piirrä myös kyseisten funktioiden derivaattoja.
- Muokkaa funktioiden "parametrejä", lisää animointeja ajan avulla ja testaile ja hahmottele funktioiden käyttäytymistä eri tilanteissa (testaa **minimissään 20** eri funktion toimintaa)
- Muokkaa testisovellus sellaiseksi, että se ottaa automaattisesti screenshotteja kustakin funktion kuvaajasta. Kuvien palautus submissions/t1/xxx.png, missä xxx on juokseva numero.
- Palauta repositoryyn cpp, markdown ja png:t, jossa upotettuna png screenshotit.

# Tehtävä 2: Numeerinen integrointi Newtonin menetelmällä:
Palautustiedosto: **submissions/t2/test_integration.cpp, submissions/t2/vastaukset.md, + screenshotit**
- Etsi funktion f(x) = x^3 − 1 juuri Newtonin menetelmällä, kun x0=0.5.
- Etsi yhtälön f(x) = cos(x)−x^3 = 0 ratkaisu Newtonin menetelmällä, kun x0=0.5.
- Etsi funktion f(x) = (x^4 + 11*x^3 + 8*x^2 + 20*x - 10) / 1000 minimi. Millä x:n arvolla se saadaan.
- ~~Mallinna Koronaviruksen leviämistä: https://thl.fi/documents/10531/5814325/THL+korona+mallinnuswebinaarin+kalvot+20.4.2020.pdf/cc23f5f0-87a0-8080-7b5c-121b5532bf5c. Piirrä alttiden ja tartunnan saaneiden määrä ajan (aika viikoissa) funktiona, kun R0=4.4, Tartuttavuuden kesto (D) 7 vrk. Paljonko jää alttiita ihmisiä, kun aikaa on kulunut 30 viikkoa epidemian alkamisesta? Ento jos R0 on 2,4. Paljonko siinä tapauksessa jää alttiita ihmisiä?~~
- Muokkaa testisovellus sellaiseksi, että se tulostaa oikean vastausksen konsoliin ja lisäksi piirtää ratkaistavan funktion ruudulle. Tallenna kukin funktio png-tiedostoon ja luo markdown syntaksin tiedosto **submissions/t2/vastaukset.md**, jossa tulostetaan nätisti (Kukin funktio oman otsikon alle) tehtävien funktiot tekstinä, niiden juuret ja linkki screensottiin.

# Tehtävä 3: Vektorien ja matriisien toiminnallisuuden ohjelmointi:
Palautustiedostot: **submissions/t3/test_math.cpp, submissions/t3/math.h, submissions/t3/math.cpp**
- Koodaa [assignments/math.h](assignments/math.h)  tiedoston määrittelyjen mukaiset toiminnot tiedostoon submissions/t3/math.cpp ja testaa toiminta testisovelluksen (submissions/t3/test_math.cpp) avulla. Voit myös tehdä oman näköisesi headerin (sellainen matikkakirjasto kuin haluat), pääasia että on oleelliset funktiot koodattuna, niitä tarvitaan myöhemmin.
- Luo testisovelluskeen testicaset matematiikka toiminnallisuuden testaamiseen. Mikäli jokin testicase feilaa, sovelluksen pitää palauttaa negatiivinen paluuarvo (jotta pipeline menee punaiseksi)
- Lisää gitlabin pipelineen build stagen lisäksi myös test stage, jossa käännöksen lisäksi ajetaan test_math sovellus ja testilogi tallennetaan build artifakteihin.

# Tehtävä 4: Separated axis theorem:
Palautustiedostot: **submissions/t4/test_sat.cpp, submissions/t4/sat.h**
- Googlaa tekniikka "Separated axis theorem" ja toteuta kahden suorakaiteen törmäystarkistus tiedostoon sat.h (käytä koodaamiasi lineaarialgebran funktioita tässä apuna).
- Ohjelmoi testisovellus main_sat.cpp, jolla voi testata törmäysten toimintaa. Käyttäjän pitää voida liikuttaa ja rotatoida suorakaiteita. Testisovellus pitää koodata käyttäen MikRoPlot-kirjastoa.

