#include <stdio.h>
#include <math.h>
int main(int argc, char **argv){

 int A, B;
 int C, D, E, F, G, I;
 float H, K;
 system ("chcp 1253");
 printf ("Βασικές αριθμητικές πράξεις με Ακεραίους\n");
 printf ("========================================\n\n");
 printf ("Εισάγετε τον πρώτο αριθμό : ");
 scanf ("%d",&A);
 printf ("Εισαγετε το δεύτερο αριθμό :" );
 scanf ("%d", &B);
 C = A + B;
 D = A - B;
 E = A * B;
 F = A / B;
 G = A & B;
 H = (float)A / B;
 I = A * A;
 K = sqrt((float)B);
 printf ("Άθροισμα : %6d\n", C);
 printf ("Διαφορά : %6d\n", D);
 printf ("Γινόμενο : %6d\n", E);
 printf ("Πηλίκο : %6d\n", F);
 printf ("Υπόλοιπο Διαίρεσης : %6d\n", G);
 printf ("Πραγματικό Πηλίκο : %10.3f\n", H);
 printf ("Τετράγωνο πρώτου αριθμού : %6d\n", I);
 printf ("Τετραγωνική ρίζα δεύτερου αριθμού : %10.3f\n", K);

 return 0;;

}
