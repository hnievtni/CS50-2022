#include <stdio.h> //input and output library
#include <stdlib.h> //pointer and rand library
#include <string.h> //string functions
#include <time.h> //date and time library
#include <cs50.h> //includes get_string and get_int and ...

void diggingupblocks(char, int, int); //digging up blocks
void updateplayersposition(char, int, int); //movements
void updategamefield(void); //update and display game field
void inputs(void); //check inputs for movements and digging up
void gainvictory(int); //check if player won
void gravity(void); //gravity chcek
void error(int); //different errors
void randpositions(void); //random poisitions for different blocks
void menu(void); //main menu
void settings(void); //setting menu
void saverecords(void); //saving records into a .txt file
void displayrecords(void); //displaying records
void playersinfo(void); //players info such az name
void startgame(void); //introduction
void movementlimit(int); //check the movements limit
void blockcheck(int, int); //check the blocks for digging up
void enteringcheck(int, int); //check the blocks for entering
void updatelifecount(int); //check the players life counter
void updateplayersstrength(int); //check the players strength counter

struct player
{
	string name;
	int life;
	int movelimit;
	int strength;
	int score;
	int row; //players row position
	int column; //players column poistion
};
struct robot
{
	int life;
};
struct gamefield
{
	int rows;
	int columns;
	int rocknumber;
	int coinnumber;
	int bombnumber;
	int robotsnumber;
	int lifepotionnumber;
	int powerpotionnumber;
	int bombpower;
	int powerpotionstrength;
};

struct player plyr;
struct gamefield field;
struct robot **rbt;
char **gamefield;

int lifecounter, strengthcounter, remainmoves, coincounter = 0, movecounter = 0;
char w, s, a, d, i, k, j, l;

int main(void)
{
	//initialization
	field.rows = 5, field.columns = 10;
	field.coinnumber = 4, field.rocknumber = 7, field.bombnumber = 5, field.bombpower = 3, field.robotsnumber = 3;
	field.lifepotionnumber = 4, field.powerpotionnumber = 3, field.powerpotionstrength = 2;

	plyr.row = 0, plyr.column = 0; //players start position
	plyr.movelimit = ((field.rows * field.columns) * 2) / 3;
	plyr.life = 12, plyr.strength = 5;

	lifecounter = plyr.life, strengthcounter = plyr.strength, remainmoves = plyr.movelimit;

	menu();
	return 0;
}
void menu(void)
{
	system("clear");
	int menuinput = get_int("1. Start Game \n2. Settings \n3. Records \n4. Exit \nInput: ");
	switch (menuinput)
	{
		case 1:
		playersinfo();
	    break;

	    case 2:
		settings();
		break;

	    case 3:
		displayrecords();
		break;

	    case 4:
		exit(0);
		break;

	    default: //for unknown chars
		error(4);
		menu();
	}
}
void playersinfo(void)
{
	system("clear");
	plyr.name = get_string("Please enter your name: ");
	startgame();
}
void startgame(void)
{
	system("clear");
	//defining instructions and chars
	//for more instructions and games rules please read README.txt file
	printf("Hello  '%s'  welcome to DIG OUT.\n\n", plyr.name);
	printf("in order to win you have to collect all the coins in the field.\n");
	printf("watch out the gravity.\n\n");
	printf("player\t\t[ ! ]\trobot \t\t[ | ]\n\n");
	printf("sand\t\t[ # ]\trock \t\t[ @ ]\n\n");
	printf("coin\t\t[ $ ]\tlife potion\t[ + ]\n\n");
	printf("bomb\t\t[ & ]\tpower potion\t[ %% ]\n\n");
	printf("dig up\t\t[ i ]\tmove up\t\t[ w ]\n\n");
	printf("dig down\t[ k ]\tmove down\t[ s ]\n\n");
	printf("dig right\t[ l ]\tmove right\t[ d ]\n\n");
	printf("dig left\t[ j ]\tmove left\t[ a ]\n\n");
	printf("for previous menu enter 1.\nand for exiting the game enter 0.\n\n");

	char continuatorofthegame = get_char("if you are ready,enter any key to start the game.\n");
	if (continuatorofthegame == '1')
	{
	  menu();
	}
	else
	{
		system("clear");

		gamefield = malloc(field.rows * sizeof(int *));
		for (int x = 0; x < field.rows; x++)
		{
		  gamefield[x] = malloc(field.columns * sizeof(int));
		}
		for (int x = 0; x < field.rows; x++)
		{
			for (int y = 0; y < field.columns; y++)
			{
			  gamefield[x][y] = '#';
			}
		}

		gamefield[plyr.row][plyr.column] = '!'; //players starting position

		randpositions();
		updategamefield();
	}
}
void settings(void)
{
	system("clear");
	int menuinput = get_int("1. Edit width and height \n2. Edit the initial values of the variables \n3. previous menu \nInput:");

	switch (menuinput)
	{
		case 1:
	    system("clear");

        field.rows = get_int("Width: ");
	    field.columns = get_int("Height: ");
	    plyr.movelimit = ((field.rows * field.columns) * 2) / 3;
	    remainmoves = plyr.movelimit;

	    settings();
	    break;

	    case 2:
	    system("clear");

	    field.rocknumber = get_int("rock number: ");
	    field.coinnumber = get_int("coin number: ");
    	field.bombnumber = get_int("bomb number: ");
	    field.robotsnumber = get_int("robots number: ");
	    field.lifepotionnumber = get_int("life potion number: ");
	    field.powerpotionnumber = get_int("power potion number: ");

	    plyr.life = get_int("players life number: ");
	    plyr.strength = get_int("players strength: ");
	    lifecounter = plyr.life;
	    strengthcounter = plyr.strength;

	    settings();
	    break;

	    case 3:
	    menu();
	    break;

	    default: //for unknown chars
	    error(4);
	    settings();
	}
}
void saverecords(void)
{
	plyr.score = remainmoves + (lifecounter * strengthcounter) + coincounter;

	printf("Your score is: %d\n", plyr.score);

	FILE *recordsfile;
	recordsfile = fopen("recordsfile.txt", "a+");
	if (recordsfile == NULL)
	{
		printf("Error opening file");
	}

	fprintf(recordsfile, "%s\t\t|\t%d\n", plyr.name, plyr.score);
	fclose(recordsfile);
}
void displayrecords(void)
{
	system("clear");

	char character;
	FILE *recordsfile;
	recordsfile = fopen("recordsfile.txt", "r");
	while (!feof(recordsfile))
	{
        character = fgetc(recordsfile);
        printf("%c", character);
    }
	fclose(recordsfile);

	printf("enter any key to exit.");
	char continuatorofthegame = get_char("");
	menu();
}
void randpositions(void)
{
	srand(time(0)); //a function for choosing random numbers each time

	for (int count = 0; count < field.rocknumber;) //rock
	{
		int x = rand() % field.rows, y = rand() % field.columns;
		if (gamefield[x][y] == '#')
		{
			gamefield[x][y] = '@';
			count++;
		}
	}
	for (int count = 0; count < field.coinnumber;) //coin
	{
		int x = rand() % field.rows, y = rand() % field.columns;
		if (gamefield[x][y] == '#')
		{
			gamefield[x][y] = '$';
			count++;
		}
	}
	for (int count = 0; count < field.lifepotionnumber;) //life potion
	{
		int x = rand() % field.rows, y = rand() % field.columns;
		if (gamefield[x][y] == '#')
		{
			gamefield[x][y] = '+';
			count++;
		}
	}
	for (int count = 0; count < field.bombnumber;) //bom
	{
	    int x = rand() % field.rows, y = rand() % field.columns;
		if (gamefield[x][y] == '#')
		{
			gamefield[x][y] = '&';
			count++;
		}
	}
	for (int count = 0; count < field.powerpotionnumber;) //power potion
	{
		int x = rand() % field.rows, y = rand() % field.columns;
		if (gamefield[x][y] == '#')
		{
			gamefield[x][y] = '%';
			count++;
		}
	}
	for (int count = 0; count < field.robotsnumber;) //robot
	{
	    rbt = malloc(field.rows * sizeof(int *));
		for (int x = 0; x < field.rows; x++)
		{
			rbt[x] = malloc(field.columns * sizeof(int));
		}

		int x = rand() % field.rows, y = rand() % field.columns;
		if (gamefield[x][y] == '#')
		{
			gamefield[x][y] = '|';
			rbt[x][y].life = plyr.life / 3;
			count++;
		}
	}
}
void updategamefield(void)
{
	system("clear");

	gamefield[plyr.row][plyr.column] = '!'; //specify players position

	//displaying the game field
	for (int x = 0; x < field.rows; x++)
	{
		for (int y = 0; y < field.columns; y++)
		{
		  printf("%c ",gamefield[x][y]);
		}
		printf("\n");
	}

	printf("Life: %d\n", lifecounter);
	printf("Coins: %d\n", coincounter);
	printf("Strength: %d\n", strengthcounter);
	printf("Remain moves: %d\n", remainmoves);

	inputs();
}
void inputs(void)
{
	char input = get_char("Input: ");
	switch (input)
	{
		case 'i': //dig up the upper block
		diggingupblocks(input, plyr.row, plyr.column);
		break;

	    case 'k': //dig up the bottom block
		diggingupblocks(input, plyr.row, plyr.column);
		break;

	    case 'j': //dig up the left block
		diggingupblocks(input, plyr.row, plyr.column);
		break;

	    case 'l': //dig up the right block
		diggingupblocks(input, plyr.row, plyr.column);
		break;

	    case 'w': //move to the upper block
		updateplayersposition(input, plyr.row, plyr.column);
		break;

	    case 's': //move to the bottom block
		updateplayersposition(input, plyr.row, plyr.column);
		break;

	    case 'a': //move to the left block
		updateplayersposition(input, plyr.row, plyr.column);
		break;

	    case 'd': //move to the right block
		updateplayersposition(input, plyr.row, plyr.column);
		break;

	    case'0': //changing game field
		menu();

	    default: //for unknown chars
		error(4);
		updategamefield();
	}
}
void diggingupblocks(char digging, int row, int column)
{
	//row is players row position and column in players column position
	switch (digging)
	{
	    case 'i': //upper block
		if (row == 0) //game field limit
		{
			error(0);
		}
		else
		{
			row--;
			blockcheck(row, column);
		}
		break;
	    case 'k': //bottom block
		if (row == field.rows - 1) //game field limit
		{
			error(0);
		}
		else
		{
			row++;
			blockcheck(row, column);
		}
		break;
	    case 'j': //left block
		if (column == 0) //game field limit
		{
			error(0);
		}
		else
		{
			column--;
			blockcheck(row, column);
		}
		break;
	    case 'l': //right block
		if (column == field.columns - 1) //game field limit
		{
			error(0);
		}
		else
		{
			column++;
			blockcheck(row, column);
		}
		break;
	}
	updategamefield();
}
void blockcheck(int row, int column)
{
	switch (gamefield[row][column])
	{
		case '@': //immunity against drilling
		error(1);
		break;

		case '$'://immunity against drilling
		error(1);
		break;

		case '+'://immunity against drilling
		error(1);
		break;

		case '&'://immunity against drilling
		error(1);
		break;

		case '%'://immunity against drilling
		error(1);
		break;

		case '|'://immunity against drilling
		error(1);
		break;

		case ' ': //already empty
		error(3);
		break;

		case '#':
		gamefield[row][column] = ' ';
		gravity();
		break;
	}
}
void updateplayersposition(char movement, int row, int column)
{
	//row is players row position and column in players column position
	gamefield[plyr.row][plyr.column] = ' ';

	switch (movement)
	{
		case 'w': //uuper block
		if (row == 0) //game field limit
		{
			error(0);
		}
		else
		{
			row--;
			enteringcheck(row, column);
		}
		break;

	    case 's': //bottom block
		if (row == field.rows - 1) //game field limit
		{
			error(0);
		}
		else
		{
			row++;
			enteringcheck(row, column);
		}
		break;

	    case 'a': //left block
		if (column == 0) //game field limit
		{
			error(0);
		}
		else
		{
			column--;
			enteringcheck(row, column);
		}
		break;

	    case 'd': //right block
		if (column == field.columns - 1) //game field limit
		{
			error(0);
		}
		else
		{
			column++;
			enteringcheck(row, column);
		}
		break;
	}
	gamefield[plyr.row][plyr.column] = '!';
	gravity();
	updategamefield();
}
void enteringcheck(int row, int column)
{
	switch (gamefield[row][column])
	{
		case '@': //immunity against entering
		error(2);
		break;

	    case '#': //immunity against entering
	    error(2);
		break;

		case '$':
		plyr.row = row;
		plyr.column = column;

		coincounter++;
		movecounter++;
		remainmoves = plyr.movelimit - movecounter;

		movementlimit(remainmoves);
		gainvictory(coincounter);
		break;

		case '&':
		plyr.row = row;
		plyr.column = column;

		movecounter++;
		remainmoves = plyr.movelimit - movecounter;
		if (strengthcounter > field.bombpower)
		{
			strengthcounter -= field.bombpower;
		}
		else
		{
			strengthcounter = 0;
		}

		movementlimit(remainmoves);
		updateplayersstrength(strengthcounter);
		break;

		case '+':
		plyr.row = row;
		plyr.column = column;

		lifecounter++;
		movecounter++;
		remainmoves = plyr.movelimit - movecounter;

		movementlimit(remainmoves);
		break;

		case '%':
		plyr.row = row;
		plyr.column = column;

		movecounter++;
		strengthcounter += field.powerpotionstrength;
		remainmoves = plyr.movelimit - movecounter;

		movementlimit(remainmoves);
		break;

		case '|':
		if (rbt[row][column].life >= lifecounter)
		{
			lifecounter = 0;
			updatelifecount(lifecounter);
		}
		else
		{
			plyr.row = row;
			plyr.column = column;
			lifecounter--;
		}
		movecounter++;
		remainmoves = plyr.movelimit - movecounter;

		movementlimit(remainmoves);
		break;

		case ' ':
		plyr.row = row;
		plyr.column = column;

		movecounter++;
		remainmoves = plyr.movelimit - movecounter;

		movementlimit(remainmoves);
		break;
	}
}
void gainvictory(int coincounter0)
{
	if (coincounter0 == field.coinnumber)
	{
		system("clear");
		printf("congratulations, you WIN!\nenter any key to exit.\n");
		saverecords();
		char consolekeeper = get_char("");
		main();
	}
}
void gravity()
{
	//for checking every row in the specified column twice
	for (int columngravitycheckcounter = 0; columngravitycheckcounter < field.rows; columngravitycheckcounter++)
	{
		for (int y = 0; y < field.columns; y++)
		{
			for (int x = 0; x < field.rows; x++)
			{
				if (x != field.rows - 1)
				{
					switch (gamefield[x][y])
					{
					    case '@':
						if (gamefield[x + 1][y] == ' ')
						{
							gamefield[x][y] = ' ';
							gamefield[x + 1][y] = '@';
						}
						if (gamefield[x + 1][y] == '!')
						{
							gamefield[x][y] = ' ';
							gamefield[x + 1][y] = '@';
							lifecounter = 0; //player dies
							updatelifecount(lifecounter);
						}
						if (gamefield[x + 1][y] == '|')
						{
							gamefield[x][y] = ' '; //robot dies
							gamefield[x + 1][y] = '@';
						}
						break;

					    case '$':
						if (gamefield[x + 1][y] == ' ')
						{
							gamefield[x][y] = ' ';
							gamefield[x + 1][y] = '$';
						}
						if (gamefield[x + 1][y] == '!')
						{
							coincounter++;
							gainvictory(coincounter);
							gamefield[x][y] = ' ';
						}
						break;

					    case '&':
						if (gamefield[x + 1][y] == ' ')
						{
							gamefield[x][y] = ' ';
							gamefield[x + 1][y] = '&';
						}
						if (gamefield[x + 1][y] == '!')
						{
							gamefield[x][y] = ' ';
							if (strengthcounter > field.bombpower)
							{
								strengthcounter -= field.bombpower;
							}
							else
							{
								strengthcounter = 0;
								updateplayersstrength(strengthcounter);
							}
						}
						if (gamefield[x + 1][y] == '|')
						{
							rbt[x + 1][y].life -= field.bombpower;
							gamefield[x][y] = ' ';
							if (rbt[x + 1][y].life == 0) //robot dies
							{
								gamefield[x + 1][y] = ' ';
							}
						}
						break;

					    case '+':
						if (gamefield[x + 1][y] == ' ')
						{
							gamefield[x][y] = ' ';
							gamefield[x + 1][y] = '+';
						}
						if (gamefield[x + 1][y] == '!')
						{
							lifecounter++;
							gamefield[x][y] = ' ';
						}
						break;
					    case '%':
						if (gamefield[x + 1][y] == ' ')
						{
							gamefield[x][y] = ' ';
							gamefield[x + 1][y] = '%';
						}
						if (gamefield[x + 1][y] == '!')
						{
							gamefield[x][y] = ' ';
							strengthcounter += field.powerpotionstrength;
						}
						break;
					   case '|':
						if (gamefield[x + 1][y] == ' ')
						{
							gamefield[x][y] = ' ';
							gamefield[x + 1][y] = '|';
						}
						if (gamefield[x + 1][y] == '!')
						{
							if (rbt[x][y].life >= lifecounter)
							{
								lifecounter = 0; //player dies
								updatelifecount(lifecounter);
							}
							else
							{
								lifecounter--;
								gamefield[x][y] = ' ';
							}
						}
						break;
					}
				}
				else //last row
				{
					if (gamefield[x][y] == '@' || gamefield[x][y] == '$' || gamefield[x][y] == '&' ||
						gamefield[x][y] == '+' || gamefield[x][y] == '%' || gamefield[x][y] == '|')
						{
							break;
					}
				}
			}
		}
	}
}
void error(int value)
{
	char continuatorofthegame;
	switch (value)
	{
	    case 0:
		continuatorofthegame = get_char("\ngame field area is over.enter any button to try again.\n");
		break;

	    case 1:
		continuatorofthegame = get_char("\nyou can't dig this block.enter any button to try again.\n");
		break;

	    case 2:
		continuatorofthegame = get_char("\nthe block isn't empty.enter any button to try again.\n");
		break;

	    case 3:
		continuatorofthegame = get_char("\nthis block is already empty.enter any button to try again.\n");
		break;

	    case 4:
		continuatorofthegame = get_char("\nthis input is unknown.enter any button to try again.\n");
		break;
	}
}
void updatelifecount(int lifecounter0)
{
	if (lifecounter0 == 0)
	{
		system("clear");
		printf("Oops!you died.Gameover\nenter any key to exit.\n");
		saverecords();
		char consolekeeper = get_char("");
		main();
	}
}
void updateplayersstrength(int strengthcounter0)
{
	if (strengthcounter0 == 0)
	{
		system("clear");
		lifecounter--;
		strengthcounter = plyr.strength;
		updatelifecount(lifecounter);
	}
}
void movementlimit(int counter)
{
	if (counter == 0)
	{
		system("clear");
		printf("Oops!you died.Gameover\nenter any key to exit.\n");
		saverecords();
		char consolekeeper = get_char("");
		main();
	}
}