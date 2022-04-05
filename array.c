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
   x è divisvile per y, 0 altrimenti.
*/
int isDivisibilePer(int x, int y) {
/*
  Input: 2 interi x e y.
  Pre-condizione: x deve essere un intero e y un intero != 0.
  Output: un valore booleano.
  Post-condizione: viene ritornato true se 
  				   x è divisibile per y (quindi x è un multiplo di y), false altrimenti.
*/
	return (x % y) == 0;
}

/*
   funzione che prende come parametro un array di interi e la sua lunghezza e ritorna 1 se
   per ogni tripla della sequenza in ingresso esiste almeno un elemento della tripla che
   divide l'altro 0 altrimenti.
*/
int almenoUnoMultiplo(int interi[], int num_interi) {
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
      verifica = 0; /* la condizione data non Ã¨ verificata */
   }
   /* se la sequenza ha meno di 3 valori (interi) allora possiede tutte triple che soddisfano la condizione data */
   return verifica;
}

/*
   funzione che prende come parametro un array di interi e la sua lunghezza e ritorna 1 se
   per ogni tripla della sequenza in ingresso esiste almeno un elemento della tripla che
   divide l'altro 0 altrimenti. (versione ricorsiva della funzione almenoUnoMultiplo scritta in alto).
*/
int recursiveAlmenoUnoMultiplo(int interi[], int num_interi) {
/*
  Input: un riferimento ad un array di interi chiamato interi e la sua lunghezza num_interi (anch'essa un intero).
  Pre-condizione: interi deve contenere solo interi e la sua lunghezza num_interi deve essere >= 0.
  Output: un valore intero chiamato verifica.
  Post-condizione: verifica vale 1 se per ogni tripla della sequenza in ingresso
                   esiste almeno un elemento della tripla che divide l'altro, 0 altrimenti.
  TIPO DI PROBLEMA: verifica universale con ricorsione.
*/
   int verifica = 1; /* variabile di verifica universale */
   if(num_interi < 3) 
		verifica = 1; /* se la sequenza ha meno di 3 valori (interi) allora possiede tutte triple che soddisfano la condizione data */
   else {
   		verifica =  ( /* 3 fattoriale = 3! = 6 possibili combinazioni */
			isDivisibilePer(interi[num_interi - 1], interi[num_interi - 2]) ||
	        isDivisibilePer(interi[num_interi - 1], interi[num_interi - 3]) ||
	        isDivisibilePer(interi[num_interi - 2], interi[num_interi - 1]) ||
	        isDivisibilePer(interi[num_interi - 2], interi[num_interi - 3]) ||
	        isDivisibilePer(interi[num_interi - 3], interi[num_interi - 1]) ||
	        isDivisibilePer(interi[num_interi - 3], interi[num_interi - 2])
		) && (recursiveAlmenoUnoMultiplo(interi, num_interi - 1));
   }
   return verifica;
}

/*
   funzione che prende come parametro un array di interi e la sua lunghezza e ritorna 1 se
   per ogni tripla della sequenza in ingresso esiste almeno un elemento della tripla che
   divide l'altro 0 altrimenti. (versione con puntatori della funzione almenoUnoMultiplo scritta in alto).
*/
int pointerAlmenoUnoMultiplo(int* interi, int* num_interi) { 
/*
  Input: un riferimento ad un array di interi chiamato interi e la sua lunghezza num_interi passata per riferimento.
  Pre-condizione: interi deve contenere solo interi e la sua lunghezza num_interi deve essere >= 0.
  Output: un valore intero chiamato verifica.
  Post-condizione: verifica vale 1 se per ogni tripla della sequenza in ingresso
                   esiste almeno un elemento della tripla che divide l'altro, 0 altrimenti.
  TIPO DI PROBLEMA: verifica universale con puntatori.
*/
   int 
   	verifica = 1, /* variabile di verifica universale */
   	i = 0;
   for(; (i < *num_interi - 2) && verifica; i++, interi++) {
      if(!( /* 3 fattoriale = 3! = 6 possibili combinazioni */
        isDivisibilePer(*interi, *(interi + 1)) ||
        isDivisibilePer(*interi, *(interi + 2)) ||
        isDivisibilePer(*(interi + 1), *(interi)) ||
        isDivisibilePer(*(interi + 1), *(interi + 2)) ||
        isDivisibilePer(*(interi + 2), *interi) ||
        isDivisibilePer(*(interi + 2), *(interi + 1))
      ))
      verifica = 0; /* la condizione data non Ã¨ verificata */
   }
   /* se la sequenza ha meno di 3 valori (interi) allora possiede tutte triple che soddisfano la condizione data */
   return verifica;
}

/* funzione pricipale */
int main(void) {
  int
    num_interi = 0, /* lunghezza sequenza di interi in ingresso */
    i = 0; /* contatore i per scandire la sequenza di interi in ingresso */
  printf("\nSalve Utente, sono un programma che legge una sequenza di interi e dice se per ogni\ntripla della sequenza in ingresso esiste almeno un elemento della tripla che divide l'altro.\n");
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
  printf("\nSequenza di %d interi in ingresso:", num_interi);
  for(i = 0; i < num_interi; i++) 
    printf(" %d ", interi[i]);
  /* OUTPUT finale */
  printf("\n \nPer ogni tripla della sequenza in ingresso esiste almeno un elemento della tripla che divide l'altro (0 = no, 1 = si): %d.\n", almenoUnoMultiplo(interi, num_interi));
  printf("\n \nFine esecuzione programma.\n");
  return 0;
}         
