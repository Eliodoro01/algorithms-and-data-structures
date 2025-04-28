# DFS (Depth-First Search) e BFS (Breadth-First Search)

## **DFS (Depth-First Search) - Visita in Profondità**
- **Concetto**: Segue un percorso il più possibile profondo prima di fare backtracking.
- **Strategia**: 
  - Usa una **struttura LIFO** (stack, esplicito o implicito nella ricorsione).
  - Esplora ricorsivamente fino a raggiungere un nodo foglia, poi torna indietro.
- **Passi**:
  1. Visita un nodo e lo marca come "visitato".
  2. Per ogni vicino non visitato, applica ricorsivamente la DFS.
  3. Se non ci sono più nodi da esplorare, effettua backtracking.
- **Complessità**:
  - **Tempo**: `O(V + E)` (dove `V` = nodi, `E` = archi).
  - **Spazio**: `O(V)` (dipende dall'altezza dello stack/ricorsione).
- **Applicazioni**:
  - Risoluzione di labirinti.
  - Ordinamento topologico (DAG).
  - Ricerca di componenti connesse (grafi non diretti).
  - Rilevazione di cicli.

---

## **BFS (Breadth-First Search) - Visita in Ampiezza**
- **Concetto**: Esplora tutti i nodi allo stesso livello prima di passare a quelli successivi.
- **Strategia**:
  - Usa una **struttura FIFO** (coda).
  - Visita i nodi in ordine di distanza dalla radice.
- **Passi**:
  1. Inserisci il nodo sorgente in una coda.
  2. Estrai il primo nodo e visita tutti i suoi vicini non visitati, aggiungendoli in coda.
  3. Ripeti finché la coda non è vuota.
- **Complessità**:
  - **Tempo**: `O(V + E)`.
  - **Spazio**: `O(V)` (memorizza tutti i nodi dello stesso livello).
- **Applicazioni**:
  - Percorso più breve in grafi non pesati.
  - Visita per livelli (alberi).
  - Algoritmi di rete (es. flooding).

---

## **Differenze Chiave**
| Caratteristica      | DFS                          | BFS                          |
|---------------------|------------------------------|------------------------------|
| **Struttura dati**  | Stack (LIFO)                 | Coda (FIFO)                  |
| **Ordine visita**   | Profondità prima             | Ampiezza prima               |
| **Spazio**          | Meno (buono per grafi profondi) | Più (ottimo per grafi larghi) |
| **Ottimale per**    | Esplorazione completa        | Cammini minimi               |

> **Nota**:  
> - La **DFS** è spesso implementata con **ricorsione**, mentre la **BFS** richiede una **coda esplicita**.  
> - La scelta tra DFS e BFS dipende dal problema (es. percorsi vs esplorazione completa).



Per trovare l'**MST** (Minimum Spanning Tree) si usanon 2 algoritmi, Prim e Kruskal.

In genere per trovare il rango di un nodo di usa Kruskal perché tramite le sue funzioni controlla i ranghi dei nodi.

**N.B.** il rango di un nodo può essere il numero di archi che un nodo possiede, ma può anche riferirsi alla profondità del nodo rispetto la radice dell'albero, quindi l'altezza dell'albero della foresta disgiunta.

# Algoritmi per Grafi: Kruskal, Prim e Bellman-Ford

## **Algoritmo di Kruskal**
- **Scopo**: Trova un **Minimum Spanning Tree (MST)** in un grafo non orientato e pesato.
- **Strategia**:  
  - Ordina tutti gli archi in ordine crescente di peso.  
  - Aggiunge gli archi all'MST uno per uno, evitando cicli (usando **Union-Find**).  
- **Passi**:  
  1. Ordina gli archi per peso (crescente).  
  2. Inizializza una foresta di alberi disgiunti (ogni nodo è un albero separato).  
  3. Per ogni arco (in ordine):  
     - Se connette due alberi diversi, uniscili e aggiungi l'arco all'MST.  
     - Altrimenti, scarta l'arco (per evitare cicli).  
- **Complessità**:  
  - **Tempo**: `O(E log E)` (dovuto all'ordinamento).  
  - **Spazio**: `O(V + E)` (per gestire Union-Find).  
- **Applicazioni**:  
  - Reti di connessione a costo minimo (es. cavi, strade).  
  - Clusterizzazione gerarchica.  

---

## **Algoritmo di Prim**
- **Scopo**: Trova un **Minimum Spanning Tree (MST)** partendo da un nodo sorgente.  
- **Strategia**:  
  - Costruisce l'MST incrementalmente, aggiungendo l'arco più leggero adiacente all'albero corrente.  
  - Usa una **coda a priorità** (min-heap) per selezionare efficientemente gli archi.  
- **Passi**:  
  1. Inizializza un albero con un nodo arbitrario.  
  2. Aggiungi tutti gli archi adiacenti a una coda a priorità.  
  3. Estrai l'arco con peso minimo:  
     - Se connette un nodo non ancora nell'MST, aggiungilo.  
     - Aggiorna la coda con i nuovi archi adiacenti.  
  4. Ripeti finché tutti i nodi non sono inclusi.  
- **Complessità**:  
  - **Tempo**: `O(E log V)` (con heap binario).  
  - **Spazio**: `O(V + E)`.  
- **Applicazioni**:  
  - Reti elettriche, cablaggio.  
  - Approcci "greedy" per problemi di ottimizzazione.  

---

## **Algoritmo di Bellman-Ford**
- **Scopo**: Trova i **cammini minimi** da un nodo sorgente in un grafo **con pesi negativi** (ma senza cicli negativi).  
- **Strategia**:  
  - Rilassa tutti gli archi `V-1` volte, dove `V` è il numero di nodi.  
  - Rileva cicli negativi se un ulteriore rilassamento è possibile.  
- **Passi**:  
  1. Inizializza le distanze: `0` per la sorgente, `+∞` per gli altri.  
  2. Per `V-1` iterazioni:  
     - Per ogni arco `(u, v)`, aggiorna la distanza se `d[u] + peso(u,v) < d[v]`.  
  3. Controlla cicli negativi:  
     - Se un arco può ancora essere rilassato, il grafo contiene un ciclo negativo.  
- **Complessità**:  
  - **Tempo**: `O(V · E)`.  
  - **Spazio**: `O(V)` (per memorizzare le distanze).  
- **Applicazioni**:  
  - Routing in reti (es. protocolli Internet).  
  - Analisi finanziaria (arbitraggio).  

---

## **Differenze Chiave**
| Caratteristica      | Kruskal                      | Prim                        | Bellman-Ford               |
|---------------------|------------------------------|-----------------------------|----------------------------|
| **Tipo di grafo**   | Non orientato, pesato        | Non orientato, pesato       | Orientato/N.O., pesi negativi |
| **Output**          | MST                          | MST                         | Cammini minimi             |
| **Struttura dati**  | Union-Find + Ordinamento     | Min-Heap                    | Array delle distanze       |
| **Complessità**     | `O(E log E)`                | `O(E log V)`               | `O(V · E)`                |
| **Pesi negativi?**  | No                           | No                          | **Sì** (senza cicli neg.) |

> **Note**:  
> - **Kruskal** e **Prim** sono algoritmi **greedy**, mentre **Bellman-Ford** è basato su rilassamento.  
> - **Dijkstra** (non incluso) è simile a Prim ma non funziona con pesi negativi.  
> - Bellman-Ford è più lento di Dijkstra ma più flessibile.  