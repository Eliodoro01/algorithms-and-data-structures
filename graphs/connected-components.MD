# Algoritmo di Kosaraju per SCC - Pseudocodice Commentato

```pseudocode
/**
 * ================================================
 * ALGORITMO PRINCIPALE
 * ================================================
 * Input: Grafo orientato G = (V, E)
 * Output: Lista di componenti fortemente connesse (SCC)
 * Complessità: O(V + E)
 */
ALGORITMO TrovaSCC(graph)
    // --------------------------------------------
    // Fase 1: Ordina i nodi per tempo di completamento
    // --------------------------------------------
    stack = nuovo Stack()  // Struttura LIFO per ordinamento nodi
    time = 0               // Timer globale per visite DFS
    
    // Inizializzazione nodi
    PER OGNI node IN graph.nodes
        node.color = white  // Stato iniziale: non visitato
        node.d = 0          // Tempo di scoperta (discovery time)
        node.f = 0          // Tempo di completamento (finishing time)
    FINE PER
    
    // Prima visita DFS (riempimento stack)
    PER OGNI node IN graph.nodes
        SE node.color == white
            DFS_PrimoPasso(node, stack)  // Visita ricorsiva
        FINE SE
    FINE PER
    
    // --------------------------------------------
    // Fase 2: Costruzione grafo trasposto
    // --------------------------------------------
    t_graph = TrasponeGrafo(graph)  // Inverte tutti gli archi
    
    // --------------------------------------------
    // Fase 3: Ricerca SCC nel grafo trasposto
    // --------------------------------------------
    // Reset stati di visita
    PER OGNI node IN t_graph.nodes
        node.color = white
    FINE PER
    
    scc_list = []  // Lista risultato
    
    // Processa nodi in ordine inverso di completamento
    MENTRE stack.nonVuoto()
        node = stack.pop()
        SE node.color == white
            scc = []  // Nuova componente connessa
            DFS_SecondoPasso(node, t_graph, scc)
            scc_list.aggiungi(scc)  // Aggiunge la SCC trovata
        FINE SE
    FINE MENTRE
    
    RESTITUISCI scc_list
FINE ALGORITMO


/**
 * ================================================
 * DFS PRIMO PASSO (Ordinamento nodi)
 * ================================================
 * Riempie lo stack in ordine di finishing time decrescente
 * Complessità: O(V + E)
 */
PROCEDURA DFS_PrimoPasso(node, stack)
    time = time + 1
    node.d = time           // Registra tempo di scoperta
    node.color = gray       // Marca come "in visita"
    
    // Visita ricorsiva dei vicini
    PER OGNI neighbor IN node.adjacent_nodes
        SE neighbor.color == white
            DFS_PrimoPasso(neighbor, stack)
        FINE SE
    FINE PER
    
    // Completamento visita
    node.color = black      // Marca come "completamente visitato"
    time = time + 1
    node.f = time           // Registra tempo di completamento
    stack.push(node)        // Aggiunge allo stack (ordine LIFO)
FINE PROCEDURA


/**
 * ================================================
 * DFS SECONDO PASSO (Identificazione SCC)
 * ================================================
 * Trova tutti i nodi raggiungibili nel grafo trasposto
 * Complessità: O(V + E)
 */
PROCEDURA DFS_SecondoPasso(node, t_graph, scc)
    node.color = gray
    scc.aggiungi(node)  // Aggiunge il nodo alla SCC corrente
    
    // Visita i vicini nel grafo TRASPOSTO
    PER OGNI neighbor IN t_graph.getAdjacent(node)
        SE neighbor.color == white
            DFS_SecondoPasso(neighbor, t_graph, scc)
        FINE SE
    FINE PER
    
    node.color = black  // Marca come visitato
FINE PROCEDURA


/**
 * ================================================
 * TRASPOSIZIONE GRAFO
 * ================================================
 * Crea un nuovo grafo con archi invertiti
 * Complessità: O(E)
 */
FUNZIONE TrasponeGrafo(graph)
    t_graph = nuovo Grafo()
    
    // Per ogni arco (u → v), crea (v → u)
    PER OGNI node IN graph.nodes
        PER OGNI neighbor IN node.adjacent_nodes
            t_graph.aggiungiArco(neighbor, node)  // Inversione
        FINE PER
    FINE PER
    
    RESTITUISCI t_graph
FINE FUNZIONE