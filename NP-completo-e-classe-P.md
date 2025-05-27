# Problemi NP-completi e la classe P

## Cos'è un problema NP-completo?

Un problema è **NP-completo** se soddisfa due condizioni:

1. **Appartiene a NP**: cioè le sue soluzioni *possono essere verificate* in tempo polinomiale.
2. **È NP-hard**: cioè **ogni problema in NP** può essere **ridotto** a esso in tempo polinomiale.

---

## Un problema NP-completo può appartenere alla classe P?

**Sì, può.**  
**Ma se anche solo uno dei problemi NP-completi è in P, allora P = NP.**

---

## Dimostrazione logica

Assumiamo che esista un problema NP-completo che **è anche in P**. Chiamiamolo \( A \).

**Cosa implica?**

1. Poiché \( A \) è NP-completo, *ogni problema* \( B \in \text{NP} \) può essere **ridotto** ad \( A \) in tempo polinomiale.
2. Poiché \( A \in \text{P} \), può essere **risolto** in tempo polinomiale.
3. Quindi, ogni problema \( B \in \text{NP} \) può essere **risolto** in tempo polinomiale (tramite la riduzione a \( A \)).

**Conclusione**: se un problema NP-completo appartiene a P, allora **tutti i problemi NP** possono essere risolti in tempo polinomiale → **P = NP**.

---

## Stato attuale della questione

Ad oggi (2025), **nessuno ha dimostrato** né che **P = NP**, né che **P ≠ NP**.  
È uno dei **grandi problemi aperti** della matematica e dell'informatica teorica.

---

## Esempio famoso: SAT

Il problema **SAT (soddisfacibilità booleana)** è stato il **primo problema** dimostrato NP-completo (Teorema di Cook-Levin).

- Se un giorno si trovasse un **algoritmo polinomiale** per risolvere SAT, ciò implicherebbe **P = NP**.
