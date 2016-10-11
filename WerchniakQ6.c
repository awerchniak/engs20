#include <stdio.h>
#include <string.h>
#define MAXNAME 50
#define MAXCOUNTRY 10

typedef struct {
   char name[MAXNAME];    /* country name */
   int population;        /* population in million */
} country_t;

void newCountry(country_t mylist[], int *n);
void printCountries(country_t mylist[], int numCountries);
void addCountry(country_t mylist[], int *n, char name[], int size);

int main(void) {
   country_t list[MAXCOUNTRY]; /* array of structures to hold countries */
   char findname[MAXNAME];     /* country name to be searched for */
   int add, found, i;
   int n = 0;	/* country counter - counts how many countries are stored */

   strcpy(list[0].name, "Germany");
   list[0].population = 81; 
   n = 1;
   
   addCountry(list, &n, "India", 1251);
   addCountry(list, &n, "USA", 316);
   addCountry(list, &n, "Canada", 35);
   
   printf("Enter country name: ");
   scanf("%s", findname);
   
   found = 0;
   for (i = 0; i < n; i++) { 
      if (strcmp(list[i].name, findname) == 0) {
         found = 1;
         printf("The population of %s is ", findname);
         printf("%d million.\n", list[i].population);
      }
   }
   if (!found) {
      printf("Country not found, try again.\n");
      printf("Valid countries are:\n"); 
      printCountries(list, n); 
      printf("Would you like to add a country to the list? ");
      printf("Please enter 1 for yes or 0 for no. ");
      scanf("%d", &add);
      if (add) {
      	newCountry(list, &n);
      	printCountries(list, n);
      }     
   }
   return(0);
}


/* This functions asks the user for input, adds a new 
   country (name and its population) to the 
   array mylist[] and increases the country counter 
   numCountries by 1. */
void newCountry(country_t mylist[], int *numCountries)
{
	/* Declare variables */
	char name[MAXNAME];
	int pop;
	
	/* Get country name from user */
	printf("Enter the name of your new country: ");
	scanf("%s", name);
	
	/* Get population from user */
	printf("Enter the population (in millions) of your new country: ");
	scanf("%d", &pop);
	
	/* Copy the name and population to the new country */
	strcpy(mylist[*numCountries].name, name);
	mylist[*numCountries].population = pop;
	
	/* Increment the number of countries */
	(*numCountries)++;
}


/* This functions prints the names and populations of all 
   countries stored in the array passed to the function. */
void printCountries(country_t mylist[], int numCountries)
{
	/* Declare your counter */
	int i;
	
	/* Print name & population of countries 0-numCountries-1 */
	for(i=0; i<numCountries; i++){
		printf("%s\n", mylist[i].name);
		printf("\tPopulation: %d million\n", mylist[i].population);
	}
} 

/* This function adds the new country information passed into it
   to the array and increases the country counter by 1. 
   mylist[] is the list of countries, numCountries is the country 
   conter, name is the name of the new country, and size is the
   population of the new country. */
   
void addCountry(country_t mylist[], int *numCountries, char name[], int size)
{
	/* Copy the name & population of the new country, increment numCountries */
	strcpy(mylist[*numCountries].name, name);
	mylist[*numCountries].population = size;
	(*numCountries)++;
}


//output
/*
engs20-4:~/engs20/workspace$ WerchniakQ6
Enter country name: China
Country not found, try again.
Valid countries are:
Germany
	Population: 81 million
India
	Population: 1251 million
USA
	Population: 316 million
Canada
	Population: 35 million
Would you like to add a country to the list? Please enter 1 for yes or 0 for no. 1
Enter the name of your new country: China
Enter the population (in millions) of your new country: 1400
Germany
	Population: 81 million
India
	Population: 1251 million
USA
	Population: 316 million
Canada
	Population: 35 million
China
	Population: 1400 million
	
engs20-4:~/engs20/workspace$ WerchniakQ6
Enter country name: USA    
The population of USA is 316 million.
*/