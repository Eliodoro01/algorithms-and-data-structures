/*Dato un grafo orientato G=(V,E) ed un albero radicato T con radice g e composto da
tutti i nodi V, scrivere un algoritmo in pseudocodice che restituisca TRUE se T corrisponde
all’albero DF del grafo G e FALSE altrimenti. (8 punti).*/

VerificaAlberoDFS(G,T,g)
    for each v in V[G]
        color[v] <- WHITE 
        piDFS[v] <- NIL 
    DFS_VISIT(g)
    for each u in V[G]
        if piDFS[u] != piT[u]
            return FALSE 
        else 
            return true 

DFS_VISIT(u)
    color[u] <- GRAY 
    for each v in Adj[u]
        if color[v] = WHIITE
            piDFS[v] <- u 
            DFS_VISIT(v)
    color[u] <- GRAY 


/*Dato un grafo non orientato e definito il tempo di visita come tempo di 
fine - tempo di inizio, calcolare il numero di nodi con tempo di visita = 1 
ed il numero di nodi con tempo di visita massimo*/

DFS(G)
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NIL
        d[u] <- NIL 
        f[u] <- NIL 
    time <- 0
    for each u in V[G]
            DFS_VISIT(v)
    max_visita <- 0
    conta_uguale1 <- 0
    for each u in V[G]
        tempo_visita <- f[u] - d[u]
        if tempo_visita = 1
            conta_uguale1 <- conta_uguale1 + 1
        else if tempo_visita > max_visita
            max_visita <- tempo_visita
    return conta_uguale1, max_visita 


DFS_VISIT(u)
    color[u] <- GRAY 
    d[u] <- time <- time + 1
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v)
    color[u] <- BLACK
    f[u] <- time <- time + 1


/*Dato un albero binario verificare che sia un Red Black*/
VerificaRedBlack(root)
    if root.color != BLACK
        return FALSE 
    valido, bh <- VerificaNodo(root)
    return valido

VerificaNodo(nodo)
    if nodo = NIL 
        return (TRUE,1)
    if nodo.color = RED 
        if nodo.left.color = RED or nodo.right.color = RED 
            return (FALSE,0)
    sx_valid,sx_bh <- VerificaNodo(nodo.left)
    dx_valid,dx_bh <- VerificaNodo(nodo.right)
    if not sx_valide or not dx_valido
        return(FALSE,0)
    if sx_bh != dx_bh
        return(FALSE,0)
    if nodo.color = BLACK
        return (TRUE,sx_bh+1)
    else 
        return (TRUE,sx_bh)

/*Dato un grafo non orientato G=(V,E) pesato con funzione peso ω:E->R. 
Si scriva in pseudocodice un algoritmo che restituisca l’arco leggero e non sicuro 
di peso mediano.*/

TrovaArcoMedianoNonSicuro(G)
    creo ListaArchi vuota
    for each (u,v) in G.E
        add (u,v) in ListaArchi
    sort(ListaArchi)
    n <- |ListaArchi|
    peso_mediano <- ListaArchi[n/2].peso
    for each (u,v) in G.E
        if w(u,v) = peso_mediano
            G2 <- G - (u,v)
            MST <- <- Kruskal(G2,w)
            if (u,v) non appartiene a MST
                return (u,v)
    return NIL

Kruskal(G,w)
    A <- vuoto
    for each v in G.V
        MakeSet(v)
    sort(G.E) in ordine non decrescente di w 
    for each (u,v) in G.E
        if FindSet(u) != FindSet(v)
            A <- A + {(u,v)}
            Union(u,v)
    return A


/*Vostro padre è appassionato di vino. Vostro padre è anche affetto da diabete e
non può bere vini con un grado alcolico elevato. 
Poiché domani festeggerà gli anni, avete deciso di regalargli alcune bottiglie, 
acquistandole su Amazon. Supponendo che il vostro budget è di K euro e che per ogni 
bottiglia disponibile b sia noto sia il suo prezzo P(b) e sia il grado alcolemico A(b), 
scrivete un algoritmo che determini le bottiglie da acquistare minimizzando il grado 
alcolemico complessivamente acquistato. Supponete che P(b) ed A(b) siano interi, per 
ogni bottiglia b.*/

//zaino01

KnapsackMinAlcol(P,A,K)
    n <- length[P]
    for i=0 to n 
        for b = 0 to K 
            v[i,b] <- +inf 
    for i = 0 to n 
        for b = 1 to K 
            if b < P[i]
                v[i,b] <- v[i-1,b]
            else if v[i-1,b] > v[i-1,b-P[i]] + A[i]
                v[i,b] <- v[i-1,b]
            else 
                v[i,b] <- v[i-1,b-P[i]] + A[i]
    return v 

/*L' aeroporto di Capodichino ha appena fatto costruire una nuova pista di decollo ed atterraggio.
Il direttore dell' aeroporto decide di utilizzare la pista per servire i nuovi N aerei che
dovranno decollare dall' aeroporto. Supponiamo che sia ti il tempo necessario all' i-esimo 
aereo per decollare, scrivere un algoritmo, in pseudocodice, che utilizzando la struttura 
dati coda di prioritá minimizzi il tempo totale di attesa (o turnaround) degli N aerei 
per decollare. (7 punti)*/

TurnaroundMinimo(T,N)
    creo codi di priorità Q vuota
    for i=1 to N 
        add(T[i] in Q)
    tempo_attuale <- 0
    turn_around_totale <- 0
    while Q != vuota
        t <- EstraiMin(Q)
        turnaround_totale <- turnaround_totale + temp_attuale
        tempo_attuale <- tempo_Attuale + t 
    return turnaround_totale



/*Dato un grafo G = (V,E), scrivere un algoritmo in pseudocodice che restituisca 
l' arco non sicuro di peso minimo. (7 punti)*/

TrovaArcoMinimoNonSicuro(G,w)
    creo una Lista di Archi vuota ListaArchi
    for each (u,v) in G.E
        add (u,v,w(u,v)) in ListaArchi
    sort(ListaArchi)
    for each (u,v) in ListaArchi
        G2 <- G - (u,v)
        MST <- Kruskal(G2,w)
        if (u,v) non appartiene a MST 
            return (u,v)
    return NIL 

Kruskal(G,w)
    creo A vuoto
    for each v in G.V
        MakeSet(v)
    sort(G.E)
    for each (u,v) in G.E
        if Findset(u) != Findset(v)
            A <- A + {(u,v)}
            Union(u,v)
    return A



/*
Dato un grafo orientato G = (V,E), definiamo grado di connessione di un nodo u il
numero di nodi raggiungibili da u in G. Scrivere un algoritmo in pseudocodice che
restituisca il nodo con il grado di connessione massimo nel caso in cui G sia aciclico
*/

NodoConnessioneMassima(G)
    for each u in V[G]
        visited <- array di FALSE di dimensione |V[G]|
        grado[u] <- DFS_VISIT(u,visited)
    max_gradoo <- -1
    nodo_max <- NIL 
    for each u in V[G]
        if grado[u] > max_grado
            max_gradi <- grado[u]
            nodo_max <- u 
    return nodo_max

DFS_VISIT(u,visited)
    visited[u] <- TRUE 
    count <- 1
    for each v in Adj[u]
        if not visited[v]
        count <- count + DFS_VISIT(b,visited)
    return count


/*
Dato un grafo G = (V,E) orientato, aciclico e pesato con funzione peso w: E - R+
ed un nodo s E V, scrivere un algoritmo in pseudocodice che per ogni u E V restituisca
il peso medio degli archi del cammino minimo s~u
*/

PesoMedioCamminoMinimo(G,w,s)
    for each u in V[G]
        dist[u] <- +inf 
        numArchi[u] <- 0
    dist[s] <- 0
    ordine <- TopologicalSort(G)
    for each u in ordine
        for each v in Adj[u]
            if dist[v] > dist[u] + w(u,v)
                dist[v] <- dist[u] + w(u,v)
                numArchi[v] <- numArchi[u] + 1
    for each v in V[G]
        if v != s and numArchi[v] > 0
            pesomedio[v] <- dist[v] / numArchi[v]
        else 
            pesomedio[v] <- NIL 
        return pesomedio




TopologicalSort(G)
    L <- nuovo stack
    for each u in V[G]
        color[u] <- WHITE
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,L)
    return L

DFS_VISIT(u,L)
    color[u] <- GRAY 
    for each v in Adj[u]
        if color[v] = WHITE 
            DFS_VISIT(v,L)
    color[u] <- BLACK 
    push(L,u)


/*Dato un grafo G=(V, E) aciclico, orientato e pesato con funzione peso non negativa w: E - R+, 
due interi l e h E N con l < h ed un nodo s E V, 
si scriva un algoritmo in pseudocodice che restituisca il numero di
nodi raggiungibili da s con un cammino minimo di lunghezza m tale che l <= m <= h
*/

Djikstra(G,w,s)
    INITIALIZE_SINGLE_SOURCE(G,s)
    creo S vuoto 
    Q <- G.V
    while Q != vuoto 
        u <- EXTRACT_MIN(Q)
        S <- S + {u}
        for each v in u.Adj
            RELAX(u,v,w)
    conta <- 0
    for each v in G.V 
        if v != s and d[v] >= l and d[v] <= h 
            conta <- conta + 1
    return conta 

INITIALIZE_SINGLE_SOURCE(G,s)
    for each v in G.V - {s}
        d[v] <- +inf 
        pi[v] <- NIL 
    d[s] <- 0
    pi[s] <- NIL 

RELAX(u,v,w)
    if d[v] > d[u] + w(u,v)
        d[v] <- d[u] + w(u,v)
        pi[v] <- u


/*Ciro é ghiotto di babá ed é tifoso del Napoli. Per festeggiare la vittoria del Napoli, 
sua madre si reca in pasticceria per acquistare babá. Sfortunatamente la pasticceria 
non vende babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo C[t] ed 
un numero di babá B[t]. Infine, la madre ha deciso di spendere in pasticceria al massimo E euro. 
Scrivere un algoritmo, in pseudocodice, che, ricevendo come input le N torte a disposizione e E 
la somma massima a disposizione, restituisca il numero massimo dei babá che possono essere 
acquistati. Si assuma che sia possibile acquistare singole fette di torta. (7 punti)*/

//zaino frazionario
BabaNapoli(C,B,N,E)
    X <- array inizializzato a 0 di N elementi 
    Value <- 0.0
    k <- 1 
    while (k<=N) and (E > 0.0)
        if C[k] <= E 
            X[k] <- 1.0
            Value <- Value + B[k]
            E <- E - C[k]
        else 
            X[k] <- E / C[k]
            Value <- Value + X[k] * B[k]
            E <- 0.0
        k <- k + 1
    return Value, X

/*•	Dato un grafo orientato G = (V, E) si scriva in pseudocodice un algoritmo che 
calcoli le componenti fortemente connesse del grafo. Si descriva lo pseudocodice di 
ogni funzione richiamata. (7 punti)*/

DFS(G)
    L <- nuovo stack 
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NIL 
        time <- 0
    for each u in V[G]
        if color[u] = WHITE
            DFS_VISIT(u,L)
    create GT 
    while L != vuoto
        v <- L.pop()
        if color[v] = WHITE 
            DFS_VISIT2(v,GT)
        SCC = predecessor-subgraph

DFS_VISIT(u,L)
    color[u] <- GRAY 
    d[u] <- time <- time + 1
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v,L)
    color[u] <- BLACK
    f[u] <- time <- time + 1
    push(L,u)

DFS_VISIT2(u,GT)
    color[u] <- GRAY 
    d[u] <- time <- time + 1
    for each v in AdjT[u]
        if color[u] = WHITE 
            pi[v] <- u 
            DFS_VISIT2(v,GT)
    color[u] <- BLACK 
    f[u] <- time <- time + 1


/*Dato un grafo connesso non orientato pesato G = (V, E) con pesi w(u, v) ed un vertice r E V, 
si scriva un algoritmo in pseudocodice che restituisca il nodo di grado massimo del MST radicato 
in r. (7 punti)*/

MST_Prim(G,w,r)
    for each u in V[G]
        u.key <- +inf 
        u.pi <- NIL 
    key[r] <- 0
    while Q != vuota
        u <- EXTRACTMIN(Q)
        for each v in Adj[u]
            if v in Q and w(u,v) < v.key
                pi[v] <- u 
                key[v] <- w(u,v)
    for each u in G.V 
        grado[u] <- 0 
    for each u in G.V 
        if u.pi != NIL 
            grado[u] <- grado[u] + 1
            grado[u.pi] <- gardo[u.pi] + 1
    mx_grado <- -1
    nodo_max <- NIL 
    for each u in G.V 
        if grado[u] > max_grado 
            max_grado <- grado[u]
            nodo_max <- u 
    return nodo_max


/*Si consideri un file F costituito da 100000 simboli ( ! ) & = ? le
cui frequenze sono rispettivamente 11%, 6%, 23%, 17%, 14%, 29%. Si
scriva un programma, in pseudocodice, che costruisca l' albero di codifica
di Huffman e determinare per ogni simbolo la sua codifica di Huffman.
Calcolare l' eventuale risparmio di memoria che si otterrebbe codificando
il file con la codifica di Huffman e invece di una codifica a lunghezza fissa.
(7 punti)*/

Huffman(Simboli,|Frequenze|)
    n <- |Simboli|
    Q <- Simboli
    for i <- 1 to n-1
        z <- ALLOCATE_NODE()
        x <- LEFT[z] <- EXTRACT_MIN(Q)
        y <- RIGHT[z] <- EXTRACT_MIN(Q)
        f[z] <- f[x] + f[y]
        INSERT(Q,z)
    root <- EXTRACT_MIN(Q)
    HuffmanCode(root,"")

EXTRACT_MIN(Q)
    if Q.heapsize < 1
        error "underflow dell'heap"
    min <- Q[1]
    Q.heapsize <- Q.heapsize - 1
    MinHeapify(Q,1)
    return min 

HuffmanCode(nodo,codice)
    if nodo è una foglia 
        print nodo.simbolo,codice
    else 
        HuffmanCode(LEFT[nodo],codice + "0")
        HuffmanCode(RIGHT[nodo],codice + "1")

/*Calcolo risparmi energia:
Codifica fissa: 6 simboli -> 3 bit = 8
Totale 100000 * 3 = 300000 bit
COdifica di Huffman:
( = 100000 * (11/100) = 11000 * 4 = 44000
! = 100000 * (6/100) = 6000 * 4 = 24000
) = 100000 * (23/100) = 23000 * 2 = 46000
& = 100000 * (17/100) = 17000 * 2 = 34000
= = 100000 * (14/100) = 14000 * 3 = 42000
? = 100000 * (29/100) = 29000 * 2 = 58000
Risparmio = 300000 - 267000 = 33000 bit
*/



/*Dato un grafo non orientato G = (V,E) e non pesato, un nodo sorgente
che restituisca la lista dei nodi, il cui cammino minimo dal nodo sorgente s € V, 
ed un numero intero k E N scrivere un algoritmo, in pseudocodice, che restituisca la 
lista dei nodi, i lcui cammino minimo dal nodo sorgente
s sia minore di k. (7 punti)*/

BFS(G,s,k)
    for each u in V[G] - {s}
        color[u] <- WHITE 
        pi[u] <- NIL 
        d[u] <- +inf 
    color[s] <- GRAY 
    d[s] <- 0
    pi[s] <- NIL 
    creo coda Q vuota
    ENQUEUE(Q,s)
    qhile Q != vuota 
        u <- DEQUEUE(Q)
        for each v in Adj[u]
            if color[v] = WHITE 
                color[v] <- GRAY 
                pi[v] <- u 
                d[v] <- d[u] + 1
                ENQUEUE(Q,v)
        color[u] <- BLACK 
    creo ListaNodi vuota
    for each u in V[G]
        if u != s and d[u] < k 
            add u in ListaNodi 
    return ListaNodi

/*Gennaro è ghiotto di babá. Per il compleanno di Gennaro, sua madre si
reca in pasticceria per acquistarne. Sfortunatamente la pasticceria non
vende babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo 
C[t] ed un numero di babá B[t]. Infine, la madre ha deciso di spendere in pasticceria 
al massimo E euro. Scrivere un algoritmo, in pseudocodice, che, ricevendo come input le N
torte a disposizione e E la somma massima a disposizione, restituisca il
numero massimo dei babá che possono essere acquistati. Si assuma che sia possibile 
acquistare parti di torta. (7 punti)*/

MaxBaba(C,B,N,E)
    X <- array inizializzato a 0 di N elementi
    Value <- 0.0
    k <- 1
    while (k<=N) and (E>0.0)
        if C[k] <= E 
            X[k] <- 1.0
            Value <- Value + B[k]
            E <- E - C[k]
        else 
            X[k] <- E/C[k]
            Value <- Vaue + X[k] * B[k]
            E <- 0.0
        k <- k + 1
    return Value,X



/*Dato un grafo orientato G = (V, E) e pesato con funzione peso w : E -> R scrivere in 
pseudocodice un algoritmo ricorsivo che restituisca la somma dei pesi del più lungo ciclo in G. 
(7 punti)*/

TrovaIlCicloMassimo(G,w)
    max_ciclo <- -inf 
    for each u in G.V
        visited <- array inzializzato a FALSE di G.V elementi
        max_ciclo <- max(max_ciclo,DFS_VISIT(u,u,0,visited,w))
    return max_ciclo

DFS_VISIT(start,u,somma,visited,w)
    u.visited <- TRUE 
    maxSomma <- somma 
    for each v in u.Adj
        if v = start 
            maxSomma <- max(maxSomma,somma + w(u,v))
        else if not v.visted
            temp <- DFS_VISIT(start,v,somma+w(u,v),visited,w)
            maxSomma <- max(maxSomma,temp)
    u.visited <- FALSE 
    return maxSomma


/*Dato un grafo non orientato G = (V,E) scrivere un algoritmo in pseu-
docodice che restituisca l' arco di peso massimo appartenente al MST
costruito su G. Per semplicitá supporre di porre una condizione su G in
modo tale che MST sia unico. Indicare quale debba essere la condizione
(7 punti)*/

TrovaArcoMassimo(G,w)
    MST <- Kruskal(G,w)
    peso_max <- -inf 
    arco_max <- NIL 
    for each (u,v) in MST 
        if w(u,v) > peso_max 
            peso_max <- w(u,v)
            arco_max <- (u,v)
    return arco_max

Kruskal(G,w)
    A <- vuoto
    for each v in G.V
        Makeset(v)
    sort(G.E) in ordine crescente di w 
    for each (u,v) in G.E
        if FindSet(u) != Findest(v)
            A <- A + {(u,v)}
            Union(u,v)
    return A 


/*Per il compleanno di Gennaro, sua madre si reca in edicola per acquistare
figurine di calciatori. L'edicola non vende figurine singole, ma soltanto N
bustine contenenti figurine. Ogni bustina di figurina b ha un costo C[b] e
contiene un numero di figurine F[b] e sia E la somma massima, in euro,
che la madre ha deciso di spendere in edicola.
Scrivere un algoritmo, in pseudocodice, che, ricevendo come input le N
bustine a disposizione e E la somma massima a disposizione, restituisca il
numero massimo di figurine che possono essere acquistate. (7 punti)*/

Zaino0_1_MaxFigurine(N,C,F,E)
    for i = 0 to N 
        V[i,0] <- 0
    for e to E 
        V[0,e] <- 0
    for i = 1 to N 
        for e = 1 to E 
            if e < C[i]
                V[i,e] <- V[i-1,e]
            else if V[i-1,e] > V[i-1,e-C[i]] + F[i]
                V[i,e] <- V[i-1,e]
            else 
                V[i,e] <- V[i-1,e-C[i]] + F[i]
    return V


/*Dato un grafo orientato G = (V, E) aciclico e pesato con funzione peso
w : E - R e sorgente s, scrivere un algoritmo, in pseudocodice, che
restituisca il nodo di grado massimo dell'albero dei cammini minimi di G.
(7 punti)*/


NodoGradoMassimo(G,w,s)
    for each v in V[G]
        dist[v] <- +inf 
        pi[v] <- NIL 
    dist[s] <- 0

    ordine <- TopologicalSort(G)

    for each u in ordine
        for each (u,v) in E 
            if dist[v] > dist[u] + w(u,v)
                dist[v] <- dist[u] + w(u,v)
                pi[v] <- u 
    for each v in V[G]
        grado[v] <- 0 
    for each v in V[G]
        if pi[v] != NIL 
            grado[pi[v]] <- grado[pi[v]] + 1
    max_grado <- 1 
    nodo_max <- NIL 
    for each v in V[G]
        if grado[v] > max_grado 
            max_grado <- grado[v]
            nodo_max <- v 
    return nodo_max



/*Dato un grafo orientato G=(V,E) non pesato, si scriva in pseudocodice un algoritmo che 
restituisca il numero dei cicli presenti nel grafo. (8 punti) */

DFS(G)
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NULL 
        time <- 0
    count <- 0
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,count)
    return count

DFS_VISIT(u,count)
    color[u] <- GRAY 
    d[u] <- time <- time + 1
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v,count)
        else if color[v] = GRAY //ciclo trovato
            count <- count + 1
    color[u] <- BLACK
    f[u] <- time <- time + 1


/*Il vostro provider di internet vi ha dato la possibilità di accedere ad un videoserver per 
un’ora e di fare liberamente il download di un file alla volta. Il videoserver vi mette anche a 
disposizione per ogni suo film F il suo tempo stimato di download. Supponete che nell’ora 
a vostra disposizione la velocità di download rimanga costante e che non sia possibile 
scaricare contemporaneamente più film. Scrivete un algoritmo in peseudocodice che 
massimizzi il numero di film scaricati nel tempo a disposizione. 
Stimate la complessità computazionale del vostro algoritmo. (8 punti) */

MaxDilmScaricati(Film,T)
    sort(Film)
    conta <- 0
    tempo_usato <- 0
    for each d in Film 
        if tempo_usato + d <= T 
            tempo_usato <- tempo_usato + d 
            conta <- conta + 1
        else 
            break 
    return conta 



/*Dato un grafo non orientato G=(V,E) pesato con funzione peso ω:E->R. 
Si scriva in pseudocodice un algoritmo che restituisca l’arco leggero e non sicuro di peso 
mediano.*/


TrovaArcoMedianoNoSicuro(G)
    creao ListaArchi vuota 
    for each (u,v) in G.E
        add(u,v,w) in ListaArchi 
    sort(ListaArchi)
    n <- |ListaArchi|
    peso_mediano <- ListaArchi[n/2].peso
    for each (u,v) in ListaArchi
        if w(u,v) = peso_mediano
            G2 <- G - (u,v)
            MST <- Kruskal(G2,w)
            if (u,v) non appartiene a MST
                return (u,v)
    return NIL 

Kruskal(G,w)
    creo A vuoto
    for each v in G.V
        Makeset(v)
    sort(G.E)
    for each (u,v) in G.E 
        if Findset(u) != Findset(v)
            A <- A + {(u,v)}
            Union(u,v)
    return A 



/*Vostro padre è appassionato di vino. Vostro padre è anche affetto da diabete e non può 
bere vini con un grado alcolico elevato. 
Poiché domani festeggerà gli anni, avete deciso di regalargli alcune bottiglie, acquistandole 
su Amazon. 
Supponendo che  il vostro budget è di K euro e che per ogni bottiglia disponibile b sia noto 
sia il suo prezzo P(b) e sia il grado alcolemico A(b), scrivete un algoritmo che determini le 
bottiglie da acquistare minimizzando il grado alcolemico complessivamente acquistato. 
Supponete che P(b) ed A(b) siano interi, per ogni bottiglia b. */

KnapsackAlcol(K,P,A)
    n <- length(P)
    for i = 0 to n 
        V[i,0] <- +inf
    for w = 0 to K  
        V[0,w] <- +inf
    for i = 1 to n 
        for w = 1 to K 
            if w < P[i]
                V[i,w] <- V[i-1,w]
            else 
                V[i,w] <- min(V[i-1,w], V[i-1,w-P[i]] + A[i])
    min_alcol <- +inf 
    for w = 0 to K 
        min_alcol <- min(min,alcol,V[n,w])
    return min_alcol



/*Dato un grafo orientato G=(V,E) non pesato, si scriva in pseudocodice un algoritmo che 
restituisca il numero dei cicli presenti nel grafo. (8 punti) */

DFS(G)
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NIL 
        count <- 0
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,count)


DFS_VISIT(u,count)
    color[u] <- GRAY
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v,count)
        else if color[v] = GRAY //ciclo trovato
            count <- count + 1
    color[u]<- BLACK


/*Il vostro provider di internet vi ha dato la possibilità di accedere ad un videoserver per 
un’ora e di fare liberamente il download di un file alla volta. Il videoserver vi mette anche a 
disposizione per ogni suo film F il suo tempo stimato di download. Supponete che nell’ora 
a vostra disposizione la velocità di download rimanga costante e che non sia possibile 
scaricare contemporaneamente più film. Scrivete un algoritmo in peseudocodice che 
massimizzi il numero di film scaricati nel tempo a disposizione. 
Stimate la complessità computazionale del vostro algoritmo. (8 punti) */

MaxDilmScaricati(Film,T)
    n <- |Film|
    sort(Film)
    conta <- 0
    tempo_usato <- 0
    for each f in Film 
        if tempo_usato + f <= T 
            tempo_usato <- tempo_usato + f 
            conta <- conta + 1
        else 
            break 
    return conta 

//Ordinamento: O(n log n) , Scansiuone : O(n) , Totlae : O(n log n)


/*Dato un grafo orientato G=(V,E) ed un albero radicato T con radice g e composto da tutti i 
nodi V, scrivere un algoritmo in pseudocodice che restituisca TRUE se T corrisponde 
all’albero DF del grafo G e FALSE altrimenti. (8 punti) */

VerificaAlberoDFS(G,T,g)
    for each V in V[G]
        color[v] <- WHITE 
        pi[v] <- NIL
    DFS_VISIT(g)
    for each u in V[G]
        if pi[v] != piT[v]
            return FALSE 
        return TRUE 
    
DFS_VISIT(u)
    color[u] <- GRAY 
    for each v in Adj[u]
        if coor[v] <- WHITE 
            pi[v] <- u 
            DFS_VISIT(v)
    color[u] <- BLACK



/*Scrivere un algoritmo in pseudocodice, che risolva il problema dello zaino 01, utilizzando la 
tecnica della memoization (8 punti) */

Zaino01_Memo(i,W)
    if i=0 or W = 0
        return 0 
    if Memo[i,W] != NIL 
        return Memo[i,W]
    if P[i] > W 
        Memo[i,W] <- Zaino01_Memo(i-1,W)
    else 
        Memo[i,W] <- max(Zaino01_Memo(i-1,W), Zaino01_Memo(i-1,W-P[i]) + V[i])
    return Memo[i,W]



/*Dato un grafo G=(V,E) aciclico orientato e pesato con funzione peso non negativa w: E ->R+ ed un nodo s (appartenente) a V, 
si scriva un algoritmo in pseudocodice che restituisca
i nodi foglia dell’albero dei cammini minimi radicato in s. (7 punti)*/

NodiFogliaCamminiMinimi(G,w,s)
    for each v in V[G]
        dist[v] <- +inf 
        pi[v] <- NIL 
    dist[s] <- 0
    ordine <- TopologicalSort(G)
    for each u in ordine 
        for each v in Adj[u]
            if dist[v] > dist[u] + w(u,v)
                dist[v] <- dist[u] <- w(u,v)
                pi[v] <- u 
    foglie <- vuoto 
    for each v in V[G]
        is_foglia <- TRUE 
        for each u in V[G]
            if pi[v] = u 
                is_foglia = FALSE 
        if is_foglia and v != s and pi[v] != NIL 
            add v in foglie
    return foglie 


TopologicalSort(G)
    L <- new Stack 
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NIL 
        
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,L)
    return L

DFS_VISIT(u,L)
    color[u] <- GRAY 
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[V] <- u 
            DFS_VISIT(v,L)
    color[u] <- BLACK 
    push(L,u)


/*Dato un grafo orientato G = (V,E), scrivere un algoritmo, in pseucodice, che calcoli il numero dei cicli, di 
lunghezza maggiore di 1, presenti nel grafo (7 punti).*/

ContaCicli(G)
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NULL 
        count <- 0
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,count)

DFS_VISIT(u,count)
    color[u] <- GRAY 
    for each v in Adj[u]
        if color[v] = GRAY 



/*Dato un grafo non orientato G=(V,E) pesato, con funzione peso w:E->R. 
Si scriva in pseudocodice un algoritmo che restituisca l’arco leggero non sicuro di peso 
minimo. (7 punti) */

ArcoNonSicuroPesoMinimo(G)
    creo listaarchi <- vuota
    for each (u,v) in G.E
        add(u,v,w(u,v)) in ListaArchi 
    sort(listaarchi) //in ordine crescente di w
    for each (u,v) in listaarchi
        G2 <- G -{(u,v)}
        MST <- Kruskal(G2,w)
        if (u,v) non appartiene a MST 
            return (u,v)
    return NIL


Kruskal(G,w)
    A <- vuoto 
    for each v in G.V
        Makeset(v)
    sort(G.E)
    for each (u,v) in G.E
        if Findset(u) != Findset(v)
            A <- A + {(u,v)}
            Union(u,v)
    return A


/*La Fiat per la produzione della nuova panda ha installato nello stabilimento di Pomigliano
d’Arco K catene di montaggio.
Ogni catena di montaggio ha L stazioni di lavoro.
Ogni stazione di lavoro ha un tempo di lavorazione differente T.
Inoltre il telaio della nuova panda impiega un tempo iniziale I per entrare nella catena di
montaggio ed un tempo differente U per ogni catena di montaggio per uscire. Si assuma
che il tempo di migrazione tra due stazioni successive all’interno della stessa catena sia e.
Infine, per fornire all’impianto la massima flessibilità si preveda la possibilità che la nuova
panda possa migrare da una catena di montaggio all’altra e tale operazione impieghi un
tempo, differente per ogni catena, pari ad S.
Si risolva, mediante la programmazione dinamica, il problema di individuazione per ogni
vettura del percorso più rapido, scrivendo le relative equazioni di ricorrenza.
Successivamente si scriva, un algoritmo di memoization, in pseudocodice, che, utilizzando
le equazioni di ricorrenza suddette, individui per ogni vettura il percorso più rapido.
(7 punti)*/

Fastest_way(K,L,T,I,U,e,S)
    for i = 1 to K 
        DP[i][1] <- I[i] + T[i][1]
        prec[i][1] <- NIL 
    for j <- 2 to L
        for i = 1 to K 
            minTempo <- DP[i][j-1] + T[i][j] + e[i]
            prevCat <- i 
            for k = 1 to K 
                if k != i 
                    temp <- DP[k][j-1] + S[k][i] + T[i][j]
                    if temp < minTempo 
                        minTempo <- temp 
                        prevCat <- k 
            DP[i][j] <- minTempo 
            prev[i][j] <- prevCat 
    minTot <- +inf 
    lastCat <- NIL 
    for i = 1 to K 
        temp <- DP[i][L] + U[i]
        if temp < minTot
            minTot <- temp 
            lastCat <- i 
    percorso <- array vuoto 
    cat <- lastCat 
    for j = L downto 1 
        percorso[j] <- cat 
        cat <- prev[cat][j]
    return minTot, percorso 


/*Dato un grafo orientato G=(V,E) e pesato con funzione peso w: E->R, scrivere un algoritmo, 
in pseudocodice, che restituisca TRUE se ogni nodo è raggiungibile da ogni altro nodo e 
FALSE altrimenti. (7 punti) */


IsConnected(G)
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NIL 
    time <- 0 
    DFS_VISIT(u)
    for each v in V[G]
        if color[v] = WHITE 
            return FALSE 
    return TRUE

DFS_VISIT(u)
    color[u] <- GRAY 
    d[u] <- time <- time + 1
    for each v in Adj[u]
        if color[b] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v)
    color[u] <- BLACK 
    f[u] <- time <- time + 1


/*Si scriva un algoritmo che calcoli la Longest Common Sequence tra il proprio nome ed i lproprio cognome*/

LCS(nome,cognome)
    m <- length(nome)
    n <- length(cognome)
    for i = 0 to m 
        L[i,0] <- 0
    for j = 0 to n 
        L[0,j] <- 0
    for i = 1 to m 
        fr j = 1 to n 
            if nome[i] = cognome[j]
                L[i,j] <- L[i-1,j-1] + 1
                b[i,j] <- "D"
            else if L[i-1,j] >= L[i,j-1]
                L[i,j] <- L[i-1,j]
                b[i,j] <- "U"
            else    
                L[i,j] <- L[i,j-1]
                b[i,j] <- "L"
    return L,b


/*Dato un grafo orientato G=(V,E) aciclico e pesato con funzione peso w: E->R e sorgente s , scrivere un 
algoritmo, in pseudocodice, che restituisca il nodo di grado massimo dell'alberop dei cammini minimi di G. (7 punti)*/

NodoGradoMAssimo(G,w,s)
    for each v in V[G]
        dist[v] <- + inf 
        pi[v] <- NIL 
    dist[s] <- 0

    ordine <- TopologicalSort(G)
    for each u in ordine 
        for each (u,v) in G.E
            if dist[v] > dist[u] + w(u,v)
                dist[v] <- dist[u] + w(u,v)
                pi[v] <- u 

    for each v in V[G]
        grado[v] <- 0
    for each v in V[G]
        if p[v] != NIL 
            grado[pi[v]] <- grado[pi[v]] + 1
    
    max_grado <- 0
    nodo_max <- NIL 
    for each v in V[G]
        if grado[v] > max_grado 
            max_grado <- grado[v]
            nodo_max <- v 
    return nodo_max

TopologicalSort(G)
    L <- new Stack 
    for each u in V[G]
        color[u] <- WHITE 
        pi[u] <- NIL 
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,L)
    return L


DFS_VISIT(u,L)
    color[u] <- GRAY 
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v,L)
    color[u] <- BLACK 
    push(L,u)


/*Dato un grafo orientato G=(V,E) un nodo sorgente s E V , scrivere un algoritmo, in pseudocodice, 
che restituisca la lista dei nodi, il cui cammino minimo dal nodo sorgente s è massimo. (7 punti)*/

ListaNodiCamminoMassimo(G,s)
    for each v in V[G]
        dist[v] <- + inf 
        pi[v] <- NIL 
    dist[s] <- 0

    ordine <- TopologicalSort(G)
    for each u in ordine 
        for each v in Adj[u]
            if dist[v] > dist[u] + 1
                dist[v] <- dist[u] + 1
                pi[v] <- u 
    max_dist <- -inf 
    for each v in V[G]
        if dist[v] != +inf and dist[v] > max_dist
            max_dist <- dist[v]
    creo listaNOdi vuota 
    for each v in V[G]
        if dist[v] = max_dist
            add c in ListaNodi
    return ListaNodi


/*archi trasversali*/

DFS(G)
    time <- 0
    trsversali <- 0
    for each v in V[G]
        color[v] <- WHITE
        pi[v] <- NIL 
        d[v] <- 0
        f[v] <- 0 
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,trasversali)
    return trasversali 


DFS_VISIT(u,trasversali)
    color[u] <- GRAY 
    time <- time + 1 
    d[u] <- time 
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v,trasversali)   
        else if color[v] = BLACK and d[u] > d[v]
            traversli <- trasversali + 1 
    time <- time + 1
    f[u] <- time 
    color[u] <- BLACK 

// se vuoi contare i cappi 
    else if color[v] = GRAY and d[u] = d[v]
        cappi <- cappi + 1

//se vuoi contare i cicli 
    else if color[v] = GRAY 
        cicli <- cicli + 1

//se vuo icontare archi in avanti 
    else if color[v] = BLACK and d[u] < d[v]
        avanti <- avanti + 1

    

/*Ciro é ghiotto di babá. Per il compleanno di Ciro, sua madre si reca
in pasticceria per acquistarne. Sfortunatamente la pasticceria non vende
babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo C[t]
ed un numero di babá B[t]. Infine, la madre ha deciso di spendere in
pasticceria al massimo E euro.
Scrivere un algoritmo che, ricevendo come input le N torte a disposizione
e E la somma massima a disposizione, restituisca il numero massimo dei
babá che possono essere acquistati. Si assuma che i valori del costo
numero di babá siano interi per ogni torta e che non sia possibile acquistare
singole fette di torta. (5 punti)*/

// B[t] = valore degli elementi v , C[t] = e il peso degli elementi w, E = la capictà dello zaino W,
// N = numero di elemnti n 

Knapsack0_1(N,C,B,E)
    for i <- 0 to N 
        V[i,0] <- 0 
    for e <- 0 to E 
        V[0,e] <- 0 
    for i <- 1 to N 
        for e <- 1 to W 
            if e < C[i]
                V[i,e] <- V[i-1,e]
            else if V[i-1,e] > V[i-1,e-C[i]] + B[i]
                V[i,e] <- V[i-1,e]
            else 
                V[i,e] <- V[i-1,e-C[i]] + B[i]
    return V

    

/*Dato un grafo connesso non orientato pesato G = (V, E) con pesi w(u, v)
ed un vertice r € V, si scriva un algoritmo in pseudocodice che restituisca
il nodo di grado massimo del MST radicato in r. (8 punti)*/

Prim(G,w,r)
    for each u in G.V 
        u.key <- +inf 
        u.pi <- NIL 
    key[t] <- 0
    Q <- G.V 
    while Q != vuoto 
        u <- EXTRACTMIN(Q)
        for each v in Adj[u]
            if v in Q and w(u,v) < key[v]
                v.pi <- u 
                v.key <- w(u,v)

    for each u in G.V 
        grado[u] <- 0
    for each u in G.V 
        if u.pi != NIL 
            grado[u] <- grado[u] + 1
            grado[u.pi] <- grado[u.pi] + 1
    max_grado <- -1 
    nodo_max <- NIL 
    for each v in G.V 
        if grado[v] > max_grado
            max_grado <- grado[v]
            nodo_max <- v 
    return nodo_max 


/*Dato un grafo orientato G = (V,E), scrivere un algoritmo, in pseucodice, che calcoli il numero dei cicli, di 
lunghezza maggiore di 1, presenti nel grafo (7 punti). */

DFS(G)
    time <- 0
    cicli <- 0
    for each v in V[G]
        color[v] <- WHITE
        pi[v] <- NIL 
        d[v] <- 0
        f[v] <- 0 
    for each u in V[G]
        if color[u] = WHITE 
            DFS_VISIT(u,cicli)
    return cicli 


DFS_VISIT(u,cicli)
    color[u] <- GRAY 
    time <- time + 1 
    d[u] <- time 
    for each v in Adj[u]
        if color[v] = WHITE 
            pi[v] <- u 
            DFS_VISIT(v,cicli)   
        else if color[v] = GRAY and pi[u] != v
            cicli <- cicli + 1 
    time <- time + 1
    f[u] <- time 
    color[u] <- BLACK 


/*Dato un grafo orientato G = (V,E), scrivere un algoritmo, in pseu-
docodice, che restituisca il numero degli archi trasversali. (8 punti)*/

DFS(G)
    time <- 0 
    trsversali <- 0
    for each v in V[G]
        u.color <- WHITE 
        u.pi <- NIL 
    for each u in V[G]
        if u.color = WHITE 
            DFS_VISIT(u,trasversali)

DFS_VISIT(u,trasversali)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in u.Adj 
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,trasversali)
        else if v.color = BLACK and u.d > v.d
            trasversali <- trasversali + 1
    time <- time + 1
    u.f <- time 
    u.color <- BLACK



/*2. Ciro é ghiotto di babá. Per il compleanno di Ciro, sua madre si reca
in pasticceria per acquistarne. Sfortunatamente la pasticceria non vende
babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo C[t]
ed un numero di babá B[t]. Infine, la madre ha deciso di spendere in
pasticceria al massimo E euro.
Scrivere un algoritmo che, ricevendo come input le N torte a disposizione
e E la somma massima a disposizione, restituisca il numero massimo dei
babá che possono essere acquistati. Si assuma che i valori del costo e del
numero di babá siano interi per ogni torta e che non sia possibile acquistare
singole fette di torta. (5 punti)*/

//mappando: N = numero di torte, C = costo della torta quindi peso della torta, B = valore della torta, E = budget capacità dell ozaino
Knapsack0_1(N,B,C,E)
    for i <- 0 to N 
        V[i,0] <- 0
    for e <- 0 to E 
        V[0,e] <- 0

    for i <- 1 to N 
        for e <- 1 to E 
            if e < C[i]
                V[i,e] <- V[i-1,e]
            else if V[i-1,e] > V[i-1,e-C[i]] + B[i]
                V[i,e] <- V[i-1,e]
            else 
                V[i,e] <- V[i-1,e-C[i]] + B[i]
    return V

/*Considerare il problema precedente e si costrisca un esempio in cui i costi
C[t] siano valori reali. Fornire un algoritmo per risolvere l'esempio costru-
ito descrivendo l' albero delle soluzioni prodotto. (7 punti)*/



/*Dato un grafo connesso non orientato pesato G = (V, E) con pesi w(u, v)
ed un vertice r € V, si scriva un algoritmo in pseudocodice che restituisca
il nodo di grado massimo del MST radicato in r. (8 punti)*/

MST_Prim(G,w,r)
    for each u in G.V
        u.key <- +inf
        u.pi <- NIL 
    r.key <- 0
    Q <- G.V 
    while Q != vuoto 
        u <- EXTRACT_MIN(Q)
        for each v in u.Adj
            if v in Q and w(u,v) > v.key 
                v.pi <- u
                v. key <- w(u,v) //Decrease-Key

    for each u in G.V
        u.grado <- 0 
    for each v in G.V
        if v.pi != NIL 
            v.grado <- v.grado + 1
            v.pi.grado <- v.pi.grado + 1
    max_grado <- 1 
    nodo_max <- NIL 
    for each v in G.V
        if v.grado > max_grado 
            max_grado <- v.grado 
            nodo_max <- v 
    return nodo_max 



/*Si consideri un file F costituito da 300000 simboli ! ( £ ) & = ?  le
cui frequenze sono rispettivamente 33%, 6%, 4%, 26%, 13%, 10%, 8%. Si
scriva un programma, in pseudocodice, che costruisca l'albero di codifica
di Huffman e determinare per ogni simbolo la sua codifica di Huffman.
Calcolare l'eventuale risparmio di memoria che si otterrebbe codificando
il file con la codifica di Huffman e invece di una codifica a lunghezza fissa.
(7 punti)*/

Huffman(C)
    n <- |C
    Q <- C 
    for i <- 1 to n - 1
        z <- allocate_node()
        x <- z.left <- EXTRACT_MIN(Q)
        y <- z.right <- EXTRACT_MIN(Q)
        z.f <- x.f + y.f
        Insert(Q,z)
    return z

/*Calcolo risparmi energia:
Codifica fissa: 7 simboli -> 3 bit = 8
Totale 300000 * 3 = 900000 bit
COdifica di Huffman:
! = 300000 * (33/100) = 33000 * 2 = 66000
( = 300000 * (6/100) = 6000 * 4 = 24000
£ = 300000 * (4/100) = 4000 * 4 = 16000
) = 300000 * (26/100) = 26000 * 2 = 52000
& = 300000 * (13/100) = 13000 * 3 = 39000
= = 300000 * (10/100) = 10000 * 3 = 30000
? = 300000 * (8/100) = 8000 * 3 = 24000
Risparmio = 900000 - 251000 = 649000 bit
*/


/*Dato un grafo orientato G = (V,E), scrivere un algoritmo, in pseu-
docodice, che restituisca la differeraa tra il tumero dei cicli con numero
di vertici maggiore di uno. (7 punti)*/

DFS(G)
    time <- 0
    cicli <- 0
    cappi <- 0
    for each v in V[G]
        v.color <- WHITE 
        v.pi <- NIL 
    for each u in V[G]
        if u.color = WHITE 
            DFS_VISIT(u,cicli,cappi)
    differenza <- cicli - cappi
    return differenza
    
    

DFS_VISIT(u,cicli,cappi)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in u.Adj
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,cicli)
        else if v.color = GRAY 
            cicli <- cicli + 1 
        else if v.color = GRAY and u.d = v.d
            cappi <- cappi + 1
    time <- time + 1
    u.f <- time 
    u.color <- BLACK 


/*Dato un grafo non orientato G= (V,E), implementare in pseudocodice 
un algoritmo ricorsivo che restituisca TRUE se G è presente in un ciclo hamiltonianano e FALSE
altrimenti*/

Hamiltoniano(G)
    for each v in V[G]
        visited[v] <- FALSE 
    for each v in V[G]
        if HamiltonianoUtil(G,v,v,visted,1)
            return TRUE 
    return FALSE 

HamiltonianoUtil(G,start,u,visited,count)
    visted[u] <- TRUE 
    if count = |V[G]|
        if start in Adj[u]
            return TRUE 
        else 
            visited[u] <- FALSE 
            return FALSE 
    for each v in Adj[u]
        if not visited[v]
            if HamiltonianoUtil(G,start,v,visited,count+1)
                return TRUE 
    visited[u] <- FALSE 
    return FALSE 


/*Dato un grafo G(V,E), un nodo s, un intero k, restituire il numero di nodi, il cui cammino minimo da s è maggiore di k*/

BFS(G,s)
    for each v in V[G] - {s}
        v.color <- WHITE 
        v.pi <- NIL 
        v.d <- +inf 
    s.color <- GRAY 
    s.d <- 0
    s.pi <- NIL 
    creo Q vuoto 
    Enqueue(Q,s)
    while Q != vuoto
        u <- Dequeue(Q)
        for each v u.Adj
            if v.color = WHITE 
                v.color <- GRAY 
                v.d <- u.d + 1
                v.pi <- u 
                Enqueue(Q,v)
        u.color <- BLACK 
    count <- 0
    for each v in V[G]
        if v != s and dist[v] > k 
            count <- count + 1
    return count 

/*Costruire un MST e individuare il rango minimo dell'MST*/
Mst_Prim(G,w,r)
    for each v in G.V
        v.key <- +inf 
        v.pi <- NIL 
    r.key <- 0
    Q <- G.V
    while  Q != vuoto 
        u <- EXTRACT_MIN(Q)
        for each v in u.Adj
            if v in Q and w(u,v) < v.key
                v.pi <- u 
                v.key <- w(u,v)
    nodo_min <- NIL 
    min_ranfo <- +inf
    for each v in G.V
        v.grado <- 0
    for each v in G.V
        if v.pi != NIL 
            v.grado <- v.grado + 1
            v.pi.grado <- v.pi.grado + 1
            if v.grado < min_rango
                min_rango <- v.gardo 
                nodo_min <- v 
    return nodo_min, min_rango

/*Dfs con Differenza fra numero di Cicli e numero di Cappi o Verifica che il ciclo non è un cappio*/
DFS(G)
    time <- 0
    cicli <- 0 
    cappi <- 0
    for each v in V[G]
        v.color <- WHITE 
        v.pi <- NIL 
    for each u in V[G]
        if v.color = WHITE 
            DFS_VISIT(u,cicli,cappi)
    risultato <- cicli - cappi 
    return risultato
    

DFS_VISIT(u,cicli,cappi)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in u.Adj
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,cicli,cappi)
        else if v.color = GRAY and u.d = v.d
            cappi <- cappi + 1 
        else if v.color = GRAY 
            cicli <- cili + 1
    time <- time + 1
    u.d <- time 
    u.color <- BLACK
                

/*Dato un grafo non orientato, pesato, con radice R. Calcolare l'altezza del MST radicato in R*/
Mst_Prim(G,w,r)
    for each u in G.v
        u.key <- +inf 
        u.pi <- NIL 
    r.key <- 0
    Q <- G.V
    while Q != vuoto 
        u <- Extract_Min(Q)
        for each v in u.Adj
            if v in Q and w(u,v) < v.key
                v.pi <- u 
                v.key <- w(u,v)
    altezza <- 0 
    for each v in G.V 
        if v.pi != NIL 
            altezza <- max(altezza, v.d - v.pi.d)
    return altezza


/*Grafo che ritorna i pesi minimi non appartenenti all'mst e dire che se un MST è unico*/
Mst_Kruskal(G,w)
    A <- vuoto
    for each v in G.V
        Makeset(v)
    sort(G.E)
    for each (u,v) in G.E
        if Findset(u) != Findest(v)
            A <- A + {(u,v)}
            Union(u,v)
    peso_non_mst <- 0
    for each (u,v) in G.E
        if (u,v) non appartiene ad A 
            peso_non_mst <- peso_non_mst + w(u,v)
    return peso_mst

/*Grafo G non orientato e pesato con nodo sorgente s restituisce il nodo di grado massimo dell'mst*/
Mst_Prim(G,w,s)
    for each v in G.V
        v.key <- +inf 
        v.pi <- NIL 
    s.key <- 0
    Q <- G.V
    while Q != vuoto
        u <- Extract_Min(Q)
        for each v in u.Adj 
            if v in Q and w(u,v) < v.key 
                v.key <- w(u,v)
                v.pi <- u
    grado_max <- -1
    nodo_max <- NIL 
    for each u in G.V
        u.grado <- 0
    for each v in G.V
        if v.pi != NIL 
            v.pi.grado <- v.pi.grado + 1
            v.grado <- v.grado + 1
            if v.grado> grado_max 
                grado_max <- v.grado
                nodo_max <- v 
    return nodo_max

/*Dato un grafo orientato G = (V,E), scrivere un algoritmo, in pseu-
docodice, che restituisca il numero degli archi trasversali nel grafo (7 punti).*/

DFS(G)
    time <- 0
    trasversali <- 0
    for each v in V[G]
        v.color <- WHITE 
        v.pi <- NIL 
    for each u in V[G]
        if v.color = WHITE 
            DFS_VISIT(u,trasversali)
    return trasversali 

DFS_VISIT(u,trasversali)
    time <- time + 1
    u.color <- GRAY 
    u.d <- time 
    for each v in u.Adj
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,trasversali)
        else if v.color = BLACK and u.d > v.d 
            trasversali <- trasversali + 1
    time <- time + 1
    u.f <- time 
    u.color <- BLACK 


/*Prim torna il nodo di peso minore*/

Mst_Prim(G,w,s)
    for each u in G.V 
        u.key <- +inf 
        u.pi <- NIL 
    s.key <- 0
    Q <- G.V
    while Q != vuoto 
        u <- EXTRACT_MIN(Q)
        for each v in u.Adj
            if v in Q and w(u,v) < v.key 
                v.pi <- u 
                v.key <- w(u,v) 
    nodo_min <- NIL 
    min_peso <- +inf 
    for each v in G.V
        if v.key < min_peso 
            min_peso <- v.key 
            nodo_min <- v 
    return nodo_min 

/*Un esercizio sui grafi, dove devi calcolare il peso medio degli archi 
per ogni cammino minimo da un vertice s a tutti gli altri vertici (Dijkstra)*/

Dijkstra(G,w,s)
    Initialize_single_source(G,s)
    creo S vuoto 
    Q <- G.V
    while Q != vuoto 
        u <- Extract_min(Q)
        S <- S + {u}
        for each v in u.Adj
            Relax(u,v,w)
    peso_medio <- 0
    for each v in S 
        if v != s
            peso_medio <- peso_medio + (dist[v]/S)
            peso_medio <- peso_medio / (|S| - 1) //escludo il nodo sorgente
    return peso_medio 


/*Gennaro è ghiotto di babá. Per il compleanno di Gennaro, sua madre si
reca in pasticceria per acquistarne. Sfortunatamente la pasticceria non
vende babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo 
C[t] ed un numero di babá B[t]. Infine, la madre ha deciso di spendere in pasticceria 
al massimo E euro. Scrivere un algoritmo, in pseudocodice, che, ricevendo come input le N
torte a disposizione e E la somma massima a disposizione, restituisca il
numero massimo dei babá che possono essere acquistati. Si assuma che sia possibile 
acquistare parti di torta. (7 punti)*/

//mappo: N = numero di torte, C = costo della torta quindi peso w, B = valore della torta,
// E = capacità dello zaino W

KnapsackFractional(C,B,N,E)
    X <- array inizializzato a 0 di dimensione N 
    value <- 0.0
    k <- 1
    while (k <= N) and (E > 0.0)
        if C[k] <= E 
            X[j] <- 1.0
            value <- value + B[k]
            E <- E - C[k]
        else 
            X[k] <- E/C[k]
            Value <- Value + X[k] * B[k]
            E <- 0.0
        k <- k+1
    return X,value 

/*Dato un grafo non orientato ( G = (V, E) ) e non pesato, un nodo sorgente 
( s \in V ), ed un numero intero ( k \in \mathbb{N} ), scrivere un algoritmo, 
in pseudocodice, che restituisca la lista dei nodi il cui cammino minimo dal 
nodo sorgente ( s ) sia minore di ( k ). (7 punti)*/

BFS(G,s,k)
    for each u in V[G] - {s}
        u.color <- WHITE 
        u.pi <- NIL 
        u.d <- +inf 
    s.color <- GRAY 
    s.d <- 0
    s.pi <- NIL 
    creo Q vuota 
    Enqueue(Q,s)
    while Q != vuota 
        u <- Dequeue(Q)
        for each v in u.Adj
            if v.color = WHITE 
                v.color <- GRAY 
                v.d <- u.d + 1
                v.pi <- u 
                Enqueue(Q,v)
        u.color <- BLACK 
    ListaNodi <- vuota
    for each v in V[G]
        if v != s and v.d < k 
            add v in ListaNodi 
    return ListaNodi

/*Dato un grafo orientato ( G = (V, E) ) e pesato con funzione peso
( w : E \to \mathbb{R} ), scrivere in pseudocodice un algoritmo ricorsivo 
che restituisca la somma dei pesi del più lungo ciclo in ( G ). (7 punti)*/

TrovaIlCicloMassimo(G,w)
    max_ciclo <- -inf 
    for each u in V[G]
        visited <- array inizializzato a FALSE di dimensione V[G]
        max_ciclo <- max(max_ciclo, DFS_VISIT(u,u,0,visited,w))
    return max_ciclo

DFS_VISIT(start,u,somma,visited,w)
    visited[u] <- TRUE 
    maxSomma <- -inf 
    for each v in u.Adj 
        if v = start and somma + w(u,v) > maxSomma 
            maxSomma <- maxSomma + w(u,v) 
        else if not visited[v]
            temp <- DFS_VISIT(start, v, somma + w(u,v),visited,w)
            maxSomma <- max(maxSomma,temp)
    visited[u] <- FALSE 
    return maxSomma

/*Dato un grafo non orientato ( G = (V, E) ), scrivere un algoritmo in pseudocodice
che restituisca l'arco di peso massimo appartenente al MST costruito su ( G ). 
Per semplicità, supporre di porre una condizione su ( G ) in modo tale che il MST sia unico. 
Indicare quale debba essere la condizione. (7 punti)*/

Kruskal(G,w)
    A <- vuoto 
    for each u in G.V
        Makeset(u)
    sort(G.E)
    for each (u,v) in G.E
        if Findset(u) != Findset(v)
            A <- A + {(u,v)}
            Union(u,v)
    peso_max <- -inf 
    arco_max <- NIL 
    for each (u,v) in A 
        if w(u,v) > peso_max 
            peso_max <- w(u,v)
            arco_max <- (u,v)
    return arco_max

/*Per il compleanno di Gennaro, sua madre si reca in edicola per acquistare ( N ) figurine 
di calciatori. L'edicola non vende figurine singole, ma soltanto bustine contenenti figurine. 
Ogni bustina di figurine ( b ) ha un costo ( C[b] ) e contiene un numero di figurine ( F[b] ). 
Sia ( E ) la somma massima, in euro, che la madre ha deciso di spendere in edicola.
Scrivere un algoritmo, in pseudocodice, che, ricevendo come input le ( N ) bustine a disposizione 
e ( E ) la somma massima a disposizione, restituisca il numero massimo di figurine che possono 
essere acquistate. (7 punti)*/

Knapsack0_1(N,F,C,E)
    for i <- 0 to N 
        V[i,0] <- 0 
    for e <- 0 to E 
        V[0,e] <- 0 
    for i <- 1 to N 
        for e <- 1 to E 
            if e < C[i]
                V[i,e] <- V[i-1,e]
            else if V[i-1,e] > V[i-1,e-C[i]] + F[i]
                V[i,e] <- V[i-1,e]
            else 
                V[i,e] <- V[i-1,e-C[i]] + F[i]
    return V

/*Dato un grafo orientato ( G = (V, E) ) aciclico e pesato con funzione peso 
( w : E \to \mathbb{R} ) e sorgente ( s ), scrivere un algoritmo, in pseudocodice, 
che restituisca il nodo di grado massimo dell'albero dei cammini minimi di ( G ). (7 punti)*/

NodoGradoMassimo(G,w,s)
    for each v in G.V
        v.d <- +inf 
        v.pi <- NIL 
    s.d <- 0
    s.pi <- NIL 
    ordien <- TopologicalSort(G)
    for each u in ordine 
        for each v in u.Adj
            if v.d > u.d + w(u,v)
                v.d <- u.d + w(u,v)
                v.pi <- u 
    grado <- array inizilaizzatoa  0 di dimensione G.V //opzionale
    grado_max <- -1
    nodo_max <- NIL 
    for each v in G.V 
        if v.pi != NIL 
            v.pi.grado <- v.pi.grado + 1 
            if  v.pi.grado > grado_max
                grado_max <- vpi.grado
                nodo_max <- v.pi 
    return nodo_max

TopologicalSort(G)
    L <- new stack()
    time <- 0
    for each u in G.V
        u.color <- WHITE 
        u.pi <- NIL 
    for each u in G.V
        if u.color = WHITE 
            DFS_VISIT(u,L)

DFS_VISIT(u,L)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in u.Adj
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,L)
    u.color <- BLACK 
    time <- time + 1
    u.f <- time 
    push(L,u)
    return L

/***Traccia:**

Si consideri un file \( F \) costituito da 100000 simboli \( (!), (), &, =, ? \),
le cui frequenze sono rispettivamente 11%, 6%, 23%, 17%, 14%, 29%. Scrivere un programma,
in pseudocodice, che costruisca l'albero di codifica di Huffman e determini per ogni simbolo
la sua codifica di Huffman. Calcolare l'eventuale risparmio di memoria che si otterrebbe codificando 
il file con la codifica di Huffman invece di una codifica a lunghezza fissa. (7 punti)*/

Huffman(C)
    n <- |C|
    Q <- C 
    for i <- 1 to n-1
        z <- Allocate_Node()
        x <- left[z] <- Extract_min(Q)
        y <- right[z] <- Extract_min(Q)
        z.f <- z.x + z.y
        Insert(Q,z)
    return Extract_Min(Q)

/*Dato un grafo non orientato ( G = (V, E) ), implementare in pseudocodice un 
algoritmo ricorsivo che restituisca TRUE se in ( G ) è presente un ciclo Hamiltoniano 
e FALSE altrimenti. (7 punti)
Suggerimento:
Un percorso Hamiltoniano in un grafo non orientato è un percorso che visita ogni 
vertice esattamente una volta.*/

Hamiltoniano(G)
    for each v in G.V
        visited[v] <- FALSE 
    for each v in G.V
        if HamiltonianoUtil(G,v,v,visted,1)
            return TRUE 
    return FALSE 

HamiltonianoUtil(G,start,u,visited,count)
    visited[u] <- TRUE 
    if count = |G.V|
        if start in u.Adj 
            return TRUE 
        else 
            visited[u] <- FALSE 
            return FALSE 
    for each v in u.Adj
        if not visited[v]
            if HamiltonianoUtil(G,start,v,visited,count + 1)
                return TRUE 
    visited[u] <- FALSE 
    return FALSE

/*Dato un grafo G=(V,E) aciclico orientato e pesato con funzione peso non negativa w: E ->R+ ed 
un nodo s (appartenente) a V, si scriva un algoritmo in pseudocodice che restituisca
i nodi foglia dell’albero dei cammini minimi radicato in s. (7 punti)*/

NodiFogliaCamminiMinimi(G,w,s)
    for each v in G.V
        v.d <- +inf 
        v.pi <- NIL 
    s.d <- 0
    s.pi <- NIL 
    ordine <- TopologicalSort(G)
    for each u in ordine 
        for each v in u.Adj
            if v.d > u.d + w(u,v)
                v.d <- u.d + w(u,v)
                v.pi <- u 
    nodi_foglia <- vuoto 
    for each v in G.V
        if v.pi != NIL and not has v.adj
            add v in nodi_foglia
    return nodi_foglia

TopologicalSort(G)
    L <- new stack 
    time <- 0
    for each v in G.V
        v.color <- WHITE 
        v.pi <- NIL 
    for each u in G.V
        if u.color = WHITE 
            DFS_VISIT(u,L)
    return L 

DFS_VISIT(u,L)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in u.Adj
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,L)
    time <- time + 1
    u.f <- time 
    u.color <- BLACK 
    push(L,u)

/*Dato un grafo G=(V,E), scrivere un algoritmo, in pseudocodice, che restituisca il nuemro
di archi trasversali*/

DFS(G)
    time <- 0 
    tarsversali <- 0
    for each u in G.V
        u.color <- WHITE 
        u.pi <- NIL 
    for each u in G.V
        if u.color = WHITE 
            DFS_VISIT(u,trasversali)
    return trasversali 

DFS_VISIT(u,trasversali)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in u.Adj
        v.pi <- u 
        DFS_VISIT(v,trasversali)
    else if v.color = BLACK and u.d > v.d
        trasversali <- trasversali + 1
    time <- time + 1
    u.d <- time + 1
    u.color <- BLACK 


/*Ciro é ghiotto di babá ed é tifoso del Napoli. Per festeggiare la vittoria del Napoli, 
sua madre si reca in pasticceria per acquistare babá. Sfortunatamente la pasticceria 
non vende babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo C[t] ed 
un numero di babá B[t]. Infine, la madre ha deciso di spendere in pasticceria al massimo E euro. 
Scrivere un algoritmo, in pseudocodice, che, ricevendo come input le N torte a disposizione e E 
la somma massima a disposizione, restituisca il numero massimo dei babá che possono essere 
acquistati. Si assuma che sia possibile acquistare singole fette di torta. (7 punti)*/

FractionaKnapsack(C,B,N,E)
    X <- array inizialzizato a 0 di N elementi
    value <- 0.0 
    k <- 1
    while (k<=N) and (E > 0.0)
        if C[k] <= E 
            X[k] <- 1.0 
            value <- value + B[k]
            E <- E - C[k]
        else 
            X[k] <- E/C[k]
            value <- value + X[k] + B[k]
            E <- 0.0 
        k <- k+1
    return X,value 

/*Ciro é ghiotto di babá. Per il compleanno di Ciro, sua madre si reca
in pasticceria per acquistarne. Sfortunatamente la pasticceria non vende
babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo C[t]
ed un numero di babá B[t]. Infine, la madre ha deciso di spendere in
pasticceria al massimo E euro.
Scrivere un algoritmo che, ricevendo come input le N torte a disposizione
e E la somma massima a disposizione, restituisca il numero massimo dei
babá che possono essere acquistati. Si assuma che i valori del costo
numero di babá siano interi per ogni torta e che non sia possibile acquistare
singole fette di torta. (5 punti)*/

Knapsack0_1(N,C,B,E)
    for i <- 0 to N 
        V[i,0] <- 0
    for e <- 0 to E 
        V[0,e] <- 0
    for i <- 1 to N 
        for e <- 1 to E 
            if e < C[i]
                V[i,e] <- V[i-1,e]
            else if V[i-1,e] > V[i-1,e-C[i]] + B[i]
                V[i,e] <- V[i-1,e]
            else 
                V[i,e] <- V[i-1,e-C[i]] + B[i]
    return V 


/*Dato un grafo connesso non orientato pesato G=(V,E) con pesi w(u,v)
ed un vertice r appartenente a V, si scriva un algoritmo in pseudocodice che 
restituisca il nodo di gardo massimo dell'MST radicato in r*/

MST_PRIM(G,w,r)
    for each u in G.V
        u.key <- +inf 
        u.pi <- NIL 
    r.key <- 0
    Q <- G.V
    while Q != vuoto 
        u <- EXTRACT_MIN(Q)
        for each v in u.Adj
        if v in Q and w(u,v) < v.key 
            v.pi <- u 
            v.key <- w(u,v)
    grado <- array inizializzato a 0 di dimensione G.V
    for each v in G.V
        if v.pi != NIL 
            v.grado <- v.grado + 1
            v.pi.grado <- v.pi,grado + 1
    max_grado <- -inf 
    nodo_max <- NIL 
    for each v in G.V
        if v.grado > max_grado 
            max_grado <- v.grado 
            nodo_max <- v 
    return nodo_max


/*Dato un grafo orientato ( G = (V, E) ), scrivere un algoritmo, in pseudocodice, 
che restituisca la differenza tra il numero dei cicli con numero di vertici maggiore di 
uno. (7 punti)*/

DFS(G)
    time <- 0
    cicli <- 0
    cappi <- 0
    for each u in G.V
        u.color <- WHITE 
        u.pi <- NIL 
    for each u in G.V 
        if u.color = WHITE 
            DFS_VISIT(u,cicli,cappi)
    differenza <- cicli - cappi 
    return differenza 

DFS_VISIT(u,cicli,cappi)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in G.V
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,cicli,cappi)
        else if v.color = GRAY and u.d = v.d 
            cappi <- cappi + 1
        else if v.color = GRAY 
            cicli <- cicli + 1
    time <- time + 1
    u.f <- time 
    u.color <- BLACK 


/*Dato un grafo orientato ( G = (V, E) ), scrivere un algoritmo, in pseudocodice, 
che restituisca la differenza tra il numero dei cicli con numero di vertici maggiore 
di uno. (7 punti)*/

DFS(G)
    time <- 0
    cicli <- 0 
    cappi <- 0
    for each u in G.V
        u.color <- WHITE 
        u.pi <- NIL 
    for each u in G.V
        if u.color = WHITE 
            DFS_VISIT(u,cicli,cappi)
    differenza <- cicli - cappi
    return differenza 

DFS_VISIT(u,cicli,cappi)
    u.color <- GRAY 
    time <- time + 1
    u.d <- time 
    for each v in u.Adj
        if v.color = WHITE 
            v.pi <- u 
            DFS_VISIT(v,cicli,cappi)
        else if v.color = GRAY and u.d = v.d 
            cappi <- cappi + 1
        else if v.color = GRAY 
            cicli <- cicli + 1
    time <- time + 1
    u.f <- time 
    u.color <- BLACK 


/*Dato un grafo non orientato G = (V,E) scrivere un algoritmo in pseucdocodice che restituisca l' arco 
di peso massimo appartenente al MST costruito su G. Per semplicità suppore di porre una condizione su G in
modo tale che MST sia unico. Indicare quale debba essere la condizione
(7 punti)*/

/*Il MST è unico se tutti i pesi degli archi sono distinti (cioè, non ci sono due archi con lo stesso peso).*/

Mst_Kruskal(G,w)
    A <- vuoto 
    for each u in G.V
        Makeset(u)
    sort(G.E) //in modo crescente di peso 
    for each (u,v) in G.E 
        if Findset(u) != Findset(v)
            A <- A + {(u,v)}
            Union(u,v)
    peso_max <- -inf 
    arco_max <- NIL 
    for each (u,v) in A 
        if w(u,v) > peso_max 
            peso_max <- w(u,v)
            arco_max <- (u,v)
    return arco_max


/*Per il compleanno di Gennaro, sua madre si reca in edicola per acquistare
figurine di calciatori. L'edicola non vende figurine singole, ma soltanto N
bustine contenenti figurine. Ogni bustina di figurina b ha un costo C[b] e
contiene un numero di figurine F[b] e sia E la somma massima, in euro,
che la madre ha deciso di spendere in edicola.
Scrivere un algoritmo, in pseudocodice, che, ricevendo come input le N
bustine a disposizione e E la somma massima a disposizione, restituisca il
numero massimo di figurine che possono essere acquistate. (7 punti)*/

Knapsacl_01(N,F,C,E)
    for i <- 0 to N 
        V[i,0] <- 0
    for j <- 0 to E 
        V[0,j] <- 0
    
    for i <- 1 to N 
        for e <- 1 to E 
            if e < C[i]
                V[i,e] <- V[i-1,e]
            else if V[i-1,e] > V[i-1,e-C[i]] + F[i]
                V[i,e] <- V[i-1,e]
            else 
                V[i,e] <- V[i-1,e-C[i]] + F[i]
    return V 

/*Dato un grafo orientato G = (V, E) aciclico e pesato con funzione peso
w : E -> R e sorgente s, scrivere un algoritmo, in pseudocodice, che
restituisca il nodo di grado massimo dell'albero dei cammini minimi di G.
(7 punti)*/

NodoGradoMassimo(G,w,s)
    for each v in G.V
        v.d <- +inf 
        v.pi <- NIL 
    s.d <- 0
    s.pi <- NIL 
    ordine <- TopologicalSort(G)
    for each u in ordine 
        for each v in u.Adj
            if v.d > u.d + w(u,v)
                v.d <- u.d + w(u,v)
                v.pi <- u 
    grado <- array inizializzato a 0 di dimensione G.V
    grado_max <- -inf
    nodo_max <- NIL
    for each v in G.V
        if v.pi != NIL 
            v.pi.grado <- v.pi.grado + 1
    for each v in G.V
        if v.grado > grado_max
                grado_max <- v.grado
                nodo_max <- v
    return nodo_max  


/*Dato un grafo non orientato G = (V, E) e non pesato, un nodo sorgente
s € V, ed un numero intero k E N scrivere un algoritmo, in pseudocodice,
che restituisca la lista dei nodi, il cui cammino minimo dal nodo sorgente
s sia minore di k. (7 punti)*/

BFS(G,s,k)
    for each v in G.V - {s}
        v.color <- WHITE 
        v.pi <- NIL 
        v.d <- +inf
    s.color <- GRAY 
    s.d <- 0
    s.pi <- NIL 
    creo Q vuoto 
    Enqueue(Q,s)
    while Q != vuoto 
        u <- Dequeue(Q)
        for each v in u.Adj
            if v.color = WHITE 
                v.color <- GRAY 
                v.d <- u.d + 1
                v.pi <- u 
                Enqueue(Q,v)
        u.color <- BLACK 
    creo ListaNodi vuota 
    for each v in G.V 
        if v != s and v.d > k 
            add v in ListaNodi 
    return ListaNodi

/*Gennaro è ghiotto di babá. Per il compleanno di Gennaro, sua madre si
reca in pasticceria per acquistarne. Sfortunatamente la pasticceria non
vende babá singoli, ma soltanto N torte di babá. Ogni torta t ha un costo
C[t] ed un numero di babá B[t]. Infine, la madre ha deciso di spendere in
pasticceria al massimo E euro.
Serivere un algoritmo, in pseudocodice, che, ricevendo come input le N
torte a disposizione e E la somma massima a disposizione, restituisca il
numero massimo dei babá che possono essere acquistati. Si assuma che
sia possibile acquistare parti di torta. (7 punti)
*/

FractionalKnapsack(B,C,N,E)
    X <- array inizializzato a 0 di N 
    value <- 0.0 
    k <- 1 
    while (k<=N) and (E > 0.0)
        if C[k] <= E 
            X[k] <- 1.0
            value <- value + B[k]
            E <- E - C[k]
        else 
            X[k] <- E/C[k]
            value <- value + X[k] * B[k]
            E <- 0.0
        k <- k + 1
    return X,value 
    

/*5. Dato un grafo orientato G = (V, E) e pesato con funzione peso w : E -> R
scrivere in pseudocodice un algoritmo ricorsivo che restituisca la somma
dei pesi del più lungo ciclo in G. (7 punti)*/

TrovaCicloMassimo(G,w)
    max_ciclo <- -inf 
    for each v in G.V
        visited <- array inizializzato a 0 di dimensione G.v
        max_ciclo <- max(max_ciclo,DFS_VISIT(v,v,0,visited,w))
    return max_ciclo 

DFS_VISIT(start,u,somma,visited,w)
    visited[u] <- TRUE 
    maxSomma <- -inf 
    for each v in u.Adj
        if v = start and somma + w(u,v) > maxSomma 
            maxSomma <- somma + w(u,v)
        else if not visited[v]
            temp <- DFS_VISIT(start,v,somma + w(u,v),visited,w)
            maxSomma <- max(maxSomma,temp)
    visited[u] <- FALSE 
    return maxSomma 

/*Dato un grafo orientato G = (V, E) si scriva in pseudocodice un algoritmo
che calcoli le componenti fortemente connesse del grafo. Si descriva lo
pseudocodice di ogni funzione richiamata. (7 punti)*/



/*Dato un grafo connesso non orientato pesato G = (V, E) con pesi w(u, v)
ed un vertice r E V, si scriva un algoritmo in pseudocodice che restituisca
il nodo di grado massimo del MST radicato in r. (7 punti)*/

Mst_Prim(G,w,r)
    for each u in G.V
        u.key <- +inf 
        u.pi <- NIL 
    r.key <- 0
    Q <- G.V
    while Q != vuoto 
        u <- Extract_min(Q)
        for each v in u.Adj
            if v in Q and w(u,v) < v.key 
                v.pi <- u
                v.key <- w(u,v)
    grado <- array inizializzato a 0 di G.V elementi
    for each v in G.V 
        if v.pi != NIL +
            grado[v] <- grado[v] + 1
            grado[v.pi] <- grado[v.pi] + 1
    grado_max <- -inf 
    nodo_max <- NIL 
    for each v in G.V
        if grado[v] > gardo_max 
            grado_max <- grado[v]
            nodo_max <- v 
    return nodo_max
