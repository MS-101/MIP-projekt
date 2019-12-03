Na refaktoring som si vybral svoj 1. projekt z predmetu "Procedurálne programovanie".

Môj program reaguje na dané konzolové príkazy:
==============================================
v - vıpis súboru vstupného súboru autobazar.txt
o rrrrmmdd - vıpis odmien pre zamestnancov, ktorı pracovali vo firme aspoò jeden rok
n - naèítanie dynamického po¾a (bez vıpisu)
s - vıpis spz z dynamického po¾a
m - vıpis najfrekventovanejšieho znaku v poli
p - vıpis palindrómov z po¾a
z - vıpis skratiek miest, kde bol predanı najvyšší poèet aút
k - koniec programu

Refaktoring zahàòa:
===================
- vnútro funkcií bolo rozdelené na viac menších funkcií
- zmenené názvy premennıch
- zjednodušenie komplikovanıch algoritmov
- pridané komentáre

Vetvy v gite:
=============
- development:
	- zahròuje zmeny v programe vytvorené poèas tvorby projektu
	- rozdelenı na vetvy vypisSuboru, odmena, nacitajPole, vypisPola, maxPocetnostPola, palindromVPoli a zistiPredaj 
	- kadá z jeho podradenıch vetiev má v sebe zmeny príkazu prislúchajúce tejto vetve
	
- refaktoring:
	- zahròuje zmeny v programe vytvorené poèas refaktoringu hotového programu
	- pôvodne mal by rozdelenı na vetvy podobne ako vetva development (refaktoring_vypisSuboru, refaktoring_odmena, ...)
	- po zistení konfliktov spôsobené pribúdajúcou závislosou medzi funkciami v rôznych vetvách sa ïalšie zmeny refaktoringu robili len priamo vo vetve refaktoring
