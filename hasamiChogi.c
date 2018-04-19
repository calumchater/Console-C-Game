#include <stdio.h> 
#include <ctype.h> // On inclut cette bibliotheque pour s'assurer que la saisie de l'utilisateur soit en majuscules
#include <math.h> // valeur absolue
#define COL 9
#define LIG 9
#define NBJOUEUR 2
#define TAILLE_NOM 30
#define SAISI 6
#define TRUE 1
#define FALSE 0

typedef struct {
  char couleur;
  char nom[10];
}
Joueur;

void affichage_matrice(int c, char t[][c]) {
  int i;
  int j;
  for (i = 0; i < COL + 1; i++) { // Premiere ligne qui affiche de 0 a 9
    printf("%d\t", i);
  }
  for (i = 0; i < LIG; i++) { // 65 a 73
    printf("\n%c", (char) i + 65);
    for (j = 0; j < COL; j++) {
      printf("\t%c", t[i][j]);
    }
  }
  printf("\n");
}

void construction_matrice(int l, int c, char damier[l][c]) {
    int i;
    int j;
    // Pions noirs
    for (i = 0; i < 2; i++) {
      for (j = 0; j < COL; j++) {
        damier[i][j] = 'N';
      }
    }

    // Cases vides
    for (i = 2; i < 7; i++) {
      for (j = 0; j < COL; j++) {
        damier[i][j] = '.';
      }
    }

    // Pions blancs
    for (i = 7; i < 9; i++) {
      for (j = 0; j < COL; j++) {
        damier[i][j] = 'B';
      }
    }
  }
  //--------------------------------------------------------------------------------------------------------------------
int nb_pion(int x, int y, char damier[LIG][COL], char pos[SAISI]) {

    int a = pos[0] - 65;
    int b = pos[1] - 49;
    int c = pos[3] - 65;
    int d = pos[4] - 49;
    int i;
    int nb_pions = 0;

    // B2,C2 : x = 1 // y = 0 ///// a = 1 / b = 1 / c = 2 / d = 1
    if (x > 0) {
      if (a < c) { //C => E (x = 2)
        for (i = 1; i <= x; i++) {
          if (damier[a + i][b] != '.') {
            nb_pions++;
          }
        }
      }
      if (a > c) { //E => C (x = -2)
        for (i = 1; i <= x; i--) {
          if (damier[a + i][b] != '.') {
            nb_pions++;
          }
        }
      }
    }
    if (y > 0) {
      if (b < d) { //3 => 5 (y = 2)
        for (i = 1; i <= y; i++) {
          if (damier[a][b + i] != '.') {
            nb_pions++;
          }
        }
      }
      if (b > d) { //5 => 3 (y = -2)
        for (i = 1; i <= y; i--) {
          if (damier[a][b + i] != '.') {
            nb_pions++;
          }
        }
      }
    }
    return nb_pions;
  }
  //--------------------------------------------------------------------------------------------------------------------

int verificationPos(char pos[SAISI], Joueur J[NBJOUEUR], char damier[LIG][COL], int tour) {
  int verif = 0;
  int a = pos[0] - 65;
  int b = pos[1] - 49;
  int c = pos[3] - 65;
  int d = pos[4] - 49;
  int i = 0;
  int j = 0;
  int nb_pions = 0;
  //int dplt_valide = 0;

  int x = c - a; // deplacement abscisse fabs = absolue
  int y = d - b; // deplacement ordonnee fabs = absolue

  if ((a >= 0) && (a < LIG) && (b >= 0) && (b < COL) && (c >= 0) && (c < LIG) && (d >= 0) && (d < COL)) {
    if (damier[a][b] == J[tour % 2].couleur) {
      if (damier[c][d] == '.') {
        if ((x == 0) || (y == 0)) { // anti-diagonale
          nb_pions = nb_pion(x, y, damier, pos);
          printf("pion : %d\n", nb_pions);
          if (nb_pions == 0) { // pas de pion sur le deplacement
            verif = 1;
          } else if (nb_pions == 1) { // un pion sur le deplacement
            if (x > 0) { // H => I
              if (damier[a + 1][b] == '.') { //
                verif = 1;
              }
            } else if (x < 0) {
              if (damier[a - 1][b] == '.') {
                verif = 1;
              }
            }
            if (y > 0) {
              if (damier[a][b + 1] == '.') {
                verif = 1;
              }
            } else if (y < 0) {
              if (damier[a][b - 1] == '.') {
                verif = 1;
              }
            }

            if (damier[a + x][b + y] == '.') {
              verif = 1; // une pierre coll?e
            } else {
              printf("Il y a un pion sur le chemin qui n'est pas coll%c a ton pion\n", 130); // une pierre pas coll?e
              printf("damier[a+x][a+y] : %c\n", damier[a + x][b + y]);
            }
          } else {
            printf("Il y a plus d'un pion"); // plus d'une pierre
          }
          //-----------------------------------------------------------------------------------------------------------------------

        } else {
          printf("Le pion ne peut pas se d%cplacer diagonalement !\n", 130);
        }
      } else {
        printf("La case de d'arriv%ce contient d%cj%c un pion\n", 130, 130, 133);
      }
    } else {
      printf("Ce n'est pas un de tes pions\n");
    }
  } else {
    printf("La case n'est pas dans le plateau de jeu\n");
  }
  return verif;
}

void deplacement(char pos[SAISI], Joueur J[NBJOUEUR], char damier[LIG][COL], int tour) {
  int lig, col;
  int a = pos[0] - 65;
  int b = pos[1] - 49;
  int c = pos[3] - 65;
  int d = pos[4] - 49;
  int verif;


  verif = verificationPos(pos, J, damier, tour);
  if (verif == 1) {
    damier[c][d] = damier[a][b];
    damier[a][b] = '.';
  }
}

void capture(char pos[SAISI], Joueur J[NBJOUEUR], char damier[LIG][COL], int tour) {
    int c = pos[3] - 65;
    int d = pos[4] - 49;
    int i = 0;
    int j;
    int verif = FALSE;
    if (damier[c - 1][d] == J[(tour + 1) % 2].couleur) {
      while (i < (LIG - c) && damier[c - i][d] == J[(tour + 1) % 2].couleur && verif == FALSE) {
        i++;
        if (damier[c - i][d] == J[(tour) % 2].couleur) {
          for (j = 0; j < i - 1; j++) {
            damier[c - j][d] = '.';
            verif = TRUE;
          }
        }
      }
    }
    i = 0;
    if (damier[c + 1][d] == J[(tour + 1) % 2].couleur) {
      while (i < (LIG) && damier[c + i][d] == J[(tour + 1) % 2].couleur && verif == FALSE) {
        i++;
        if (damier[c + i][d] == J[(tour) % 2].couleur) {
          for (j = 0; j < i - 1; j++) {
            damier[c + j][d] = '.';
            verif = TRUE;
          }
        }
      }
    }

    i = 0;
    if (damier[c][d - 1] == J[(tour + 1) % 2].couleur) {
      while (i < (LIG) && damier[c][d - i] == J[(tour + 1) % 2].couleur && verif == FALSE) {
        i++;
        if (damier[c][d - i] == J[(tour) % 2].couleur) {
          for (j = 0; j < i - 1; j++) {
            damier[c][d - j] = '.';
            verif = TRUE;
          }
        }
      }
    }
    i = 0;
    if (damier[c][d + 1] == J[(tour + 1) % 2].couleur) {
      while (i < (LIG) && damier[c][d+i] == J[(tour + 1) % 2].couleur && verif == FALSE) {
        i++;
        if (damier[c][d+i] == J[(tour) % 2].couleur) {
          for (j = 0; j < i - 1; j++) {
            damier[c][d + j] = '.';
            verif = TRUE;
          }

        }
      }
    }
}
    int main() {
        char damier[LIG][COL];
        int tour = 0;
        int compBlanc = 18;
        int compNoir = 18; // Initialisation des compteurs de pions pour condition arret du jeu
        Joueur J[NBJOUEUR];
        char pos[SAISI];
        int verif;

        construction_matrice(LIG, COL, damier);

        printf("Joueur 1 veuillez saisir votre nom : ");
        scanf("%s", &(J[0].nom));

        J[0].couleur = 'B';

        printf("Joueur 2 veuillez saisir votre nom : ");
        scanf("%s", &(J[1].nom));

        J[1].couleur = 'N';

        affichage_matrice(COL, damier);

        while (compBlanc > 5 && compNoir > 5) {

          printf("\nSaisissez la position de d%cpart et d'arriv%ce : ", 130, 130);
          scanf("%s", &pos);

          verif = verificationPos(pos, J, damier, tour);

          if (verif == 1) {
            deplacement(pos, J, damier, tour);
            // fonction mange_pion(Joueur, pos arrive,damier, tour)
            affichage_matrice(COL, damier);
            tour++;
          }
        }
        // Joueur, pos arrive
        return 0;
      }
      
