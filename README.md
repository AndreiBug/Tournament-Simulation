# lanParty
Tema PA

-TASK I-
1. Am initializat majoritatea variabilelor necesare la inceputul codului;
2. Intr-un loop for am citit din fisier numarul de jucatori si numele echipei. In acest for am introdus un alt for si am inceput sa citesc detaliile jucatorilor: nume, prenume, puncte. Am luat o variabila care imi spunea daca era primul jucator din echipa si dupa o schimbam pentru a retine head-ul jucatorilor;
3. Am sters endline-urile si spatiile de la inceputul si finalul numelui echipelor folosind functia delete_endlines_spaces;
4. La fiecare pas al for-ului se trece la urmatoarea echipa care se adauga la inceputul listei; 
5. La final retin head_team in variabila team pentru a-l utiliza mai usor in task-urile urmatoare.

-TASK II-
1. Am inceput prin reducerea numarului de echipe astfel: am luat un numar intreg egal cu 1 la inceput si am inmultit-o cu 2 atat timp cat era mai mic decat numarul de echipe;
2. Cat timp numarul de echipe nu este egal cu n am initializat punctele echipei cu 0 si am calculat folosing media aritmetica a punctelor jucatorilor fiecarei echipe;
3. Am initializat min cu infinit pentru a determina in final minimul de puncte care se afla in lista;
4. La finalul while-ului am folosit functia deleteMin pentru a sterge echipa cu cel mai mic punctaj si am redus numarul de echipe;
5. Functionare deleteMin: Daca s-a gasit o echipa cu punctajul minim egal cu valoarea pe care o cautam noi se sterge si se refac legaturile din lista.

-TASK III-
1. Am creat coada si am initializat-o cu valorile din lista, iar dupa am creat stivele;
2. Am luat o variabila round_nr pentru a afisa numarul rundei la care ne aflam;
3. Cat timp numarul de echipe nu ajunge la 8 se executa urmatorul program: 
  - show_games: Initializez 2 structuri de echipa care semnifica cele 2 echipe care vor juca meciul. Incep sa iau echipele din coada si le afisez pe cate o linie, una la inceput, alta la finalul ei. Linia o formez folosind un sir de caractere de lungime egala cu table_size (69). Compar cele 2 punctaje ale fiecarei echipe, le adaug in stiva corespunzatoare si modific punctajul fiecarui jucator in parte. Se trece la urmatoarele elemente din structurile de echipa si se reia for-ul;
  - se sterge stiva de invinsi;
  - se goleste coada de meciuri si se reinitializeaza;
  - show_winners: am aplicat aceeasi metoda ca la show_games: foloses un sir de caractere pentru a afisa echipa castigatoare si punctajul ei;
  - la final se injumatatesc echipele si se trece la runda urmatoare.

La finalul codului inchid fisierele folosite.
