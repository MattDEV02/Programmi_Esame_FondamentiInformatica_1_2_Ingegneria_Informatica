/*
  SPECIFICA:

  Input: una sequenza di interi x1, ..., xn e la sua lunghezza n (anch'essa un intero).
  Pre-condizione: la sequenza di interi x1, ..., xn deve contenere solo interi e
                  la sua lunghezza n deve essere >= 0.
  Output: un valore booleano chiamato verifica.
  Post-condizione: verifica vale true se per ogni tripla della sequenza in ingresso
                   esiste almeno un elemento della tripla che divide l'altro, false altrimenti.
  TIPO DI PROBLEMA: verifica universale.
*/


#include <stdio.h>


/*
   funzione che prende come parametro 2 interi e ritorna 1 se 
   x � divisvile per y, 0 altrimenti.
*/
int isDivisibilePer(int x, int y) {
/*
  Input: 2 interi x e y.
  Pre-condizione: x deve essere un intero e y un intero != 0.
  Output: un valore booleano.
  Post-condizione: viene ritornato true se 
  				   x � divisibile per y (quindi x � un multiplo di y), false altrimenti.
*/
	return (x % y) == 0;
}

/*
   funzione che prende come parametro un array di interi e la sua lunghezza e ritorna 1 se
   per ogni tripla della sequenza in ingresso esiste almeno un elemento della tripla che
   divide l'altro 0 altrimenti.
*/
int almenoUnoMultiplo(int* interi, int num_interi) {
/*
  Input: un riferimento ad un array di interi chiamato interi e la sua lunghezza num_interi (anch'essa un intero).
  Pre-condizione: interi deve contenere solo interi e la sua lunghezza num_interi deve essere >= 0.
  Output: un valore intero chiamato verifica.
  Post-condizione: verifica vale 1 se per ogni tripla della sequenza in ingresso
                   esiste almeno un elemento della tripla che divide l'altro, 0 altrimenti.
  TIPO DI PROBLEMA: verifica universale.
*/
   int
     i = 0, /* contatore per scandire la sequenza di interi valore per valore */
     verifica = 1; /* variabile di verifica universale */
   for(; (i < num_interi - 2) && verifica; i++) {
      if(!( /* 3 fattoriale = 3! = 6 possibili combinazioni */
        isDivisibilePer(interi[i], interi[i + 1]) ||
        isDivisibilePer(interi[i], interi[i + 2]) ||
        isDivisibilePer(interi[i + 1], interi[i]) ||
        isDivisibilePer(interi[i + 1], interi[i + 2]) ||
        isDivisibilePer(interi[i + 2], interi[i]) ||
        isDivisibilePer(interi[i + 2], interi[i + 1])
      ))
      verifica = 0; /* la condizione data non è verificata */
   }
   /* se la sequenza ha meno di 3 valore (interi) allora non possiede triple e la condizione data non è verificata */
   return verifica && num_interi >= 3;
}

/* funzione pricipale */
int main(void) {
  int
    num_interi = 0,
    i = 0;
  printf("\nSalve Utente, sono un programma che legge una sequenza di interi e dice se per ogni tripla della sequenza in ingresso esiste almeno un elemento della tripla che divide l'altro\n");
  /* prendo in ingresso da tastiera dell'Utente la lunghezza della sequenza di interi in ingresso */
  printf("\nOra inserisci il numero di interi della sequenza di interi in ingresso: ");
  scanf("%d", &num_interi);
  int interi[num_interi]; /* per memorizzare l'array di interi */
  for(; i < num_interi; i++) {
    /* prendo in ingresso da tastiera dell'Utente ogni valore intero (uno a uno)W della sequenza di interi */
    printf("\nInserisci l'elemento in posizione %d della sequenza di interi in ingresso: ", i);
    scanf("%d", &interi[i]);
  }
  /* stampo la sequenza di interi presa in ingresso da tastiera dell'Utente valore per valore */
  printf("\nSequenza di interi in ingresso:");
  for(i = 0; i < num_interi; i++) 
    printf(" %d ", interi[i]);
  /* OUTPUT finale */
  printf("\n \nPer ogni tripla della sequenza in ingresso esiste almeno un elemento della tripla che divide l'altro (0 = no, 1 = si): %d.\n", almenoUnoMultiplo(interi, num_interi));
  printf("\n \nFine esecuzione programma.\n");
  return 0;
}         
