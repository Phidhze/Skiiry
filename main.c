

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int
main ()
{



// Initialisation, on demande C  l'utilisateur les membres de la multiplication

  int nbr1, nbr2, nbr12, nbr22;

  printf ("Entrer le premier entier facteur de la multiplication :\n");
  scanf ("%d", &nbr1);
  nbr12 = nbr1;
  printf ("Entrer le second entier facteur de la multiplication :\n");
  scanf ("%d", &nbr2);
  nbr22 = nbr2;

// On cherche C  sC)parer les chiffres composants les facteurs
// Et on souhaite prendre connaissance du nombre de chiffres composants chacun de ces facteurs

  int nbrDeci1, i, tempo, nbrDeci2;
  int nombre1[100];
  int nombre2[100];


  nbrDeci1 = 0;
  i = 0;


  while (nbr12 != 0)
    {
      i++;
      tempo = nbr12 % 10;
      nbr12 = (nbr12 - tempo) / 10;

      nombre1[i] = tempo;
      nbrDeci1++;

    }


// On fait de meme for le second facteur

nbrDeci2 = 0;
i = 0;
tempo = -1;

while (nbr22 !=0 )
{    
    i++;
    tempo = nbr22 % 10;
    nbr22 = (nbr22 - tempo)/10;

    nombre2[i] = tempo;
    nbrDeci2++;

}


// On va renverser les tableaux nombre1[] et nombre2[] pour que les nombres soient a l'endroit

int nombre1_renverse[100];
int j;

for (i=nbrDeci1, j=1 ; i>=1; i--, j++)
    nombre1_renverse[j]=nombre1[i];

for(i=1; i <= nbrDeci1; i++)
    nombre1[i]=nombre1_renverse[i];


int nombre2_renverse[100];

for (i=nbrDeci2, j=1 ; i>=1; i--, j++)
    nombre2_renverse[j]=nombre2[i];

for(i=1; i <= nbrDeci2; i++)
    nombre2[i]=nombre2_renverse[i];


// On effectue les multipications individuelles de chacun des chiffres des facteurs

int unite, dizaine;
int tableau[100][100][2];           // La troisième dimension du tableau sert a différencier les dizaines des unités

for (i = 1; i <= nbrDeci1; ++i)
{
    for (j = 1; j <= nbrDeci2; ++j)
    {
        tempo = nombre1[i] * nombre2[j];
        if (tempo > 9)
        {
            unite = tempo % 10;
            dizaine = (tempo - unite)/10;
            tableau[i][j][2] = dizaine;
            tableau[i][j][1] = unite;
        }
        else
        {
            tableau[i][j][2] = 0;
            tableau[i][j][1] = tempo;
        }
    }
}


// On effectue maintenant l'addition des résultats obtenus en diagonales selon le principe des jalousies

int nbrDeciResult, place1, place2;
int tabRetenues[200];
int tabResult[200];

nbrDeciResult = nbrDeci1 + nbrDeci2;

for (i = 0; i <= nbrDeciResult-1; ++i)
{
    tempo = 0;
    for (j = 0; j <= i; ++j)
    {
        if (nbrDeci1-j > 0)
        {
            place1 = nbrDeci1-j;
        }
        else
        {
            place1 = 0;             // Lorsque l'indice passe dans les négatifs, il n'existe plus pour le tableau nombre1 donc on le bloque à 0
        }                           // qui n'a auparavant pas été initialisé ce qui fait que nombre1[0][k] (avec k n'importe quel nombre < à nbrDeci2
                                    // est toujours = à 0 CEPENDANT cela pose des problèmes avec les dizaines des nombres précédents
                                    // et on réglera ce problème lors de l'ajout des dizaines

        if (nbrDeci2-(i-j) > 0)
        {
            place2 = nbrDeci2-(i-j);
        }
        else
        {
            place2 = 0;
        }

        tempo += tableau[place1][place2][1];
    
        if (j > 0 && j < nbrDeci1+1)        // c'est ici que l'on règle notre précédent problème, en ajoutant les dizaines que pour les nombres voulus
        {
            tempo += tableau[place1+1][place2][2];
        }
    }


// ici on enregistre dans le tableau (en marquant la séparation des dizaines et unités)

    if (i+1 > 1)
    {
        tabResult[i] = (tempo + tabRetenues[i]) % 10 ;
        tabRetenues[i+1] = ((tempo + tabRetenues[i]) - tabResult[i])/10;
    }
    else if (i+1 == 1)
    {
        tabResult[i] = tempo % 10;
        tabRetenues[i+1] = (tempo - tabResult[i])/10;
    }

}

// On renverse le tableau résultat et celui des retenues 
// (plus élégant et nous facilitera la tache dans l'affichage)

int tabResult_renverse[100];
int tabRetenues_renverse[100];

for (i=nbrDeciResult-1, j=0 ; i>=0; i--, j++)
    tabResult_renverse[j]=tabResult[i];

for(i=0; i <= nbrDeciResult-1; i++)
    tabResult[i]=tabResult_renverse[i];


for (i=nbrDeciResult-1, j=0 ; i>=0; i--, j++)
    tabRetenues_renverse[j]=tabRetenues[i];

for(i=0; i <= nbrDeciResult-1; i++)
    tabRetenues[i]=tabRetenues_renverse[i];




// La partie la plus délicate, l'affichage du tableau
// Chaque paragraphe représente une ligne affichée, hors for la boucle principale
// Certains "0" inutiles comme ceux des retenues sont supprimés de l'affichage


// Ligne 1 de l'affichage du tableau

printf("      ");
for (i = 1; i <= nbrDeci1; ++i)
{
    printf("%d   ", nombre1[i]);
}
printf("      X\n");

// Ligne 2 de l'affichage du tableau

printf("    _");
for (i = 1; i <= nbrDeci1; ++i)
{
    printf("____");
}
printf("____\n");

// Ligne 3 de l'affichage du tableau (les retenues)

printf("       ");
for (i = 0; i<= nbrDeci1-1; i++)
{
    if (tabRetenues[i] == 0)
    {
        printf("    ");
    }
    else
    {
        printf("%d   ", tabRetenues[i]);
    }
}
printf("  |\n");

// Ligne 4 de l'affichage du tableau

printf("    _");
for (i = 1; i <= nbrDeci1; ++i)
{
    printf("____");
}
if (tabRetenues[nbrDeci1] == 0)
{
    printf("    |\n");
}
else
{
    printf("  %d |\n", tabRetenues[nbrDeci1]);
}

// Ligne 5 de l'affichage du tableau

printf("   | ");
for (i = 1; i<= nbrDeci1; ++i)
{
    if (tableau[i][1][2] == 0)
    {
        printf("  / ");
    }
    else
    {
        printf("%d / ", tableau[i][1][1]);
    }
}
printf("|   |  %d\n", nombre2[1]);

// Ligne 6 de l'affichage du tableau

printf("   | ");
for (i = 1; i <= nbrDeci1; ++i)
{
    printf("/ %d ", tableau[i][1][1]);
}
if (tabRetenues[nbrDeci1+1] == 0)
{
    printf("|   |\n");
}
else
{
    printf("| %d |\n", tabRetenues[nbrDeci1+1]);
}

// Il s'agit ici de la boucle principale
// Ici on écrit les lignes deux par deux (pour le cas avec le résultat à gauche
// et le cas avec la retenue à droite)


for (i = 2; i <= nbrDeci2; ++i)
{
    printf(" %d | ", tabResult[i-2]);
    for (j = 1; j <= nbrDeci1; ++j)
    {
        if (tableau[j][i][2] == 0)
        {
            printf("  / ");
        }
        else
        {
            printf("%d / ", tableau[j][i][2]);
        }
    }
    printf("|   |  %d\n", nombre2[i]);

    printf(" / | ");
    for (j = 1; j <= nbrDeci1; ++j)
    {
        printf("/ %d ", tableau[j][i][1]);
    }
    if (nbrDeci1+i <= nbrDeciResult)
    {
        if (tabRetenues[nbrDeci1+i] == 0)
        {
            printf("|   |\n");
        }
        else
        {
            printf("| %d |\n", tabRetenues[nbrDeci1+i]);
        }
    }
    else
    {
        printf("|   |\n");
    }
}

// Ligne sous le tableau pour le fermer

printf(" %d  ‾", tabResult[nbrDeci1]);
for (i = 1; i <= nbrDeci1; ++i)
{
    printf("‾‾‾‾");
}
printf("\n");

// Dernière ligne de l'affichage

printf("  ");
for (i = nbrDeci2; i <= nbrDeciResult-1; i++)
{
    printf("/ %d ", tabResult[i]);
}
printf("\n");



// pour finir on affiche le résultat (que l'on a mis dans une variable)

int resultat;

resultat = 0;

for (i = 0, j = nbrDeciResult-1; i < nbrDeciResult; i++, j--)
{
    if (j>0)
    {
            resultat += tabResult[i]*pow(10,(j));
    }
    else if (j==0)
    {
        resultat += tabResult[i];
    }
}

printf("\n");
printf("Le calcul de %d par %d est égal à ", nbr1, nbr2);

for (i = 0; i <= nbrDeciResult-1; i++)
    printf("%d", tabResult[i]);


printf(" (%d x %d = ", nbr1, nbr2);

for (i = 0; i <= nbrDeciResult-1; i++)
    printf("%d", tabResult[i]);
   
printf(")\n");



return 0;

}
