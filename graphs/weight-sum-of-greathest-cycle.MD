# Algoritmo per Trovare la Somma dei Pesi del Ciclo più Lungo in un Grafo Orientato Pesato

## **Problema**
Dato un grafo orientato e pesato \( G = (V, E) \) con funzione di peso \( w: E \rightarrow \mathbb{R} \), trovare la somma dei pesi del ciclo più lungo (o "più pesante") in \( G \).

## **Approccio**
1. **Trasformazione del problema**:  
   - Convertire il problema da "trovare il ciclo più lungo" a "trovare il ciclo più corto" invertendo i pesi degli archi.  
   - Un ciclo di peso massimo in \( G \) diventa un ciclo di peso minimo (negativo) nel grafo con pesi invertiti.  

2. **Algoritmo modificato di Bellman-Ford**:  
   - Usare Bellman-Ford per rilevare cicli negativi (che corrispondono a cicli positivi nel grafo originale).  
   - Tracciare il ciclo con la somma dei pesi originale massima.  

## **Pseudocodice**
```python
FIND_MAX_CYCLE_SUM(G(V, E, w)):
    // Inizializzazione
    for each u ∈ V:
        dist[u] = 0
        predecessor[u] = NULL

    // Fase di rilassamento
    for i = 1 to |V| - 1:
        for each (u, v) ∈ E:
            if dist[v] > dist[u] + (-w(u, v)):
                dist[v] = dist[u] + (-w(u, v))
                predecessor[v] = u

    // Rilevamento cicli negativi (cicli positivi nel grafo originale)
    max_cycle_sum = -∞
    for each (u, v) ∈ E:
        if dist[v] > dist[u] + (-w(u, v)):
            // Ricostruzione del ciclo
            cycle_sum = 0
            visited = set()
            x = v
            while x not in visited:
                visited.add(x)
                x = predecessor[x]
                if x == NULL:
                    break  // Non è un ciclo valido
                cycle_sum += w(predecessor[x], x)  // Somma pesi originali
            if cycle_sum > max_cycle_sum:
                max_cycle_sum = cycle_sum

    if max_cycle_sum == -∞:
        return "Nessun ciclo trovato"
    else:
        return max_cycle_sum
```

## **Spiegazione Passo-Passo**
1. **Inizializzazione**:  
   - `dist[u] = 0` per tutti i nodi, poiché cerchiamo cicli (non cammini da una sorgente).  
2. **Rilassamento**:  
   - Eseguiamo \(|V| - 1\) iterazioni di rilassamento per trovare i "cammini più corti" con pesi negativi.  
3. **Rilevamento cicli**:  
   - Se dopo \(|V| - 1\) iterazioni un arco \((u, v)\) può ancora essere rilassato, esiste un ciclo negativo.  
4. **Calcolo del ciclo massimo**:  
   - Per ogni ciclo rilevato, calcoliamo la somma dei pesi originali e manteniamo il massimo.  

## **Complessità Computazionale**
- **Tempo**: \( O(|V| \cdot |E|) \) (come Bellman-Ford).  
- **Spazio**: \( O(|V|) \) per memorizzare `dist` e `predecessor`.  

## **Casi Speciali**
- Se il grafo è **aciclico (DAG)**, l'algoritmo restituisce *"Nessun ciclo trovato"*.  
- Se ci sono più cicli, viene selezionato quello con somma dei pesi maggiore.  
- Funziona anche con archi di peso negativo nel grafo originale.  

## **Esempio di Esecuzione**
```python
Grafo G:
    Archi: (A → B, w=2), (B → C, w=3), (C → A, w=-1)
    Ciclo: A → B → C → A, somma pesi = 2 + 3 + (-1) = 4
Risultato atteso: 4
```

## **Limitazioni**
- Non gestisce grafi con **cicli disgiunti** in modo ottimale (restituisce solo il primo ciclo rilevato con peso massimo).  
- Meno efficiente di algoritmi specializzati per grafi densi.  

## **Alternative**
- Per grafi con pesi non negativi, usare **DFS** con backtracking per enumerare tutti i cicli.  
- Per grafi fortemente connessi, utilizzare algoritmi basati su **componenti fortemente connesse (SCC)**.  

---
**Fonte**: Adattamento da Bellman-Ford e tecniche di rilevamento cicli in grafi pesati.
