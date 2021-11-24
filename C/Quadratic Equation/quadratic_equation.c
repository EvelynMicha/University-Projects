#include <stdio.h>
#include <math.h>
int main()
{
	int a,b,c,D;
	system ("chcp 1253");
	printf("Εισάγετε τους τρεις συντελεστές της δευτεροβάθμιας εξίσωσης:\n");
	printf("a = ");
	scanf("%d",&a);
	printf("b = ");
	scanf("%d",&b);
	printf("c = ");
	scanf("%d",&c);
	   
	if (a==0)
	{
		if(b != 0) {
			float x1=-c/b;
			printf("Η ρίζα της εξίσωσης είναι η x1 = %.2f\n",x1);	
		}else if(c != 0) {
			printf("Η εξίσωση είναι αδύνατη.");
		}else {
			printf("Η εξίσωση είναι αόριστη.");
		}
	}
	else
	{
		D=b*b-4*a*c;
		if (D<0) {
			printf("Η εξίσωση είναι αδύνατη.");
		}else if (D>0) {
			float x1=(-b+sqrt(D))/2*a;
			float x2=(-b-sqrt(D))/2*a;
			printf("Η 1η ρίζα της εξίσωσης είναι η x1 = %.2f\n",x1);
			printf("Η 2η ρίζα της εξίσωσης είναι η x2 = %.2f",x2);	
		}else {
			float x1=(b/a)/2;
			printf("Η εξίσωση είναι ταυτότητα άρα έχει διπλή ρίζα, την x = %.2f",x1);
		}
	}
	return 0;
}
