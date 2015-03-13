	Elemente de graficã pe calculator - Tema 2
******************************************************************************************

	World Builder
	Despa Diana Alexandra 331CA

******************************************************************************************

	Cuprins
1. Cerinta
2. Utilizare
3. Implementare
4. Testare
5. Probleme Aparute
6. Continutul Arhivei
7. Functionalitati
8. Mentiuni

******************************************************************************************

1. Cerinta
	Tema consta in implementarea unei aplicatii 3D ce permite construirea unei lumi in
miniatura, cu posibilitatea editarii terenului, plasarii de case, piete sau drumuri.
Perspectiva asupra lumii este una izometrica. 

******************************************************************************************

2. Utilizare
	Programul se ruleaza prin lansarea executabilului Tema2.exe, din folderul Debug,
sau din interiorul Visual Studio.
	Taste:
	Esc - inchidere program
	Shift-W - scroll harta sus
	Shift-A	- scroll harta stanga
	Shift-S - scroll harta jos
	Shift-D - scroll harta dreapta
	W - muta cursor sus
	A - muta cursor stanga
	S - muta cursor jos
	D - muta cursor dreapta
	E - intra/iese modul editare
	Q - editeaza cladire sau drum pe care e pozitionat cursorul 
	J - navigheaza in jos in panoul de editare 
	U - navigheaza in sus in panoul de editare
	Z - zoom in
	X - zoom out
	Enter - plaseaza cladire, drum sau modifica teren
	Delete - sterge cladire sau drum
	,(<) - roteste cladire sau drum spre stanga
	.(<) - roteste cladire sau drum spre dreapta

	In modul editare, cursorul se modifica in obiectul ce se doreste a fi plasat pe
harta la un moment dat.

******************************************************************************************

3. Implementare
	Ca IDE, am folosit Microsoft Visual Studio 2013, instalat pe Windows 7, insa am
implementat aplicatia folosind Visual C++ 2010, ca sa ma asigur ca functioneaza cu
versiuni mai recente de Visual C++.
	Am pornit cu implementarea de la framework-ul laboratorului 3.
	Obiectele ce pot fi plasate in lume mostenesc clasa Tile, care reprezinta teoretic
o dala de pe grid. Obiectele de tip simplu Tile care apar in lume sunt dalele ce
reprezinta terenul si patratelele grid-ului. Clasa Building mosteneste clasa Tile si
reprezinta cladirile si drumurile, detine caracteristicile comune acestora si metodele
ce pot fi aplicate lor. Din ea deriva clasele reprezentative pentru cele 3 tipuri de
obiecte ce pot fi amplasate pe harta - House, Market, Road.
	Pentru reprezentarea lumii am folosit clasa World care abstractizeaza operatiile
care se pot realiza cu obiectele din lume: deplasare obiect selectat pe grid, rotatia
caselor, pietelor si drumurilor, amplasarea sau stergerea lor, modificarea tipului
terenului. O matrice de pointeri la dale si cladiri tine evidenta pozitiilor obiectelor in
lume. Tot in acesta clasa se realizeaza verificarea conectivitatii caselor cu piete
prin intermediul unui algoritm Deep First Search pe matricea de dale, care foloseste o
matrice auxiliara pentru a indica drumurile vizitate. La fiecare modificare asupra caselor,
drumurilor sau pietelor, este verificata starea de conectivitate a caselor.In modul de
editare, in jurul pietelor, dalele care se afla in aria lor de "acoperire" sunt evidentiate
prin schimbarea culorii. De asemenea, casele care nu sunt conectate de piete printr-un drum
sunt indicate printr-o culoare rosiatica. O casa nu poate fi amplasata in afara ariei unei
piete, o cladire sau un drum nu poate fi amplasat peste apa, alta cladire sau drum, tipul
terenului nu poate fi schimbat sub case, piete sau drumuri, iar acestea sunt indicate prin
colorarea obiectului in rosu.
	Modul de editare este indicat prin panoul ce apare intr-un context vizual separat
in partea din stanga a ferestrei. El contine toate tipurile de dale sau obiecte ce pot
fi amplasate in lume. Selectia se realizeaza de la tastatura si scroll-ul este realizat
automat, odata ce offset-ul obiectului care este selectat din panou depaseste dimensiunea
panoului.
	Efectul de cursor ce se deplaseaza pe grid este realizat prin schimbarea culorii
dalei de teren sau cladirii pe care se afla, atunci cand jocul nu e in edit mode, iar
atunci cand jocul se afla in edit mode, cursorul este cladirea sau dala de teren ce se
doreste a fi amplasata.

******************************************************************************************

4. Testare
	Am testat diferite scenarii, plasand obiecte pe harta intr-un mod aleator si
schimband tipul terenului. Nu am utilizat teste automate. Am utilizat debugger-ul din
Visual Studio.

******************************************************************************************

5. Probleme aparute
	Am vrut sa folosesc si tastele sageti, dar ele au coduri comune cu anumite
caractere, astfel ca am ales sa folosesc doar caractere si tastele Enter, Esc, ',', '.',
Delete, Shift.
	Ordonarea obiectelor pentru a fi afisate corespunzator a fost o problema initial,
insa dupa mai multe incercari si teste am gasit structura de date potrivita in care sa le
retin - vector, si metoda din std, sort. Am incercat sa folosesc set sau priority_queue,
dar vector este mai intuitiv si mai simplu.

******************************************************************************************

6. Continutul Arhivei
	main.cpp - sursa principala
	Building.cpp
	Building.h
	EditPanel.cpp
	EditPanel.h
	House.cpp
	House.h
	Market.cpp
	Market.h
	Road.cpp
	Road.h
	Tile.cpp
	Tile.h
	World.cpp
	World.h
	Framework-ul de la laborator.
	README - acest fisier.

******************************************************************************************

7. Functionalitati
	Functionalitati Standard
		Grila vizibila
		Scroll harta
		Cursor harta
		Editare teren
		Amplasare piete si desenare zona de acoperire
		Amplasare si desenare case, cu rotatie
		Editare drumuri si indicare case neconectate

	Functionalitati Bonus
		Rotatie case, piete, drum dupa amplasare
		Stergere piete, case, drumuri		

	Functionalitati Suplimentare
		Zoom harta
		Rotatie piete si drum la amplasare	
		Panou vizibil in modul editare
		
******************************************************************************************

8. Mentiuni
	Majoritatea comentariilor din cod, in special cele care descriu metode si membri
ale claselor implementate se afla in fisierele de tip header.
	Pietele au bazele "dintate" intentional, in sensul ca e posibila plasarea de drum
sau colt de casa printre marginile lor. Faptul ca bazele pietelor nu apar ca forme regulate
cred ca se datoreaza transformarilor aplicate obiectului.