# <div align="center">Návrh a implementácia spätnej väzby pohonného systému</div>

<br/>
Pre možné riadenie poruchových stavov pôsobiacich na pohonnú sústavu, musíme zabezpečiť
spätné šírenie informácií z kolies k riadiacej jednotke. Výsledkom spätnej väzby bude
informácia o okamžitej zmene prejdenej dráhy a tiež o aktuálnej doprednej rýchlosti vozidla.
Na tento účel slúžia inkrementálne snímače rotácie, resp. enkodéri. Kvôli prototypovému
vývoju kolies a neprístupnosti k osi otáčania, som musel vyvinúť taktiež prototyp funkčného
inkrementálneho enkodéra. Využitie informácií o dráhe a rýchlosti kolies sa využíva okrem
riadenia rýchlosti a polohy taktiež na odometriu [15], či ako parameter pre aditívne
bezpečnostné systémy, ako sú napríklad systémy proti preklzávaniu kolies.

## Návrh inkrementálneho enkodéra

Rotačný enkodér reaguje na pootočenie kolesa zmenou diskrétnej hodnoty. Meraním času
medzi jednotlivými hranami vieme na základe známej geometrie a rozlíšenia snímača určiť
rýchlosť vozidla. Kvôli nemožnosti prístupu k osi rotácie motora vo vnútri kolesa, som použil
fotosenzitívny snímač, pred ktorým spolu s kolesom rotuje reflexná mriežka s otvormi, pozri
obrázok Obr. 6-14.

<br/>

<br/>
<p align="center">
<img src="https://github.com/Zahorack/embedded-open-projects/blob/master/SpeedEncoder/Photodocumentation/1.png" width="600" title="hover text">
</p>

<br/>

Fotosenzitívny snímač obsahuje infračervenú diódu a fototranzistor, pričom výstupné
hodnoty závisia na množstve absorbovaného žiarenia z diódy.

<br/>


<br/>

## Vývoj a spracovanie signálu


Súčasťou vývoja bol kompletný návrh reflexného mriežkového kotúča. Táto mriežka bola
vytlačená na 3D tlačiarni a teda jej povrch nemal vhodné reflexívne vlastnosti. Preto bolo nutné
aplikovať povrch z materiálu, ktorý vhodne odráža infračervené žiarenie. K riešeniu problému
som pristúpil experimentálne. Vyskúšal som a pomeral intenzitu a stabilitu odrazeného žiarenia
od troch rôznych povrchov.

<br/>

<br/>
<p align="center">
<img src="https://github.com/Zahorack/embedded-open-projects/blob/master/SpeedEncoder/Photodocumentation/2.png" width="600" title="hover text">
</p>

<br/>


Na Obr. 6-15 sú zobrazené implementované reflexné materiály a k nim prislúchajúce
merania intenzity odrazeného infračerveného žiarenia v rovnakom meracom rozsahu na
osciloskope. Na Obr. 6-15 a.) je mriežka nastriekaná chrómovým sprejom, od ktorého odrazený
signál mal dostatočnú amplitúdu, avšak nestabilný pokles na miestach medzery mriežky, čo
bolo spôsobené svetelným rozptylom ako vlastnosťou povrchu. Ďalším materiálom naObr. 6-15
b.) bol hliníkový povrch umiestnený za mriežku. Z nameraných dát vidíme, že mal dobrú
stabilitu signálu, ale kvôli pridanej vzdialenosti mal veľmi slabú amplitúdu, preto nebol vhodný
na ďalšie spracovanie. Posledným a najlepším návrhom bolo aplikovanie hliníkovej pásky na
prednú stranu mriežky podľa Obr. 6-15 c.). Signál odrazeného infračerveného žiarenia bol
stabilný, pričom dochádzalo k úplnému odrazu v mieste prekážky a k minimálnemu rozptylu
v mieste medzery mriežky. Preto sa dá s týmto signálom dobre pracovať.

<br/>

V tomto stave výstupné hodnoty snímača nadobúdajú analógový charakter, ktorý musíme
previesť na diskrétne hodnoty detekcie hrany mriežky. Na tento účel použijeme integrovaný
schmittov obvod (Obr. 6-16 b.)), ktorý analógové hodnoty nad určitú hranicu reprezentuje
logickou jednotkou a podobne nízke hodnoty ako logickú nulu.

<br/>

<br/>
<p align="center">
<img src="https://github.com/Zahorack/embedded-open-projects/blob/master/SpeedEncoder/Photodocumentation/3.png" width="600" title="hover text">
</p>
<br/>

Diskrétne signály na Obr. 6-16 c.) môžeme priamo priviesť na vstupný pin riadiacej
jednotky, ktorý nakonfigurujeme ako externé prerušenie, tým zabezpečíme veľmi efektívne
spracovanie informácií. Externé prerušenie deteguje nábežné či dobežné hrany (Obr. 6-17) na
hardvérovej úrovni, po zachytení vygeneruje prerušenie, ktoré preruší tok programu a začne sa
vykonávať obslužná funkcia. V tejto obslužnej funkcii (ISR Handler) je základným postupom,
inkrementovanie počítadla a uloženie aktuálneho času.


<br/>

<br/>
<p align="center">
<img src="https://github.com/Zahorack/embedded-open-projects/blob/master/SpeedEncoder/Photodocumentation/4.png" width="600" title="hover text">
</p>
<br/>


Zo známych geometrických rozmerov reflexnej mriežky a z časového rozdielu detekcie
dvoch po sebe idúcich hrán mriežky, vieme jednoducho určiť rýchlosť otáčania sa kolesa. Vo
väčšine prípadov pozostáva inkrementálny enkodér z dvoch rovnakých snímacích prvkov
umiestnených za sebou a so vzájomným posunutím, vďaka čomu je možné určiť aj smer
otáčania. V našom prípade ale nemôže dôjsť k neželanej zmene smeru vzhľadom na
prevodovým pomer elektromotoru, ktorý sa správa ako brzda. V konečnom dôsledku sa koleso
bude otáčať len v nami určenom smere, ktorý riadiaca jednotka pozná.

<br/>
<br/>


## Výroba DPS

Realizácia hardvéru enkodéra vyžadovala zvoliť vhodný integrovaný schmittov obvod
a nastaviť pracovné body diódy a tranzistoru v snímači. Preto som sa rozhodol vyrobiť pre
každé koleso malý plošný spoj, so všetkými potrebnými komponentami. Plošný spoj bol
navrhnutý v programe EAGLE, ako je vidno na Obr. 6-18, a vyrobený frézovaním.
Fotosenzitívny snímač je typu CNY70 a integrovaný obvod Schmitt trigger
SN74AHC1G14DBVR.

<br/>
<p align="center">
<img src="https://github.com/Zahorack/embedded-open-projects/blob/master/SpeedEncoder/Photodocumentation/5.png" width="600" title="hover text">
</p>
<br/>

## Filtrovanie signálu

Po osadení dosiek plošných spojov a implementácií snímačov do kolies, som pristúpil k
softvérovej implementácií spracovania signálov. Zaznamenal som deterministické rušenie
napäťového signálu inkrementálneho enkodéra, na ktoré nepriaznivo reagovala riadiaca
jednotka nechceným prerušením, a teda zle interpretovala informáciu. Rušenie bolo spôsobené
pulznou šírkovou moduláciou ovládania pohonu, nakoľko prívodné káble k motoru aj
k snímaču idú vedľa seba, to zapríčinilo vznik indukovaného rušivého napätia na signálnom
vedení. Napriek tomu, že signálny kábel bol precízne tienený. Prejavila sa závislosť intenzity
rušenia od frekvencie PWM. Môj prvý krok bol, že som vytvoril hardvérový filter. Taktiež som
skontroloval galvanické oddelenie logickej a výkonovej zeme, a kde nebola možnosť oddelenia
som umiestnil spojenie čo najbližšie ku zdroju. Aplikovaním vhodných kondenzátorov do
systému sa výrazne potlačilo rušenie a meranie mohlo prebiehať stabilne.

<br/>
<br/>

<br/>
<p align="center">
<img src="https://github.com/Zahorack/embedded-open-projects/blob/master/SpeedEncoder/Photodocumentation/7.png" width="600" title="hover text">
</p>
<br/>
