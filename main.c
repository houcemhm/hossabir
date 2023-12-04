#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void inputTab(int t, char Tab[50])
{

    for (int i = 0; i < t; i++)
    {
        do
        {
            printf("Caractere %d : Consonne (c/C) ou Voyelle (v/V) = ", i + 1);
            scanf(" %c", &Tab[i]);
        } while (Tab[i] != 'c' && Tab[i] != 'C' && Tab[i] != 'v' && Tab[i] != 'V');
        printf("\n");
    }
}
void generateString(char ch[50], char Tab[50], char vowels[5], char consonants[21])
{
    int index;
  //pour vider ch

    for (int i = 0; i < strlen(Tab); i++)
    {
        if (Tab[i] == 'v' || Tab[i] == 'V')
        {
            index = rand() % 5;
            strncat(ch, &vowels[index], 1);
        }
        else
        {
            index = rand() % 21;
            strncat(ch, &consonants[index], 1);
        }
    }
}
static int fn_existe(char list[35000][50], int length, char ch[50]) {
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




int fn_max(char list[35000][50], int length)
{
    int max = 0;
    for (int i = 0; i < length; i++)
    {
        if (max < strlen(list[i]))
        {
            max = strlen(list[i]);
        }
    }
    return max;
}


int processWords(FILE *file, char ch[50], char truewords[50][50])
{
    int ok, existe;
    char word[50], altch[50];
    int i, l = 0;
    file = fopen("dictionnaire.txt", "r");
    while (fscanf(file, "%s", word) != EOF)
    {

        ok = 1;//
        i = 0;
        altch[0] = '\0';
        strcat(altch, ch);

        while (i < strlen(word) && ok == 1)
        {
            int j = 0;
            existe = 0;

            while (j < strlen(altch) && existe == 0)
            {
                if (word[i] == altch[j])
                {
                    existe = 1;

                    for (int k = j; k < strlen(altch); k++)
                    {
                        altch[k] = altch[k + 1];
                    }

                    altch[strlen(altch) - 1] = '\0';
                }

                j++;
            }

            if (existe == 0)

            {
                ok = 0;
            }

            i++;
        }

        if (ok == 1)
        {
            strcpy(truewords[l], word);
            l++;
        }
    }
    fclose(file);

    return l;
}
int main()
{
    clock_t begin,begin_tentative ;
    double time_spent , time_spent_tentative ;
    FILE *file;
    int choix, choix2, t, indexv, indexc, timepassed, maxs, maxs1, maxs2, num_manche, s1, s2;
    char Tab[9], chu[50], chu1[50][50], chu2[50][50], ch[50] = "", altch[50] = "", word[50] = "", truewords[50][50], wordsu[50][50], wordsu1[50][50], wordsu2[50][50];
    int scores1[50], scores2[50];
    int ok, existe, existe2;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    char words[50][50];

    srand(time(NULL));
    printf("\t J E U        D E       M O T S\n\n");
    printf("1-Jouer a un\n");
    printf("2-Jouer a un sous une contrainte de temps\n");
    printf("3-Jouer a deux\n");
    printf("0-quitter\n");
    printf("\t\t\tvotre choix =  \n");

    do
    {
        printf("\t\t\tVotre choix = ");
        scanf("%d", &choix);

    } while (choix > 3 || choix < 0);
    if (choix == 0)
    {
        printf("\n\tau revoir, nous esperons vous voir bientot");
        return 1;
    }
    file = fopen("dictionnaire.txt", "r");
    if (file == NULL)
    {
        printf("\033[0;31mFichier introuvable\n\033[0m"); //red

        return 1;
    }
    if (choix == 1 || choix == 2)
    {
        printf("\n\n");
        printf("\033[0;34mTapez la taille (7/8/9) du mot le plus long a retrouver = \033[0m\n");
       printf("\033[0;34mTapez la taille (7/8/9) du mot le plus long a retrouver = \033[0m"); //blue color
       scanf("%d", &t);

        while (t < 7 || t > 9)
        {
            printf("\033[0;31mLa taille que vous avez saisie est erronee!\n\n\033[0m"); //red color

            printf("\x1b[34mTapez la taille (7/8/9) du mot le plus long a retrouver = \x1b[0m");

            scanf("%d", &t);
        }
        inputTab(t, Tab);
        generateString(ch, Tab, vowels, consonants);

        for (int i = 0; i < t; i++)
        {
            printf("\t%C", toupper(ch[i])); //affichage de res de generateString
        }


        int l = processWords(file, ch, truewords);//l permet de stocker les mots valides soit plus lz
      /* for (int i = 0; i < l; i++)
            {
                    printf("\n");
                    printf("%s\n", truewords[i]);

            }*/
        int max = fn_max(truewords, l);

        int i = 1;
        int k = 0;
        if (choix == 2)
            begin = clock();


        do

        { begin_tentative=clock();
            printf("\n%d-\t", i); //
            scanf("%s", chu);

            if (choix == 2)
            {
                time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;

          time_spent_tentative = (double)(clock() - begin_tentative ) / CLOCKS_PER_SEC;
                if (time_spent >= t*t )
                {
                    timepassed = 1;
                    printf("vous avez perdu car vous avez depasse le temps totale permis qui est de %fs\n",time_spent);
                 break;//break
                } else if (time_spent_tentative>= t){
                 printf("  vous avez depasse le temps permis pour une tentative qui est de %fs\n",time_spent_tentative);
                 i++;
                 continue;
            }
            }


            existe = fn_existe(truewords, l, chu);


            if (existe == 1 && (strlen(chu) == max))
            {
                if (choix == 2)
                {
                   printf("\x1b[32mVous gagnez! Le mot que vous avez saisi est correct et est le plus long.\nVous l'avez trouve en seulement %f\x1b[0m", time_spent);

              break;
                }
                else
                {
                   printf("\033[1;32mVous gagnez! Le mot que vous avez saisi est correct et est le plus long!\033[0m\n");
}

                strcpy(wordsu[k], chu);
                k++;
            }
            else if (existe == 1)
            {
                if (fn_existe(wordsu, k, chu))
                {
                    printf("\033[38;5;208mLe mot que vous avez saisi est correct mais vous l'avez déjà tape!\033[0m\n");

                }
                else
                {
                    printf("\033[38;5;208mle mot que vous avez saisi est correct mais n'est pas le plus long.\033[0m\n");

                    strcpy(wordsu[k], chu);
                    k++;
                }
            }

            else
            {
                printf("\033[31mle mot que vous avez saisi est incorrect!\033[0m\n");

            }

            i++;
        } while (i <= t && ((existe == 1 && (strlen(chu) < max)) || !existe) || (choix == 2 && !timepassed));

if (choix == 2 && timepassed)
{

  printf("passe !\n");


}





        for (i = 0; i < k; i++)
        {
            printf("%s (%d)\n", wordsu[i], strlen(wordsu[i]));
        }

        maxs = fn_max(wordsu, k);

        printf("\t\t\t tvotre score est %d .\n", maxs);

        for (int i = 0; i < t; i++)
        {
            printf("\t%C", toupper(ch[i]));
        }

        printf("\n1-Afficher le/les mot(s) le plus long(s).\n");
        printf("2-Afficher tous les mots possibles.\n");

        do
        {
            printf("\t\t\tVotre choix = ");
            scanf("%d", &choix2);
        } while (choix2 != 1 && choix2 != 2);

        if (choix2 == 2)
        {
            for (int i = 0; i < l; i++)
            {
                printf("%s\n", truewords[i]);
            }
        }
        else
        {
            for (int i = 0; i < l; i++)
            {
                if (strlen(truewords[i]) == max)
                {
                    printf("%s\n", truewords[i]);
                }
            }
        }
    }
    else if (choix == 3)
    {
        char contchoix = 'o';
        num_manche = 1;
        while (contchoix == 'o')
        {

           printf("\nMANCHE n  %d______________________________________________________\n\n", num_manche);
            do
            {
                printf("Tapez la taille (nombre pair) du mot le plus long a retrouver = ");
                scanf("%d", &t);
                if (t <= 0)
                {
                   printf("\033[1;31mLa taille que vous avez saisie ne devrait pas etre negative ou impaire!\n\n");
                  printf("\033[0m"); }
                else if (t % 2 == 1)
                {
                   printf("\033[1;31mLa taille que vous avez saisie devrait etre paire! 😡\n\n");
             printf("\033[0m");
                }
            } while (t % 2 != 0 || t <= 0);
            Tab[0]='\0';
            ch[0]='\0';
            inputTab(t, Tab);
            generateString(ch, Tab, vowels, consonants);
            for (int i = 0; i < t; i++)
            {
                printf("\t%C", toupper(ch[i]));
            }

            int l = processWords(file, ch, truewords);
              for (int i = 0; i < l; i++)
            {
                    printf("\n");
                    printf("%s\n", truewords[i]);

            }
            int max = fn_max(truewords, l);
            int i = 0;
            int k1 = 0;
            int k2 = 0;
            int rep;
            do
            {
                if (i % 2 == 0)
                {
                    printf("\nj1-\t");
                    scanf("%s", chu1);
                    existe = fn_existe(truewords, l, chu1);

                    if (existe == 1 && (strlen(chu1) == max))
                    {
                        printf("\033[1;32mVous gagnez! Le mot que vous avez saisi est correct et est le plus long! 😊\n");
                       printf("\033[0m");
                        strcpy(wordsu1[k1], chu1);
                        k1++;
                        break ;
                    }
                    else if (existe == 1)
                    {
                        if (fn_existe(wordsu1, k1, chu1))
                        {

                            printf("\033[1;33mLe mot que vous avez saisi est correct mais vous l'avez deja tape!\n");
                      printf("\033[0m");
                        }
                        else if (fn_existe(wordsu2, k2, chu1))
                        {
                            printf("\033[38;5;208mLe mot que vous avez saisi a déjà été introduit par j2!\n");
                        printf("\033[0m");
                          }
                        else
                        {
                            printf("\033[38;5;208mle mot que vous avez saisi est correct mais n'est pas le plus long.\n");
                           printf("\033[0m");
                            strcpy(wordsu1[k1], chu1);
                            k1++;
                        }

                    }
                    else
                    {
                       printf("\033[1;31mle mot que vous avez saisi est incorrect!\n");
                   printf("\033[0m");
                    }
                    rep=((existe == 1 && (strlen(chu1) < max)) || !existe);
                }
                else
                {
                    printf("\nj2-\t");
                    scanf("%s", chu2);
                    existe = fn_existe(truewords, l, chu2);

                    if (existe == 1 && (strlen(chu2) == max))
                    {
                        printf("\033[1;32mVous gagnez! Le mot que vous avez saisi est correct et est le plus long! 😊\n");
                 printf("\033[0m");
                        strcpy(wordsu2[k2], chu2);
                        k2++;
                        break;
                    }
                    else if (existe == 1)
                    {
                        if (fn_existe(wordsu2, k2, chu2))
                        {
                           printf("\033[38;5;208mLe mot que vous avez saisi est correct mais vous l'avez deja tape!\n");
                       printf("\033[0m");
                        }
                        else if (fn_existe(wordsu1, k1, chu2))
                        {
                             printf("\033[38;5;208mLe mot que vous avez saisi a déjà été introduit par j1!\n");
                       printf("\033[0m");

                        }
                        else
                        {
                            printf("\033[38;5;208mle mot que vous avez saisi est correct mais n'est pas le plus long.\n");
                       printf("\033[0m");
                            strcpy(wordsu2[k2], chu2);
                            k2++;
                        }
                    }
                    else
                    {
                        printf("\033[1;31mle mot que vous avez saisi est incorrect!\n");
                   printf("\033[0m");
                    }
                     rep=((existe == 1 && (strlen(chu2) < max)) || !existe);
                }

                i++;
            } while (i < t && rep);

            printf("\nJ1_\n");

            for (i = 0; i < k1; i++)
            {
                printf("%s (%d)\n", wordsu1[i], strlen(wordsu1[i]));
            }

            maxs1 = fn_max(wordsu1, k1);
            scores1[num_manche - 1] = maxs1;
            printf("\tLe score de J1 est %d .\n", maxs1);
            printf("\nJ2_\n");

            for (i = 0; i < k2; i++)
            {
                printf("%s (%d)\n", wordsu2[i], strlen(wordsu2[i]));
            }
            maxs2 = fn_max(wordsu2, k2);
            scores2[num_manche - 1] = maxs2;
            printf("\tLe score de J2 est %d .\n", maxs2);
            for (int i = 0; i < t; i++)
            {
                printf("\t%C", toupper(ch[i]));
            }

            printf("\n1-Afficher le/les mot(s) le plus long(s).\n");
            printf("2-Afficher tous les mots possibles.\n");

            do
            {
                printf("Votre choix = ");
                scanf("%d", &choix2);
            } while (choix2 != 1 && choix2 != 2);

            if (choix2 == 2)
            {
                for (int i = 0; i < l; i++)
                {
                    printf("%s\n", truewords[i]);
                }
            }
            else
            {
                for (int i = 0; i < l; i++)
                {
                    if (strlen(truewords[i]) == max)
                    {
                        printf("%s\n", truewords[i]);
                    }
                }
            }

            if (maxs1 == maxs2)
            {
                printf("egales");
            }
            else
            {
                printf(maxs1 > maxs2 ? "j1" : "j2");
                printf(" a remporte la manche %d\n\n", num_manche);
            }

            do
            {
                printf("vous voulez continuer? Repondez par 'o si oui et 'n' sinon = ");
                scanf(" %c", &contchoix);
            } while (contchoix != 'o' && contchoix != 'n' && contchoix != 'O' && contchoix != 'N');

            if (contchoix == 'o')
            {
                num_manche++;
            }
        }
        if (contchoix == 'n' || contchoix == 'N')
        {
            printf("\t\t\tJ1\tJ2\n");
            printf("-----------------------------------------------------------\n");
            s1 = 0;
            s2 = 0;
            int i;
            for (i = 1; i <= num_manche; i++)
            {
                s1 += scores1[i - 1];
                s2 += scores2[i - 1];
                printf("Score Manche %d\t\t%d\t%d", i, scores1[i - 1], scores2[i - 1]);
                printf("\n-----------------------------------------------------------\n");
            }
            printf("Score Final\t\t%d\t%d", s1, s2);
            printf("\n-----------------------------------------------------------\n");
            if (s1 > s2)
            {
                printf("J1 est le vainqueur!");
            }
            else if (s1 < s2)
            {
                printf("J2 est le vainqueur!");
            }
            else
            {
                printf("Egalite!");
            }
        }
    }
    return 0;
}
