#include <stdio.h>
#include <stdlib.h>


int quantiNumeri() {
   int conta = 0;
   FILE * fp = fopen("interi.txt", "r");
   if (fp == NULL)
      printf("\nFile interi.txt NON aperto (r).\n");
   else {
      int n = 0;
      while (fscanf(fp, "%d", & n) != EOF)
         conta++;
      fclose(fp);
   }
   return conta;
}

int leggiNumeri(int * sequenza) {
   int controllo = -1;
   FILE * fp = fopen("interi.txt", "r");
   if (fp == NULL)
      printf("\nFile interi.txt NON aperto (r).\n");
   else {
      int n = 0, i;
      fscanf(fp, "%d", & n);
      controllo = n;
      printf("[%d]", controllo);
      for (i = 0; fscanf(fp, "%d", & n) != EOF; i++)
         sequenza[i] = n;
      fclose(fp);
      printf("\nFile interi.txt letto con successo (r).\n");
   }
   return controllo;
}

void scriviNumeri(int * sequenza, int lunghezza, int controllo) {
   FILE * fp = fopen("interi.txt", "w");
   if (fp == NULL)
      printf("\nFile interi.txt NON aperto (w).\n");
   else {
      fprintf(fp, "%d ", controllo);
      int i;
      for (i = 0; i < lunghezza; i++)
         fprintf(fp, "%d ", sequenza[i]);
      fclose(fp);
      printf("\nSequenza salvata con successo sul file interi.txt (w).\n");
   }
}

void visualizzaSequenza(int * sequenza, int lunghezza, int controllo) {
   printf("\nSequenza di %d interi (controllo = %d): ", lunghezza, controllo);
   int i;
   for (i = 0; i < lunghezza; i++)
      printf(" %d ", sequenza[i]);
   printf("\n");
}

void leggiSequenza(int * sequenza, int lunghezza) {
   printf("\nScrivi %d interi \n", lunghezza);
   int i;
   for (i = 0; i < lunghezza; i++) {
      printf("\nInserisci l'intero in posizione %d della sequenza: ", i);
      scanf("%d", & (sequenza[i]));
   }
}

int isDivisibilePer(int x, int y) { // x divisibile per y.
   return (x % y) == 0;
}

/*
  Funzione che dato una sequenza di interi, la sua lunghezza ed un intero di controllo,
  verifica se esiste almeno una tripla di elementi adiacenti che contiene almeno 2 elementi
  divisibili per l'intero di controllo (ricorsione).
*/
int multipliDato(int * sequenza, int lunghezza, int controllo) {
   /*
     input: una sequenza di interi, la sua lunghezza ed un intero di controllo.
     pre: sequenza deve contenere solo interi e lunghezza >= 0.
     output: un valore booleano chiamato risultato.
     post: risultato vale 1 se esiste almeno una tripla che contiene almeno 2 elementi divisibili per
           l'intero controllo, 0 altrimenti.
     TIPO DI PROBLEMA: VERIFICA ESISTENZIALE.
   */
   int risultato = 0;
   /* CASO BASE */
   if (lunghezza < 3)
      risultato = 0;
   /* PASSO RICORSIVO */
   else
      risultato = (
         (isDivisibilePer(sequenza[0], controllo) && isDivisibilePer(sequenza[1], controllo)) ||
         (isDivisibilePer(sequenza[0], controllo) && isDivisibilePer(sequenza[2], controllo)) ||
         (isDivisibilePer(sequenza[1], controllo) && isDivisibilePer(sequenza[2], controllo))
      ) || multipliDato(sequenza + 1, lunghezza - 1, controllo);
   return risultato;
}

/*
  Funzione che dato una sequenza di interi, la sua lunghezza ed un intero di controllo,
  verifica se esiste almeno una tripla di elementi adiacenti che contiene almeno 2 elementi
  divisibili per l'intero di controllo (iterazione).
*/
int multipliDatoIterativa(int * sequenza, int lunghezza, int controllo) {
   /*
     input: una sequenza di interi, la sua lunghezza ed un intero di controllo.
     pre: sequenza deve contenere solo interi e lunghezza >= 0.
     output: un valore booleano chiamato risultato.
     post: risultato vale 1 se esiste almeno una tripla che contiene almeno 2 elementi divisibili per
           l'intero controllo, 0 altrimenti.
     TIPO DI PROBLEMA: VERIFICA ESISTENZIALE.
   */
   int risultato = 0;
   if (lunghezza < 3)
      risultato = 0;
   else {
      int i;
      for (i = 0; i < lunghezza; i++) {
         risultato = (
            (isDivisibilePer(sequenza[i], controllo) && isDivisibilePer(sequenza[i + 1], controllo)) ||
            (isDivisibilePer(sequenza[i], controllo) && isDivisibilePer(sequenza[i + 2], controllo)) ||
            (isDivisibilePer(sequenza[i + 1], controllo) && isDivisibilePer(sequenza[i + 2], controllo))
         );
      }
   }
   return risultato;
}

/* funzione principale */
int main(void) {
   int
      lunghezza = 0, //	lunghezza dell'array
      scelta = 0, //	scelta dell'utente
      controllo = 0; //  ulteriore intero

   /* acquisizione dati e lettura dell'array da input */
   printf("\nVuoi introdurre una nuova sequenza (premi 1) oppure recuperarla da file (premi 2)? ");
   scanf("%d", & scelta);

   /* introduzione sequenza da input */
   if (scelta == 1) {
      /* determina la lunghezza della sequenza */
      printf("\nIntroduci la lunghezza della sequenza: ");
      scanf("%d", & lunghezza);

      /* crea l'array e leggine i valori degli elementi */
      int sequenza[lunghezza];
      leggiSequenza(sequenza, lunghezza);
      printf("\nDammi l'intero di controllo: ");
      scanf("%d", & controllo);
      visualizzaSequenza(sequenza, lunghezza, controllo);
      /* invoca la funzione ricorsiva e stampa il risultato */
      if (multipliDato(sequenza, lunghezza, controllo))
         printf("\nEsiste almeno una tripla che contiene almeno 2 elementi divisibili per %d.\n", controllo);
      else
         printf("\nNON esiste almeno una tripla che contiene almeno 2 elementi divisibili per %d.\n", controllo);

      /* salva la sequenza su file */
      scriviNumeri(sequenza, lunghezza, controllo);
   } else if (scelta == 2) {
      /* recupero sequenza da file */
      /* determina la lunghezza della sequenza */
      lunghezza = quantiNumeri() - 1;

      /* prosegui se array non vuoto */
      if (lunghezza > 0) {

         /* crea l'array e leggine i valori degli elementi da file */
         int sequenza[lunghezza];
         controllo = leggiNumeri(sequenza);
         visualizzaSequenza(sequenza, lunghezza, controllo);

         /* invoca la funzione ricorsiva e stampa il risultato */
         if (multipliDato(sequenza, lunghezza, controllo))
            printf("\nEsiste almeno una tripla che contiene almeno 2 elementi divisibili per %d.\n", controllo);
         else
            printf("\nNON esiste almeno una tripla che contiene almeno 2 elementi divisibili per %d.\n", controllo);
      } else
         printf("\nNON esiste almeno una tripla che contiene almeno 2 elementi divisibili per l'intero ricercato in quanto la sequenza %c vuota.\n", 138);
   } else
      printf("\nScelta non valida.\n");
   return EXIT_SUCCESS; // 0
}
