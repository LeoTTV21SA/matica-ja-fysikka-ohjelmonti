# Funktionaalinen ohjelmointi
Funktionaalinen ohjelmointi on ohjelmointiparadigma, jossa korostetaan funktioiden käyttöä ongelman ratkaisemisessa. Se on ohjelmointityyli, joka keskittyy selkeän, tiiviin ja helposti ymmärrettävän koodin kirjoittamiseen. C++:ssa on useita funktionaalisen ohjelmoinnin periaatteita, joita voi noudattaa kirjoittaakseen parempaa koodia (modulaarinen, helpompi ylläpitää, jne...).

- **Muuttumattomuus:** Muuttumattomuus tarkoittaa, että kun muuttuja tai objekti on luotu, sen arvoa ei voi muuttaa. C++:ssa tämä voidaan saavuttaa käyttämällä const-muuttujia ja -viitteitä.

- **Puhtaat funktiot:** Puhtaat funktiot ovat funktioita, joilla ei ole sivuvaikutuksia ja jotka aina palauttavat saman tulosteen samalle syötteelle. Funktionaalinen ohjelmointi pyrkii välttämään sivuvaikutuksia, eli muutoksia järjestelmän tilaan, jotka eivät liity funktion palauttamaan arvoon. Tämä tekee ohjelmasta helpommin hallittavan ja vähentää virheiden todennäköisyyttä. C++:ssa tätä voidaan toteuttaa esimerkiksi käyttämällä const-määritteitä ja luomalla kopioita alkuperäisistä arvoista, sen sijaan että niitä muutettaisiin suoraan.

- **Tilan välttäminen:** Tila on kaikki tiedot, jotka tallennetaan ohjelmaan ja jotka voivat muuttua ajan myötä. Funktionaalisessa ohjelmoinnissa on tärkeää välttää tilaa mahdollisimman paljon. C++:ssa tämä voidaan saavuttaa käyttämällä const-muuttujia ja välttämällä globaaleja muuttujia.

- **Korkeamman asteen funktiot:** Korkeamman asteen funktiot ovat funktioita, jotka ottavat muita funktioita argumentteina tai palauttavat funktioita tulosteenaan. C++:ssa tämä voidaan saavuttaa käyttämällä funktioluokkia, funktio-osoittimia tai lambda-lausekkeita.

- **Rekursio:** Rekursio on tekniikka, jossa funktio kutsuu itseään. Se on voimakas työkalu funktionaalisessa ohjelmoinnissa ja sitä voidaan käyttää monien ongelmien ratkaisemiseen. C++:ssa rekursiota voidaan käyttää algoritmien, kuten lajittelun ja haun, toteuttamiseen. Funktionaalinen ohjelmointi kannustaa rekursion käyttöön. Tämä tekee koodista helpommin ymmärrettävää ja lukuisten silmukoiden sijaan rekursio voi olla tehokkaampi tapa käsitellä tiettyjä ongelmia. C++:ssa rekursion käyttöä on hyvä harkita tarkasti, sillä se voi aiheuttaa ylivuototilanteita ja hidastaa suoritusta.

- **Funktionaalinen eriyttäminen:** Funktionaalinen ohjelmointi pyrkii erottamaan datan ja funktion toisistaan. Tämä tarkoittaa, että funktiot eivät ole sidoksissa tiettyihin datarakenteisiin tai muuttujiin, vaan ne toimivat yleisesti eri datatyypeilla. C++:ssa tätä voidaan toteuttaa käyttämällä template-tyyppejä.

- **Lambda-lausekkeet:** ovat funktionaalisen ohjelmoinnin käsite, joka mahdollistaa anonyymien funktioiden luomisen suoraan koodiin. Lambda-lauseke on yksinkertainen tapa luoda funktioita, jotka voivat suorittaa yksinkertaisia tehtäviä ilman, että tarvitsee luoda uusia funktioita tai luokkia.

# Map, fold ja filter -funktiot

Map, fold ja filter ovat yleisiä funktionaalisia ohjelmointityökaluja, joita voidaan käyttää monien erilaisten ongelmien ratkaisemiseen. Näitä funktioita voidaan käyttää useissa ohjelmointikielissä, kuten C++, Python ja JavaScript.

- **Map:** Map-funktio ottaa syötteenään listan tai muun kokoelman ja soveltaa annettua funktiota jokaiseen sen alkioon. Se palauttaa uuden kokoelman, joka sisältää kaikki alkuperäisen kokoelman alkiot, joihin funktio on sovellettu. Map-funktio on kätevä silloin, kun halutaan tehdä muunnoksia kokoelman jokaiseen alkioon, esimerkiksi kaikkien alkion neliöjuurien laskemiseen.

- **Fold:** Fold-funktio (tunnetaan myös nimellä reduce) ottaa syötteenään kokoelman, johon se soveltaa annettua funktiota toistuvasti, kunnes lopulta palauttaa yhden arvon. Fold-funktio käyttää kokoelman alkiota ja sitä vastaavaa arvoa soveltamalla funktiota uuteen alkioon, joka käytetään seuraavassa iteraatiossa. Esimerkiksi fold-funktiota voidaan käyttää summien tai tuotteiden laskemiseen kokoelmasta.

- **Filter:** Filter-funktio ottaa syötteenään kokoelman ja palauttaa uuden kokoelman, joka sisältää vain ne alkio, jotka täyttävät annetun ehdollisen lausekkeen. Filter-funktio on hyödyllinen silloin, kun halutaan suodattaa kokoelmasta tietyt arvot, esimerkiksi poistamalla kaikki negatiiviset luvut tai säilyttämällä vain tietyt merkkijonot.

Näitä funktioita voidaan yhdistellä monin eri tavoin ratkaisemaan monimutkaisia ongelmia, ja ne ovat hyödyllisiä työkaluja funktionaalisen ohjelmoinnin työkalupakissa.

# Muita funktionaalisen ohjelmoinnin käsitteitä (ei käsitellä tarkemmin)

- **Monadi:** Monadit ovat funktionaalisen ohjelmoinnin käsitteitä, jotka auttavat käsittelemään sivuvaikutuksia, kuten syötteiden ja tulosteiden käsittelyä. Monadit ovat tietyntyyppisiä konteksteja, jotka mahdollistavat sivuvaikutusten käsittelemisen funktionaalisesti. Esimerkkejä monadeista C++:ssa ovat std::optional ja std::vector.

- **Funktori:** Funktorit ovat funktionaalisen ohjelmoinnin käsitteitä, jotka mahdollistavat funktioiden soveltamisen useille eri tietotyypeille. Funktori on luokka tai rakenne, joka mahdollistaa funktioiden käytön monipuolisesti. Esimerkkejä funktoreista C++:ssa ovat std::vector ja std::map.

- **Currytys:** Currytys on funktionaalisen ohjelmoinnin käsite, joka mahdollistaa funktioiden osittaisen soveltamisen. Currytys tarkoittaa sitä, että funktio, joka yleensä ottaa useita argumentteja, jaetaan osiin. Näin saadaan uusia funktioita, jotka ottavat vähemmän argumentteja. Esimerkiksi funktio, joka laskee kahden luvun summan, voidaan kääntää siten, että se palauttaa uuden funktion, joka odottaa toista argumenttia myöhemmin.

- **Lazy evaluation (laiska evaluointi):** Lazy evaluation tarkoittaa, että koodin suoritus lykätään mahdollisimman pitkälle. Tämä tarkoittaa sitä, että funktioiden arvot lasketaan vasta kun niitä tarvitaan, eikä ennen sitä. Tämä voi auttaa parantamaan suorituskykyä, koska turhia laskutoimituksia ei tehdä. Esimerkiksi, jos käytetään virtaa (stream) syötteen lukuun, lazy evaluation mahdollistaa sen, että syötettä ei ladata kokonaan muistiin, vaan se ladataan tarvittaessa.

- **Closure (sulkeuma):** Closure tarkoittaa sitä, että funktio voi käyttää ulkopuolisia muuttujia. Tämä tarkoittaa sitä, että funktio säilyttää tilan, vaikka se ei enää ole sidottu alkuperäiseen muuttujaan. Closure mahdollistaa funktionaalisen ohjelmoinnin tyylin, joka käyttää funktioita, jotka ovat riippumattomia niiden ympäristöstä.

- **Memoization:** Memoization tarkoittaa funktiokutsujen tulosten tallentamista muistiin, jotta niitä ei tarvitse laskea uudelleen. Tämä tarkoittaa sitä, että jos funktio kutsutaan useita kertoja samalla argumentilla, tulos lasketaan vain kerran ja tallennetaan muistiin, jotta sitä voidaan käyttää myöhemmin ilman uudelleenlaskentaa. Memoization voi parantaa suorituskykyä, kun funktioita kutsutaan useita kertoja samoilla argumenteilla.

# Funktionaalinen ohjelmointi ja matematiikka

Funktionaalinen ohjelmointi liittyy vahvasti abstraktiin algebraan ja kategoriateoriaan, sillä se pyrkii hyödyntämään matematiikan käsitteitä ja rakenteita ohjelmointikäytännöissä.

Abstrakti algebra on matematiikan osa-alue, joka tutkii algebrallisia rakenteita, kuten ryhmiä, renkaita ja kenttiä. Funktionaalinen ohjelmointi käyttää usein näitä käsitteitä kuten funktoreita ja monadeja, jotka ovat abstraktialgebran rakenteita. Esimerkiksi, funktorit ovat algebrallisia rakenteita, jotka määrittelevät, miten funktiot kuvataan yhdestä kategoriasta toiseen.

Kategoriateoria on matematiikan osa-alue, joka tutkii abstrakteja rakenteita ja niiden välisiä suhteita. Funktionaalinen ohjelmointi käyttää kategoriateoriaa abstraktien rakenteiden käsitteiden tutkimiseen ja kehittämiseen. Esimerkiksi, funktoreita ja monadeja voidaan ajatella kategoriana, jossa kategorioiden väliset nuolet kuvastavat funktioiden tai monaditoimintojen kuvauksia.

Funktionaalinen ohjelmointi hyödyntää näitä matemaattisia käsitteitä ja rakenteita, jotta ohjelmistojen kehittäjät voivat rakentaa luotettavia, tehokkaita ja monimutkaisia järjestelmiä. Käyttämällä matemaattisia abstraktioita, funktionaalinen ohjelmointi voi auttaa kehittäjiä luomaan selkeitä, abstrakteja ja helposti ymmärrettäviä järjestelmiä.

