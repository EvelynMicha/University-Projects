#include <stdio.h>
#define pi 3.14
int main(int argc, int **argv){

 float m,e1,o1,e2,o2;
 system ("chcp 1253");
 printf("Δώσε μήκος της ακμής σε μέτρα: ");
 scanf("%f",&m);
 e1 = 6 * (m * m);
 o1 = m * m * m;
 e2 = 4 * pi * (m * m);
 o2 = (4 * pi * (m * m * m))/3;
 printf("Εμβαδόν κύβου: %f\n",e1);
 printf("Όγκος κύβου: %f\n",o1);
 printf("Εμβαδόν σφαίρας: %f\n",e2);
 printf("Όγκος σφαίρας: %f\n",o2);

return 0;;

}
