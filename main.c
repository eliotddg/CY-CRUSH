
#include "header.h"


int main() {
 const char* filePath = "logo.txt";
    includeFile(filePath);
  // pour afficher le logo cy crush

 save_user();
  // pour enregistrer le nom de l'utilisateur
   
    print_menu();
  // pour afficher notre menu de jeu
  char board[MAX_SIZE][MAX_SIZE];
   
  int verif;
  int size_col;
  int size_row;
  int num_symbols;
  
struct Time initial_time, final_time, difference;

do{

  printf("Entrez l'heure initiale (format 24 heures) : \n");
   verif= scanf("%d", &initial_time.hour);
   vide_buffer();
  // utilisation de la fonction buffer pour refuser la saisie des lettres
}while((initial_time.hour>24)||(initial_time.hour<0) ||(verif!=1));
    // Saisie des heures initiales (les heures sont comprises entre 0 et 24 )

  do{
    printf("Entrez les minutes initiales : \n");
   verif= scanf("%d", &initial_time.minute);
    vide_buffer();
  // utilisation de la fonction buffer pour refuser la saisie des lettres
}while((initial_time.minute>60)||(initial_time.minute<0)||(verif!=1));
    // Saisie des minutes initiales (les minutes sont comprises entre 0 et 60 )
  do{
   
    
    printf("Choisissez un nombre de lignes entre 3 et 26  : \n");
       verif=  scanf("%d",&size_row);
    vide_buffer();
    // utilisation de la fonction buffer pour refuser la saisie des lettres
    if ((size_row<3) || (size_row>MAX_SIZE) ) {
        printf("Le nombre de lignes n'est pas valable \n");
    }
  }while( (size_row <3) || (verif!=1) || (size_row>MAX_SIZE) );
      
  do{
    printf("Choisissez un nombre de colonnes entre 3 et 26 :\n");
   verif= scanf("%d", &size_col);
        vide_buffer();
    // utilisation de la fonction buffer pour refuser la saisie des lettres
    if ((size_col <3) || (size_col>MAX_SIZE)  ) {
        printf("Le nombre de colonnes n'est pas valable \n");
    }
  }while( (size_col <3) || (verif!=1) || (size_col>MAX_SIZE) );
  
    do{
      printf("Choisissez un nombre de symboles (entre 4 et 6) : \n");
     verif= scanf("%d", &num_symbols);
        vide_buffer();
      // utilisation de la fonction buffer pour refuser la saisie des lettres
      if ((num_symbols < MIN_SYMBOLS) || (num_symbols>MAX_SYMBOLS) ) {
          printf("Le nombre de symboles n'est pas valable\n");
          
      }
    }while(((num_symbols < MIN_SYMBOLS) || (num_symbols>MAX_SYMBOLS)) || (verif!=1)  );

    
    

    int score = play_game(size_row,size_col,num_symbols);
    printf("Votre score final: %d\n", score);
// Saisie de l'heure finale
 do{
  printf("Entrez l'heure finale (format 24 heures) : \n");
   verif= scanf("%d", &final_time.hour);
   vide_buffer();
}while((initial_time.hour>24)||(initial_time.hour<0) ||(verif!=1));
    // Saisie des minutes finales
  do{
    printf("Entrez les minutes finales : \n");
   verif= scanf("%d", &final_time.minute);
    vide_buffer();
}while((initial_time.hour>24)||(initial_time.hour<0) ||(verif!=1));
    difference = calculate_time_difference(initial_time, final_time);

    // Affichage de la différence
    printf("Différence : %02d:%02d\n", difference.hour, difference.minute);

   

    return 0;
}
