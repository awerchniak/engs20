#include <stdio.h>
#include <math.h>

double cubedroot(double x);

void main(void)
{
	double num;
	printf("You best be entering a number in this bitch: ");
	scanf("%lf", &num);
	
	printf("Your cubed root is %.2lf, bitch.\n", cubedroot(num));
}

double cubedroot (double x)
{
	double root;
	
	if (x<0)
	{
		in*=-1;
		root = -pow(x, (float)1/3);
	} else
		root = pow(x, (float)1/3);
		
	return(root);
}