#include "iGraphics.h"
#include <stdlib.h>
#include <time.h>

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Global Variables :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

int screenHeight = 720;
int screenWidth = 1280;

int totalCards = 12; // 6 pairs
int cardW = 125, cardH = 171;

int cardX[12] = { 141, 292, 441, 601,   // row 1
141, 292, 441, 601,   // row 2
141, 292, 441, 601 }; // row 3

int cardY[12] = { 60, 60, 60, 60,
257, 257, 257, 257,
456, 456, 456, 456 };

int cardID[12];       // which image (0–5)
bool faceUp[12];      // card flipped?
bool matched[12];     // card already matched?

int firstPick = -1, secondPick = -1;
bool flipLock = false;
int showCounter = 0;

int moves = 0;
int matchedCount = 0;

int maxMoves = 12;
bool gameOver = false;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Story Variables :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
bool showStory = false;
int storyCardID = -1;   // which story to show
int storyX = 800;       // story coordinates (top-right side)
int storyY = 60;

// story image paths (one for each card pair)
char* storyImages[6] = {
	"images/story 1.bmp", // for cardID 0
	"images/story 2.bmp", // for cardID 1
	"images/story 3.bmp", // for cardID 2
	"images/story 4.bmp", // for cardID 3
	"images/story 5.bmp", // for cardID 4
	"images/story 6.bmp"  // for cardID 5
};

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Move Images :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

// move images (12 total, size 370x86, black background transparent)
char* moveImages[12] = {
	"images/move1.bmp",
	"images/move2.bmp",
	"images/move3.bmp",
	"images/move4.bmp",
	"images/move5.bmp",
	"images/move6.bmp",
	"images/move7.bmp",
	"images/move8.bmp",
	"images/move9.bmp",
	"images/move10.bmp",
	"images/move11.bmp",
	"images/move12.bmp"
};

int moveX = 850; // top-right corner position
int moveY = 543;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Setup :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void setupGame() {
	// Assign 6 pairs: [0,0,1,1,2,2,3,3,4,4,5,5]
	for (int i = 0; i < totalCards; i++) {
		cardID[i] = i / 2;
	}

	// Shuffle cards
	srand(time(0));
	for (int i = totalCards - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int t = cardID[i];
		cardID[i] = cardID[j];
		cardID[j] = t;
	}

	// Reset states
	for (int i = 0; i < totalCards; i++) {
		faceUp[i] = false;
		matched[i] = false;
	}

	firstPick = secondPick = -1;
	flipLock = false;
	moves = 0;
	matchedCount = 0;
	gameOver = false;
	showStory = false;
	storyCardID = -1;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: iDraw :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void iDraw() {
	iClear();

	// Background image (full screen)
	iShowBMP(0, 0, "images/level 2 background.bmp");

	// >>> Show card grid
	for (int i = 0; i < totalCards; i++) {
		if (faceUp[i] || matched[i]) {
			if (cardID[i] == 0) iShowBMP(cardX[i], cardY[i], "images/card 1.bmp");
			if (cardID[i] == 1) iShowBMP(cardX[i], cardY[i], "images/card 2.bmp");
			if (cardID[i] == 2) iShowBMP(cardX[i], cardY[i], "images/card 3.bmp");
			if (cardID[i] == 3) iShowBMP(cardX[i], cardY[i], "images/card 4.bmp");
			if (cardID[i] == 4) iShowBMP(cardX[i], cardY[i], "images/card 5.bmp");
			if (cardID[i] == 5) iShowBMP(cardX[i], cardY[i], "images/card 6.bmp");
		}
		else {
			iShowBMP(cardX[i], cardY[i], "images/card back.bmp");
		}
	}

	// >>> Show remaining move images (start with all 12 visible, decrease after each move)
	int remainingMoves = maxMoves - moves;
	for (int i = 0; i < remainingMoves; i++) {
		iShowBMP2(moveX, moveY, moveImages[i], 0); // black treated as transparent
	}

	// >>> Show story image depending on matched card
	if (showStory && storyCardID >= 0 && storyCardID < 6) {
		iShowBMP2(storyX, storyY, storyImages[storyCardID], 255);
	}

	// >>> Win/Lose messages
	if (matchedCount == totalCards) {
		iSetColor(0, 255, 0);
		iText(500, 100, "YOU WIN! Press R to Restart", GLUT_BITMAP_HELVETICA_18);
	}
	else if (gameOver) {
		iSetColor(255, 0, 0);
		iText(850, 520, "GAME OVER! Press R to Restart", GLUT_BITMAP_HELVETICA_18);
	}
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Mouse :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void iMouseMove(int mx, int my) {
	// Not needed now
}

void iPassiveMouseMove(int mx, int my) {
	// Not needed now
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (flipLock || matchedCount == totalCards || gameOver) return;

		for (int i = 0; i < totalCards; i++) {
			if (!faceUp[i] && !matched[i] &&
				mx >= cardX[i] && mx <= cardX[i] + cardW &&
				my >= cardY[i] && my <= cardY[i] + cardH) {

				faceUp[i] = true;
				PlaySound("Audios\\CardFlip.wav", NULL, SND_ASYNC);
				if (firstPick == -1) {
					firstPick = i;
				}
				else {
					secondPick = i;
					moves++;

					if (cardID[firstPick] == cardID[secondPick]) {
						matched[firstPick] = true;
						matched[secondPick] = true;
						matchedCount += 2;

						// show story for this card type
						storyCardID = cardID[firstPick];  // directly maps to storyImages[]
						showStory = true;

						firstPick = secondPick = -1;
					}
					else {
						flipLock = true;
						showCounter = 11; // ~0.5s delay
					}

					if (moves >= maxMoves && matchedCount < totalCards) {
						gameOver = true;
					}
				}
				break;
			}
		}
	}
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Keyboard :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void iKeyboard(unsigned char key) {
	if (key == 'r' || key == 'R') {
		setupGame();
	}
}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_RIGHT) {
		// Reserved
	}
	if (key == GLUT_KEY_LEFT) {
		// Reserved
	}
	if (key == GLUT_KEY_HOME) {
		// Reserved
	}
}

void fixedUpdate() {
	// nothing for now
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Timer :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void update() {
	if (flipLock) {
		showCounter--;
		if (showCounter <= 0) {
			faceUp[firstPick] = false;
			faceUp[secondPick] = false;
			firstPick = secondPick = -1;
			flipLock = false;
		}
	}
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Main :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
int main() {
	setupGame();
	iInitialize(screenWidth, screenHeight, "Puzzle Game with Story Cards");
	iSetTimer(16, update);
	iStart();
	return 0;
}