# Prova finale - Progetto di Algoritmi e Principi dell'Informatica A.A. 2020/2021

L'obiettivo di questa prova finale è stato la realizzazione di un programma in C per gestire una classifica di grafi diretti pesati.

## Descrizione del problema

Il programma riceve, all'inizio, da stdin il numero di nodi (d) nei grafi e la lunghezza (k) della classifica. In seguito, vengono ricevuti una sequenza di comandi tra:

- AggiungiGrafo
- TopK

Il comando AggiungiGrafo è immediatamente seguito dalla matrice di adiacenza del nuovo grafo da aggiungere alla classifica, passata al programma una riga alla volta, ciascun valore separato dal successivo da una virgola.

Il comando TopK richiede che venga stampato su stdout la classifica dei k grafi con la minor somma dei cammini più brevi tra il nodo 0 e tutti gli altri nodi *raggiungibili* da 0. I nodi non raggiungibili hanno distanza 0. Se ci sono più grafi con lo stesso valore, si dà precedenza ai primi arrivati. Gli indici dei grafi nella classifica non è richisto che siano in ordine.

## Esempio

Segue un esempio di funzionamento del programma, rappresentato dai comandi ricevuti in ingresso e l'output atteso.

> 3,2 &emsp;&emsp; # Il programma riceve grafi con 3 nodi e mantiene i 2 grafi migliori\
AggiungiGrafo &emsp; # Aggiunta del primo grafo (indice 0, somma cammini = 7)
\
0,4,3\
0,2,0\
2,0,0\
AggiungiGrafo &emsp; # Aggiunta del secondo grafo (indice 1, somma cammini = 5)\
0,0,2\
7,0,4\
0,1,0\
AggiungiGrafo &emsp; # Aggiunta del terzo grafo (indice 2, somma cammini = 7)\
3,1,8\
0,0,5\
0,9,0\
TopK &emsp; # Stampa 0 1 oppure 1 0

## Valutazione

La valutazione è stata assegnata in base all'efficienza del codice, confrontando il tempo e lo spazio in memoria impiegati dal programma. Il progetto è stato valutato 30/30 Cum Laude.

---

# Final test - Progetto di Algoritmi e Principi dell'Informatica A.Y. 2020/2021

The goal of this final test was to apply the knowledge acquired from the Algoritmi e Principi dell'Informatica (Algorithms and Principles of Computer Science) course held at Politecnico di Milano University to write a program that makes efficient use of algorithms and data structures to solve a problem. This year's challenge was to write a program to maintain a ranking of directed weighted graphs.

## Project description

The program takes as input, from stdin, the number of nodes of the graphs and the length of the ranking, separated by a comma.

After that, a sequence of commands are given to the program, which can be:

- AggiungiGrafo (AddGraph)
- TopK

The first command requires that a new graph is considered to be added to the ranking and it is immediatly followed by the graph's adjacency matrix.

The second command is used to print to stdout the top k graphs so far. The graphs are evaluated based on the sum of all the shortest paths from node 0 to all *reachable* nodes, those with the lowest sum are best. Non-reachable nodes have distance 0. If two or more graphs have the same value, precedence is given to those added first. No ordering is required when printing the top k graphs.

## Example

Below is an example of execution, showing the commands received from stdin and the expected output

> 3,2 &emsp;&emsp; # The program receives graphs having 3 nodes and keeps track of the 2 best ones\
AggiungiGrafo &emsp; # Adds the first graph (index 0, sum of the paths = 7)
\
0,4,3\
0,2,0\
2,0,0\
AggiungiGrafo &emsp; # Adds the second graph (index 1, sum of the paths = 5)\
0,0,2\
7,0,4\
0,1,0\
AggiungiGrafo &emsp; # Adds the third graph (index 2, sum of the paths = 7)\
3,1,8\
0,0,5\
0,9,0\
TopK &emsp; # Prints either 0 1 or 1 0

## Evaluation

Evaluation was based on efficiency of the code, measuring the time and the memory consumption of the program. The final project has been evaluated 30/30 Cum Laude.
