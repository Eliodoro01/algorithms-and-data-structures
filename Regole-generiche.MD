Per trovare il cammino minimo di un grafo **NON PESATO** in generale si usa la BFS.

# BFS: 
       
    1. Si inizializzano i nodi a bianco, la distanza(node.d) ad inf e predecessor a null.
    2. Si inizializza il nodo_di_partenza a grigio, la distanza a 0 e predecessor a NULL.
    3. Si usa una CODA, si estrae un nodo, se il colore è bianco, si imposta a grigio, si aumenta la distanza di 1 del nodo adiacente(adj_node.d = d.node + 1) e si imposta il nodo precedente come nodo padre dell' adiacente.
    4. Si imposta il colore del nodo che si è estratto dalla coda a nero.
      

Per trovare le varie compinenti di un grafo **NON ORIENTATO** in genere si usa la DFS

# DFS: 
    1. Nella prima funzione dfs(G) si inizializzano i nodi del grafo a bianco, i predecessori a NULL e il tempo di inizio e fine visita a 0(node.d = 0, node.f = 0) e dichiriamo una variabile globale time che servirà per capire il tempo di inizio visita del nodo e il tempo di fine visita.
    2. Si scorrono i nodi e se il colore del nodo è bianco, si richiama la funzione dfs_visit(node)
    3. Si incrementa la variabile time
    4. Nella dfs_visit si imposta il colore del nodo a grigio
    5. Si imposta il tempo di inizio visita (node.d)
    6. Si scorrono i nodi adiacenti e se il colore è bianco si imposta come predecessore il nodo che si è passato nella chiamata della funzione
    7. Si richiama la funzione dfs_visit(adj_node) con argomento il nodo adiacente
    8. Si imposta il colore del nodo come nero
    9. Si imposta il tempo di fine visita node.f



Per trovare l'**MST** (Minimum Spanning Tree) si usanon 2 algoritmi, Prim e Kruskal.

In genere per trovare il rango di un nodo di usa Kruskal perché tramite le sue funzioni controlla i ranghi dei nodi.

**N.B.** il rango di un nodo può essere il numero di archi che un nodo possiede, ma può anche riferirsi alla profondità del nodo rispetto la radice dell'albero, quindi l'altezza dell'albero della foresta disgiunta.

# Kruskal: 
    1. Si crea un nuovo set.
    2. Scorri i nodi del grafo e chiama la make_set(imposta il node.parent = node stesso e il suo rango a 0, il rango è il numero di archi che il nodo possiede) su tutti i nodi.
    3. Si ordinano gli archi del grafo
    4. Si scorrono gli archi e si chiama la find_set(la find_set controlla se il padre del nodo è il nodo stesso, se così non fosse si richiama la funzione find_set(node.parent) e si passa come argomeno il padre del nodo che si stava considerando) su i due nodi agli estremi dell'arco
    5. Se la find_set del primo nodo, dell'arco che si sta considerando, è diversa da quella richiamata sul secondo nodo dello stesso arco, allora si aggiunge l'arco al set.
    6. Si fa la union(imposta come rank della root il rank maggiore dei due) dei due nodi agli estremi dell'arco.


Solitamente per trovare l'altezza o la profondità(dovrebbe essere la stessa cosa) si una Prim.

**N.B.** Con Prim NON si trova direttamente l'altezza ma l'MST che verà usato per trovare l'altezza, utilizzando una BFS o una DFS sull'MST che si va a creare dopo l'utilizzo di Prim e Kruskal.

# Prim: 
    ha come input il grafo G e un nodo da cui partire source_node.
    1. Si inizializzano tutti i nodi del grafo, il predecessore a NULL e la key a inf.
    2. Si inizializza la chiave del nodo radice a 0.
    3. Si crea una coda di minima priorità.
    4. Si aggiungono i nodi alla coda.
    5. Fino a che la coda non è vuota, estraiamo l'elemento minimo.
    6. Scorriamo i nodi adiacenti, se la coda INCLUDE il nodo adiacente e il peso dell'arco (graph.weight(node, adj_node)) è minore della chiave del nodo adiacente (< adj_node.key)
    7. Se rispetta le condizioni sopra elencate si imposta come madre del nodo adiacente in nodo che è stato estratto dalla coda.
    8. Si imposta la chiave del nodo adiacente uguale al peso dell'arco (adj_node.key = graph.weight(node, adj_node)).


