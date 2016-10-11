/* Last letter word game
 * Created by Andy Werchniak, 4/15/2015 */

/* include i/o. string, and standard libraries*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* define maximum constraints to precompiler*/
#define STRLEN 50
#define WORDLEN 100
#define MAXPLAYERS 10
#define MAXWORDS 500

/* define structures for players and words */
typedef struct{
	char playerName[STRLEN];
	int score;
} player_t;

typedef struct{
	char word[WORDLEN];
	int repeat;
	int stump;
	int word_num;
} word_t;

/* declare functions */
int countString(char*);
char* upperCase(char*);
void sortArray(int *, word_t*, const int);
void game(int, player_t*, word_t *, int *, int);

/* main function includes the bulk of the I/O */
void main(void)
{
	/* define variables, arrays, and pointers relavent to entire code*/
	int numPlay, i, turnCount;
	char character;
	char category[STRLEN];
	player_t players[MAXPLAYERS];
	word_t words[MAXWORDS];
	FILE *loadGame;
	
// opening menu
	/* define variables, arrays, and pointers relevant to the opening menu */
	int finished;
	char saveName[STRLEN];
	char choice, dig;
	char gameName[STRLEN];
	
	/* Print menu options and get user's choice 
	 * Ensures that user enters a pertinent value using while loops & if conditions */
	printf("\nWelcome to the game!\n");
	printf("Enter 1 to start a new game.\n");
	printf("Enter 2 to load a previous game.\n");
	printf("Enter 3 to quit.\n");
	
	/* Flags for the loops to scan UI */
	int flag = 1;
	int flag2 = 1;
	
	while(flag)
	{
		scanf("%c", &choice);
		if(choice=='1' || choice=='2' || choice=='3')
			flag = 0;
		else{
			if(choice==10)
				printf("Please enter a valid number. ");
			while(flag2)
			{
				scanf("%c", &dig);
				if(dig==10)
				{
					flag2 = 0;
					printf("Please enter a valid number. ");
				}
			}
		}
	}
	
	/* Define variables relavent to switch statement */
	int cease = 0;
	char choice2;
	int needNewPlay;
	
	switch (choice) {
		/* If the user enters one, start a new game */
		case '1':
			/* Prompt the user where to save the file 
			 * If it already exists, ask the user to overwrite it */
			while (!cease){
				printf("Enter the name of the file you would like to save to: ");
				scanf("%s", saveName);
			
				if(fopen(saveName, "r") != NULL){
					printf("Warning: File already exists. Would you like to overwrite it?\n");
					printf("Enter y or n: ");
					
					do{
						scanf("%c", &choice2);
					} while (choice2!='y' && choice2!='n');
					
					if(choice2=='y')
						cease = 1;
							
				} else cease = 1;
			}
			
			printf("\nNew game.\n");
			/* Get the category from the user */
			printf("Enter the category: ");
			scanf("%s", category);
			
			/* not finished (continue), and still need to prompt for new players */
			needNewPlay = 1;
			finished = 0;
			break;
		/* If the user enters 2, load a previous game */
		case '2':
			/* Get the name of the file from the user 
			 * check if it's too long and if it exists */
			do{
				printf("Enter the filename you would like to load: ");
				scanf("%s", gameName);
				
				if(countString(gameName)>STRLEN)
					printf("Error! Filename too long. Please enter less than %d characters.\n", STRLEN);
					
				if(fopen(gameName, "r") == NULL)
					printf("Error! File does not exist.\n");
					
			} while (fopen(gameName, "r") == NULL && countString(gameName)<=STRLEN);
			
			/*Open the saved file for reading*/
			loadGame = fopen(gameName, "r");
			
			/*scan the category and the number of players from the file */
			fscanf(loadGame, "%s", category);
			fscanf(loadGame, "%d", &numPlay);
	
			/* Scan the player names and their scores */
			for(i=0; i<numPlay; i++){
				fscanf(loadGame, "%s %d", players[i].playerName, &players[i].score);
		
				/* Buffer the commas in between */
				if(i != numPlay-1){
					do{
						fscanf(loadGame, "%c", &character);
					}while(character != ',');
				}
			}
	
			/* Buffer last character */
			fscanf(loadGame, "%c", &character);
	
			/* Scan the words/stumps and count the number of turns */
			turnCount=-1;
			do{
				turnCount++;
				fscanf(loadGame, "%s%d", words[turnCount].word, &words[turnCount].stump);
			}while(words[turnCount].word[0] != '\0');
	
			/* Close the file */
			fclose(loadGame);
			
			/* Prompt the user where to save the file 
			 * If it already exists, ask to override it */
			while (!cease){
				printf("Enter the filename you would like to save to: ");
				scanf("%s", saveName);
			
				if(fopen(saveName, "r") != NULL){
					printf("Warning: File already exists. Would you like to overwrite it?\n");
					printf("Enter y or n: ");
					
					do{
						scanf("%c", &choice2);
					} while (choice2!='y' && choice2!='n');
					
					if(choice2=='y')
						cease = 1;
							
				} else cease = 1;
			}
			
			/* not finished, and don't need new players */
			finished = 0, needNewPlay=0;
			
			/* Print the details from the loaded game */
			printf("\nWelcome back!\n");
			printf("The category is %s.\n", category);
			printf("Scores:\n");
			for(i=0; i<numPlay; i++)
				printf("%s: %d ", players[i].playerName, players[i].score);
			printf("\n");
			printf("Words played:\n");
			for(i=0; i<turnCount; i++)
				printf("%s\n", words[i].word);
			break;
			
		/* If the user enters 3, the game quits */
		case '3':
			finished = 1;
			printf("Have a nice day!\n");
			break;
			
		default:
			printf("An error has occurred.\n");
			
	}

//get new players
	/* declare variables relavent to this portion */
	int j, stop;
	char junk;
	char dummyString[STRLEN];
	
	/* Proceed if the game is not finished and players have not been entered */
	if(!finished && needNewPlay){
		/* Get the number of players between 1-10, buffer any other junk */
		do{
			printf("Enter the number of players (between 1-10): ");
			scanf("%d", &numPlay);
			
			do{
				scanf("%c", &junk);
			} while(junk != '\n');
			
		} while(numPlay<1 || numPlay >MAXPLAYERS);
	
		/* Enter each player's name */
		for(i=0;i<numPlay;i++)
		{
			printf("Player %d\n", (i+1));
			stop = 0;
		
			/* Must scan each individual character so that
			 * it will still read if the user presses enter */
			while(!stop){
				printf("Enter player name: ");
				scanf("%c", &character);
				j=0;
				while(character !='\n' && j<STRLEN){
					dummyString[j]=character;
					j++;
					scanf("%c", &character);
				}
				dummyString[j]='\0';
			
				/* Check to make sure the array is not too long */
				if(j>=STRLEN)
					printf("Please enter a string shorter than %d characters.\n", STRLEN);
				else{
					stop = 1;
				
					/* Declare the string */
					players[i].playerName[STRLEN];
			
					/* If the user presses enter, assign the default name
					 * append A, B, C, etc. to the end, depending on which number player */
					if(dummyString[0]=='\0'){
						strcpy(players[i].playerName, "Player ");
						players[i].playerName[6]=i+65;
					} else strcpy(players[i].playerName, dummyString);
				}
				
			/* Assign all initial scores to 0 */			
			players[i].score=0;
			
			}
		}
	}
	
// Call the game function only if the user has not quit
	
	if (!finished)
		game(numPlay, players, words, &turnCount, needNewPlay);

// Save the game
	/* If the game is done and the user did not quit the menu, continue */
	if (!finished){
		/* Open the file for writing */
		FILE *saveFile;
		saveFile = fopen(saveName, "w");

		// Print the category
		for(i=0; i<countString(category); i++)
			fprintf(saveFile, "%c", category[i]);
	
		// Print the number of players
		fprintf(saveFile, "\n%d\n", numPlay);
	
		// Print each player's name and score
		for(i=0; i<numPlay; i++)
		{
			fprintf(saveFile, "%s", players[i].playerName);
			fprintf(saveFile, " %d", players[i].score);
			if(i!=numPlay-1)
				fprintf(saveFile, ", ");
		}
		fprintf(saveFile, "\n");
	
		// Print each word & whether it was a stump
		for(i=0; i<turnCount; i++)
		{
			fprintf(saveFile, "%s", words[i].word);
			fprintf(saveFile, " %d \n", words[i].stump);
		}

		fclose(saveFile);
	}
}

//functions

/* Function to count the number of elements in a string */
int countString(char *string)
{
	int i=0;
	
	while(string[i]!='\0')
		i++;
		
	return(i);
}

/* Function to change all characters in a string to uppercase */
char* upperCase(char *string)
{
	int i, size;
	
	size = countString(string);
	
	for(i=0;i<size;i++){
		if(string[i]>=97 && string[i]<=122)
			string[i]-=32;
	}
	
	return(string);
}

/* Bubble sort function to alphabetize entries */
void sortArray(int *sort, word_t *words, const int turnCount)
{
	int store, i, j;
	
	/* Initialize entries in the sort array */
	for(i=0; i<turnCount; i++)
		sort[i]=i;
		
	/* Compare adjacent entries letter by letter */
 	for (j=0; j<turnCount-1;j++){
     	for(i=0; i<turnCount-1; i++){
	  		if(strcmp(upperCase(words[sort[i]].word), upperCase(words[sort[i+1]].word))>0){
   	    		store = sort[i];
 	    		sort[i] = sort[i+1];
 	    		sort[i+1] = store;
 	    	}
	 	}
   	}
}

/* Function for the game */
void game(int numPlay, player_t *players, word_t *words, int *turnCount, int needNewPlay)
{
	/* Declare variables and arrays */
	int done = 0;
	int i, j, already, length, stump, stumpCount;
	char inCategory, choice, junk;
	int sort[MAXWORDS];
	word_t stumps[MAXWORDS];
	
	/* Declare and initialize the array to test if the user enters 'stump' */
	char stumpTest[5];
	strcpy(stumpTest, "stump");
	
	/* Get the first word only if its a new game */
	if (needNewPlay){
		printf("Enter the word to start with: ");
		scanf("%s", words[*turnCount].word);
		
		(*turnCount)++;
	}
	
	/* Loop the game until the user quits*/
	while(!done)
	{
		printf("\n");
		
		/* Ask each player to enter a word every round */
		for(i=0; i<numPlay; i++)
		{
			stump = 1;
			
			/* Get the word from the player */
			printf("%s, enter your word (if you're stumped, type 'stump'): ", players[i].playerName);
			scanf("%s", words[*turnCount].word);
			scanf("%c", &junk);
			
			/* Check if it's a stump based on the last word */
			length = countString(words[(*turnCount)-1].word);
			
			if(upperCase(words[*turnCount].word)[0] == upperCase(words[(*turnCount)-1].word)[length-1])
				stump = 0;
			else words[*turnCount-1].stump = 1;
			
			if(strcmp(upperCase(words[*turnCount].word), upperCase(stumpTest))==0){
				stump = 1;
				words[*turnCount-1].stump = 1;
			}

			/* Check if the word has already been played */
			already = 0;
			for(j=0; j<*turnCount; j++)
			{
				if(strcmp(upperCase(words[j].word), upperCase(words[*turnCount].word))==0)
					already = 1;
			}
			
			/* Check if the word is in the category */
			if(strcmp(upperCase(words[*turnCount].word), upperCase(stumpTest))!=0){
				printf("Other players, is this word within the given category (y or n): ");
				scanf("%c", &inCategory);
				scanf("%c", &junk);
			}
			
			if(inCategory != 'y'){
				words[*turnCount-1].stump = 1;
				stump = 1;
			}

			/* Award 5 points for good, 3 points for already, -1 point for stump or not in category */
			if(stump == 0 && already != 1)
				players[i].score += 5;
			if(stump == 0 && already == 1)
				players[i].score += 3;
			if(stump != 0)
				players[i].score -= 1;

			if(stump == 0)
				(*turnCount)++;
		}
		
		/* Print the scores*/
		printf("\nEnd of turn.\n");
		
		printf("Scores:\n");
		for(i=0; i<numPlay; i++)
			printf("%s: %d ", players[i].playerName, players[i].score);
		
		/* Prompt the user for what to do */
		printf("\n\nSimply press enter to continue, or\n");
		printf("Enter 1 to view words in order played\n");
		printf("Enter 2 to view words in alphabetical order\n");
		printf("Enter 3 to view all stumps (in alphabetical order)\n");
		printf("Enter 4 to save & quit\n");
		
		int flag = 1;
		int flag2 = 1;
	
		/* Get the user's choice, only accept valid entries*/
		while(flag)
		{
			scanf("%c", &choice);
			
			if(choice=='1' || choice=='2' || choice=='3' || choice =='4' || choice == '\n')
				flag = 0;
			else{
				if(choice==10)
					printf("Please enter a valid number. ");
				while(flag2)
				{
					scanf("%c", &junk);
					if(junk==10)
					{
						flag2 = 0;
						printf("Please enter a valid number. ");
					}
				}
			}
			
		}

		switch(choice){
			/* If the user presses enter, simply continue */
			case '\n':
				break;
			/* If the user enters 1, print the words in order played */
			case '1':
				for(i=0; i<*turnCount; i++)
					printf("%s\n", words[i].word);
				break;
			/* If the user enters 2, print the words in alphabetical order 
			 * Only print repeated entries once */
			case '2':
				/* Sort into alphabetical order */
				sortArray(sort, words, *turnCount);
				printf("%s\n", words[sort[0]].word);		//print the first entry, since the loop has to start at 1
				for(i=1; i<*turnCount; i++){
					already = 0;
					/* Since the entries are alphabetized, we only need to compare adjacent ones */
					if(strcmp(words[sort[i]].word, words[sort[i-1]].word)==0)
						already = 1;
					
					if(!already)
						printf("%s\n", words[sort[i]].word);
				}
				break;
			/* If the user enters 3, print the stumps in alphabetical order 
			 * Only print repeated entries once */
			case '3':
				stumpCount = 0;
				/* Make a separate array of just stumps */
				for(i=0; i<*turnCount; i++){
					if(words[i].stump){
						stumps[stumpCount] = words[i];
						stumpCount += 1;
					}
				}	
				/* Alphabetize the stumps */
				sortArray(sort, stumps, stumpCount);

				printf("%s\n", stumps[sort[0]].word);	//print the first entry, since the loop has to start at 1
				for(i=1; i<=stumpCount; i++){
					already = 0;
					
					/* Compare each entry to the first one and to the adjacent ones */
					if(strcmp(stumps[sort[i]].word, stumps[sort[i-1]].word)==0 ||strcmp(stumps[sort[i]].word, stumps[sort[0]].word)==0)
						already = 1;
					
					if(!already)
						printf("%s\n", stumps[sort[i]].word);
				}

				break;
			/* If the user enters 4, quit the game function */
			case '4':
				done = 1;
				break;
			
			/* Default option just in case */
			default:
				printf("An error has occurred.\n");
				done = 1;
		}	
		
		/* Quit the game once more words than allotted for the array are played */
		if(*turnCount >= MAXWORDS){
			done = 1;
			printf("Maximum number of word entries exceed. Saving & quitting.\n Have a nice day!\n");
		}
	}
}