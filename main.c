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
 
int fn_max(char list [50][50],int length)
 {
   int  max=  0;
     for ( int i = 0; i <length ; i++)
     {
         if (max<strlen(list[i]))
         {
           max=strlen(list[i]);
         }   
     }  
     return max;
     }

int main() {
    //for timer y abir 
        clock_t begin;
        double time_spent;
    
    
     FILE *file;
    int choix,choix2, t, indexv, indexc,timepassed;
    char Tab[9], chu[50], ch[50] = "",altch[50] = "",word[50]="",truewords[50][50],wordsu[50][50];
    int ok, existe,existe2;
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
    for ( int i = 0; i < t; i++)
    {
            printf("\t%C", toupper(ch[i]));
    } 
      file = fopen("C:/Users/houssem/Desktop/hossabir/dictionnaire.txt", "r");
    if (file == NULL) {
        printf("Fichier introvable\n");
        return 1;
    }
     int i;
     int l=0;
        
     while (fscanf(file, "%s", word)
            != EOF) {
         ok=1;
         i=0;
        altch[0] = '\0'; 
         strcat(altch, ch);
    
        while(i< strlen(word)&&ok==1){
        int j=0;
            existe=0;
            while(j< strlen(altch)&& existe==0) {
        if (word[i] == altch[j]) {
           existe=1;
           for (int k=j ; k<strlen(altch);k++)
           {
               altch[k]=altch[k+1];
           }
           altch[strlen(altch)-1]='\0';
        } 
      
      j++;
    }
    if(existe == 0)
       {
           ok= 0;
       }   
     i++;
     } 
      if (ok==1)
     {
               strcpy(truewords[l], word);
       l++;
     }
    }
   int  max=fn_max(truewords,l);

i=1 ; 
int  k=0; 
 begin = clock();

do
{

if (choix==1||choix==2)

{  printf("\n%d-\t",i);   scanf("%s", chu);  
if (choix==2)
{
    	 time_spent = (double)(clock() - begin) / CLOCKS_PER_SEC;
         if (time_spent>=t*t)
         {
           timepassed=1;
         }         
}
}
 existe=fn_existe(truewords,l,chu);

 
if (existe==1&&(strlen(chu)==max))
{
       printf("Vous gagnez! Le mot que vous avez saisi est correct et est le plus long!\n");
     strcpy(wordsu[k], chu);
     k++;
}else if(existe==1)
{
    printf("le mot qui vous avez saisi est correct mais n'est pas le plus long.\n");
    strcpy(wordsu[k], chu); 
    k++;
}
else{
        printf("le mot qui vous avez saisi est incorrect!\n");
}
i++;
} while (i<=t&&((existe==1&&(strlen(chu)<max))||!existe
)||(choix==2&&timepassed));
    for ( i = 0; i < k; i++)
    {
       printf("%s (%d)\n",wordsu[i],strlen(wordsu[i]));
    }

     int maxs=fn_max(wordsu,k);
    printf("\tvotre score est %d .\n",maxs);
        for ( int i = 0; i < t; i++)
    {
            printf("\t%C", toupper(ch[i]));
    }    
    printf("\n1-Afficher le/les mot(s) le plus long(s).\n");
    printf("2-Afficher tous les mots possibles.\n");
    do {
        printf("Votre choix = ");
        scanf("%d", &choix2);
    } while (choix2 !=1 && choix2!=2);
if (choix2==2)
{
   for (int i = 0; i < l; i++)
{
       printf("%s\n",truewords[i]);
} 
}else
{
    for (int i = 0; i < l; i++)
{
    if (strlen(truewords[i])==max)
    {
        printf("%s\n",truewords[i]);
    }  
}


}
return 0;
}