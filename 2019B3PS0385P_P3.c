#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct reading_questions	//Structure to store questions and respective options along with correct option number.
{
	char qname[250];
	char option[4][50];
	char correctoption;
} ques;

ques question[16][3];	//Each of the 16 level question has set of 3 questions each out of which 1 would be asked thats why 2D array initialized.
FILE * file_ptr;
int prize_money[17] = { 0, 1000, 2000, 3000, 5000, 10000, 20000, 400000, 80000, 160000, 320000, 640000, 1250000, 2500000, 5000000, 10000000, 70000000 };
char char_reading;	//To read characters from Question_File.txt
int hasUsedFiftyFifty = 0;	//To ensure each lifeline is used only once
int hasUsedFlipTheQuestion = 0;

// Declaration of all the functions used in the program
void startgame();
void introduction();
void animation();
void question_read(int i, int j);
void print_question(int i, int j);
int randnum();
char input_taker();
char chooseoption();
char fifty_fifty(int i, int j);
void flip_the_question(int i, int j);
int lifeline(int i, int j);
void lost_moneywon(int i);
void quit(int i);
void sixteenth_question_details();
void sixteenth_option();
void jackpot_question();
void sixteenth_ques_option_selected(int j);

int main()
{
	file_ptr = fopen("Question_File.txt", "r");	//Opening the Question_File.txt to read introduction along with questions and their options from it.
	if (file_ptr == NULL)
	{
		//Error Check
		printf("\nFILE ERROR !!\nFile \"Question_File.txt\" is not found. Please check the file name and file path, resolve and then start again !!\n");
		exit(0);
	}
	char_reading = fgetc(file_ptr);
	srand(time(0));	//To generate random number from time at which program is run.
	introduction();
	printf("\n\nPress enter to start the game: ");
	startgame();
	printf("\n\n");
	int i, j;	// 'i' is Quesition Level No. and 'j' is Question No. out of 3
	for (i = 0; i < 16; i++)	//Reading questions from Assignment_Question_File.txt and storing them in structures.
	{
		for (j = 0; j < 3; j++)	//Since each level has 3 questions
		{
			question_read(i, j);
		}
	}

	i = 0;
	while (i < 15)	// Randomly choosing 1 out of 3 question available for each level (Total 15) to ask.
	{
		j = randnum();
		print_question(i, j);	//The flow of program starts from this function and ends when all 15 questions are answered correctly.
		i++;
	}

	sixteenth_question_details();	//Once player correctly answers all 15 questions, details of 16th question are displayed.

	return 0;

}	//End of main() function

//Starts the game when the user enters 'ENTER' key
void startgame()
{
	char enter;
	enter = getchar();
	if (enter != '\n')
		startgame();
}

// Reads and prints the introductions of the game from Question_File.txt
void introduction()
{
	while (char_reading != '~')
	{
		fputc(char_reading, stdout);
		char_reading = fgetc(file_ptr);
		animation();
	}

	char_reading = fgetc(file_ptr);
}

// Function used for time delay
void animation()
{
	for (int animation = 0; animation < 2500000; animation++);
}

// Reads all the questions and options from Question_File.txt and stores them in our global 2D structure array question
void question_read(int i, int j)
{
	int char_array_number = 0, option_number = 0;
	while (char_reading != '~')	//Questions and indivisual options are seperated by '~' in Question_File.txt
	{
		question[i][j].qname[char_array_number] = char_reading;
		char_array_number++;
		char_reading = fgetc(file_ptr);
	}

	char_array_number = 0;
	char_reading = fgetc(file_ptr);
	while (option_number < 4)	//Reading options
	{
		while (char_reading != '~')
		{
			question[i][j].option[option_number][char_array_number] = char_reading;
			char_array_number++;
			char_reading = fgetc(file_ptr);
		}

		char_array_number = 0;
		char_reading = fgetc(file_ptr);
		option_number++;
	}

	question[i][j].correctoption = char_reading;	//Storing the correct option for each question.
	while (char_reading != '\n')
	{
		char_reading = fgetc(file_ptr);
	}
}

//prints the current question and options
//also responds according to the option selected by user
void print_question(int i, int j)
{
	printf("%s\n\n", question[i][j].qname);
	printf("%s\n%s\n%s\n%s\n", question[i][j].option[0], question[i][j].option[1], question[i][j].option[2], question[i][j].option[3]);
	char option_selected = chooseoption();
	if (option_selected == 'Q')	//To quit
		quit(i);
	while (option_selected == 'L')	//For Lifeline
	{
		char lifeline;
		printf("Press -:\n1.> For 50-50 Lifeline\n2.> For Flip The Question \nAny other key to exit lifeline: ");
		lifeline = input_taker();
		if (lifeline == '1')
			option_selected = fifty_fifty(i, j);
		else if (lifeline == '2')
		{
			if (hasUsedFlipTheQuestion == 1)
			{
				printf("Sorry ,You have already used this lifeline.\n");
				option_selected = chooseoption();
			}
			else
			{
				flip_the_question(i, j);
				return;
			}
		}
		else option_selected = chooseoption();
	}

	if (option_selected == question[i][j].correctoption)
	{
		printf("You Won Rs.%d !!", prize_money[i + 1]);
		printf("\n\n");
		for (int pau = 0; pau < 250000000; pau++);	//For time-delay
	}
	else if (option_selected == 'Q')
		quit(i);
	else
	{
		printf("Incorrect answer. The correct answer was %d ", question[i][j].correctoption - 48);
		lost_moneywon(i);
		exit(0);
	}
}

//Returns a random integer between 0 and 3
int randnum()
{
	return (rand() % 3);
}

//For error checking in input from user
char input_taker()
{
	char input = getchar();
	while (input == '\n')	//ERROR CHECK
		input = getchar();	//ERROR CHECK
	while (getchar() != '\n');	//ERROR CHECK
	return input;
}

//returns the option selected by user
char chooseoption()
{
	char option_selected;
	for (int pau = 0; pau < 150000000; pau++);	//For time-delay
	printf("Choose your option (1-4) or L for Lifeline or Q if you want to Quit: ");
	option_selected = input_taker();
	if ((option_selected >= '1' && option_selected <= '4') || option_selected == 'L' || option_selected == 'Q')
	{
		return (option_selected);
	}
	else
	{
		printf("Select between 1-4 or L or Q only !!\n");
		return chooseoption();	// Keeps asking till the user enters a valid option
	}
}

//Executes the fifty fifty lifeline. Prints the correct and one random incorrect option.
char fifty_fifty(int i, int j)
{
	if (hasUsedFiftyFifty == 1)	//Checks if user has already used this lifeline
	{
		printf("Sorry, you have already used this lifeline :(\n");
		return chooseoption();
	}

	printf("You have chosen the lifeline 50-50. Now two incorrect options will be removed.\n");
	int incorrectOpt;
	int correctOpt = (question[i][j].correctoption - 48);
	srand(time(0));
	incorrectOpt = (rand() % 4) + 1;	//Randomly selecting one of the 4 options
	for (; incorrectOpt == correctOpt;)	//Checks if randomly selected option is correct option or not, if it is the random option is selected again.
	{
		srand(time(0));
		incorrectOpt = (rand() % 4) + 1;
	}

	printf("Choose one of these two options or Q to Quit: \n");
	if (correctOpt > incorrectOpt)	//For ordering of options
		printf("%s\n%s\n", question[i][j].option[incorrectOpt - 1], question[i][j].option[correctOpt - 1]);
	else
		printf("%s\n%s\n", question[i][j].option[correctOpt - 1], question[i][j].option[incorrectOpt - 1]);
	char option_selected = input_taker();
	for (;
		(option_selected != (correctOpt + 48)) && (option_selected != (incorrectOpt + 48)) && (option_selected != 'Q');)	//ERROR CHECK
	{
		printf("Invalid Choice. Choose Again\n");
		option_selected = input_taker();
	}

	hasUsedFiftyFifty = 1;	//So that once used 50-50, same lifeline can't be used again.
	return option_selected;
}

//prints one of other 2 questions in the set of 3.
void flip_the_question(int i, int j)
{
	printf("You have chosen the lifeline flip the question. Now you will have to answer a different question\n");
	int j_new = randnum();
	for (; j_new == j;)
		j_new = randnum();
	hasUsedFlipTheQuestion = 1;
	print_question(i, j_new);
}

// print the money won by the user and ends the game when he/she answers incorrectly.
void lost_moneywon(int i)
{
	int prizeMoney;
	if (i < 4)
		prizeMoney = 0;
	else if (i < 8)
		prizeMoney = prize_money[4];
	else if (i < 12)
		prizeMoney = prize_money[8];
	else
		prizeMoney = prize_money[12];
	printf("\nYou have won Rs.%d\n", prizeMoney);
	printf("\nTHE GAME HAS ENDED !!\nTHANKS FOR PLAYING !!\n\n");
}

// Quits the game when the user enters Q
void quit(int i)
{
	printf("You are going home with Rs.%d !!\nBest Of Luck for future aspects :)\nTHANKS FOR PLAYING!!\n\n", prize_money[i]);
	exit(0);
}

// Reads and prints the details of the 16th question
void sixteenth_question_details()
{
	char_reading = fgetc(file_ptr);
	while (char_reading != '~')
	{
		fputc(char_reading, stdout);
		char_reading = fgetc(file_ptr);
		animation();
	}

	sixteenth_option();
}

// Asks the user whether he wants to play the 16th question
void sixteenth_option()
{
	printf("Press Y for Yes and N for No: ");
	char sixteenth;
	sixteenth = input_taker();
	if (sixteenth == 'Y')
	{
		printf("Here is your JACKPOT question -");
		jackpot_question();
	}
	else if (sixteenth == 'N')
	{
		printf("So you don't like taking risk XD !! Nevermind... You are going back home along with huge amount of 1 Crore... Congratulations once again !!\n\nTHANKS FOR PLAYING !!\n\n");
		exit(0);
	}
	else
		sixteenth_option();
}

//Prints the 16th question
void jackpot_question()
{
	int j = randnum();
	printf("%s\n\n%s\n%s\n%s\n%s\n", question[15][j].qname, question[15][j].option[0], question[15][j].option[1], question[15][j].option[2], question[15][j].option[3]);
	sixteenth_ques_option_selected(j);

}

// Asks and checks the option selected by the user for the 16th question
void sixteenth_ques_option_selected(int j)
{
	char sixteenth_option_selected;
	printf("Choose your life-changing option between 1-4: ");
	sixteenth_option_selected = input_taker();
	if (sixteenth_option_selected > '4' || sixteenth_option_selected<'1')	//ERROR CHECK
	{
		printf("Choose between 1-4 only...\n");
		sixteenth_ques_option_selected(j);
	}

	if (sixteenth_option_selected == question[15][j].correctoption)	//If user selects correct option
	{
		printf("\nWohoooo !!!! Congratulations.... You have won 7 Crore Rupees !!!!\nTHANKS FOR PLAYING !!!\n\n");
	}
	else	//If user selects wrong option
	{
		printf("\nOhhh:( Unfortunately that's a wrong answer... You have not only lost the chance to win 7 Crore but also lost 50 Lakhs out of your 1 Crore Rupees.\nTHANKS FOR PLAYING !!\n\n");
	}
}

//End of program
