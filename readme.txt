Na refaktoring som si vybral svoj 1. projekt z predmetu "Procedur�lne programovanie".

M�j program reaguje na dan� konzolov� pr�kazy:
==============================================
v - v�pis s�boru vstupn�ho s�boru autobazar.txt
o rrrrmmdd - v�pis odmien pre zamestnancov, ktor� pracovali vo firme aspo� jeden rok
n - na��tanie dynamick�ho po�a (bez v�pisu)
s - v�pis spz z dynamick�ho po�a
m - v�pis najfrekventovanej�ieho znaku v poli
p - v�pis palindr�mov z po�a
z - v�pis skratiek miest, kde bol predan� najvy��� po�et a�t
k - koniec programu

Refaktoring zah��a:
===================
- vn�tro funkci� bolo rozdelen� na viac men��ch funkci�
- zmenen� n�zvy premenn�ch
- zjednodu�enie komplikovan�ch algoritmov
- pridan� koment�re

Vetvy v gite:
=============
- development:
	- zahr�uje zmeny v programe vytvoren� po�as tvorby projektu
	- rozdelen� na vetvy vypisSuboru, odmena, nacitajPole, vypisPola, maxPocetnostPola, palindromVPoli a zistiPredaj 
	- ka�d� z jeho podraden�ch vetiev m� v sebe zmeny pr�kazu prisl�chaj�ce tejto vetve
	
- refaktoring:
	- zahr�uje zmeny v programe vytvoren� po�as refaktoringu hotov�ho programu
	- p�vodne mal by� rozdelen� na vetvy podobne ako vetva development (refaktoring_vypisSuboru, refaktoring_odmena, ...)
	- po zisten� konfliktov sp�soben� prib�daj�cou z�vislos�ou medzi funkciami v r�znych vetv�ch sa �al�ie zmeny refaktoringu robili len priamo vo vetve refaktoring
