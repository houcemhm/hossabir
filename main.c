#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int fn_existe(char list[50][50], int length, char ch[50]) {
    int existe = 0;
    int i = 0;

    while (i < length && existe == 0) {
        if (strcmp(list[i], ch) == 0) {
            existe = 1;
        }
        i++;
    }

    return existe;
}

int fn_max(char list[50][50], int length) {
    int max = 0;
    for (int i = 0; i < length; i++) {
        if (max < strlen(list[i])) {
            max = strlen(list[i]);
        }
    }
    return max;
}

int main() {
    clock_t begin;
    double time_spent;
    FILE *file;
    int choix, choix2, t, indexv, indexc, timepassed, maxs,maxs1,maxs2,num_manche;
    char Tab[9], chu[50], chu1[50], chu2[50], ch[50] = "", altch[50] = "", word[50] = "", truewords[50][50], wordsu[50][50], wordsu1[50][50], wordsu2[50][50];
    int ok, existe, existe2;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    char words[50][50];
    srand(time(NULL));

    printf("\t J E 1U        D E       M O T S\n\n");
    printf("1-Jouer a un\n");
    printf("2-Jouer a un sous une contrainte de temps\n");
    printf("3-Jouer a deux\n");
    printf("0-quitter\n");

    do {
        printf("Votre choix = ");
        scanf("%d", &choix);
    } while (choix > 3 || choix < 0);

    printf("Tapez la taille (7/8/9) du mot le plus long a retrouver = ");
    scanf("%d", &t);

    while (t < 7 || t > 9) {
        printf("La taille que vous avez saisie est erronee!\n\n");
        printf("Tapez la taille (7/8/9) du mot le plus long a retrouver = ");
        scanf("%d", &t);
    }

    for (int i = 0; i < t; i++) {
        do {
            printf("Caractere %d : Consonne (c/C) ou Voyelle (v/V) = ", i + 1);
            scanf(" %c", &Tab[i]);
        } while (Tab[i] != 'c' && Tab[i] != 'C' && Tab[i] != 'v' && Tab[i] != 'V');
    }

    for (int i = 0; i < t; i++) {
        if (Tab[i] == 'v' || Tab[i] == 'V') {
            indexv = rand() % 5;
            strncat(ch, &vowels[indexv], 1);
        } else {
            indexc = rand() % 21;
            strncat(ch, &consonants[indexc], 1);
        }
    }

    for (int i = 0; i < t; i++) {
        printf("\t%C", toupper(ch[i]));
    }

    file = fopen("C:/Users/houssem/Desktop/hossabir/dictionnaire.txt", "r");

    if (file == NULL) {
        printf("Fichier introvable\n");
        return 1;
    }

    int i;
    int l = 0;

    while (fscanf(file, "%s", word) != EOF) {
        ok = 1;
        i = 0;
        altch[0] = '\0';
        strcat(altch, ch);

        while (i < strlen(word) && ok == 1) {
            int j = 0;
            existe = 0;

            while (j < strlen(altch) && existe == 0) {
                if (word[i] == altch[j]) {
                    existe = 1;

                    for (int k = j; k < strlen(altch); k++) {
                        altch[k] = altch[k + 1];
                    }

                    altch[strlen(altch) - 1] = '\0';
                }

                j++;
            }

            if (existe == 0) {
                ok = 0;
            }

            i++;
        }

        if (ok == 1) {
            strcpy(truewords[l], word);
            l++;
        }
    }

    int max = fn_max(truewords, l);
    i = 1;
    int k = 0;

    begin = clock();

    if (choix == 1 || choix == 2) {
        do {
            printf("\n%d-\t", i);
            scanf("%s", chu);

            if (choix == 2) {
                time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;

                if (time_spent >= t * t) {
                    timepassed = 1;
                }
            }

            existe = fn_existe(truewords, l, chu);

            if (existe == 1 && (strlen(chu) == max)) {
                if (choix == 2) {
                    printf("Vous gagnez! Le mot que vous avez saisi est correct et est le plus long.\nVous l'avez trouve en seulement %f", time_spent);
                } else {
                    printf("Vous gagnez! Le mot que vous avez saisi est correct et est le plus long!\n");
                }

                strcpy(wordsu[k], chu);
                k++;
            } else if (existe == 1) {
                printf("le mot qui vous avez saisi est correct mais n'est pas le plus long.\n");
                strcpy(wordsu[k], chu);
                k++;
            } else {
                printf("le mot qui vous avez saisi est incorrect!\n");
            }

            i++;
        } while (i <= t && ((existe == 1 && (strlen(chu) < max)) || !existe) || (choix == 2 && timepassed));
  
  
  
     for (i = 0; i < k; i++) {
            printf("%s (%d)\n", wordsu[i], strlen(wordsu[i]));
        }

        maxs = fn_max(wordsu, k);

        printf("\tvotre score est %d .\n", maxs);
  
  
   for (int i = 0; i < t; i++) {
        printf("\t%C", toupper(ch[i]));
    }

    printf("\n1-Afficher le/les mot(s) le plus long(s).\n");
    printf("2-Afficher tous les mots possibles.\n");

    do {
        printf("Votre choix = ");
        scanf("%d", &choix2);
    } while (choix2 != 1 && choix2 != 2);

    if (choix2 == 2) {
        for (int i = 0; i < l; i++) {
            printf("%s\n", truewords[i]);
        }
    } else {
        for (int i = 0; i < l; i++) {
            if (strlen(truewords[i]) == max) {
                printf("%s\n", truewords[i]);
            }
        }
    }
  
  
  
  
    } else if (choix == 3) {
        char contchoix='o';
  num_manche =1;
        while (contchoix=='o')
        
{        i = 0;
        int k1 = 0;
        int k2 = 0;


printf("\nManche %d______________________________________________________",num_manche);



        do {
            if (i % 2 == 0) {
                printf("\nj1-\t");
                scanf("%s", chu1);
                existe = fn_existe(truewords, l, chu1);

                if (existe == 1 && (strlen(chu1) == max)) {
                    printf("Vous gagnez! Le mot que vous avez saisi est correct et est le plus long!\n");
                    strcpy(wordsu1[k1], chu1);
                    k1++;
                } else if (existe == 1) {
                    if (fn_existe(wordsu1, k1, chu1)) {
                        printf("Le mot qui vous avez saisi est correct mais vous l'avez deja tape!\n");
                    } else if (fn_existe(wordsu2, k2, chu1)) {
                        printf("Le mot gui vous avez saisi a deja ete introduitpar j2!\n");
                    } else {
                        printf("le mot qui vous avez saisi est correct mais n'est pas le plus long.\n");
                        strcpy(wordsu1[k1], chu1);
                        k1++;
                    }
                } else {
                    printf("le mot qui vous avez saisi est incorrect!\n");
                }
            } else {
                printf("\nj2-\t");
                scanf("%s", chu2);
                existe = fn_existe(truewords, l, chu2);

                if (existe == 1 && (strlen(chu2) == max)) {
                    printf("Vous gagnez! Le mot que vous avez saisi est correct et est le plus long!\n");
                    strcpy(wordsu2[k2], chu2);
                    k2++;
                } else if (existe == 1) {
                    if (fn_existe(wordsu2, k2, chu2)) {
                        printf("Le mot qui vous avez saisi est correct mais vous l'avez deja tape!\n");
                    } else if (fn_existe(wordsu1, k1, chu2)) {
                        printf("Le mot qui vous avez saisi a deja ete introduitpar j1!\n");
                    } else {
                        printf("le mot qui vous avez saisi est correct mais n'est pas le plus long.\n");
                        strcpy(wordsu2[k2], chu2);
                        k2++;
                    }
                } else {
                    printf("le mot qui vous avez saisi est incorrect!\n");
                }
            }

            i++;
        } while (i <= t && ((existe == 1 && (strlen(chu) < max)) || !existe) || (choix == 2 && timepassed));

        printf("\nJ1_\n");

        for (i = 0; i < k1; i++) {
            printf("%s (%d)\n", wordsu1[i], strlen(wordsu1[i]));
        }

        maxs1 = fn_max(wordsu1, k1);

        printf("\tLe score de J1 est %d .\n", maxs1);
        printf("\nJ2_\n");

        for (i = 0; i < k2; i++) {
            printf("%s (%d)\n", wordsu2[i], strlen(wordsu2[i]));
        }

        maxs2 = fn_max(wordsu2, k2);

        printf("\tLe score de J2 est %d .\n", maxs2);
   



    for (int i = 0; i < t; i++) {
        printf("\t%C", toupper(ch[i]));
    }

    printf("\n1-Afficher le/les mot(s) le plus long(s).\n");
    printf("2-Afficher tous les mots possibles.\n");

    do {
        printf("Votre choix = ");
        scanf("%d", &choix2);
    } while (choix2 != 1 && choix2 != 2);

    if (choix2 == 2) {
        for (int i = 0; i < l; i++) {
            printf("%s\n", truewords[i]);
        }
    } else {
        for (int i = 0; i < l; i++) {
            if (strlen(truewords[i]) == max) {
                printf("%s\n", truewords[i]);
            }
        }
    }


if (maxs1==maxs2)
{
    printf("egales");
}
else


{    printf(maxs1>maxs2?"j1":"j2");
    printf(" a remporte la manche %d\n\n",num_manche);}

do  {  printf("vous voulez continuer? Repondez par 'o si oui et 'n' sinon = ");
     scanf(" %c",&contchoix);



}while (contchoix!='o'&&contchoix!='n'&&contchoix!='O'&&contchoix!='N');

if(contchoix=='o')
{
    num_manche++;
}
 }

}
    return 0;
}
