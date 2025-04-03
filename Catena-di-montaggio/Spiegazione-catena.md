**Algoritmo FASTEST per il problema della catena di montaggio**

### **Descrizione**
L'algoritmo FASTEST risolve il problema della catena di montaggio determinando il percorso ottimale per minimizzare il tempo totale di produzione. Il problema considera due linee di assemblaggio, ciascuna con `n` stazioni, e il tempo di transizione tra le due linee.

### **Input**
- `a1, a2`: tempi di lavorazione per ciascuna stazione sulle due linee.
- `t1, t2`: tempi di trasferimento tra le linee.
- `e1, e2`: tempi di ingresso nelle due linee.
- `x1, x2`: tempi di uscita dalle due linee.
- `n`: numero di stazioni.

### **Output**
- `f_opt`: tempo minimo necessario per completare il processo.
- `l_opt`: ultima linea utilizzata nel percorso ottimale.

### **Passaggi dell'algoritmo**
1. **Inizializzazione**  
   - La prima stazione di ogni linea inizia con il tempo `e1 + a1,1` e `e2 + a2,1`.

2. **Iterazione sulle stazioni**  
   - Per ogni stazione `j` da `2` a `n`, decidiamo se rimanere sulla stessa linea o spostarci.
   - Se restare è più veloce, aggiorniamo il tempo senza cambiare linea:
     ```
     f1[j] = f1[j-1] + a1,j
     ```
   - Se cambiare è più veloce, paghiamo il costo di transizione:
     ```
     f1[j] = f2[j-1] + t2[j-1] + a1,j
     ```
   - Lo stesso procedimento viene applicato per la linea `2`.

3. **Determinazione del tempo di uscita**  
   - Dopo aver completato l'ultima stazione `n`, calcoliamo il tempo minimo considerando i tempi di uscita `x1` e `x2`:
     ```
     if f1[n] + x1 <= f2[n] + x2:
         f_opt = f1[n] + x1
         l_opt = 1
     else:
         f_opt = f2[n] + x2
         l_opt = 2
     ```

### **Complessità dell'algoritmo**
Poiché visitiamo ogni stazione **una sola volta**, l'algoritmo ha una complessità **O(n)**, rendendolo molto efficiente rispetto a una ricerca esaustiva di complessità **O(2^n)**.

### **Esempio di utilizzo**
Se i valori sono:
```
a1 = [4, 5, 3, 2]
a2 = [2, 10, 1, 4]
t1 = [7, 4, 5]
t2 = [9, 2, 8]
e1 = 10
e2 = 12
x1 = 18
x2 = 7
```
L'algoritmo calcola il tempo minimo necessario e il percorso ottimale da seguire lungo le stazioni della catena di montaggio.

