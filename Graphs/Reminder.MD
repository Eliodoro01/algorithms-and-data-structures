# BFS – Breadth-First Search: Quando e Perché Usarla

### 🔹 Trovare il cammino più corto (shortest path) in un grafo non pesato
- Es: da un nodo sorgente a un nodo destinazione.
- Tipico esercizio: “Dato un labirinto/griglia, trova il percorso più breve”.

### 🔹 Livelli o distanze minime
- Es: calcolare la distanza minima di ogni nodo da una sorgente.
- Utile nei problemi tipo “grado di separazione” nei social network.

### 🔹 Riconoscere se un grafo non orientato è bipartito
- Si colora con due colori mentre si fa BFS, verificando che non ci siano conflitti.

### 🔹 Visita in ampiezza (esplorazione per livelli)
- Utile se vuoi processare nodi “vicini” prima di quelli “lontani”.

### 🔹 Applicazioni su alberi
- Es: stampa a livelli (level-order traversal).

### 🔹 Algoritmi su griglie 2D
- Es: flood fill, problemi di tipo “isola”, percorsi in labirinti, ecc.

---

# DFS – Depth-First Search: Quando e Perché Usarla

### 🔴 Ordinamento topologico in un DAG (grafo aciclico diretto)
- DFS è usata per generare l'ordinamento topologico.

### 🔴 Individuare cicli
- In un grafo diretto o non diretto, DFS permette di trovare back edges.

### 🔴 Esplorare componenti connesse
- Per contare le componenti o determinare se due nodi appartengono alla stessa componente.

### 🔴 Costruire alberi di visita (DFS tree)
- Per algoritmi su grafi orientati/non orientati.

### 🔴 Algoritmi avanzati
- Tarjan per componenti fortemente connesse (SCC)
- Bridge-finding, articulation points

### 🔴 Generazione e risoluzione di puzzle e giochi
- Es: Sudoku, labirinti → DFS è utile in algoritmi di backtracking.

### 🔴 Traversal di alberi (preorder, inorder, postorder)
- Classico negli esercizi su strutture dati ad albero (es. BST, heap, trie).

---

# 📚 Tipici esercizi d'esame

- Scrivi un algoritmo che visita un grafo usando BFS e stampa la distanza da un nodo sorgente.
- Usa DFS per trovare tutte le componenti connesse.
- Usa DFS per rilevare se il grafo ha un ciclo.
- Confronta BFS e DFS in termini di tempo e spazio per una determinata struttura del grafo.
- Dai un grafo e chiedi: quale dei due (BFS o DFS) è più adatto per trovare un cammino minimo?
- Problemi su griglie 2D: inondazioni, isole, labirinti (BFS/DFS possono essere equivalenti con variazioni).
