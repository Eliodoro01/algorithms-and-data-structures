# Problemi NP-completi e la classe P

## Definizione di problema NP-completo

Un problema è detto **NP-completo** se soddisfa le seguenti condizioni:

1. Appartiene alla classe **NP**, ovvero la sua soluzione può essere **verificata** in tempo polinomiale da una macchina deterministica.
2. **Ogni altro problema in NP è riducibile** ad esso in tempo polinomiale.

In altre parole, un problema NP-completo è **uno dei problemi più difficili della classe NP**: se riusciamo a risolvere un problema NP-completo in tempo polinomiale, possiamo risolvere **tutti** i problemi in NP nello stesso modo.

---

## Un problema NP-completo può appartenere alla classe P?

**Solo se \( P = NP \).**

Spiegazione:

- Se esistesse anche un solo algoritmo polinomiale per risolvere un problema NP-completo, allora, per definizione di NP-completezza, esisterebbe un algoritmo polinomiale per **tutti** i problemi in NP.
- Quindi \( P = NP \), il che è uno dei problemi aperti più importanti dell'informatica teorica.

Attualmente:

- **Non conosciamo** alcun algoritmo polinomiale per un problema NP-completo.
- **Non sappiamo** se \( P = NP \) o \( P \neq NP \).
- Ma **se un problema NP-completo fosse in P**, allora tutti i problemi in NP sarebbero in P.

---

## Conclusione

> Un problema NP-completo *può* appartenere alla classe P, ma ciò implicherebbe che **P = NP**, cosa ancora non dimostrata né confutata.
