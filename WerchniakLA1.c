/* Long Assignment 1
 * Encrypt quote.txt, decrypt whatIsThis.vern, or do both 
 * Andy Werchniak, 4/29/2015 */

/* Include I/O and Math functions */
#include <stdio.h>
#include <math.h>

/* Declare functions before calling them */
void shiftPad(void);
int binToDec(int bin);
int decToBin(int dec);
int xor(int bin1, int bin2);
void encrypt(void);
void decrypt(void);

/* Main function only for user input and to call other functions! */
void main(void)
{
	char choice, dig;
	int flag = 1;
	int flag2 = 1;
	
	/* Get input from the user */
	printf("Enter: \n1 to encrypt 'quote.txt' \n2 to decrypt 'whatIsThis.vern' \n3 to do both \n");
	
	/* This checks to make sure the user input valid values */
	/* It will run until the user enters 1,2,or 3 (flag then = 0) */
	/* The nested loop and the second if statement accounts for 
	 * if the user enters more than one character */
	/* It will only print the error message when the user presses enter 
	 * (ASCII value 10 on my system), to ensure it only prints once */
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

	/* Shift the values in the pad the appropriate amount before using it to decode */
	shiftPad();
	
	/* Based on the user-inputed value above, choose which function to execute */
	switch (choice) {
		case '1':
			encrypt();
			printf("\nEncrypted quote.txt!\nFile available in quote.vern.\n\n");
			break;
		case '2':
			decrypt();
			printf("\nDecrypted whatIsThis.vern!\nFile available in whatIsThis.txt.\n\n");
			break;
		case '3':
			encrypt();
			decrypt();
			printf("\nEncrypted quote.txt and decrypted whatIsThis.vern!\n\n");
			printf("Files available in quote.vern and whatIsThis.txt.\n\n");
			break;
		default:
			printf("Error!");
	}
	
}

/* The function to shift the pad before encrypting/decrypting */
void shiftPad(void)
{
	/* Open the old pad to read and write a new, decoded one */
	FILE *pad = fopen("pad2.txt", "r");
	FILE *outpad = fopen("decodedPad.txt", "w");
	char read, new;

	/* Read the entire pad and shift each character over 14 */
	/* If 14 digits over is less than the range we are using,
	 * continue from the other end */
	while(fscanf(pad, "%c", &read) != EOF)
	{
		if(read-14>=32)
		{
			new = read - 14;
			fprintf(outpad, "%c", new);
		}
		else
		{
			new = 127-(14-(read-32));
			fprintf(outpad, "%c", new);
		}
	}

	fclose(pad);
	fclose(outpad);

}

/* The function to change 'binary' numbers back to decimal */
int binToDec(int bin)
{
	int dec = 0;
	int j, remainder;
	
	/* Integer math, so division by 10 allows us to read each digit individually */
	/* Reverse of the method used in class to get binaries from decimals */
	for(j=0; j<8; j++)
	{
		remainder = bin%10;
		dec+= pow(2,j)*remainder;
		bin = bin/10;
	}
	
	return dec;
}

/* The function to change decimal numbers to 'binary' numbers */
int decToBin(int dec)
{
	int bin = 0;
	int i = 1;
	int k, remainder;
	
	/* Let the computer do the remainder method we learned in class */
	for(k=1; k<=8; k++)
	{
		remainder = dec%2;
		dec/= 2;
		bin+= i*remainder;
		i*=10;
	}
	
	return bin;
}

/* Exclusive OR function */
int xor(int bin1, int bin2)
{
	int i;
	int bin = 0;
	int power;
	
	/* Compare each digit in the 'binary' numbers individually */
	/* If both are 1 or both are 0, put zero to that digit in the output */
	/* Otherwise, put one */
	/* Able to enter digits in the integer by multiplying by each power of 10 and adding */
	for(i=0; i<=8; i++)
	{
		power = pow(10, i);
		
		if((bin1%2==1 && bin2%2==1) || (bin1%2==0 && bin2%2==0))
			bin+=0*power;
		else
			bin+=1*power;
		
		bin1/=10; bin2/=10;
	}
			
	return bin;
}

/* Function to encrypt 'quote.txt' */
void encrypt(void)
{
	char padChar, realChar, outChar;
	int padNum, realNum, outNum;
	FILE *quote = fopen("quote.txt", "r");
	FILE *pad = fopen("decodedPad.txt", "r");
	FILE *encrypted = fopen("quote.vern", "w");
	
	/* Check to make sure the file and pad exist */
	/* Read each character in the file */
	/* If statement to notify if end of pad is reached */
	/* Store binaries of character ASCII's as ints because this is less confusing */
	/* Use exclusive OR function to find binary of ASCII of new character */
	/* Convert the binary to decimal and output it as a character to 'quote.vern' */
	if(quote != NULL && pad != NULL){
		while(fscanf(quote, "%c", &realChar) != EOF)
		{
			if (fscanf(pad, "%c", &padChar) != EOF){
				padNum = decToBin((int)padChar); 
				realNum = decToBin((int)realChar);
				outNum = xor(realNum, padNum);
				fprintf(encrypted, "%c", (char)binToDec(outNum));
			} else{
				fclose(pad);
				pad = fopen("decodedPad.txt", "r");
				printf("Warning: the end of the pad was reached.\n");
				printf("Encryption continued from the beginning of the pad.\n");
			}
		}
	} 
	else{ 
		if(quote == NULL) 
			printf("Error! The file does not exist.\n"); 
		if(pad == NULL) 
			printf("Error! The pad does not exist.\n");
	}
	
	fclose(pad);fclose(encrypted); fclose(quote);
}

/* Function to decrypt "whatIsThis.vern" */
void decrypt(void)
{
	/* Declare variables, open files */
	char padChar, codeChar, outChar;
	int padNum, codeNum, outNum;
	FILE *code = fopen("whatIsThis.vern", "r");
	FILE *pad = fopen("decodedPad.txt", "r");
	FILE *out = fopen("whatIsThis.txt", "w");
	
	/* Check to make sure the file and pad exist */
	/* Read each character in the file */
	/* If statement to notify if end of pad is reached early */
	/* Store binaries of character ASCII's as ints because this is less confusing */
	/* Use exclusive OR function to find binary of ASCII of decoded character */
	/* Convert that binary to decimal and output it as the decoded 
	 * character to 'whatIsThis.txt' */
	if(code != NULL && pad != NULL){
		while(fscanf(code, "%c", &codeChar) != EOF)
		{
			if(fscanf(pad, "%c", &padChar) != EOF){
				padNum = decToBin((int)padChar);
				codeNum = decToBin((int)codeChar);
				outNum = xor(codeNum, padNum);
				fprintf(out, "%c", (char)binToDec(outNum));
			} else{
				fclose(pad);
				pad = fopen("decodedPad.txt", "r");
				printf("Warning: the end of the pad was reached.\n");
				printf("Decryption will continue from the beginning of the pad.\n");
			}
		}
	}
	else{
		if(code == NULL)
			printf("Error! The file does not exist.\n");
		if(pad == NULL)
			printf("Error! The pad does not exist.\n");
	}
	
	fclose(code); fclose(pad); fclose(out);
}


/* Sample Output

engs20-4:~/engs20/workspace$ WerchniakLA1
Enter: 
1 to encrypt 'quote.txt' 
2 to decrypt 'whatIsThis.vern' 
3 to do both 
q
Please enter a valid number. 9
Please enter a valid number. 47
Please enter a valid number. sdflkj
Please enter a valid number. (*&%&*SDnsdidfh89760SDJH
Please enter a valid number. 1

Encrypted quote.txt!
File available in quote.vern.

engs20-4:~/engs20/workspace$ WerchniakLA1
Enter: 
1 to encrypt 'quote.txt' 
2 to decrypt 'whatIsThis.vern' 
3 to do both 
2

Decrypted whatIsThis.vern!
File available in whatIsThis.txt.

engs20-4:~/engs20/workspace$ WerchniakLA1
Enter: 
1 to encrypt 'quote.txt' 
2 to decrypt 'whatIsThis.vern' 
3 to do both 
3

Encrypted quote.txt and decrypted whatIsThis.vern!

Files available in quote.vern and whatIsThis.txt.

engs20-4:~/engs20/workspace$ cat whatIsThis.txt
Start by doing what's necessary; then do what's possible; and suddenly you are doing 
the impossible.
Francis of Assisi

Perfection is not attainable, but if we chase perfection we can catch excellence.
Vince Lombardi

Your work is going to fill a large part of your life, and the only way to be truly 
satisfied is to do what you believe is great work. And the only way to do great work 
is to love what you do. If you haven't found it yet, keep looking. Don't settle. 
As with all matters of the heart, you'll know when you find it.
Steve Jobs

Believe you can and you're halfway there.
Theodore Roosevelt

Don't limit yourself. Many people limit themselves to what they think they can do. 
You can go as far as your mind lets you. What you believe, remember, you can achieve.
Mary Kay Ash

Don't judge each day by the harvest you reap but by the seeds that you plant.
Robert Louis Stevenson
engs20-4:~/engs20/workspace$ cat quote.vern
3-]!@4-C]8[ZOX]RO?
                  =W&@$@a1U9{D;sO"fE$2+#}]S]?B [xYD45E1!PEP
                                                           [AI0NLZV+}<
qW'MF)MF_YU}%>HXPT1MQ2XIB!1p5-`1XL+rT- 3
5D1Kp=:K.$^Ko.Ya_!
                  .,j?_E%nRWM'C?NpR3e_J-sC4M8Xd;[ASYAO$1N'2>hZO^/6EA
+QX$                                                                .'T9^]W9
    ]2;EYe<

*          CN(T;:$~17]2MYUC
v2\%D:G^)V;,TUW!*
               19aC>1C|
                       %[~Z#@^UtQ
#VHDA
     z	-nC&N,Z :""N.JQK9eZD.U\W5       3J%.
                                            =TGQ#
                                                 -1;+MS
                                                       Dv|M5*GPeI5Y:+\@r	#D<?X/D\
  8RJ)
      &SHM<Q@!66T]NU
2i9Xr/"P]U#$BB
Uc_	cX
Fw(3CF    ;5*v^34^?!F65j<6D0}HM$a$H1+VTLH$,
      K:0B:c
<vMY_u+ZVE.;^H	"
                 cJR-}[M#'B]F=YD-	Zz\:@73T=DVW	S
AvEKE|OO#<B *6^Q2\X_#GhP IH*Y_=/08I<J8Z|1
NstR$
     sM;Z)]|cK|LYIg
*/