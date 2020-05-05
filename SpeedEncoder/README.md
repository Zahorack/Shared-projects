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
<img src="https://github.com/Zahorack/udp-firmware-uploader/blob/master/img/probes.jpg" width="600" title="hover text">
</p>

<br/>


