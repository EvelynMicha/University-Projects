#include <stdio.h>

int main()
{
system ("chcp 1253");		
	
int a,b,c;
int c11,c12,c21,c22,c31,c32;

printf("Δώσε μου τρεις αριθμούς:\n");
printf("a = ");
scanf("%d",&a);
printf("b = ");
scanf("%d",&b);
printf("c = ");
scanf("%d",&c);

c11 = (a>b) ? 1 : 0;
c12 = (a>c) ? 1 : 0;
c21 = (b>a) ? 1 : 0;
c22 = (b>c) ? 1 : 0;
c31 = (c>a) ? 1 : 0;
c32 = (c>b) ? 1 : 0;
      
(c11 && c12) ? printf("Ο πρώτος αριθμός (a = %d) είναι μεγαλύτερος!",a):  
(c21 && c22) ? printf("Ο δεύτερος αριθμός (b = %d) είναι μεγαλύτερος!",b) : 
(c31 && c32) ? printf("Ο τρίτος αριθμός (c = %d) είναι μεγαλύτερος!",c) : 
printf("Όλοι οι αριθμοί είναι ίσοι!");
    
return 0;
}
