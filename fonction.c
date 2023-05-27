#include "header.h"


// Fonction pour calculer la différence entre deux horaires
struct Time calculate_time_difference(struct Time initial_time, struct Time final_time) {
    struct Time difference;

    // Conversion des heures en minutes
    int initial_minutes = initial_time.hour * 60 + initial_time.minute;
    int final_minutes = final_time.hour * 60 + final_time.minute;

    // Calcul de la différence en minutes
    int time_difference = final_minutes - initial_minutes;

    // Conversion de la différence en heures et minutes
    difference.hour = time_difference / 60;
    difference.minute = time_difference % 60;

    return difference;
}
// Cette fonction calcule la différence entre l'heure initiale et l'heure finale pour donner le temps de jeu du joueur .




// 
void vide_buffer(){
while(getchar()!='\n'){}
}



void includeFile(const char* filePath) {
    FILE* fichier = fopen(filePath, "r"); // Ouvrir le fichier en mode lecture

    if (fichier != NULL) {
        int caractere;

        // Lire et afficher chaque caractère du fichier
        while ((caractere = fgetc(fichier)) != EOF) {
            putchar(caractere);
        }

        fclose(fichier); // Fermer le fichier
    } else {
        printf("Erreur lors de l'ouverture du fichier.\n");
    }
}

// Sauvegarde le nom d'utilisateur du joeur
void save_user() {
    char nomUtilisateur[100];
    
    printf("\n\n\n\nEntrez votre nom d'utilisateur : \n");
    fgets(nomUtilisateur, sizeof(nomUtilisateur), stdin);
    
    // Supprimer le saut de ligne final généré par fgets
    size_t longueurNom = strlen(nomUtilisateur);
    if (longueurNom > 0 && nomUtilisateur[longueurNom - 1] == '\n') {
        nomUtilisateur[longueurNom - 1] = '\0';
    }


    // Sauvegarder le nom dans un fichier (par exemple)
    FILE *fichier = fopen("données_utilsiateur.txt", "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier pour la sauvegarde.\n");
        return;
    }
    
    fprintf(fichier, "%s", nomUtilisateur);
    fclose(fichier);
    
    printf("Le nom d'utilisateur a été sauvegardé avec succès.\n");
}




// affichage du menu principale et sert à selectionner le choix de jouer, quitter ou voir la sauvegarde.
void print_menu() {
    int choice;
    int verif;
    
    do {
        printf("╔═══════════════════════ Menu ═══════════════════════╗\n");
        printf("║                                                    ║\n");
        printf("║                1. Jouer et rejoindre               ║\n");
      
        printf("║                   notre aventure                   ║\n");
     
        printf("║                                                    ║\n");
        printf("║                2. Sauvegarde de votre              ║\n");
        printf("║                       partie                       ║\n");
      
        printf("║                                                    ║\n");
        printf("║                       3. Sortie                    ║\n");
        printf("║                                                    ║\n");
     
        
    printf("╚════════════════════════════════════════════════════╝\n");
        printf("\nVeuillez entrer votre choix : ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Saisie invalide.\n");
            vide_buffer();
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Vous avez choisi de lancer le jeu.\n\n");
                // pour accéder au jeu
                break;
            
            case 2:
                printf("Vous avez choisi de voir la sauvegarde.\n\n");
                // pour accéder à la sauvegarde
                break;
            
            case 3:
                printf("Vous avez choisi de quitter le jeu.\n\n");
                exit(7);
                break;
          // quitter le jeu
            
            default:
                printf("Choix invalide. Veuillez refaire votre choix.\n\n");
              // resaisir le choix
                break;
        }
        
    } while (choice != 1 && choice != 2 && choice != 3);
}

// cette matrice est le plateau du jeu :
char board[MAX_SIZE][MAX_SIZE];


// fonction pour genere aleatoirement et l'utiliser a chaque fois
int aléatoire(int min, int max) {
    return min + rand() % (max - min + 1);
}


void init_board(int size_row,int size_col,int num_symbols) {
    int i, j;
    char tiles[MAX_SYMBOLS] = {'A','B','C','D','E','F'};
  //  un tableau qui contient les caraactere et qui prend en variable max symbole 6
  
    srand(time(NULL));
  // pour generer une variable aleatoire 

    for (i = 0; i < size_row; i++) {
      // parcourir les lignes
      
      for (j = 0; j < size_col; j++) {
          // parcourir les colones
        
            char symbole;
          // variable symbole pour stocker les symboles
            do {
                symbole = tiles[aléatoire(0, num_symbols- 1)];
              // elle genere un symbole aleatoire et le stock dans symbole
            } while ((i > 1 && board[i-1][j] == symbole) ||
                     (j > 1 && board[i][j-1] == symbole)||
              (j > 1 && board[i-1][j-1] == symbole));// change le  symbole si les deux symboles avant au dessus et à gauche de lui sont les mêmes 
            board[i][j] = symbole;
        }
    }
}

//fonction qui permet d'afficher les emojis
const char* get_fruit_emoji(char fruit) {
    switch (fruit) {
        case 'A':
            return "\U0001F34E"; // pomme
        case 'B':
            return "\U0001F347"; // raisin
        case 'C':
            return "\U0001F34C"; // banane
        case 'D':
            return "\U0001F34A"; // orange
        case 'E':
            return "\U0001F346"; // aubergine
        case 'F':
            return "\U0001F353"; // fraise
        default:
            return " ";
    }
}

// creation du tableau
void print_board(int size_col, int size_row) {
    printf("    "); // Affiche un espace avant la première colonne 
    for (int col = 0; col < size_col; col++) {
        printf(" %c ", 'A' + col); // Affiche les lettres des colonnes 
    }
    printf("\n"); // Passe à la ligne
    
    for (int row = 0; row < size_row; row++) { // Parcours des lignes du plateau
        printf("%2d│", row + 1); // Affiche le numéro de la ligne 
        for (int col = 0; col < size_col; col++) {
            printf(" %2s", get_fruit_emoji(board[row][col])); // Affiche le symbole de la case
        }
        printf("\n"); // Passe à la ligne après avoir affiché une ligne complète
    }
}
// cette fonction est utiliser pour afficher le tableau de jeu board et les couleurs dans le tableau 

 int is_valid_move(char board[MAX_SIZE][MAX_SIZE], int size_row, int size_col, int x1, int y1, int x2, int y2) {
    if (x1 < 0 || x1 >= size_row || y1 < 0 || y1 >= size_col ||
        x2 < 0 || x2 >= size_row || y2 < 0 || y2 >= size_col ||
        (abs(x1 - x2) + abs(y1 - y2) != 1) || board[x1][y1]== ' ' || board[x2][y2]== ' ' ) {
        return 0;
    }

    char temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;

     if ((board[x1][y1] == board[x1][y1+1]) && (board[x1][y1] == board[x1][y1+2])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1][y1-1]) && (board[x1][y1] == board[x1][y1-2])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1][y1-1]) && (board[x1][y1] == board[x1][y1+1])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1+1][y1]) && (board[x1][y1] == board[x1+2][y1])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1-1][y1]) && (board[x1][y1] == board[x1-2][y1])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1-1][y1]) && (board[x1][y1] == board[x1+1][y1])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1+1][y1+1]) && (board[x1][y1] == board[x1+2][y1+2])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1-1][y1-1]) && (board[x1][y1] == board[x1-2][y1-2])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1-1][y1-1]) && (board[x1][y1] == board[x1+1][y1+1])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1-1][y1+1]) && (board[x1][y1] == board[x1-2][y1+2])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1+1][y1-1]) && (board[x1][y1] == board[x1+2][y1-2])) {
    return 1;
}
    else if ((board[x1][y1] == board[x1+1][y1-1]) && (board[x1][y1] == board[x1-1][y1+1])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2][y2+1]) && (board[x2][y2] == board[x2][y2+2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2][y2-1]) && (board[x2][y2] == board[x2][y2-2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2][y2-1]) && (board[x2][y2] == board[x2][y2+1])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2+1][y2]) && (board[x2][y2] == board[x2+2][y2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2-1][y2]) && (board[x2][y2] == board[x2-2][y2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2-1][y2]) && (board[x2][y2] == board[x2+1][y2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2+1][y2+1]) && (board[x2][y2] == board[x2+2][y2+2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2-1][y2-1]) && (board[x2][y2] == board[x2-2][y2-2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2-1][y2-1]) && (board[x2][y2] == board[x2+1][y2+1])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2-1][y2+1]) && (board[x2][y2] == board[x2-2][y2+2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2+1][y2-1]) && (board[x2][y2] == board[x2+2][y2-2])) {
    return 1;
}
    else if ((board[x2][y2] == board[x2+1][y2-1]) && (board[x2][y2] == board[x2-1][y2+1])) {
    return 1;
}
else{
    
        temp = board[x1][y1];
        board[x1][y1] = board[x2][y2];
        board[x2][y2] = temp;
        return 0;
     }  


}


// Cette fonction elle permet d'échanger des cases du tableau pour avoir 3 cases identiques :horizontalement verticalement et en diagonale

// Fonction qui supprime les symboles sous certaines conditions
int remove_matches(char board[MAX_SIZE][MAX_SIZE], int size_row, int size_col) {
    int i, j, k;
    int removed = 0;

    // Suppression des lignes horizontales
    for (i = 0; i < size_row; i++) {
        j = 0;
        while (j < size_col - 2) {
            if (board[i][j] != ' ' && board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2]) {
                char symbol = board[i][j];
                k = j;
                while (k < size_col && board[i][k] == symbol) {
                    board[i][k] = ' ';
                    k++;
                    removed++;
                }
                j = k; // On passe à la colonne suivante pour éviter les doublons
            } else {
                j++;
            }
        }
    }

    // Suppression des lignes verticales
    for (j = 0; j < size_col; j++) {
        i = 0;
        while (i < size_row - 2) {
            if (board[i][j] != ' ' && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j]) {
                char symbol = board[i][j];
                k = i;
                while (k < size_row && board[k][j] == symbol) {
                    board[k][j] = ' ';
                    k++;
                    removed++;
                }
                i = k; // On passe à la ligne suivante pour éviter les doublons
            } else {
                i++;
            }
        }
    }

    // Suppression des diagonales ascendantes
    for (i = 0; i < size_row - 2; i++) {
      // parcourir les lignes 
        for (j = 0; j < size_col - 2; j++) {
          // parcourir les colonnes
            if (board[i][j] != ' ' && board[i][j] == board[i+1][j+1] && board[i][j] == board[i+2][j+2]) {
                char symbol = board[i][j];
                k = 0;
                while (i+k < size_row && j+k < size_col && board[i+k][j+k] == symbol) {
                    board[i+k][j+k] = ' ';
                    k++;
                    removed++;
                }
            }
        }
    }

    // Suppression des diagonales descendantes
    for (i = size_row - 1; i >= 2; i--) {
      // parcourir les lignes
        for (j = 0; j < size_col - 2; j++) {
          // parcourir les colonnes
            if (board[i][j] != ' ' && board[i][j] == board[i-1][j+1] && board[i][j] == board[i-2][j+2]) {
                char symbol = board[i][j];
                k = 0;
                while (i-k >= 0 && j+k < size_col && board[i-k][j+k] == symbol) {
                    board[i-k][j+k] = ' ';
                    k++;
                    removed++;
                }
            }
        }
    }

    return removed;
}
//fonction qui crée la gravité du jeu
void apply_gravity(int size_col, int size_row, char board[MAX_SIZE][MAX_SIZE]) {
    int i, j, k;
    for (j = 0; j < size_col; j++) {
        k = size_row - 1;
        for (i = size_row - 1; i >= 0; i--) {
            if (board[i][j] != ' ') {
                board[k][j] = board[i][j];
                k--;
            }
        }
        for (; k >= 0; k--) {
            board[k][j] = ' ';
        }
    }
}




int play_game(int size_row, int size_col, int num_symbols) {
    int exit;
    int verif;
    int score = 0; // Variable pour stocker le score du joueur
    init_board(size_row, size_col, num_symbols); // Initialise le plateau de jeu avec les dimensions et le nombre de symboles donnés
    
    for(int i=0;i<999;i++){ // Boucle principale du jeu 
        printf("Votre score: %d\n", score); // Affiche le score actuel du joueur
        print_board(size_col, size_row); // Affiche le plateau de jeu
        
        int x1, y1, x2, y2; // Variables pour stocker les coordonnées des cases que le joueur souhaite échanger
        do{
          printf("Voulez-vous quitter le jeu ? (0:exit ou 1:continue)\n");
           verif= scanf("%d",&exit);
            vide_buffer();
          }while(exit<0||exit>1 || verif!=1);
          
          if(exit==0){
            printf("vous avez demander d'arreter le jeu\n");
            return score;
          }
        do {
            
            printf("Quelle case voulez-vous déplacer ? (ex. A1 B2): \n");
            char col1, col2; // Variables pour stocker les lettres des colonnes   
          
            int row1, row2; // Variables pour stocker les numéros de lignes 
            scanf(" %c%d %c%d", &col1, &row1, &col2, &row2); // Demande au joueur de saisir les cases à échanger
            col1 = toupper(col1); // Convertit la lettre de la colonne en majuscule
            col2 = toupper(col2); // Convertit la lettre de la colonne en majuscule
            x1 = row1 - 1; // Convertit le numéro de ligne en index
            y1 = col1 - 'A'; // Convertit la lettre de la colonne en index 
            x2 = row2 - 1; // Convertit le numéro de ligne en index 
            y2 = col2 - 'A'; // Convertit la lettre de la colonne en index 
        } while (is_valid_move(board, size_row, size_col, x1, y1, x2, y2) == 0); // Vérifie si le mouvement est valide, si non, redemande au joueur
        
        int removed = remove_matches(board, size_row, size_col); // Supprime les combinaisons de symboles identiques sur le plateau
        while (removed) {
            score += removed; // Ajoute le nombre de symboles supprimés au score du joueur
            apply_gravity(size_col, size_row, board); // Applique la gravité pour faire descendre les symboles restants
            remove_matches(board, size_row, size_col); // Supprime les nouvelles combinaisons de symboles identiques
            apply_gravity(size_col, size_row, board); // Applique à nouveau la gravité
            removed = remove_matches(board, size_row, size_col); // Vérifie s'il y a encore des combinaisons à supprimer
            print_board(size_col, size_row); // Affiche le plateau de jeu
            printf("Votre score est : %d\n", score); // Affiche le score du joueur 
          //printf("%d",check_end(size_row,size_col ,board));
        }
    }
    
    return score; // Retourne le score final du joueur
}