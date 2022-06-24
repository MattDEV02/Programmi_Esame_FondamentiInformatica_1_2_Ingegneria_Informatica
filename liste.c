#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20 // numero massimo caratteri stringhe


/*********************************************
/**************	STRUTTURE ********************
**********************************************/

typedef struct Esame {
   char nome[MAX];
   char professore[MAX];
   int voto;
   int cfu;
}
Esame;

typedef struct Nodo {
   Esame esame;
   struct Nodo * next;
}
Nodo;

Nodo * allocaNodo() {
   return malloc(sizeof(Nodo));
}

/**********************************************
 ************** VISUALIZZAZIONE ***************
 **********************************************/

int lunghezza(Nodo * head) {
   int l = 0;
   /* CASO BASE */
   if (head == NULL)
      l = 0;
   /* PASSO RICORSIVO */
   else
      l = lunghezza(head -> next) + 1;
   return l;
}

void visualizzaEsame(Esame e) {
   printf("Professor %s ; Materia = %s ; Voto = %d ; CFU = %d\n", e.professore, e.nome, e.voto, e.cfu);
}

void visualizzaLista(Nodo * head) {
   if (head == NULL)
      printf("\nLista vuota, nulla da visualizzare.\n");
   else {
      printf("\nLista di %d esami: \n \n", lunghezza(head));
      int i = 0;
      while (head != NULL) {
         printf("\nEsame in posizione %d:  ", i);
         visualizzaEsame(head -> esame);
         head = head -> next;
         i++;
      }
   }
}

/*********************************************
 ************** INSERIMENTO ******************
 **********************************************/

void leggiStringa(char * stringa) {
   fgets(stringa, MAX, stdin);
   stringa[strlen(stringa) - 1] = '\0';
}

void leggiEsame(Esame * e) {
   printf("\nInserisci il nome dell'esame: ");
   leggiStringa(e -> nome);
   printf("\nInserisci il nome del professore dell'esame: ");
   leggiStringa(e -> professore);
   do {
      printf("\nInserisci il voto dell'esame: ");
      scanf("%d", & (e -> voto));
      if (e -> voto < 0)
         printf("\nIl voto deve essere > 0, riprova.\n");
   } while (e -> voto < 0);
   do {
      printf("\nInserisci i cfu dell'esame: ");
      scanf("%d", & (e -> cfu));
      if (e -> cfu < 0)
         printf("\nI CFU devono essere > 0, riprova.\n");
   } while (e -> cfu < 0);
}

void inserisciCodaLista(Nodo ** puntaHead) {
   Nodo * nuovo = allocaNodo();
   leggiEsame( & (nuovo -> esame));
   nuovo -> next = NULL;
   if ( * puntaHead == NULL)
      *
      puntaHead = nuovo;
   else {
      Nodo * nodo = * puntaHead;
      while (nodo -> next != NULL)
         nodo = nodo -> next;
      nodo -> next = nuovo;
      printf("\nEsame inserito con successo in coda alla lista.\n");
   }
}

/**********************************************
 ************** CANCELLAZIONE *****************
 **********************************************/

int precede(Nodo * nodo1, Nodo * nodo2) {
   return (
      (nodo1 -> esame).voto < (nodo2 -> esame).voto ||
      (nodo1 -> esame).cfu > (nodo2 -> esame).cfu
   );
}

Nodo * minimo(Nodo * head) {
   Nodo * min = head;
   Nodo * primo = head -> next;
   while (primo != NULL) {
      if (precede(primo, min))
         min = primo;
      primo = primo -> next;
   }
   return min;
}

int stringheUguali(char * stringa1, char * stringa2) {
   return strcmp(stringa1, stringa2) == 0;
}

int uguaglianza(Nodo * nodo1, Nodo * nodo2) {
   return (
      stringheUguali((nodo1 -> esame).nome, (nodo2 -> esame).nome) &&
      stringheUguali((nodo1 -> esame).professore, (nodo2 -> esame).professore) &&
      (nodo1 -> esame).voto == (nodo2 -> esame).voto &&
      (nodo1 -> esame).cfu == (nodo2 -> esame).cfu
   );
}

void cancella(Nodo ** puntaHead) {
   if ( * puntaHead == NULL)
      printf("\nLista vuota, nulla da cancellare.\n");
   else {
      Nodo * precedente = * puntaHead;
      Nodo * successivo = precedente -> next;
      Nodo * dealloca = minimo( * puntaHead); // il minimo va cancellato
      int cancellato = 0;
      if (uguaglianza( * puntaHead, dealloca)) {
         free( * puntaHead);
         * puntaHead = successivo;
         cancellato = 1;
      } else {
         while (successivo != NULL && !cancellato) {
            if (uguaglianza(successivo, dealloca)) {
               precedente -> next = successivo -> next;
               free(successivo);
               cancellato = 1;
            } else {
               precedente = successivo;
               successivo = successivo -> next;
            }
         }
      }
      if (cancellato)
         printf("\nEsame cancellato con successo.\n");
      else
         printf("\nEsame NON cancellato.\n");
   }
}

/**********************************************
 ************ FUNZIONE PRINCIPALE ************
 **********************************************/

int main(void) {
   /* inizializza la lista */
   Nodo * head = NULL;
   int risposta = 0; // per interazione con utente
   do {
      /* richiedi un'operazione all'utente */
      printf("\nChe operazione vuoi svolgere?\n");
      printf("1 -> Visualizzazione\n");
      printf("2 -> Inserimento\n");
      printf("3 -> Cancellazione\n");
      printf("0 -> Termina il programma\n");
      scanf("%d%*c", & risposta);
      /* gestisci le operazioni dell'utente */
      switch (risposta) {
         case 0: {
            printf("\nFinito!\n");
            break;
         }
         case 1: {
            visualizzaLista(head);
            break;
         }
         case 2: {
            inserisciCodaLista( & head);
            break;
         }
         case 3: {
            cancella( & head);
            break;
         }
         default: {
            printf("\nSelezione non valida!\n");
            break;
         }
      }
   } while (risposta);
   return EXIT_SUCCESS; // 0
}
