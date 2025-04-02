# Definizione di Macchina di Turing e Insieme degli Stati Accettanti

La **Macchina di Turing** è un automa a stati finiti con un **nastro di lunghezza infinita**, su cui si può **leggere e sovrascrivere dati**. Essa viene descritta dalla **sestupla**:  

M = (Q, Sigma, Gamma, delta, q_0, B, F) 

### Componenti della Macchina di Turing:
- **Q** : L'insieme finito degli stati del controllo.
- **Σ** : L'insieme finito dei simboli in input.
- **Γ** : L'insieme completo dei simboli del nastro.
- **δ** : La funzione di transizione.
- **q₀** : Lo stato iniziale del controllo.
- **B** : Il simbolo dello *blank*.
- **F** : L'insieme degli stati finali o accettanti, con **F ⊆ Q**.

### Stati Accettanti
Gli **stati accettanti** sono quegli stati in cui la macchina, dopo aver eseguito la computazione su un input, **raggiunge uno stato che indica che l'input è accettato**.  
