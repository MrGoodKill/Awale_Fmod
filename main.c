#include <stdio.h>
#include <stdlib.h>
#define N 6
#define CLR_SCR() printf("\033[H\033[2J")
#include <fmodex/fmod.h>

// Prototypes des fonctions

void initialisation (void);
void sauvegarde(void);
void chargement(void);
int Menu_Mode(void);
int Menu_Chargement(void);
void affichage(void);
int selection_case(void);
void semer2(int esac_semer);
void menu_escape(void);
int ramassage(int ligne, int colonne);
int affamer(int joueur);
int affamer_temp(int joueur);
void coller_plateau_temp_dans_plateau (void);
void coller_plateau_dans_plateau_temp (void);
int contrainte_nourrir(int joueur);
int fin_jeu(void);
void ecran_victoire(int findejeu);
int nourrir_case(int joueur, int esac_nourrir);
void humain_vs_humain(void);
int aide(void);
void humain_vs_ia(void);
void ia(void);
void coin(void);
void tada(void);


//Définition des variables et tableaux

int plateau[2][N];
int plateau_temp[2][N];
int plateau_temp2[2][N];
int Mode_Jeu;
int score_J1 = 0;
int score_J2 = 0;
int joueur = 1;
int victoire = 0;
char argument[] = "\n    _      _                                _      _\n __(.)< __(.)<  Your argument is invalid  >(.)__ >(.)__\n \\___)  \\___)                              (___/  (___/\n\n";
char coupe[] = "        .-..-\"\"``\"\"-..-.\n        |(`\\`'----'`/`)|\n         \\\\ ;:.    ; //\n          \\\\|%.    |//\n           )|%:    |(\n         ((,|%.    |,))\n          '-\\::.   /-'\n             '::..'\n               }{\n              {__}\n             /    \\\n            |`----'|\n            | [#1] |\n            '.____.'\n";



// Corps du programme

int main(void)
{
     Mode_Jeu = Menu_Chargement();
     affichage();
     srand(time(NULL));

     switch(Mode_Jeu)
        {
                        case 1:
                            humain_vs_humain();
                            break;
                        case 2:;
                            humain_vs_humain();
                            break;
                        case 3:
                            humain_vs_ia();
                          break;
                        default:
                            coin();
                            printf("%s\n",argument);
                            break;
        }
}

void initialisation (void) // Remplissage du tableau "plateau" avec des 4
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<2;j++)
        {
            plateau[j][i]=4;
        }
    }
}

void sauvegarde(void) // Sauvegarde de partie
{
    FILE* fichier = NULL;
    fichier = fopen("sauvegarde.txt", "w");
    if (fichier != NULL)  // Si le fichier a été ouvert correctment alors...
    {
        int i,j;
        for(i=0;i<6;i++)
        {
            for(j=0;j<2;j++)
            {
                fprintf(fichier,"%d\n", plateau[j][i]); // On écrit chaque case du tableau sur une ligne du fichier texte
            }
        }

        fprintf(fichier,"%d\n%d\n%d\n%d\n",joueur,score_J1,score_J2,Mode_Jeu);
        fclose(fichier); // Fermeture du fichier texte pour éviter des fuites de mémoires
    }
    else
    {
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
        return;
    }
    printf("Votre partie a bien ete sauvegardee.\n\n");

}

void chargement(void)  // Chargement de la partie
{
    FILE* fichier = NULL;
    fichier = fopen("sauvegarde.txt", "r");
    if (fichier != NULL)  // Si le fichier a été ouvert correctment alors...
    {
        char chaine[5];
        int entier;
        int i,j;
        for(i=0;i<6;i++)
        {
            for(j=0;j<2;j++)
            {
               fgets(chaine, 4, fichier);  // On met une ligne tu fichier texte dans une chaine
               entier = atoi(chaine);  // On convertit la chaine en entier
               plateau[j][i] = entier;  // On met l'entier dans la case correspondante du tableau
            }
        }
        fgets(chaine, 4, fichier);
        joueur = atoi(chaine);
        fgets(chaine, 4, fichier);
        score_J1 = atoi(chaine);
        fgets(chaine, 4, fichier);
        score_J2 = atoi(chaine);
        fgets(chaine, 4, fichier);
        Mode_Jeu = atoi(chaine);

        fclose(fichier);
    }
    else
    {
        printf("\nPas de sauvegarde enregistree\n");
        system("PAUSE");
        system("cls");
        main();
    }
}

int Menu_Mode(void) // Menu permettant de choisir le mode de jeu
{
     int choixMenu;
     printf("\n________________________________\n\n+---------MENU MODE------------+\n________________________________\n\n\n");
     printf("1.Mode humain contre humain\n");
     printf("2.Mode humain contre humain avec aide\n");
     printf("3.Mode humain contre ordinateur\n");

     while (choixMenu!=1 && choixMenu!=2 && choixMenu!=3) // Empêche un utilisateur de rentrer un nombre autre que 1,2 ou 3.
     {
        printf("\nVotre choix: ");
        scanf("%d", &choixMenu);
        switch(choixMenu)
        {
                        case 1:
                            return choixMenu;
                            break;
                        case 2:;
                            return choixMenu;
                            break;
                        case 3:
                            return choixMenu;
                          break;
                        default:
                            coin();
                            printf("%s\n",argument);
                            break;
        }
     }
}

int Menu_Chargement(void)  // Menu de chargement d'un partie
{
     int choixMenu=0;

     printf("\n________________________________\n\n+-------MENU CHARGEMENT--------+\n________________________________\n\n\n");
     printf("1.Charger la derniere partie\n");
     printf("2.Nouvelle Partie\n");

     while (choixMenu!=1 && choixMenu!=2) // Empêche un utilisateur de rentrer un nombre autre que 1 ou 2.
     {
        printf("\nVotre choix: ");
        scanf("%d", &choixMenu);
        switch(choixMenu)
        {
                        case 1:
                            chargement();
                            return Mode_Jeu;
                            break;
                        case 2:
                            initialisation();
                            joueur =(rand()%(2))+1;
                            return Menu_Mode();
                            break;
                        default:
                            coin();
                            printf("%s\n",argument);
                            break;
        }
     }
}

void affichage(void)  // Affichage du tableau
{
    int i,j;
    system ("cls");// On efface la console
    if (Mode_Jeu ==1)
    printf("________________________________\n\n+------HUMAIN VS HUMAIN--------+\n________________________________\n");
    if (Mode_Jeu ==2)
    printf("________________________________\n\n+--HUMAIN VS HUMAIN AVEC AIDE--+\n________________________________\n");
    if (Mode_Jeu ==3)
    printf("________________________________\n\n+--------HUMAIN VS IA----------+\n________________________________\n");
    printf("\n\n   Joueur 1       graine= %d\n\n",score_J1);
    printf("   6    5    4    3    2    1\n");
    printf("+----+----+----+----+----+----+\n");
    printf("|    |    |    |    |    |    |\n");
    j=0;
    for(i=0;i<6;i++)
    {
        if (plateau[j][i]<10)
        printf("|  %d ",plateau[j][i]);
        else
        printf("| %d ",plateau[j][i]);  // On rectfie l'alignement du tableau si la valeur n'est pas un chiffre
    }
    printf("|\n");
    printf("+----+----+----+----+----+----+\n");
    printf("|    |    |    |    |    |    |\n");
    j=1;
    for(i=0;i<6;i++)
    {
        if (plateau[j][i]<10)
        printf("|  %d ",plateau[j][i]);
        else
        printf("| %d ",plateau[j][i]);  // On rectfie l'alignement du tableau si la valeur n'est pas un chiffre
    }
    printf("|\n");
    printf("+----+----+----+----+----+----+\n");
    printf("   1    2    3    4    5    6\n\n");
    printf("   Joueur 2       graine= %d\n\n",score_J2);
}

int selection_case(void)
{
    int esac = 2;
    int parametre = 1;
    int esac_nourrir = esac;
    while (esac<1 || esac>6 || parametre == 1 || (affamer(joueur)== 1 && nourrir_case(joueur, esac_nourrir - 1) == 0))
    {
        parametre = 1;
        printf("\nAu joueur %d de jouer\n",joueur);
        printf("\nQuelle case voulez vous jouer? (27 pour afficher menu) ");
        scanf("%d",&esac);
        esac_nourrir = esac;
        if (joueur == 1)
        esac = 7 - esac;
        if(plateau[joueur -1][esac-1] != 0)
        parametre = 0;
        if (esac == 27 || esac == -20)
        menu_escape();
        else if (esac<1 || esac>6 || (affamer(joueur)== 1 && nourrir_case(joueur, esac_nourrir - 1) == 0) || parametre == 1)
        {
            coin();
            printf("%s",argument);
        }

    }

    return esac;
}

void semer2(int esac_semer)
{
    int colonne = esac_semer - 1;
    int colonne_for = esac_semer - 1;
    int ligne = joueur - 1;
    int ligne_for = joueur - 1;
    int i;
    int j;
    int quotient;
    int reste;
    coller_plateau_dans_plateau_temp();

    reste = plateau_temp[ligne_for][colonne_for] % 11;
    quotient = plateau_temp[ligne_for][colonne_for] / 11;

    for(i=0;i<6;i++)
        {
            for(j=0;j<2;j++)
            {
               if (j != ligne_for || i != colonne_for)
               plateau_temp[j][i] = plateau_temp[j][i] + quotient;
            }
        }

    for(i=0;i<reste;i++)
    {
        if (ligne == 1 && colonne != 5)
        {
            colonne++;
            plateau_temp[1][colonne]++;
        }
        else if (ligne == 0 && colonne != 0)
        {
            colonne--;
            plateau_temp[0][colonne]++;
        }
        else if (ligne == 1 && colonne == 5)
        {
            plateau_temp[0][5]++;
            ligne = 0;
        }
        else if (ligne == 0 && colonne == 0)
        {
            plateau_temp[1][0]++;
            ligne = 1;
        }
    }
    plateau_temp[ligne_for][colonne_for] = 0;

    if (joueur == 1)
    {
        printf("\nJ1\n");
        score_J1= score_J1 + ramassage(ligne,colonne);
    }
    else if (joueur == 2)
    {
        printf("\nJ2\n");
        score_J2= score_J2 + ramassage(ligne,colonne);
    }
}

void menu_escape(void)
{
  int choixMenu;

     printf("\n________________________________\n\n+------------MENU--------------+\n________________________________\n\n\n");
     printf("1.Sauvegarder la partie\n");
     printf("2.Continuer la partie\n");
     printf("3.Quitter\n");

     while (choixMenu!=1 && choixMenu!=2 && choixMenu!=3) // Empêche un utilisateur de rentrer un nombre autre que 1,2 ou 3.
     {
        printf("\nVotre choix: ");
        scanf("%d", &choixMenu);
        switch(choixMenu)
        {
                        case 1:
                            sauvegarde();
                            break;
                        case 2:
                            affichage();
                            break;
                        case 3:
                            exit(EXIT_SUCCESS);
                            break;
                        default:
                            coin();
                            printf("%s\n",argument);
                            break;
        }
     }
}

int ramassage(int ligne, int colonne)
{
    int nb_graines = 0;
    if (ligne == 0 && ligne!=(joueur-1))
    {
        while ((plateau_temp[ligne][colonne]==2 || plateau_temp[ligne][colonne]==3) && colonne <6)
        {
            nb_graines = nb_graines + plateau_temp[ligne][colonne];
            plateau_temp[ligne][colonne] = 0;
            colonne++;
        }
    }
    else if (ligne == 1 && ligne!=(joueur-1))
    {
        while ((plateau_temp[ligne][colonne]==2 || plateau_temp[ligne][colonne]==3) && colonne >-1)
        {
            nb_graines = nb_graines + plateau_temp[ligne][colonne];
            plateau_temp[ligne][colonne] = 0;
            colonne--;

        }
    }
    if(affamer_temp(joueur) == 0)
    {
    aide();
    coller_plateau_temp_dans_plateau();
    return nb_graines;
    }
    else
    return 0;

}

int affamer_temp(int joueur)
{
    int i;
    int somme =0;
    int y = (joueur - 1 == 0);
    for(i=0;i<6;i++)
    {
        somme = somme + plateau_temp[y][i];
    }
    if (somme == 0)
    return 1;
    else if (somme != 0)
    return 0;
}

int affamer(int joueur)
{
    int i;
    int somme =0;
    int y = (joueur - 1 == 0);
    for(i=0;i<6;i++)
    {
        somme = somme + plateau[y][i];
    }
    if (somme == 0)
    return 1;
    else if (somme != 0)
    return 0;
}

void coller_plateau_dans_plateau_temp (void)
{
    int i;
    int j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<2;j++)
        {
            plateau_temp[j][i]=plateau[j][i];
        }
    }
}

void coller_plateau_temp_dans_plateau (void)
{
    int i;
    int j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<2;j++)
        {
            plateau[j][i]=plateau_temp[j][i];
        }
    }
}

int contrainte_nourrir(int joueur)
{
    int i;
    int somme = 0;
    if (joueur == 2)
    {
        for(i=0;i<6;i++)
        {
            somme = somme + (plateau[joueur-1][i] - (5 - i) > 0);
        }
        if (somme > 0)
        return 1;
    }
    else if (joueur == 1)
    {
        for(i=0;i<6;i++)
        {
            somme = somme + (plateau[joueur-1][i] - i > 0);
        }
        if (somme > 0)
        return 1;
    }
    else
    return 0;
}

int fin_jeu(void)
{
    int i;
    int j;
    int somme = 0;
    for(i=0;i<6;i++)
    {
        for(j=0;j<2;j++)
        {
            somme = somme + plateau[j][i];
        }
    }
    printf("somme: %d\n",somme);
    printf("Conditions: (%d et %d et %d) ou (%d et %d et %d)\n",affamer(1) == 1, contrainte_nourrir(2) == 0,joueur == 2,affamer(2) == 1, contrainte_nourrir(1) == 0,joueur == 1);
    if (score_J1 >= 25)
    return 1;
    else if (score_J2 >= 25)
    return 2;
    else if (somme < 7 || (affamer(1) == 1 && contrainte_nourrir(2) == 0 && joueur == 2) || (affamer(2) == 1 && contrainte_nourrir(1) == 0 && joueur == 1) )
    {
        if (score_J1 > score_J2)
        return 1;
        if (score_J2 > score_J1)
        return 2;
        if (score_J1 == score_J2)
        return 3;
    }
    else
    return 0;

}

void ecran_victoire(int findejeu)
{
    int i;
    if (findejeu == 0)
    return;
    else if (findejeu == 1 || findejeu == 2)
    {
        tada();
        printf("\n\nLe joueur %d a gagne! Les scores sont J1: %d et J2: %d\n\n",findejeu,score_J1,score_J2);
        printf("%s",coupe);
    }
    else if(findejeu == 3)
    {
        tada();
        printf("\n\nEx aequo. Vos scores: %d\n\n",score_J1);
    }
    system("PAUSE");
    exit(EXIT_SUCCESS);
}

int nourrir_case(int joueur, int esac_nourrir)
{
    if (joueur == 2)
    {
        if (plateau[joueur-1][esac_nourrir] - (5 - esac_nourrir) > 0)
        return 1;
        else
        return 0;
    }
    else if (joueur == 1)
    {
        if (plateau[joueur-1][5 - esac_nourrir] - (5 - esac_nourrir) > 0)
        return 1;
        else
        return 0;
    }
    else
    return 0;
}
void humain_vs_humain(void)
{
    while(Mode_Jeu == 1 || Mode_Jeu == 2)
    {
         int esac_humain_vs_humain;
         esac_humain_vs_humain = selection_case();
         semer2(esac_humain_vs_humain);
         affichage();
         if (joueur == 1)
         joueur = 2;
         else if (joueur == 2)
         joueur = 1;
         ecran_victoire(fin_jeu());
    }
}

void humain_vs_ia(void)
{
    while(Mode_Jeu == 3)
    {
        int esac_humain_vs_ia;
        if (joueur == 2)
        {
        esac_humain_vs_ia = selection_case();
        semer2(esac_humain_vs_ia);
        }
        else if(joueur == 1)
        ia();
        affichage();
        if(joueur == 2)
        system("PAUSE");
        if (joueur == 1)
        joueur = 2;
        else if (joueur == 2)
        joueur = 1;
        ecran_victoire(fin_jeu());
    }

}

void ia(void)
{
    int esac_ia = 0;
    int parametre = 1;
    int esac_nourrir = esac_ia;
    while (esac_ia<1 || esac_ia>6 || parametre == 1 || (affamer(joueur)== 1 && nourrir_case(joueur, esac_nourrir - 1) == 0))
    {
        parametre = 1;
        esac_ia=(rand()%(6))+1;
        esac_nourrir = esac_ia;
        if (joueur == 1)
        esac_ia = 7 - esac_ia;
        if(plateau[joueur -1][esac_ia-1] != 0)
        parametre = 0;
    }
    semer2(esac_ia);
}

int aide(void)
{
    if(Mode_Jeu == 1 || Mode_Jeu == 3)
    return 1;
    else if (Mode_Jeu == 2)
    {
        int i;
        int j;
        for(i=0;i<6;i++)
        {
            for(j=0;j<2;j++)
            {
                plateau_temp2[j][i]=plateau[j][i];
            }
        }
        for(i=0;i<6;i++)
        {
            for(j=0;j<2;j++)
            {
                plateau[j][i]=plateau_temp[j][i];
            }
        }
        affichage();
        printf("\nValider coup: 1\nAnnuler: 2\n\nVotre choix: ");
        scanf("%d",&i);
        if(i==2)
        {
            for(i=0;i<6;i++)
        {
            for(j=0;j<2;j++)
            {
                plateau[j][i]=plateau_temp2[j][i];
            }
        }
        affichage();
        humain_vs_humain();
        }
        else if(i == 1)
        return 1;
    }
}

void coin(void)
{
    FMOD_SYSTEM *system;
    FMOD_SOUND *coin = NULL;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    FMOD_System_CreateSound(system, "Quack.wav", FMOD_CREATESAMPLE, 0, &coin);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, coin, 0, NULL);
}

void tada(void)
{
    FMOD_SYSTEM *system;
    FMOD_SOUND *tada = NULL;

    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    FMOD_System_CreateSound(system, "TADA.wav", FMOD_CREATESAMPLE, 0, &tada);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, tada, 0, NULL);

}
