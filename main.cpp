#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include <stdlib.h>
#include"conio2.h"

/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */

enum player_stone_t {
	NONE,
	BLACK_ST,
	WHITE_ST,
	DOT_KO,
	BLACK_ATARI,
	WHITE_ATARI
};

struct Score {
	float white;
	float black;
};

struct TableSetting {
	int boardSize = BOARDSIZE;
	int boardSizeToPrint = boardSize;
	char** printStaticArr;
	enum player_stone_t** stoneEvolvingArr;
};

struct Input {
	int zn = KEY_0;
	int x = BOARDX + 1;
	int y = BOARDY + 1;
	int boardSize = BOARDSIZE;
	int boardSizeToPrint = boardSize; //if the user enters size of the board that is bigger than the screen choosen boardSize and size of the board that is printed is different
	int gameState = PRE_GAME_STATE; //first state of the game
	char** g_tab;
	enum player_stone_t** g_tab2;
	int moveTabY = 0;
	int moveTabX = 0;
	enum player_stone_t player = BLACK_ST;
	Score score;
	Score endScore;
	TableSetting arr;
	TableSetting tempArr;
};



Input setInput();
void menu(int* x, int* y, Score* score, int* gameState, int* moveTabY, int* moveTabX, Score* endScore);
void endMenu(Score* endScore, Score* score);
void boardTab(char** g_tab, int* boardSizeToPrint, int* gameState);
void putBoard(char** g_tab, int* boardSizeToPrint);
void boardBorder(int* boardSizeToPrint);
void printingBorder(int s, int i, int j);
void mvConditions(int zn, int* x, int* y, int* boardSize, int* moveTabY, int* moveTabX, int boardSizeToPrint);
void stoneSetTab(enum player_stone_t put, enum player_stone_t** g_tab2, int* boardSize);
void stonePrint(enum player_stone_t** g_tab2, int* boardSizeToPrint, int* gameState, int* moveTabY, int* moveTabX);
void keyMenu(int zn, enum player_stone_t* player, int* x, int* y, enum player_stone_t*** g_tab2, char*** g_tab, int* boardSize, Score* score, int* gameState, int* boardSizeToPrint, int* moveTabY, int* moveTabX, Score* endScore);
void RolesOfKeyNSatrtingGame(enum player_stone_t* player, int* x, int* y, enum player_stone_t*** g_tab2, int* boardSize, Score* score, int* gameState, Score* endScore);
void RolesOFKeyIPuttingStone(int zn, enum player_stone_t* player, enum player_stone_t*** g_tab2, int* boardSize, Score* score, int* gameState, int* moveTabY, int* moveTabX);
bool setOnBoard(enum player_stone_t* player, enum player_stone_t** g_tab2, int* moveTabY, int* moveTabX);
void checkPositionAround(int y, int x, enum player_stone_t* player, enum player_stone_t** g_tab2, int* boardSize, Score* score);
void killOpponent(int y, int x, enum player_stone_t* player, enum player_stone_t** g_tab2, Score* score);
bool checkIfSuicide(int y, int x, enum player_stone_t* player, enum player_stone_t** g_tab2, int* boardSize);
void checkIfSuicideLogic(enum player_stone_t** g_tab2, int*** arr, int* boardSize, enum player_stone_t* player, int yNow, int xNow, int* notPut, int free, int checkBoardSide, int boardCondition);
void menuDuringGame(int state);
void keyMenuFirst(int zn, enum player_stone_t*** g_tab2, char*** g_tab, int* boardSize, Score* score, int* gameState, int* boardSizeToPrint, enum player_stone_t* player, Score* endScore);
void firstMenu();
void setNewSizeTabs(char zn, enum player_stone_t*** g_tab2, char*** g_tab, int* boardSize);
void allocateTabs(int* boardSize, enum player_stone_t*** g_tab2, char*** g_tab);
void freeTabs(int* boardSize, enum player_stone_t** g_tab2, char** g_tab);
void intoFile(enum player_stone_t** g_tab2, int* boardSize, Score* score, enum player_stone_t* player);
bool fromFile(enum player_stone_t*** g_tab2, int* boardSize, char*** g_tab, Score* score, enum player_stone_t* player);
void setFromFile(enum player_stone_t*** g_tab2, int* boardSize, int* nfromFile);
bool nameOfFile(char* txt);
bool checkForOtherPlayerIsSurr(enum player_stone_t*** g_tab2, int* boardSize, enum player_stone_t* player, int moveBackY, int moveBackX, Score* score);
void check(enum player_stone_t*** g_tab2, int*** arr, int* boardSize, int yNow, int xNow, int* free, int endPlayer, int lookForPlayer, int checkAgain);
void chainRemoval(int** arr, enum player_stone_t*** g_tab2, int* boardSize, Score* score, int otherPlayer);
void allocatetabChainAndFillWithZero(int*** arr, int* boardSize);
void freetabTempChain(int** arr, int* boardSize);
void checkIfNextToMineIsOtherPlayerThenHisLiberties(enum player_stone_t*** g_tab2, int*** arr, int* boardSize, enum player_stone_t* player, int yNow, int xNow, int* free, int otherPlayer, int* returnTemp, Score* score);
void checkKo(enum player_stone_t*** g_tab2, int* boardSize, Score* score, int otherPlayer, int y, int x);
void outFromKoRule(enum player_stone_t*** g_tab2, int* boardSize, Score* score, int currScoreWhite, int currScoreBlack);
void countingPoints(int* boardSize, enum player_stone_t** g_tab2, enum player_stone_t notTosurround, Score* endScore);

int main() {

	Input in;
	allocateTabs(&in.boardSize, &in.g_tab2, &in.g_tab);
	in.score.white = 0;
	in.score.black = 0;

	in.endScore.white = 0;
	in.endScore.black = 0;


#ifndef __cplusplus
	Conio2_Init();
#endif

	settitle("Monika, Mazella, 193334");
	_setcursortype(_NOCURSOR);

	stoneSetTab(NONE, in.g_tab2, &in.boardSize);
	do {
		textbackground(BLACK);
		clrscr();

		menu(&in.x, &in.y, &in.score, &in.gameState, &in.moveTabY, &in.moveTabX, &in.endScore);

		boardTab(in.g_tab, &in.boardSizeToPrint, &in.gameState);
		stonePrint(in.g_tab2, &in.boardSizeToPrint, &in.gameState, &in.moveTabY, &in.moveTabX);

		gotoxy(in.x, in.y);
		textcolor(LIGHTGRAY);
		textbackground(BLACK);
		if ((in.gameState != PRE_GAME_STATE)&& (in.gameState != END_GAME_STATE)) putch('x');

		in.zn = getch();
		keyMenu(in.zn, &in.player, &in.x, &in.y, &in.g_tab2, &in.g_tab, &in.boardSize, &in.score, &in.gameState, &in.boardSizeToPrint, &in.moveTabY, &in.moveTabX, &in.endScore);

	} while (in.zn != KEY_Q);

	freeTabs(&in.boardSize, in.g_tab2, in.g_tab);

	_setcursortype(_NORMALCURSOR);
	return 0;
}

//printing menu
void menu(int* x, int* y, Score* score, int* gameState, int* moveTabY, int* moveTabX, Score* endScore) {
	char txt[32];
	textcolor(LIGHTGRAY);

	if ((*gameState) == PRE_GAME_STATE) {
		firstMenu();
	}
	else if ((*gameState) == END_GAME_STATE) {
		endMenu(endScore, score);
	}
	else {
		gotoxy(MENUX, MENUY + 4);
		cputs("arrows = moving the cursor over the board");
		gotoxy(MENUX, MENUY + 5);
		cputs("i      = place a stone on the board");
		gotoxy(MENUX, MENUY + 6);
		cputs("enter  = confirm choice and end player turn");
		gotoxy(MENUX, MENUY + 7);
		cputs("esc    = cancel current action");
		gotoxy(MENUX, MENUY + 8);
		cputs("s      = save the game state");
		gotoxy(MENUX, MENUY + 9);
		cputs("f      = finish the game");
		gotoxy(MENUX, MENUY + 10);
		cputs("n      = start a new game");
		gotoxy(MENUX, MENUY + 11);
		cputs("q      = exit");
		gotoxy(MENUX, MENUY + 14);
		cputs("x statemet  = ");
		cputs(itoa(((*x - BOARDX - 1) / 4) + (*moveTabX) + 1, txt, 10)); /////// czy pierwsze pole koordynat 1 czy 0
		gotoxy(MENUX, MENUY + 15);
		cputs("Y statemet  = ");
		cputs(itoa(((*y - BOARDY - 1) / 2) + (*moveTabY) + 1, txt, 10));
		gotoxy(MENUX, MENUY + 17);
		cputs("BLACK SCORE  = ");
		cputs(itoa((*score).black, txt, 10));
		gotoxy(MENUX, MENUY + 18);
		cputs("WHITE SCORE  = ");
		cputs(itoa((*score).white, txt, 10));
		gotoxy(MENUX, MENUY + 20);
		cputs("creator: Monika Mazella nr.193334");
		gotoxy(MENUX, MENUY + 22);
		cputs("list of implemented points:");
		gotoxy(MENUX, MENUY + 23);
		cputs("a,b,c,d,e,f,g,h,i,j,k,1/2 l");
		if (*gameState == HANDICAP_STATE) {
			menuDuringGame(7);
		}
	}
}

void firstMenu() {
	textcolor(LIGHTGRAY);

	textbackground(RED);
	gotoxy(MENUX + 3, MENUY);
	cputs("PRESS THE KEY");
	textbackground(BLACK);
	gotoxy(MENUX + 3, MENUY + 2);
	cputs("n      = start a new game");
	gotoxy(MENUX + 3, MENUY + 3);
	cputs("l      = load the game state");
	gotoxy(MENUX + 3, MENUY + 4);
	cputs("p      = select board size");
	gotoxy(MENUX + 3, MENUY + 5);
	cputs("h      = state editor - handicap");
	gotoxy(MENUX + 3, MENUY + 6);
	cputs("q      = exit");
}

//part of menu printed durign putting sth on the screen
void menuDuringGame(int state) {
	if (state == 1) {
		textbackground(RED);
		gotoxy(MENUX, MENUY);
		cputs("You can't put a stone here - SUICIDE ");
		gotoxy(MENUX, MENUY + 1);
		cputs("Put it somewhere else");
	}
	else if (state == 2) {
		textbackground(LIGHTMAGENTA);
		gotoxy(MENUX, MENUY);
		cputs("If you confirm the action press ENTER");
		gotoxy(MENUX, MENUY + 1);
		cputs("If NOT press ESC");
	}

	else if (state == 3) {
		gotoxy(MENUX, MENUY);
		cputs("Choose the size of the board");
		gotoxy(MENUX, MENUY + 3);
		cputs("1. 9x9");
		gotoxy(MENUX, MENUY + 4);
		cputs("2. 13x13");
		gotoxy(MENUX, MENUY + 5);
		cputs("3. 19x19");
		gotoxy(MENUX, MENUY + 6);
		cputs("4. custome your size");
	}

	else if (state == 4) {
		gotoxy(MENUX, MENUY);
		textbackground(LIGHTGREEN);
		cputs("Input the file name and confirm by pressing ENTER");
		textbackground(BLACK);
	}

	else if (state == 5) {
		textbackground(RED);
		gotoxy(MENUX, MENUY + 3);
		cputs("NO SUCH A FILE");
		gotoxy(MENUX, MENUY + 4);
		cputs("press ENTER to continue");
	}

	else if (state == 6) {
		textbackground(RED);
		gotoxy(MENUX, MENUY);
		cputs("You can't put a stone here - ALREADY OCCUPIED ");
		gotoxy(MENUX, MENUY + 1);
		cputs("Put it somewhere else");
	}

	else if (state == 7) {
		textbackground(LIGHTBLUE);
		gotoxy(MENUX, MENUY + 2);
		cputs("PRESS N TO START A GAME");
	}
}

void endMenu(Score* endScore, Score* score) {
	textcolor(LIGHTGRAY);
	char txt[32];

	
	(*endScore).black += (*score).black;
	(*endScore).white += (*score).white;
	(*endScore).white += 6.5;

	gotoxy(MENUX, MENUY + 4);
	if ((*endScore).black > (*endScore).white) {
		cputs("CONGRATULATIONS ");
		textbackground(RED);
		cputs("BLACK PLAYER");
		textbackground(BLACK);
	}
	else if ((*endScore).black == (*endScore).white) {
		cputs("DRAW");
	}
	else {
		cputs("CONGRATULATIONS ");
		textbackground(RED);
		cputs("WHITE PLAYER");
		textbackground(BLACK);
	}

	gotoxy(MENUX, MENUY+7);
	cputs("BLACK END SCORE  = ");
	sprintf(txt, "%.1f", (*endScore).black);
	cputs(txt);
	gotoxy(MENUX, MENUY+9);
	cputs("WHITE END SCORE  = ");
	sprintf(txt, "%.1f", (*endScore).white);
	cputs(txt);
	gotoxy(MENUX, MENUY + 11);
	cputs("Press 'n' to start a new game");
	gotoxy(MENUX, MENUY + 12);
	cputs("Press 'q' to exit");
}

//filling the array, which is a board, with the appropriate signs
void boardTab(char** g_tab, int* boardSizeToPrint, int* gameState) {
	textbackground(LIGHTGRAY);
	textcolor(BLACK);

	if (((*gameState) != PRE_GAME_STATE)) {
		for (int i = 0; i < (((*boardSizeToPrint) * 2) - 1); i++) {
			for (int j = 0; j < (((*boardSizeToPrint) * 4) - 2); j++) {
				if ((i % 2) == 0) {
					if (((j % 2) == 0) && ((j % 4) != 0)) {
						g_tab[i][j] = '+';
					}
					else {
						g_tab[i][j] = 32;
					}
				}
				else {
					if ((j % 4) == 0) {
						g_tab[i][j] = '+';
					}
					else {
						g_tab[i][j] = 32;
					}
				}
			}
		}
		putBoard(g_tab, boardSizeToPrint);
		boardBorder(boardSizeToPrint);
	}
}

//printing board on the screen
void putBoard(char** g_tab, int* boardSizeToPrint) {
	for (int i = 0; i < (((*boardSizeToPrint) * 2) - 1); i++) {
		for (int j = 0; j < (((*boardSizeToPrint) * 4) - 2); j++) {
			gotoxy(BOARDX + j + 1, BOARDY + i + 1);
			putch(g_tab[i][j]);
		}
	}
}

//creating the border
void boardBorder(int* boardSizeToPrint) {
	textcolor(BROWN);

	for (int i = 0; i < (((*boardSizeToPrint) * 2) + 1); i++) {
		for (int j = 0; j < (((*boardSizeToPrint) * 4) - 1); j++) {
			if (i == 0 && j == 0) {
				printingBorder(BORDER_LEFT_COR_UP, i, j); //left upper corner of the border
			}
			else if (i == 0 && j == ((*boardSizeToPrint * 4) - 2)) {
				printingBorder(BORDER_RIGHT_COR_UP, i, j); //right upper corner of the border
			}
			else if (j == 0 && i == (*boardSizeToPrint * 2)) {
				printingBorder(BORDER_LEFT_COR_DOWN, i, j); //left lower corner of the border
			}
			else if (i == (*boardSizeToPrint * 2) && j == ((*boardSizeToPrint * 4) - 2)) {
				printingBorder(BORDER_RIGHT_COR_DOWN, i, j); //right lower corner of the border
			}
			else if ((i == 0 || i == (*boardSizeToPrint * 2)) && (j != 0 && j != ((*boardSizeToPrint * 4) - 2))) {
				printingBorder(BORDER_ROW, i, j); //horizontal line of the border
			}
			else if ((j == 0 || j == ((*boardSizeToPrint * 4) - 2)) && (i != 0 && i != (*boardSizeToPrint * 2))) {
				printingBorder(BORDER_COL, i, j); //vertical line of the border
			}
		}
	}
}

void printingBorder(int s, int i, int j) {
	//placement of ascii sign and its printing
	gotoxy(BOARDX + j, BOARDY + i);
	putch(s);
}

//setting fields of the board designed for players moves - at the beggining NONE
void stoneSetTab(player_stone_t put, enum player_stone_t** g_tab2, int* boardSize) {
	for (int i = 0; i < *boardSize; i++) {
		for (int j = 0; j < *boardSize; j++) {
			g_tab2[i][j] = put;
		}
	}
}

//printing the stones on the board
void stonePrint(enum player_stone_t** g_tab2, int* boardSizeToPrint, int* gameState, int* moveTabY, int* moveTabX) {
	textcolor(BLACK);

	if (((* gameState) != PRE_GAME_STATE)) {
		for (int i = 0; i < *boardSizeToPrint; i++) {// boardsize - move/tabY ???????
			for (int j = 0; j < *boardSizeToPrint; j++) {
				if (g_tab2[i + (*moveTabY)][j + (*moveTabX)] == NONE) {
					gotoxy(BOARDX + (j * 4) + 1, BOARDY + (i * 2) + 1);
					putch('+');
				}
				else if (g_tab2[i + (*moveTabY)][j + (*moveTabX)] == BLACK_ST) {
					gotoxy(BOARDX + (j * 4) + 1, BOARDY + (i * 2) + 1);
					putch(219);
				}
				else if (g_tab2[i + (*moveTabY)][j + (*moveTabX)] == WHITE_ST) {
					gotoxy(BOARDX + (j * 4) + 1, BOARDY + (i * 2) + 1);
					putch(79);
				}
				else if (g_tab2[i + (*moveTabY)][j + (*moveTabX)] == DOT_KO) {
					gotoxy(BOARDX + (j * 4) + 1, BOARDY + (i * 2) + 1);
					putch(250);
				}
			}
		}
	}
}


//key menues -> first one without anything initialized (for settings) and second one during the game

void keyMenu(int zn, enum player_stone_t* player, int* x, int* y, enum player_stone_t*** g_tab2, char*** g_tab, int* boardSize, Score* score, int* gameState, int* boardSizeToPrint, int* moveTabY, int* moveTabX, Score* endScore) {

	if (((*gameState) == PRE_GAME_STATE) && ((*gameState) != END_GAME_STATE)) keyMenuFirst(zn, g_tab2, g_tab, boardSize, score, gameState, boardSizeToPrint, player, endScore);
	else if(((*gameState) != END_GAME_STATE)) {
		if (zn == KEY_0) mvConditions(zn, x, y, boardSize, moveTabY, moveTabX, *boardSizeToPrint);
		else if (zn == KEY_I) {
			RolesOFKeyIPuttingStone(zn, player, g_tab2, boardSize, score, gameState, moveTabY, moveTabX);
		}
		else if (zn == KEY_N) {
			RolesOfKeyNSatrtingGame(player, x, y, g_tab2, boardSize, score, gameState, endScore);
		}
		else if (zn == KEY_S) intoFile(*g_tab2, boardSize, score, player);
		else if (zn == KEY_F) {
			countingPoints(boardSize, *g_tab2, BLACK_ST, endScore);
			countingPoints(boardSize, *g_tab2, WHITE_ST, endScore);
			*gameState = END_GAME_STATE;
			if ((*endScore).black == ((*boardSize) * (*boardSize))) {
				(*endScore).black = 0;
				(*endScore).white = 0;
			}
		}
	}
}

void RolesOFKeyIPuttingStone(int zn, enum player_stone_t* player, enum player_stone_t*** g_tab2, int* boardSize, Score* score, int* gameState, int* moveTabY, int* moveTabX) {
	static int changePlayer;
	static int moveBackX;
	static int moveBackY;
	int temp = 0;
	int currScoreWhite = (*score).white;
	int currScoreBlack = (*score).black;

	if (*player == BLACK_ST) changePlayer = 0;
	else changePlayer = 1;

	moveBackY = ((wherey() - BOARDY - 1) / 2) + (*moveTabY);
	moveBackX = ((wherex() - BOARDX - 1) / 4) + (*moveTabX);
	if (setOnBoard(player, *g_tab2, moveTabY, moveTabX)) {
		while ((zn != KEY_ENTER) && (zn != KEY_ESC)) {
			menuDuringGame(2);
			zn = getch();
			if (zn == KEY_ENTER) {
				if (checkForOtherPlayerIsSurr(g_tab2, boardSize, player, moveBackY, moveBackX, score) == false) {
					if (checkIfSuicide(moveBackY, moveBackX, player, *g_tab2, boardSize)) {
						menuDuringGame(1);
						zn = getch();
						temp = 1;
					}
				}
				outFromKoRule(g_tab2, boardSize, score, currScoreWhite, currScoreBlack);

				if ((temp != 1) && (*gameState != HANDICAP_STATE)) {
					if (changePlayer == 0) {
						*player = WHITE_ST;
					}
					else {
						*player = BLACK_ST;
					}
				}
			}
			else if (zn == KEY_ESC) (*g_tab2)[moveBackY][moveBackX] = NONE;
		}
	}
	else {
		while (zn != KEY_0) {
			menuDuringGame(6);
			zn = getch();
		}
	}
}

void RolesOfKeyNSatrtingGame(enum player_stone_t* player, int* x, int* y, enum player_stone_t*** g_tab2, int* boardSize, Score* score, int* gameState, Score* endScore) {
	if (*gameState == HANDICAP_STATE) {
		*gameState = PLAY_GAME_STATE;
		*player = WHITE_ST;
	}
	else {
		stoneSetTab(NONE, *g_tab2, boardSize);
		*gameState = PRE_GAME_STATE;
		*boardSize = BOARDSIZE;
		*x = BOARDX + 1, * y = BOARDY + 1;
		*player = BLACK_ST;
		(*score).white = 0;
		(*score).black = 0;
		(*endScore).white = 0;
		(*endScore).black = 0;
	}
}

void keyMenuFirst(int zn, enum player_stone_t*** g_tab2, char*** g_tab, int* boardSize, Score* score, int* gameState, int* boardSizeToPrint, enum player_stone_t* player, Score* endScore) {
	if (zn == KEY_N) {
		*gameState = PLAY_GAME_STATE;
		_setcursortype(_NOCURSOR);
	}
	else if (zn == KEY_P) {
		clrscr();
		menuDuringGame(3);
		zn = getch();
		if (zn == KEY_1) {
			setNewSizeTabs(KEY_1, g_tab2, g_tab, boardSize);
			*boardSizeToPrint = *boardSize;
		}
		else if (zn == KEY_2) {
			setNewSizeTabs(KEY_2, g_tab2, g_tab, boardSize);
			*boardSizeToPrint = *boardSize;
		}
		else if (zn == KEY_3) {
			setNewSizeTabs(KEY_3, g_tab2, g_tab, boardSize);
			*boardSizeToPrint = *boardSize;
		}
		else if (zn == KEY_4) {
			setNewSizeTabs(KEY_4, g_tab2, g_tab, boardSize);
			if (*boardSize > BOARDSIZE_SCROLL) {
				*boardSizeToPrint = 9;
			}
			else *boardSizeToPrint = *boardSize;
		}
	}
	else if (zn == KEY_L) {
		if (fromFile(g_tab2, boardSize, g_tab, score, player)) *gameState = PLAY_GAME_STATE;
		else *gameState = PRE_GAME_STATE;
	}
	else if (zn == KEY_H) {
		*gameState = HANDICAP_STATE;
		(*endScore).white += 0.5;
	}
}


void setNewSizeTabs(char zn, enum player_stone_t*** g_tab2, char*** g_tab, int* boardSize) {
	freeTabs(boardSize, *g_tab2, *g_tab);
	int zn2 = KEY_0;
	if (zn == KEY_1) {
		*boardSize = 9;
	}
	else if (zn == KEY_2) {
		*boardSize = 13;
	}
	else if (zn == KEY_3) {
		*boardSize = 19;
	}
	else if (zn == KEY_4) {
		int arr[32];
		int size = 0;
		int place = 1;
		int playerSize = 0;
		gotoxy(MENUX, MENUY + 7);
		_setcursortype(_NORMALCURSOR);
		while (true) {
			zn2 = getch();
			if (zn2 == KEY_ENTER) break;
			else if ((zn2 >= '0') && (zn2 <= '9')) {
				arr[size] = int(zn2) - 48;
				size++;
				putch(zn2);
			}
		}
		_setcursortype(_NOCURSOR);
		for (int i = size - 1; i >= 0; i--) {
			playerSize += (arr[i] * place);
			place *= 10;
		}
		*boardSize = playerSize;
	}
	allocateTabs(boardSize, g_tab2, g_tab);
	stoneSetTab(NONE, *g_tab2, boardSize);
}

//setting on the board appropriate color of the stone if not occupied
bool setOnBoard(enum player_stone_t* player, enum player_stone_t** g_tab2, int* moveTabY, int* moveTabX) {
	if (g_tab2[((wherey() - BOARDY - 1) / 2) + (*moveTabY)][((wherex() - BOARDX - 1) / 4) + (*moveTabX)] == NONE) {
		g_tab2[((wherey() - BOARDY - 1) / 2) + (*moveTabY)][((wherex() - BOARDX - 1) / 4) + (*moveTabX)] = *player;
		return true;
	}
	else {
		return false;
	}
}

//checking if the field is surrounded -> if not suicide
bool checkIfSuicide(int y, int x, enum player_stone_t* player, enum player_stone_t** g_tab2, int* boardSize) {
	int notPut = 0;
	int** arr;
	int free = 0;
	allocatetabChainAndFillWithZero(&arr, boardSize);

	checkIfSuicideLogic(g_tab2, &arr, boardSize, player, y, x - 1, &notPut, free, x, 0);
	checkIfSuicideLogic(g_tab2, &arr, boardSize, player, y, x + 1, &notPut, free, x, (*boardSize - 1));
	checkIfSuicideLogic(g_tab2, &arr, boardSize, player, y - 1, x, &notPut, free, y, 0);
	checkIfSuicideLogic(g_tab2, &arr, boardSize, player, y + 1, x, &notPut, free, y, (*boardSize - 1));

	if (notPut > 3) {
		g_tab2[y][x] = NONE;
		return true;
	}
	return false;
}

void checkIfSuicideLogic(enum player_stone_t** g_tab2, int*** arr, int* boardSize, enum player_stone_t* player, int yNow, int xNow, int* notPut, int free, int checkBoardSide, int boardCondition) {
	if (checkBoardSide != boardCondition) {
		if (g_tab2[yNow][xNow] == *player) {
			check(&g_tab2, arr, boardSize, yNow, xNow, &free, NONE, *player, *player);
			if (free == 0) {
				(*notPut)++;
			}
			free = 0;
			freetabTempChain(*arr, boardSize);
			allocatetabChainAndFillWithZero(arr, boardSize);
		}
		else if (g_tab2[yNow][xNow] != NONE) (*notPut)++;
	}
	else (*notPut)++;
}

//moving over the board and setting conditions for not leaving the board by players
void mvConditions(int zn, int* x, int* y, int* boardSize, int* moveTabY, int* moveTabX, int boardSizeToPrint) {
	int movex = 4;
	int movey = 2;
	int BiggerTabX = 0;
	int BiggerTabY = 0;

	if (zn == 0) {
		zn = getch();
		if (zn == KEY_UP) { //condition for the upper line of the board (not to cross)
			if (((*y) - movey) < (BOARDY + 1)) {
				(*y) = (BOARDY + 1);
				BiggerTabY--;
			}
			else {
				(*y) -= movey;
			}

			if ((BiggerTabY < 0) && (*boardSize > BOARDSIZE_SCROLL) && ((*moveTabY) > 0)) {
				(*moveTabY)--;
			}

		}
		else if (zn == KEY_DOWN) { //condition for the lower line of the board
			if (((*y) + movey) > (BOARDY + ((boardSizeToPrint) * 2) - 1)) {
				(*y) = (BOARDY + ((boardSizeToPrint) * 2) - 1);
				BiggerTabY++;
			}
			else {
				(*y) += movey;
			}

			if ((BiggerTabY > 0) && (*boardSize > BOARDSIZE_SCROLL) && ((*moveTabY) < ((*boardSize) - (boardSizeToPrint)))) {
				(*moveTabY)++;
			}
		}
		else if (zn == KEY_LEFT) { //condition for the left side of the board
			if (((*x) - movex) < (BOARDX + 1)) {
				(*x) = (BOARDX + 1);
				BiggerTabX--;
			}
			else {
				(*x) -= movex;
			}

			if ((BiggerTabX < 0) && (*boardSize > BOARDSIZE_SCROLL) && ((*moveTabX) > 0)) {
				(*moveTabX)--;
			}

		}
		else if (zn == KEY_RIGHT) { //condition for the right side of the board
			if (((*x) + movex) > (BOARDX + ((boardSizeToPrint) * 4) - 3)) {
				(*x) = (BOARDX + ((boardSizeToPrint) * 4) - 3);
				BiggerTabX++;
			}
			else {
				(*x) += movex;
			}

			if ((BiggerTabX > 0) && (*boardSize > BOARDSIZE_SCROLL) && ((*moveTabX) < ((*boardSize) - (boardSizeToPrint)))) {
				(*moveTabX)++;
			}
		}
	}
}


//allocating and deleting used tabs

void allocateTabs(int* boardSize, enum player_stone_t*** g_tab2, char*** g_tab) {
	*g_tab = new char* [((*boardSize) * 2) - 1];
	//*g_tab = (char**)malloc(sizeof(char*) * (((*boardSize) * 2) - 1));

	for (int i = 0; i < ((*boardSize) * 2) - 1; i++) {
		(*g_tab)[i] = new char[((*boardSize) * 4) - 1];
	}

	*g_tab2 = new enum player_stone_t* [*boardSize];
	for (int i = 0; i < *boardSize; i++) {
		(*g_tab2)[i] = new enum player_stone_t[*boardSize];
	}
}

void freeTabs(int* boardSize, enum player_stone_t** g_tab2, char** g_tab) {
	for (int i = 0; i < ((*boardSize) * 2) - 1; i++) {
		delete g_tab[i];
	}
	delete[] g_tab;

	for (int i = 0; i < *boardSize; i++) {
		delete g_tab2[i];
	}
	delete g_tab2;
}

void allocatetabChainAndFillWithZero(int*** arr, int* boardSize) {
	*arr = new int* [*boardSize];

	for (int i = 0; i < (*boardSize); i++) {
		(*arr)[i] = new int[*boardSize];
	}

	for (int i = 0; i < (*boardSize); i++) {
		for (int j = 0; j < (*boardSize); j++) {
			(*arr)[i][j] = 0;
		}
	}
}

void freetabTempChain(int** arr, int* boardSize) {
	for (int i = 0; i < *boardSize; i++) {
		delete arr[i];
	}
	delete arr;
}


//files

bool nameOfFile(char* txt) {
	int zn2 = KEY_0;
	int size = 0;
	while (true) {
		_setcursortype(_NORMALCURSOR);
		zn2 = getch();
		if (zn2 == KEY_ENTER)break;
		else if (((zn2 >= 'A') && (zn2 <= 'Z')) || ((zn2 >= 'a') && (zn2 <= 'z')) || ((zn2 >= '1') && (zn2 <= '9'))) {
			txt[size] = zn2;
			size++;	
			putch(zn2);
		}
	}
	_setcursortype(_NOCURSOR);
	txt[size] = '\0';
	if (size != 0) return true;
	else return false;
}

void intoFile(enum player_stone_t** g_tab2, int* boardSize, Score* score, enum player_stone_t* player) {
	char txt[32];
	menuDuringGame(4);
	gotoxy(MENUX + 1, MENUY + 1);
	int playerFile;

	if (*player == BLACK_ST) playerFile = 0;
	else playerFile = 1;
	if (nameOfFile(txt) != false) {
		sprintf_s(txt, "%s.bin", txt);

		FILE* plik;
		plik = fopen(txt, "ab");
		fwrite((void*)&playerFile, sizeof(int), 1, plik);
		fwrite((void*)boardSize, sizeof(int), 1, plik);
		fwrite((void*)&((*score).white), sizeof(int), 1, plik);
		fwrite((void*)&((*score).black), sizeof(int), 1, plik);
		int temp;
		if (plik != NULL) {
			for (int i = 0; i < *boardSize; i++) {
				for (int j = 0; j < *boardSize; j++) {

					if (g_tab2[i][j] == NONE) {
						temp = NONE_FILE;
						fwrite((void*)&temp, sizeof(int), 1, plik);
					}
					else if (g_tab2[i][j] == BLACK_ST) {
						temp = BLACK_FILE;
						fwrite((void*)&temp, sizeof(int), 1, plik);
					}
					else if (g_tab2[i][j] == WHITE_ST) {
						temp = WHITE_FILE;
						fwrite((void*)&temp, sizeof(int), 1, plik);
					}
					else if (g_tab2[i][j] == DOT_KO) {
						temp = DOT_FILE;
						fwrite((void*)&temp, sizeof(int), 1, plik);
					}

				}
			}
			fclose(plik);
		}
	}
}

bool fromFile(enum player_stone_t*** g_tab2, int* boardSize, char*** g_tab, Score* score, enum player_stone_t* player) {
	int playerTurn;
	clrscr();
	menuDuringGame(4);

	char txt[32];
	if (nameOfFile(txt) == false) return false;
	sprintf_s(txt, "%s.bin", txt);

	FILE* plik;
	plik = fopen(txt, "rb");
	if (plik != NULL) {
		freeTabs(boardSize, *g_tab2, *g_tab);

		fread(&playerTurn, sizeof(int), 1, plik);
		if (playerTurn == 0)*player = BLACK_ST;
		else *player = WHITE_ST;

		fread(boardSize, sizeof(int), 1, plik);
		int* nfromFile = new int[((*boardSize) * (*boardSize)) + 2];

		allocateTabs(boardSize, g_tab2, g_tab);
		stoneSetTab(NONE, *g_tab2, boardSize);

		fread(&((*score).white), sizeof(int), 1, plik);
		fread(&((*score).black), sizeof(int), 1, plik);
		fread(nfromFile, sizeof(int), (((*boardSize) * (*boardSize))), plik);

		setFromFile(g_tab2, boardSize, nfromFile);
		fclose(plik);
		delete[] nfromFile;
	}
	else {
		menuDuringGame(5);
		int zn = KEY_0;
		zn = getch();
		return false;
	}
	return true;
}

void setFromFile(enum player_stone_t*** g_tab2, int* boardSize, int* nfromFile) {
	int k = 0;
	for (int i = 0; i < *boardSize; i++) {
		for (int j = 0; j < *boardSize; j++) {
			if (nfromFile[k] == NONE_FILE) {
				(*g_tab2)[i][j] = NONE;
			}
			else if (nfromFile[k] == BLACK_FILE) {
				(*g_tab2)[i][j] = BLACK_ST;
			}
			else if (nfromFile[k] == WHITE_FILE) {
				(*g_tab2)[i][j] = WHITE_ST;
			}
			else if (nfromFile[k] == DOT_FILE) {
				(*g_tab2)[i][j] = DOT_KO;
			}
			k++;
		}
	}
}


//removing chains

bool checkForOtherPlayerIsSurr(enum player_stone_t*** g_tab2, int* boardSize, enum player_stone_t* player, int moveBackY, int moveBackX, Score* score) {
	int yNow = moveBackY;
	int xNow = moveBackX;
	int** arr;
	int returnTemp = 0;
	allocatetabChainAndFillWithZero(&arr, boardSize);

	int otherPlayer;
	if ((*player) == BLACK_ST) {
		otherPlayer = WHITE_ST;
	}
	else
	{
		otherPlayer = BLACK_ST;
	}

	int free = 0;
	if ((xNow != 0) && ((*g_tab2)[yNow][xNow - 1] == otherPlayer)) {
		checkIfNextToMineIsOtherPlayerThenHisLiberties(g_tab2, &arr, boardSize, player, yNow, xNow - 1, &free, otherPlayer, &returnTemp, score);
	}
	if ((xNow != (*boardSize - 1)) && ((*g_tab2)[yNow][xNow + 1] == otherPlayer)) {
		checkIfNextToMineIsOtherPlayerThenHisLiberties(g_tab2, &arr, boardSize, player, yNow, xNow + 1, &free, otherPlayer, &returnTemp, score);
	}
	if ((yNow != 0) && ((*g_tab2)[yNow - 1][xNow] == otherPlayer)) {
		checkIfNextToMineIsOtherPlayerThenHisLiberties(g_tab2, &arr, boardSize, player, yNow - 1, xNow, &free, otherPlayer, &returnTemp, score);
	}
	if ((yNow != (*boardSize - 1)) && ((*g_tab2)[yNow + 1][xNow] == otherPlayer)) {
		checkIfNextToMineIsOtherPlayerThenHisLiberties(g_tab2, &arr, boardSize, player, yNow + 1, xNow, &free, otherPlayer, &returnTemp, score);
	}
	freetabTempChain(arr, boardSize);

	//chain was destroid so my move is not for sure suicide move
	if (returnTemp > 0) {
		return true;
	}
	return false;
}

void checkIfNextToMineIsOtherPlayerThenHisLiberties(enum player_stone_t*** g_tab2, int*** arr, int* boardSize, enum player_stone_t* player, int yNow, int xNow, int* free, int otherPlayer, int* returnTemp, Score* score) {
	check(g_tab2, arr, boardSize, yNow, xNow, free, NONE, otherPlayer, otherPlayer);
	if ((*free) == 0) {
		chainRemoval(*arr, g_tab2, boardSize, score, otherPlayer);
		(*returnTemp)++;
	}
	freetabTempChain(*arr, boardSize);
	allocatetabChainAndFillWithZero(arr, boardSize);
	(*free) = 0;
}

void check(enum player_stone_t*** g_tab2, int*** arr, int* boardSize, int yNow, int xNow, int* free, int endPlayer, int lookForPlayer, int checkAgain)
{
	if ((*arr)[yNow][xNow] == 1) return;

	(*arr)[yNow][xNow] = 1;
	if (((xNow != 0) && ((*g_tab2)[yNow][xNow - 1] == endPlayer)) || ((xNow != (*boardSize - 1)) //it schouldn't be next to main player (during kiling is NONE, during counting for ex. if I count for white_stones surrounding I dont want to meet black stone)
		&& ((*g_tab2)[yNow][xNow + 1] == endPlayer)) || ((yNow != 0) && ((*g_tab2)[yNow - 1][xNow] == endPlayer))
		|| ((yNow != (*boardSize - 1)) && ((*g_tab2)[yNow + 1][xNow] == endPlayer))) {
		(*free)++;
	}
	else {
		if ((xNow != 0) && ((*g_tab2)[yNow][xNow - 1] == lookForPlayer)) check(g_tab2, arr, boardSize, yNow, xNow - 1, free, endPlayer, lookForPlayer, checkAgain);
		if ((xNow != ((*boardSize) - 1)) && ((*g_tab2)[yNow][xNow + 1] == lookForPlayer)) check(g_tab2, arr, boardSize, yNow, xNow + 1, free, endPlayer, lookForPlayer, checkAgain);
		if ((yNow != 0) && ((*g_tab2)[yNow - 1][xNow] == lookForPlayer)) check(g_tab2, arr, boardSize, yNow - 1, xNow, free, endPlayer, lookForPlayer, checkAgain);
		if ((yNow != ((*boardSize) - 1)) && ((*g_tab2)[yNow + 1][xNow] == lookForPlayer)) check(g_tab2, arr, boardSize, yNow + 1, xNow, free, endPlayer, lookForPlayer, checkAgain);
	}
}

void chainRemoval(int** arr, enum player_stone_t*** g_tab2, int* boardSize, Score* score, int otherPlayer) {
	int scoreCount = 0;
	int x;
	int y;
	for (int i = 0; i < *boardSize; i++) {
		for (int j = 0; j < *boardSize; j++) {
			if (arr[i][j] == 1) {
				scoreCount++;
				y = i;
				x = j;
			}
		}
	}

	if (scoreCount == 1) {
		checkKo(g_tab2, boardSize, score, otherPlayer, y, x);
	}
	else {
		for (int i = 0; i < *boardSize; i++) {
			for (int j = 0; j < *boardSize; j++) {
				if (arr[i][j] == 1) {
					(*g_tab2)[i][j] = NONE;
				}
			}
		}
		if (otherPlayer == BLACK_ST) {
			(*score).white += scoreCount;
		}
		else {
			(*score).black += scoreCount;
		}
	}
}

//KO rule

void checkKo(enum player_stone_t*** g_tab2, int* boardSize, Score* score, int otherPlayer, int y, int x) {
	static int KO = 0;
	static int tempx, tempy;
	enum player_stone_t playerTocheckforKo;

	if (KO == 0) {
		tempx = x;
		tempy = y;
	}

	if (KO == 0) {
		KO++;
		if (otherPlayer == BLACK_ST) {
			(*score).white++;
			playerTocheckforKo = BLACK_ST;
		}
		else {
			(*score).black++;
			playerTocheckforKo = WHITE_ST;
		}
		if (checkForOtherPlayerIsSurr(g_tab2, boardSize, &playerTocheckforKo, y, x, score) == false) (*g_tab2)[tempy][tempx] = NONE;
	}
	else {
		(*g_tab2)[tempy][tempx] = DOT_KO;
		if (otherPlayer == BLACK_ST) {
			(*g_tab2)[y][x] = BLACK_ST;
		}
		else {
			(*g_tab2)[y][x] = WHITE_ST;
		}
		KO--;
	}
}

void outFromKoRule(enum player_stone_t*** g_tab2, int* boardSize, Score* score, int currScoreWhite, int currScoreBlack) {
	int static move = 0;
	for (int i = 0; i < *boardSize; i++) {
		for (int j = 0; j < *boardSize; j++) {
			//checking if during one move is possible to create a situation of killing one chain and second that passes contitions for KO (in this situation we will not consider KO rule)
			if (((*g_tab2)[i][j] == DOT_KO) && ((((*score).white - currScoreWhite) > 1) || (((*score).black - currScoreBlack) > 1))) {
				(*g_tab2)[i][j] = NONE;
				move = 0;
				return;
			}
			else if ((*g_tab2)[i][j] == DOT_KO) {
				if (move > 0) { //next move remove dot from the place where the KO rule applied
					(*g_tab2)[i][j] = NONE;
					move = 0;
					return;
				}
				move++;
				return;
			}
		}
	}
}


//count end points/ count area

void countingPoints(int* boardSize, enum player_stone_t** g_tab2, enum player_stone_t notTosurround, Score* endScore) {
	int** arr;
	int** arr2;
	int yNow, xNow;
	int free = 0;
	int count = 0;
	allocatetabChainAndFillWithZero(&arr, boardSize);
	allocatetabChainAndFillWithZero(&arr2, boardSize);
	for (int i = 0; i < *boardSize; i++) {
		for (int j = 0; j < *boardSize; j++) {
			if ((g_tab2[i][j] == NONE) && (arr2[i][j] != 1)) {
				yNow = i;
				xNow = j;
				check(&g_tab2, &arr, boardSize, yNow, xNow, &free, notTosurround, NONE, NONE);//czy dookoÃÂ¯ÃÂ¿ÃÂ½a biaÃÂ¯ÃÂ¿ÃÂ½e
				if (free != 0) {
					freetabTempChain(arr, boardSize);
					allocatetabChainAndFillWithZero(&arr, boardSize);
				}
				else {
					for (int k = 0; k < *boardSize; k++) {
						for (int p = 0; p < *boardSize; p++) {
							if (arr[k][p] == 1) {
								arr2[k][p] = arr[k][p];
							}
						}
					}
				}
				free = 0;
			}
		}
	}
	
	for (int i = 0; i < *boardSize; i++) {
		for (int j = 0; j < *boardSize; j++) {
			if (notTosurround == BLACK_ST) {
				(*endScore).white += arr2[i][j];
			}
			else {
				(*endScore).black += arr2[i][j];
			}
		}
	}

	freetabTempChain(arr, boardSize);
	freetabTempChain(arr2, boardSize);
}