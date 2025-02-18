#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOP "TopK"
#define AGG "AggiungiGrafo"
#define NUM 48

struct struttura_successivo {
    unsigned long int arco;
    struct struttura_nodo* adiacente;
};
typedef struct struttura_nodo {
    unsigned long int distanza;
    int numero_adiacenti;
    struct struttura_successivo* adiacenti;
} NODO;
typedef struct struttura_classifica {
    unsigned long int somma_cammini_minimi;
    int indice_del_grafo;
} CLASSIFICA;

int main() {
    /*
     * numero_nodi                  -> Numero di nodi letto da stdin in prima riga
     * numero_k                     -> Numero massimo della classifica letto da stdin in prima riga
     * indice_mucchio_classifica    -> Indice per tenere traccia della posizione nel mucchio della classifica
     * indice_nodo                  -> Indice per tenere traccia della posizione nell'array di nodi
     * indice_coda                  -> Indice per tenere traccia della posizione nel mucchio della coda
     * indice_stringa               -> Indice della posizione nel buffer di lettura
     * numero_di_grafo              -> Numero del grafo da leggere da stdin
     *
     * carattere_letto              -> Carattere letto da stdin
     * flag_temporaneo              -> Flag per tenere traccia di cosa si sta leggendo sulla prima riga (|d| e |k|)
     */
    int numero_nodi = 0, numero_k = 0, indice_mucchio_classifica = 0, indice_coda = 0, indice_stringa = 0, numero_di_grafo = 0;
    char carattere_letto, flag_temporaneo = 0;

    // Leggere all'inizio il numero di nodi e il limite della classifica
    do {

        // Legge un carattere
        carattere_letto = (char) fgetc(stdin);

        // Se il carattere è End Of File e non c'è nulla termina ora
        if (carattere_letto == EOF) {
            printf("\n");
            return 0;
        }

        // Se non leggo uno spazio che separa i due numeri, né un break-line costruisco i numeri
        if (carattere_letto != ' ' && carattere_letto != '\n') {

            // Se il flag è != 0 ho già letto il numero di nodi, ora leggo il numero_k
            if (flag_temporaneo) {
                numero_k = numero_k * 10 + (carattere_letto - NUM);

                // Se il flag è = 0 sto leggendo il numero di nodi
            } else {
                numero_nodi = numero_nodi * 10 + (carattere_letto - NUM);
            }
        }

        // Se leggo uno spazio, ho smesso di leggere il numero di nodi e passo a leggere il numero_k
        if (carattere_letto == ' ') {
            flag_temporaneo++;
        }
    } while (carattere_letto != '\n');

    flag_temporaneo = 0;

    // Array per memorizzare i nodi e le loro informazioni
    NODO array_nodi[numero_nodi];

    // Mucchio per memorizzare la coda dei nodi per Dijkstra
    NODO* mucchio_coda[numero_nodi];

    // Mucchio delle somme della classifica dei k grafi
    CLASSIFICA mucchio_classifica[numero_k];

    // Stringa per leggere l'istruzione
    char istruzione[14];
    do {

        // Legge un carattere
        carattere_letto = (char) fgetc(stdin);

        // Se non sono ancora all'End Of File
        if (carattere_letto != EOF) {

            // Se sono arrivato a fine riga
            if (carattere_letto == '\n') {

                // Ho terminato di leggere la stringa di istruzione e aggiungo il carattere terminale \0
                istruzione[indice_stringa] = '\0';

                // Se la stringa è uguale all'istruzione TopK (strcmp ritorna 0 = FALSE in questo caso)
                if (!strcmp(TOP, istruzione)) {
                    if (indice_mucchio_classifica > 0) {
                        if (flag_temporaneo) {
                            printf("\n");
                        }
                        for (int indice = 0; indice < indice_mucchio_classifica - 1; indice++) {

                            // Stampo fino al penultimo indice dei grafi nella classifica (mucchio)
                            printf("%d ", mucchio_classifica[indice].indice_del_grafo);
                            //printf("Grafo: %d - Peso: %lu\n", mucchio_classifica[indice].indice_del_grafo, mucchio_classifica[indice].somma_cammini_minimi);
                        }
                        // Se c'è almeno un elemento nella classifica, stampo l'ultimo a parte per non mettere lo spazio
                        if (indice_mucchio_classifica > 0) {
                            printf("%d", mucchio_classifica[indice_mucchio_classifica - 1].indice_del_grafo);
                            //printf("Grafo: %d - Peso: %lu ", mucchio_classifica[indice_mucchio_classifica - 1].indice_del_grafo, mucchio_classifica[indice_mucchio_classifica - 1].somma_cammini_minimi);
                        }
                        flag_temporaneo = 1;
                    } else {
                        printf("\n");
                    }
                // Se la stringa è uguale all'istruzione AggiungiGrafo (strcmp ritorna 0 = FALSE in questo caso)
                } else if (!strcmp(AGG, istruzione)) {

                    // Leggo tutte le righe una alla volta
                    for (int indice_riga = 0; indice_riga < numero_nodi; indice_riga++) {

                        // Istanzio un nuovo nodo nell'array inizializzato
                        array_nodi[indice_riga].distanza = 0;
                        array_nodi[indice_riga].numero_adiacenti = 0;

                        // Istanzio le zone di memoria solo una volta, le volte successive saranno riscritte o ignorate
                        if (numero_di_grafo == 0) {
                            if (numero_nodi - 2 > 0) {
                                array_nodi[indice_riga].adiacenti = (struct struttura_successivo*) malloc((sizeof(struct struttura_successivo) * (numero_nodi - 1)));
                            } else {
                                array_nodi[indice_riga].adiacenti = (struct struttura_successivo*) malloc((sizeof(struct struttura_successivo) * (numero_nodi)));
                            }
                        }

                        // Indice della colonna della matrice
                        int colonna = 0;

                        // Il valore della matrice
                        unsigned long int valore_matrice = 0;
                        do {
                            carattere_letto = (char) fgetc(stdin);

                            // Se non leggo una virgola né un break-line, sto leggendo un numero e lo costruisco
                            if (carattere_letto != ',' && carattere_letto != '\n') {
                                valore_matrice = valore_matrice * 10 + (int) (carattere_letto - NUM);
                            // Se ho finito di leggere un numero
                            } else {

                                // Se non sto leggendo una distanza verso il nodo zero né verso il nodo stesso
                                // E se c'è un arco tra i nodi
                                if (colonna != 0 && colonna != indice_riga && valore_matrice > 0) {

                                    // Memorizzo il valore della matrice
                                    array_nodi[indice_riga].adiacenti[array_nodi[indice_riga].numero_adiacenti].arco = valore_matrice;

                                    // Il nodo adiacente è quello sulla colonna
                                    array_nodi[indice_riga].adiacenti[array_nodi[indice_riga].numero_adiacenti].adiacente = &array_nodi[colonna];
                                    array_nodi[indice_riga].numero_adiacenti++;
                                }
                                colonna++;
                                valore_matrice = 0;
                            }
                        } while (carattere_letto != '\n');

                        // Inserisco il nodo appena letto in coda in fondo al mucchio
                        mucchio_coda[indice_coda] = &array_nodi[indice_riga];

                        // Risalgo il mucchio se non sono in cima
                        if (indice_coda > 0) {

                            // Indice temporaneo per risalire la coda
                            int indice_coda_temporaneo = indice_coda;

                            // Itero finché non arrivo in cima o finché non arrivo nella posizione corretta
                            while(1) {

                                // Se non sono in cima
                                if (indice_coda_temporaneo > 0) {

                                    // Indice del genitore nel mucchio
                                    int parent;
                                    if ((indice_coda_temporaneo % 2) == 0) {
                                        parent = (indice_coda_temporaneo - 2) / 2;
                                    } else {
                                        parent = (indice_coda_temporaneo - 1) / 2;
                                    }

                                    // Se la distanza è minore strettamente, scambio
                                    if (mucchio_coda[indice_coda_temporaneo]->distanza < mucchio_coda[parent]->distanza) {
                                        NODO* tmp = mucchio_coda[indice_coda_temporaneo];
                                        mucchio_coda[indice_coda_temporaneo] = mucchio_coda[parent];
                                        mucchio_coda[parent] = tmp;
                                    } else {
                                        break;
                                    }
                                    indice_coda_temporaneo = parent;

                                // Se sono in cima
                                } else {
                                    break;
                                }
                            }
                        }
                        indice_coda++;
                    }
                    indice_coda--;

                    // Algoritmo Dijkstra
                    while (mucchio_coda[0] != NULL) {

                        // Prelevo il nodo in cima al mucchio della coda
                        NODO* u = mucchio_coda[0];

                        // Sistema il mucchio
                        // Sposta l'ultimo elemento al primo posto
                        mucchio_coda[0] = mucchio_coda[indice_coda];
                        mucchio_coda[indice_coda] = NULL;

                        // Sposta l'elemento in basso finché non è in fondo o non è nella posizione corretta
                        if (indice_coda > 0) {
                            int indice_coda_temporaneo = 0;
                            while(1) {
                                int left = (indice_coda_temporaneo * 2) + 1;
                                int right = (indice_coda_temporaneo * 2) + 2;
                                if (left >= numero_nodi && right >= numero_nodi) {
                                    break;
                                } else {
                                    int indice = indice_coda_temporaneo;
                                    unsigned long int mindist = mucchio_coda[indice]->distanza;
                                    if  (left < numero_nodi && mucchio_coda[left] != NULL) {
                                        if (mucchio_coda[left]->distanza > 0 &&
                                            (mucchio_coda[left]->distanza < mindist || mindist == 0)) {
                                            mindist = mucchio_coda[left]->distanza;
                                            indice = left;
                                        }
                                    }
                                    if  (right < numero_nodi && mucchio_coda[right] != NULL) {
                                        if (mucchio_coda[right]->distanza > 0 &&
                                                (mucchio_coda[right]->distanza < mindist || mindist == 0)) {
                                            indice = right;
                                        }
                                    }
                                    if (indice == indice_coda_temporaneo) {
                                        break;
                                    }
                                    NODO* tmp = mucchio_coda[indice];
                                    mucchio_coda[indice] = mucchio_coda[indice_coda_temporaneo];
                                    mucchio_coda[indice_coda_temporaneo] = tmp;
                                    indice_coda_temporaneo = indice;
                                }
                            }
                        }
                        if (u->distanza > 0 || indice_coda == numero_nodi - 1) {
                            for (int indice_adiacente = 0; indice_adiacente < u->numero_adiacenti; indice_adiacente++) {
                                /*if (numero_di_grafo == 19) {
                                    int power = 0;
                                }*/
                                unsigned long int ndis = u->distanza + u->adiacenti[indice_adiacente].arco;
                                NODO* v = u->adiacenti[indice_adiacente].adiacente;
                                if (ndis > 0 && (v->distanza > ndis || v->distanza == 0)) {
                                    v->distanza = ndis;
                                    int indice_v = 0;
                                    for (int x = 0; x <= indice_coda; x++) {
                                        if (mucchio_coda[x] == v) {
                                            indice_v = x;
                                            break;
                                        }
                                    }
                                    while (1) {
                                        if (indice_v == 0) {
                                            break;
                                        }
                                        int parent;
                                        if (indice_v % 2 == 0) {
                                            parent = (indice_v - 2) / 2;
                                        } else {
                                            parent = (indice_v - 1) / 2;
                                        }
                                        if (mucchio_coda[indice_v]->distanza < mucchio_coda[parent]->distanza ||
                                            (mucchio_coda[parent]->distanza == 0 && mucchio_coda[indice_v]->distanza > 0)) {
                                            NODO* temp = mucchio_coda[indice_v];
                                            mucchio_coda[indice_v] = mucchio_coda[parent];
                                            mucchio_coda[parent] = temp;
                                            indice_v = parent;
                                        } else {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        indice_coda--;
                    }

                    unsigned long int somma_del_grafo = 0;

                    for (int i = 0; i < numero_nodi; i++) {
                        somma_del_grafo += array_nodi[i].distanza;
                    }

                    /*if (numero_di_grafo == 14) {
                        somma_del_grafo = 0;
                        for (int i = 0; i < numero_nodi; i++) {
                            somma_del_grafo += array_nodi[i].distanza;
                        }
                    }*/

                    // Finito di applicare Dijkstra, controllo se il grafo entra nella classifica
                    // Se la classifica non è piena, inserisco l'elemento in fondo e lo faccio risalire
                    if (indice_mucchio_classifica < numero_k) {
                        mucchio_classifica[indice_mucchio_classifica].indice_del_grafo = numero_di_grafo;
                        mucchio_classifica[indice_mucchio_classifica].somma_cammini_minimi = somma_del_grafo;
                        int indice_mucchio_temporaneo = indice_mucchio_classifica;
                        while (1) {
                            if (indice_mucchio_temporaneo == 0) {
                                break;
                            } else {
                                int parent;
                                if (indice_mucchio_temporaneo % 2 == 0) {
                                    parent = (indice_mucchio_temporaneo - 2) / 2;
                                } else {
                                    parent = (indice_mucchio_temporaneo - 1) / 2;
                                }
                                if (mucchio_classifica[indice_mucchio_temporaneo].somma_cammini_minimi >= mucchio_classifica[parent].somma_cammini_minimi) {
                                    CLASSIFICA temp = mucchio_classifica[indice_mucchio_temporaneo];
                                    mucchio_classifica[indice_mucchio_temporaneo] = mucchio_classifica[parent];
                                    mucchio_classifica[parent] = temp;
                                    indice_mucchio_temporaneo = parent;
                                } else {
                                    break;
                                }
                            }
                        }
                        indice_mucchio_classifica++;
                    } else {
                        if (somma_del_grafo < mucchio_classifica[0].somma_cammini_minimi) {
                            mucchio_classifica[0].somma_cammini_minimi = somma_del_grafo;
                            mucchio_classifica[0].indice_del_grafo = numero_di_grafo;

                            int indice_mucchio_temporaneo = 0;

                            while (1) {
                                int right = (indice_mucchio_temporaneo * 2) + 2;
                                int left = (indice_mucchio_temporaneo * 2) + 1;
                                if (left >= indice_mucchio_classifica && right >= indice_mucchio_classifica) {
                                    break;
                                } else {
                                    int indice = indice_mucchio_temporaneo;
                                    if  (right < indice_mucchio_classifica &&
                                            mucchio_classifica[right].somma_cammini_minimi > mucchio_classifica[indice].somma_cammini_minimi) {
                                        indice = right;
                                    }
                                    if  (left < indice_mucchio_classifica &&
                                         mucchio_classifica[left].somma_cammini_minimi > mucchio_classifica[indice].somma_cammini_minimi) {
                                        indice = left;
                                    }
                                    if (indice == indice_mucchio_temporaneo) {
                                        break;
                                    }
                                    CLASSIFICA temp = mucchio_classifica[indice];
                                    mucchio_classifica[indice] = mucchio_classifica[indice_mucchio_temporaneo];
                                    mucchio_classifica[indice_mucchio_temporaneo] = temp;
                                    indice_mucchio_temporaneo = indice;
                                }
                            }
                        }
                    }

                    // Finito di leggere il grafo si passa all'indice successivo
                    numero_di_grafo++;

                    // Si ri-azzera la coda
                    indice_coda = 0;
                }
                indice_stringa = 0;

            // Se non sono arrivato alla fine dell'istruzione
            } else {
                istruzione[indice_stringa] = carattere_letto;
                indice_stringa++;
            }
        }
    } while (carattere_letto != EOF && carattere_letto != '&');
    return 0;
}
