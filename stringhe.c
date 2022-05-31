#include <stdio.h>
#include <string.h>

#define ZERO '0'
#define NULL_CHAR '\0'


/*
  funzione che prende come parametro un char e restituisce 1 se Ã¨ un carattere numerico, 0 altrimenti.
*/
int isNumero(char c) {
  return (c >= ZERO && c <= '9');
}

/*
  funzione che prende come parametro un intero e restituisce il suo valore assoluto.
*/
int valoreAssoluto(int x) {
  return x >= 0 ? x : -1 * x; /* operatore ternario */
}

/* funzione che converte in intero il suo parametro char */
int charToInt(char c) {
  return c - ZERO;
}

/* funzione che converte in char il suo parametro intero */
char intToChar(int x) {
  return x + ZERO;
}

/*
  funzione che prende come parametro un riferimento ad una stringa (sequenza di caratteri)
  e la modifica a tal modo da rimpiazzare ogni sequenza (massimale) di esattamente due caratteri
  numerici adiacenti nella stringa con la differenza fra i numeri corrispondenti ai caratteri.
*/
void differenzaDueNumerici(char stringa[]) {
/*
  Input: una stringa (sequenza di caratteri) chiamata stringa.
  Pre-condizione: stringa deve contere solo caratteri.
  Output: nessun output perchÃ¨ la funzione ha tipo di ritorno void.
  Post-condizione: nessun output perchÃ¨ la funzione ha tipo di ritorno void.
*/
   int
      i = 0, /* contatore per scandire la stringa carattere per carattere */
      j = 0, /* contatore di appoggio per il contatore i */
      differenza = 0; /* differenza fra i numeri corrispondenti ai caratteri numerici adiacenti */
   while(stringa[i] != '\0') { /* guardo carattere per carattere fino all'ultimo */
     if(
        ((i == 0) || !isNumero(stringa[i - 1])) && /* carattere precedente all'i-esimo non numerico oppure non esistente (prima posizione) */
        isNumero(stringa[i]) && /* i-esimo carattere numerico */
        isNumero(stringa[i + 1]) && /* successivo carattere all'i-esimo carattere numerico */
        !isNumero(stringa[i + 2]) /* successivo carattere del successivo carattere all'i-esimo carattere numerico */
     ) {
		/* calcolo la differenza in valore assoluto fra i numeri corrispondenti ai caratteri numerici adiacenti e la salvo nella variabile differenza  */
        differenza = charToInt(stringa[i]) - charToInt(stringa[i + 1]);
        if(differenza >= 0) {
        	/* elimino l'iesimo carattere numerico */
        	for(j = i; stringa[j] != '\0'; j++)
            	stringa[j] = stringa[j + 1];
          	/* sostituisco  il successivo carattere numerico all'iesimo carattere numerico con la rispettiva differenza tra i 2 */
        	stringa[i] = intToChar(differenza);		
		} else {
			stringa[i] = '-';
			stringa[i + 1] = intToChar(valoreAssoluto(differenza));
		}
     } else /* altrimenti vado avanti al prossimo carattere */
        i++;
   }
}

/*
  funzione che prende come parametro un riferimento ad una stringa (sequenza di caratteri)
  e la modifica a tal modo da rimpiazzare ogni sequenza (massimale) di esattamente due caratteri
  numerici adiacenti nella stringa con la differenza fra i numeri corrispondenti ai caratteri.
  E' la versione con puntatori della funzione differenzaDueNumerici scritta sopra.
*/
void pointerDifferenzaDueNumerici(char* stringa) {
/*
  Input: un riferimento ad una stringa (sequenza di caratteri) chiamata stringa.
  Pre-condizione: stringa deve contere solo caratteri.
  Output: nessun output perchÃ¨ la funzione ha tipo di ritorno void.
  Post-condizione: nessun output perchÃ¨ la funzione ha tipo di ritorno void.
*/
   int
      i = 0, 
      j = 0,
      differenza = 0; /* differenza fra i numeri corrispondenti ai caratteri numerici adiacenti */
   while(*(stringa + i) != NULL_CHAR) { /* guardo carattere per carattere fino all'ultimo */
	 if(
        ((i == 0) || (!isNumero(*(stringa + i - 1)))) && /* carattere precedente all'i-esimo non numerico oppure non esistente (prima posizione) */
        isNumero(*(stringa + i)) && /* i-esimo carattere numerico */
        isNumero(*(stringa + i + 1)) && /* successivo carattere all'i-esimo carattere numerico */
        !isNumero(*(stringa + i + 2)) /* successivo carattere del successivo carattere all'i-esimo carattere numerico */
     ) {
		/* calcolo la differenza in valore assoluto fra i numeri corrispondenti ai caratteri numerici adiacenti e la salvo nella variabile differenza  */
		differenza = charToInt(*(stringa + i)) - charToInt(*(stringa + i + 1));
        if(differenza >= 0) {
        	/* elimino l'iesimo carattere numerico */
        	for(j = i; *(stringa + j) != NULL_CHAR; j++)
            	*(stringa + j) = *(stringa + j + 1);
          	/* sostituisco  il successivo carattere numerico all'iesimo carattere numerico con la rispettiva differenza tra i 2 */
        	*(stringa + i) = intToChar(differenza);		
		} else {
			*(stringa + i) = '-';
			*(stringa + i + 1) = intToChar(valoreAssoluto(differenza));
		}
     } else   /* altrimenti vado avanti al prossimo carattere */
        	i++;
   }
}

/* test della funzione void differenzaDueNumerici(char* stringa) con 11 classi di equivalenza ==> 11 test */
void testDifferenzaDueNumerici() {

   /* stringa vuota */
   char stringa1[] = "";
   differenzaDueNumerici(stringa1);
   printf("\nTest differenzaNumerici(\"\") 1: Atteso: \"\", Calcolato: \"%s\" \n", stringa1);

   /* stringa con una sola sequenza di esattamente due caratteri numerici adiacenti */
   char stringa2[] = "12";
   differenzaDueNumerici(stringa2);
   printf("\nTest differenzaNumerici(\"12\") 2: Atteso: \"-1\", Calcolato: \"%s\" \n", stringa2);

   /* stringa senza sequenze di esattamente due numerici adiacenti */
   char stringa3[] = "ab";
   differenzaDueNumerici(stringa3);
   printf("\nTest differenzaNumerici(\"ab\") 3: Atteso: \"ab\", Calcolato: \"%s\" \n", stringa3);

   /* stringa con una sequenza di esattamente due caratteri numerici adiacenti all'inizio */
   char stringa4[] = "11ab";
   differenzaDueNumerici(stringa4);
   printf("\nTest differenzaNumerici(\"11ab\") 4: Atteso: \"0ab\", Calcolato: \"%s\" \n", stringa4);

   /* stringa con una sequenza di esattamente due caratteri numerici adiacenti alla fine */
   char stringa5[] = "cd21";
   differenzaDueNumerici(stringa5);
   printf("\nTest differenzaNumerici(\"cd21\") 5: Atteso: \"cd1\", Calcolato: \"%s\" \n", stringa5);

   /* stringa con non contiene sequenze di esattamente due caratteri numerici adiacenti all'inizio */
   char stringa6[] = "cdowdjuw00";
   differenzaDueNumerici(stringa6);
   printf("\nTest differenzaNumerici(\"cdowdjuw00\") 6: Atteso: \"cdowdjuw0\", Calcolato: \"%s\" \n", stringa6);

   /* stringa con non contiene sequenze di esattamente due caratteri numerici adiacenti alla fine */
   char stringa7[] = "rr00dedefef";
   differenzaDueNumerici(stringa7);
   printf("\nTest differenzaNumerici(\"rr00dedefef\") 7: Atteso: \"rr0dedefef\", Calcolato: \"%s\" \n", stringa7);

   /* stringa con tante sequenze di esattamente due caratteri numerici adiacenti */
   char stringa8[] = "sa65ss44ddd00grg9977efe88ef23";
   differenzaDueNumerici(stringa8);
   printf("\nTest differenzaNumerici(\"sa65ss44ddd00grg9977efe88ef23\") 8: Atteso: \"sa1ss0ddd0grg9977efe0ef-1\", Calcolato: \"%s\" \n", stringa8);

   /* stringa con poche sequenze di esattamente due caratteri numerici adiacenti (l'unica si trova in una posizione intermededia) */
   char stringa9[] = "sass444ddd00grg77efe88881ef2328738dd";
   differenzaDueNumerici(stringa9);
   printf("\nTest differenzaNumerici(\"sass444ddd00grg77efe88881ef2328738dd\") 9: Atteso: \"sass444ddd00grg0efe88881ef2328738dd\", Calcolato: \"%s\" \n", stringa9);

   /* stringa con soli e multipli caratteri numerici adiacenti */
   char stringa10[] = "0123456789";
   differenzaDueNumerici(stringa10);
   printf("\nTest differenzaNumerici(\"0123456789\") 10: Atteso: \"0123456789\", Calcolato: \"%s\" \n", stringa10);

   /* stringa normale (uso la stringa data come esempio nel compito) */
   char stringa11[] = "xx13xxx74xx784xx00xx6xx";
   differenzaDueNumerici(stringa11);
   printf("\nTest differenzaNumerici(\"xx13xxx74xx784xx00xx6xx\") 11: Atteso: \"xx-2xxx3xx784xx0xx6xx\", Calcolato: \"%s\" \n", stringa11);
   																				
   /* N.B. = qualche test in piÃ¹ non fa mica male */
}



/* funzione principale */
int main(void) {
  /* lunghezza massima (numero di caratteri) della stringa in ingresso */
  const int lunghezza_max_stringa = 50;
  char stringa[lunghezza_max_stringa];  /* per memorizzare la stringa */
  printf("\nCiao Utente sono un programma che data una stringa la modifica a tal modo da rimpiazzare ogni sequenza (massimale) di esattamente due caratteri numerici adiacenti nella stringa con la differenza fra i numeri corrispondenti ai caratteri.\n");
  /* prendo in ingresso da tastiera dell'Utente la stringa (sequenza di caratteri) */
  printf("\nOra inserisci una bella stringa: ");
  fgets(stringa, lunghezza_max_stringa, stdin);
  int lunghezza_stringa = strlen(stringa); /* calcolo la lunghezza della stringa */
  /* elimino l'ultimo carattere ('\n') della stringa presa in ingresso da tastiera dell'Utente tramite fgets */
  stringa[lunghezza_stringa - 1] = '\0';
  /* printo la stringa presa in ingresso da tastiera dell'Utente */
  printf("\nStringa input di %d caratteri: \"%s\" \n", lunghezza_stringa - 1, stringa);
   /* modifico la stringa presa in ingresso da tastiera dell'Utente tramite la funzione void differenzaDueNumerici(char* stringa) */
  pointerDifferenzaDueNumerici(stringa);
  /* OUTPUT finale della stringa modificata */
  printf("\nStringa output di %d caratteri: \"%s\" \n", strlen(stringa), stringa);
  testDifferenzaDueNumerici(); /* avvio il test della funzione void differenzaDueNumerici(char* stringa) tramite la funzione void testDifferenzaDueNumerici() */
  printf("\n \nFine esecuzione programma.\n");
  return 0;
}
