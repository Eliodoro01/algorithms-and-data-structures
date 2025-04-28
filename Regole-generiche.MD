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

---

Per trovare l'**MST** (Minimum Spanning Tree) si usanon 2 algoritmi, Prim e Kruskal.

In genere per trovare il rango di un nodo di usa Kruskal perché tramite le sue funzioni controlla i ranghi dei nodi.

**N.B.** il rango di un nodo può essere il numero di archi che un nodo possiede, ma può anche riferirsi alla profondità del nodo rispetto la radice dell'albero, quindi l'altezza dell'albero della foresta disgiunta.

# Algoritmi per Grafi: Kruskal, Prim, Bellman-Ford e Dijkstra

## **Kruskal (Minimum Spanning Tree - MST)**
- **Obiettivo**: Trova un albero di copertura minimo (MST) in un grafo **non orientato** e **pesato**.
- **Strategia**:  
  - Ordina tutti gli archi in ordine crescente di peso.  
  - Aggiunge gli archi uno per uno, evitando cicli (usando **Union-Find**).  
- **Complessità**:  
  - **Tempo**: `O(E log E)` (dovuto all'ordinamento).  
  - **Spazio**: `O(E + V)` (per gestire gli archi e l'Union-Find).  
- **Applicazioni**:  
  - Reti di connessione (es. cablaggio elettrico).  
  - Clusterizzazione gerarchica.  

---

## **Prim (Minimum Spanning Tree - MST)**
- **Obiettivo**: Trova un MST in un grafo **non orientato** e **pesato**, partendo da un nodo sorgente.  
- **Strategia**:  
  - Usa una **coda a priorità** (min-heap) per selezionare l'arco con peso minimo adiacente al MST corrente.  
  - Espande il MST aggiungendo il nodo più vicino.  
- **Complessità**:  
  - **Tempo**: `O(E log V)` (con heap binario).  
  - **Spazio**: `O(V + E)`.  
- **Applicazioni**:  
  - Reti stradali o di telecomunicazioni.  
  - Approssimazione per problemi di Steiner.  

---

## **Bellman-Ford (Cammini Minimi)**
- **Obiettivo**: Trova i cammini minimi da un nodo sorgente in un grafo **orientato**/**non orientato** con **pesi negativi** (ma senza cicli negativi).  
- **Strategia**:  
  - Rilassa tutti gli archi `V-1` volte (dove `V` = numero di nodi).  
  - Rileva cicli negativi se un ulteriore rilassamento migliora i pesi.  
- **Complessità**:  
  - **Tempo**: `O(V * E)`.  
  - **Spazio**: `O(V)` (distanze).  
- **Applicazioni**:  
  - Routing in reti con vincoli di costo.  
  - Analisi di arbitraggio (finanza).  

---

## **Dijkstra (Cammini Minimi)**
- **Obiettivo**: Trova i cammini minimi da un nodo sorgente in un grafo **senza pesi negativi**.  
- **Strategia**:  
  - Usa una **coda a priorità** (min-heap) per selezionare il nodo con distanza minima.  
  - Aggiorna le distanze dei vicini in modo greedy.  
- **Complessità**:  
  - **Tempo**: `O(E log V)` (con heap binario).  
  - **Spazio**: `O(V + E)`.  
- **Applicazioni**:  
  - Mappe (es. Google Maps).  
  - Reti di routing (protocolli come OSPF).  

---

## **Differenze Chiave**
| Caratteristica      | Kruskal            | Prim               | Bellman-Ford       | Dijkstra           |
|---------------------|--------------------|--------------------|--------------------|--------------------|
| **Tipo di grafo**   | Non orientato      | Non orientato      | Orientato/N.O.     | Orientato/N.O.     |
| **Pesi negativi?**  | Ignora             | Ignora             | **Supportati**     | Non ammessi        |
| **Complessità**     | `O(E log E)`       | `O(E log V)`       | `O(V * E)`         | `O(E log V)`       |
| **Struttura dati**  | Union-Find + Sort  | Min-Heap           | Array              | Min-Heap           |
| **Uso principale**  | MST                | MST                | Cammini con pesi neg. | Cammini minimi    |

> **Note**:  
> - **Kruskal** e **Prim** risolvono lo stesso problema (MST) con approcci diversi.  
> - **Dijkstra** è più efficiente di Bellman-Ford, ma non funziona con pesi negativi.  
> - **Bellman-Ford** è più flessibile ma meno efficiente.  

### Esempio di codice (Dijkstra in Python):
```python
import heapq

def dijkstra(graph, start):
    distances = {node: float('infinity') for node in graph}
    distances[start] = 0
    heap = [(0, start)]
    
    while heap:
        current_dist, current_node = heapq.heappop(heap)
        for neighbor, weight in graph[current_node].items():
            distance = current_dist + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(heap, (distance, neighbor))
    return distances