#include "iGraphics.h"
#include <ctime>
#include <cstdlib>
#include <windows.h> // For GetAsyncKeyState

// ===================== HERO VARIABLES ======================
int heroHealth = 100;
bool isHeroDamaged = false;
double heroX = 150;
double heroY = 190;

int killCount = 0;
const int requiredKills = 10;

// ===================== MAP AND GAME GLOBALS =====================
int mapX = 0; // Controls map scrolling
int platformX = 0; // Not explicitly used for platforms in the provided code, but kept
int gameWidth = 1280; // Width of a single map segment

// Map image IDs for scrolling background
int map1, map2, map3, map4, map5, map6, map7, map8, map9, map10, map11, map12;

// NEW: Loading screen image ID
int loadingLevel1Image;

// Image ID for the pause screen
int pauseScreenImage; // <--- ADDED THIS LINE

char settingsImage[50] = "images\\setting-image-sound-on.bmp"; // Current settings image (for sound on/off)
bool settingsAlternate = false;    // Track sound toggle

// Control images and current index
char controlImages[4][50] = {
	"images\\D-key-for-right.bmp",
	"images\\walk-left-A-key.bmp",
	"images\\w-key-jump.bmp",
	"images\\Attack-q-with-character.bmp"
};
int currentControlImageIndex = 0; // Index for the currently displayed control image

// ===================== ENUM GAME STATES =====================
enum GameState {
	STATE_HOMEPAGE,
	STATE_MENU,
	STATE_LEVEL1,
	STATE_LEVEL_INTRO,
	STATE_PAUSE,
	STATE_MESSAGE,
	STATE_SETTINGS,
	STATE_CONTROLS,
	STATE_HELP,
	STATE_CREDITS
};

GameState gameState = STATE_HOMEPAGE;

// ===================== GAME STATE VARIABLES =====================
int homepageErButton = 0; // For menu button hover effect
bool prevEscState = false; // To detect single ESC press

bool showMessage = false;
char messageText[50];
int messageTimer = 0;
const int messageDuration = 200;

int introTimer = 0;
const int introDuration = 75; // 1.5 seconds / 0.020 seconds/tick = 75 ticks

// ====================== HERO STATES AND ANIMATION ======================
int charIndex = 0;
bool idlePosition = true; // Not actively used but kept
bool facingRight = true;
bool isMoving = false;
bool isJumping = false;
bool isFalling = false;
bool isAttacking = false;
bool isResting = false;

int swordIndex = 0;
int jumpIndex = 0;
int restIndex = 0;

// Physics
double jumpVelocity = 0;
const double gravity = 1.2;
const double jumpStrength = 12;
const double fallSpeed = 6;
const double groundLevel = heroY; // Assuming heroY is the ground level when game starts
const double moveSpeed = 3;

// Dimensions
const int HERO_WIDTH = 80;
const int HERO_HEIGHT = 100;
const int ENEMY_WIDTH = 80;
const int ENEMY_HEIGHT = 100;

// Hero Animation paths
char restAnim[6][30] = {
	"images\\rest 1.bmp", "images\\rest 2.bmp", "images\\rest 3.bmp",
	"images\\rest 4.bmp", "images\\rest 5.bmp", "images\\rest 6.bmp"
};

char walkRight[11][30] = {
	"images\\right 1.bmp", "images\\right 2.bmp", "images\\right 3.bmp", "images\\right 4.bmp", "images\\right 5.bmp",
	"images\\right 6.bmp", "images\\right 7.bmp", "images\\right 8.bmp", "images\\right 9.bmp", "images\\right 10.bmp", "images\\right 11.bmp"
};

char walkLeft[11][20] = {
	"images\\left 1.bmp", "images\\left 2.bmp", "images\\left 3.bmp", "images\\left 4.bmp", "images\\left 5.bmp",
	"images\\left 6.bmp", "images\\left 7.bmp", "images\\left 8.bmp", "images\\left 9.bmp", "images\\left 10.bmp", "images\\left 11.bmp"
};

char jumpRight[10][30] = {
	"images\\jump right 1.bmp", "images\\jump right  2.bmp", "images\\jump right  3.bmp", "images\\jump right  4.bmp", "images\\jump right  5.bmp",
	"images\\jump right  6.bmp", "images\\jump right  7.bmp", "images\\jump right  8.bmp", "images\\jump right  9.bmp", "images\\jump right  10.bmp"
};

char jumpLeft[10][50] = {
	"images\\jump left_0000_jump right  10.bmp", "images\\jump left_0001_jump right  9.bmp", "images\\jump left_0002_jump right  8.bmp",
	"images\\jump left_0003_jump right  7.bmp", "images\\jump left_0004_jump right  6.bmp", "images\\jump left_0005_jump right  5.bmp",
	"images\\jump left_0006_jump right  4.bmp", "images\\jump left_0007_jump right  3.bmp", "images\\jump left_0008_jump right  2.bmp",
	"images\\jump left_0009_jump right 1.bmp"
};

char swordRight[12][100] = {
	"images\\sword right 1.bmp", "images\\sword right 2.bmp", "images\\sword right 3.bmp", "images\\sword right 4.bmp",
	"images\\sword right 5.bmp", "images\\sword right 6.bmp", "images\\sword right 7.bmp", "images\\sword right 8.bmp",
	"images\\sword right 9.bmp", "images\\sword right 10.bmp", "images\\sword right 11.bmp", "images\\sword right 12.bmp"
};

char swordLeft[12][100] = {
	"images\\sword left 0.bmp", "images\\sword left 1.bmp", "images\\sword left 2.bmp", "images\\sword left 3.bmp",
	"images\\sword left 4.bmp", "images\\sword left 5.bmp", "images\\sword left 6.bmp", "images\\sword left 7.bmp",
	"images\\sword left 8.bmp", "images\\sword left .bmp9", "images\\sword left 10.bmp", "images\\sword left 11.bmp"
};

// ====================== ENEMY VARIABLES ======================
double enemyX = 1280;
double enemyY = 190;
int enemyIndex = 0;
const double enemySpeed = 4;

bool isEnemyAlive = true;
bool isEnemyDying = false; // Not explicitly used, but kept
int enemyRespawnCounter = 0;
const int enemyRespawnTime = 75;

char enemyWalk[12][50] = {
	"images\\mob 1.bmp", "images\\mob 2.bmp", "images\\mob 3.bmp", "images\\mob 4.bmp",
	"images\\mob 5.bmp", "images\\mob 6.bmp", "images\\mob 7.bmp", "images\\mob 8.bmp",
	"images\\mob 9.bmp", "images\\mob 10.bmp", "images\\mob 11.bmp", "images\\mob 12.bmp"
};

// ====================== HELPER FUNCTIONS (DECLARATIONS) ======================
void movementDraw();
void drawEnemy();
void checkHeroStatus();
void movementKey();
void movementUpdate();
void updateAnimation();
void updateEnemy2();

// ====================== COLLISION FUNCTION ======================
bool checkCollision(double hx, double hy, double hw, double hh,
	double ex, double ey, double ew, double eh) {
	return !(hx + hw < ex || hx > ex + ew || hy + hh < ey || hy > ey + eh);
}

// ====================== HERO FUNCTIONS ======================
void movementDraw() {
	if (isAttacking) {
		if (facingRight) iShowBMP2(heroX, heroY, swordRight[swordIndex], 0);
		else iShowBMP2(heroX, heroY, swordLeft[swordIndex], 0);
	}
	else if (isResting) {
		iShowBMP2(heroX, heroY, restAnim[restIndex], 0);
	}
	else if (isJumping || isFalling) {
		if (facingRight) iShowBMP2(heroX, heroY, jumpRight[jumpIndex], 0);
		else iShowBMP2(heroX, heroY, jumpLeft[jumpIndex], 0);
	}
	else if (isMoving) {
		if (facingRight) iShowBMP2(heroX, heroY, walkRight[charIndex], 0);
		else iShowBMP2(heroX, heroY, walkLeft[charIndex], 0);
	}
	else {
		iShowBMP2(heroX, heroY, restAnim[1], 0); // Default idle frame
	}

	// Hero Health Bar
	iSetColor(255, 0, 0);
	iFilledRectangle(heroX + 50, heroY + HERO_HEIGHT + 50, HERO_WIDTH, 8);
	iSetColor(0, 255, 0);
	iFilledRectangle(heroX + 50, heroY + HERO_HEIGHT + 50, (heroHealth * HERO_WIDTH) / 100, 8);

	// Kill Counter
	char killText[50];
	sprintf_s(killText, "Kills: %d / %d", killCount, requiredKills);
	iSetColor(255, 255, 255);
	iText(1100, 680, killText, GLUT_BITMAP_HELVETICA_18);
}

void updateAnimation() {
	if (isMoving) charIndex = (charIndex + 1) % 11;
	if (isResting) restIndex = (restIndex + 1) % 6;
	if (isAttacking) {
		swordIndex++;
		if (swordIndex >= 12) {
			swordIndex = 0;
			isAttacking = false;
		}
	}
	if (isJumping || isFalling) {
		if (jumpIndex < 9) jumpIndex++;
	}
}

void movementKey() {
	isMoving = false;

	if (!isAttacking) { // Cannot move or jump while attacking
		if (GetAsyncKeyState('A') & 0x8000) { // Using GetAsyncKeyState for continuous press
			if (heroX > 300) heroX -= moveSpeed;
			else if (mapX < 0) { mapX += moveSpeed; enemyX += moveSpeed; }
			isMoving = true; facingRight = false; isResting = false;
		}
		if (GetAsyncKeyState('D') & 0x8000) {
			if (heroX < 800) heroX += moveSpeed;
			else { mapX -= moveSpeed; enemyX -= moveSpeed; }
			isMoving = true; facingRight = true; isResting = false;
		}
		if ((GetAsyncKeyState('W') & 0x8000) && !isJumping && !isFalling) {
			isJumping = true; jumpVelocity = jumpStrength; jumpIndex = 0; isResting = false;
		}
		if ((GetAsyncKeyState('S') & 0x8000) && !isJumping && !isFalling) {
			isFalling = true; jumpVelocity = -fallSpeed; jumpIndex = 0; isResting = false;
		}
		if (GetAsyncKeyState('E') & 0x8000) { // Attack key
			isAttacking = true; swordIndex = 0; isResting = false;
			// Play attack sound if desired
		}
	}

	// Determine if hero is resting
	if (!isMoving && !isAttacking && !isJumping && !isFalling) {
		isResting = true;
	}
	else {
		isResting = false;
	}

	// Reset walk animation index if not moving or attacking
	if (!isMoving && !isAttacking && !isResting) {
		charIndex = 0;
	}
}

void movementUpdate() {
	if (isJumping || isFalling) {
		heroY += jumpVelocity;
		jumpVelocity -= gravity;
		if (heroY <= groundLevel) {
			heroY = groundLevel; isJumping = false; isFalling = false;
			jumpVelocity = 0; jumpIndex = 0;
		}
	}
}

// ====================== ENEMY FUNCTIONS ======================
void respawnEnemy() {
	enemyX = 1280 + rand() % 300; // Randomize respawn X position off-screen
	enemyY = 190;
	isEnemyAlive = true;
}

void drawEnemy() {
	if (isEnemyAlive) iShowBMP2(enemyX, enemyY, enemyWalk[enemyIndex], 255);
}

void updateEnemy2() { // Renamed from updateEnemy to avoid confusion, using this one as it's more complete
	if (!isEnemyAlive) {
		enemyRespawnCounter++;
		if (enemyRespawnCounter > enemyRespawnTime) {
			enemyRespawnCounter = 0;
			respawnEnemy();
		}
		return;
	}
	enemyX -= enemySpeed;
	enemyIndex = (enemyIndex + 1) % 12; // Cycle through enemy walk animation

	// If enemy goes off screen, mark it as not alive
	if (enemyX < -ENEMY_WIDTH) { // Use ENEMY_WIDTH to ensure it's fully off screen
		isEnemyAlive = false;
		return;
	}

	// Collision detection with hero
	if (checkCollision(heroX, heroY, HERO_WIDTH, HERO_HEIGHT,
		enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT)) {
		if (isAttacking) {
			// Hero attacked enemy
			isEnemyAlive = false;
			enemyRespawnCounter = 0;
			killCount++;
			// Play enemy death sound or animation here
		}
		else if (!isHeroDamaged) {
			// Enemy damaged hero
			heroHealth -= 10;
			if (heroHealth < 0) heroHealth = 0;
			isHeroDamaged = true; // Prevents continuous damage from one collision
			// Play hero damage sound/animation here
		}
	}
	else {
		isHeroDamaged = false; // Reset damage flag when not colliding
	}
}

// ===================== DRAW MAP =====================
void drawMap() {
	// Draw 12 backgrounds side by side for extensive scrolling
	iShowImage(mapX, 0, 1280, 720, map1);
	iShowImage(mapX + 1 * gameWidth, 0, 1280, 720, map2);
	iShowImage(mapX + 2 * gameWidth, 0, 1280, 720, map3);
	iShowImage(mapX + 3 * gameWidth, 0, 1280, 720, map4);
	iShowImage(mapX + 4 * gameWidth, 0, 1280, 720, map5);
	iShowImage(mapX + 5 * gameWidth, 0, 1280, 720, map6);
	iShowImage(mapX + 6 * gameWidth, 0, 1280, 720, map7);
	iShowImage(mapX + 7 * gameWidth, 0, 1280, 720, map8);
	iShowImage(mapX + 8 * gameWidth, 0, 1280, 720, map9);
	iShowImage(mapX + 9 * gameWidth, 0, 1280, 720, map10);
	iShowImage(mapX + 10 * gameWidth, 0, 1280, 720, map11);
	iShowImage(mapX + 11 * gameWidth, 0, 1280, 720, map12);

	// Reset mapX when background fully scrolled to create an infinite loop effect
	// This would need more sophisticated logic for very long levels,
	// but for now, it resets after 12 screens.
	// You might want to remove this if the level has a definitive end.
	if (mapX <= -(11 * gameWidth)) mapX = 0; // Reset after last map segment
	if (mapX >= gameWidth) mapX = -(11 * gameWidth); // Allow scrolling backwards and loop
}

// ===================== HERO STATUS CHECK =====================
void checkHeroStatus() {
	if (heroHealth <= 0) {
		sprintf_s(messageText, 50, "Level Failed! Kills: %d/%d", killCount, requiredKills);
		showMessage = true;
		messageTimer = 0;

		// Reset game state for next attempt
		heroHealth = 100; heroX = 150; heroY = 190; // Using groundLevel for heroY
		killCount = 0; isEnemyAlive = true;
		enemyX = 1280; enemyY = 190; // Using groundLevel for enemyY
		enemyIndex = 0; enemyRespawnCounter = 0; isEnemyDying = false;
		mapX = 0; // Reset map position

		gameState = STATE_MESSAGE;
	}

	if (killCount >= requiredKills) {
		sprintf_s(messageText, 50, "Level Passed! Kills: %d/%d", killCount, requiredKills);
		showMessage = true;
		messageTimer = 0;

		// Reset game state for next level or return to menu
		heroHealth = 100; heroX = 150; heroY = 190;
		killCount = 0; isEnemyAlive = true;
		enemyX = 1280; enemyY = 190;
		enemyIndex = 0; enemyRespawnCounter = 0; isEnemyDying = false;
		mapX = 0; // Reset map position

		gameState = STATE_MESSAGE; // Transition to message, then maybe next level or menu
	}
}

// ===================== DRAW =====================
void iDraw() {
	iClear();

	switch (gameState) {
	case STATE_HOMEPAGE:
		iShowBMP(0, 0, "images\\game starting screen.bmp");
		// PlaySound("sounds\\bgsong.wav", NULL, SND_ASYNC | SND_LOOP); // REMOVED SOUND
		break;

	case STATE_MENU:
		iShowBMP(0, 0, "images\\menu-screen.bmp");
		if (homepageErButton == 1) {
			int b = iLoadImage("images\\button-new-game-hover.png");
			iShowImage(455, 316, 345, 52, b);
		}
		else if (homepageErButton == 2) {
			int c = iLoadImage("images\\button-settings-hover.png");
			iShowImage(455, 261, 345, 52, c);
		}
		else if (homepageErButton == 3) {
			int d = iLoadImage("images\\button-help-hover.png");
			iShowImage(455, 206, 345, 52, d);
		}
		else if (homepageErButton == 4) {
			int e = iLoadImage("images\\button-credits-hover.png");
			iShowImage(455, 151, 345, 52, e);
		}
		else if (homepageErButton == 5) {
			int f = iLoadImage("images\\button-exit-hover.png");
			iShowImage(455, 96, 345, 52, f);
		}
		break;

	case STATE_SETTINGS:
		iShowBMP(0, 0, settingsImage); // Show current settings image (sound on/off)
		break;

	case STATE_CONTROLS:
		iShowBMP(0, 0, controlImages[currentControlImageIndex]); // Assuming images are full screen or positioned within a background.
		break;

	case STATE_HELP:
		iShowBMP(0, 0, "images\\Help.bmp");
		break;

	case STATE_CREDITS:
		iShowBMP(0, 0, "images\\Credits.bmp");
		break;

	case STATE_LEVEL_INTRO:
	{ // Add curly braces to create a new scope for progressWidth
							  iShowImage(0, 0, 1280, 720, loadingLevel1Image); // Show the loading screen image

							  // Draw loading bar background (red)
							  iSetColor(255, 0, 0);
							  iFilledRectangle(360, 150, 555, 20); // x, y, width, height (width 950-400=550)

							  // Draw loading bar progress (green)
							  iSetColor(0, 255, 0);
							  double progressWidth = 550.0 * introTimer / introDuration; // Calculate green bar width
							  iFilledRectangle(360, 150, progressWidth, 20);
							  break;
	} // Close curly braces

	case STATE_LEVEL1:
		drawMap();
		movementDraw();
		drawEnemy();
		checkHeroStatus(); // Check hero health and kill count
		break;

	case STATE_PAUSE:
		iShowImage(0, 0, 1280, 720, pauseScreenImage); // Use the loaded pause screen image
		break;

	case STATE_MESSAGE:
		iShowBMP(0, 0, "images\\ESC_background.bmp");
		if (showMessage) {
			iSetColor(255, 255, 0);
			iText(480, 360, messageText, GLUT_BITMAP_TIMES_ROMAN_24); // Centered text for messages
		}
		break;

	}
}

// ===================== INPUT HANDLING =====================
void iMouseMove(int mx, int my) {
	// Not explicitly used for game logic, but required by iGraphics
}

void iPassiveMouseMove(int mx, int my) {
	if (gameState == STATE_MENU) {
		homepageErButton = 0; // Reset hover
		if (mx >= 455 && mx <= 800) { // Check horizontal range for all buttons
			if (my >= 316 && my <= 368) homepageErButton = 1; // New Game
			else if (my >= 261 && my <= 313) homepageErButton = 2; // Settings
			else if (my >= 206 && my <= 258) homepageErButton = 3; // Help
			else if (my >= 151 && my <= 203) homepageErButton = 4; // Credits
			else if (my >= 96 && my <= 148) homepageErButton = 5; // Exit
		}
	}
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (gameState == STATE_HOMEPAGE) {
			gameState = STATE_MENU;
		}
		else if (gameState == STATE_MENU) {
			if (homepageErButton == 1) { // New Game
				gameState = STATE_LEVEL_INTRO;
				introTimer = 0;
				showMessage = false; // Ensure message is off
			}
			else if (homepageErButton == 2) { // Settings
				gameState = STATE_SETTINGS;
				// When entering settings, ensure sound toggle is reset to 'on' image
				settingsAlternate = false;
				strcpy_s(settingsImage, "images\\setting-image-sound-on.bmp");
			}
			else if (homepageErButton == 3) { // Help
				gameState = STATE_HELP;
			}
			else if (homepageErButton == 4) { // Credits
				gameState = STATE_CREDITS;
			}
			else if (homepageErButton == 5) { // Exit
				exit(0);
			}
		}
		else if (gameState == STATE_SETTINGS) {
			// Back button for settings (return to menu)
			// Assuming a specific region for a 'back to menu' button from settings
			if (mx >= 465 && mx <= 800 && my >= 190 && my <= 235) { // Example coordinates
				gameState = STATE_MENU;
			}

			// First block toggle (sound on/off)
			if (mx >= 680 && mx <= 940 && my >= 325 && my <= 372) {
				if (!settingsAlternate) {
					strcpy_s(settingsImage, "images\\setting-image-sound-off.bmp");
					settingsAlternate = true;
					// PlaySound(NULL, NULL, 0); // REMOVED SOUND
				}
				else {
					strcpy_s(settingsImage, "images\\setting-image-sound-on.bmp");
					settingsAlternate = false;
					// PlaySound("sounds\\bgsong.wav", NULL, SND_ASYNC | SND_LOOP); // REMOVED SOUND
				}
			}

			// Second block (Control button -> now goes to STATE_CONTROLS)
			if (mx >= 350 && mx <= 930 && my >= 260 && my <= 305) { // Example coordinates for 'Controls' button
				gameState = STATE_CONTROLS;
				currentControlImageIndex = 0; // Reset to the first control image when entering this state
			}
		}
		else if (gameState == STATE_CONTROLS) {
			// Previous image button (left side)
			if (mx >= 76 && mx <= 195 && my >= 255 && my <= 446) { // Adjusted coordinates for click area
				currentControlImageIndex--;
				if (currentControlImageIndex < 0) {
					currentControlImageIndex = sizeof(controlImages) / sizeof(controlImages[0]) - 1; // Loop to last image
				}
			}
			// Next image button (right side)
			else if (mx >= 1100 && mx <= 1228 && my >= 255 && my <= 446) { // Adjusted coordinates for click area
				currentControlImageIndex++;
				if (currentControlImageIndex >= sizeof(controlImages) / sizeof(controlImages[0])) {
					currentControlImageIndex = 0; // Loop to first image
				}
			}
			// Back button on controls page (e.g., in bottom right similar to Help/Credits back)
			else if (mx >= 1120 && mx <= 1270 && my >= 10 && my <= 80) { // Example coordinates for 'Back'
				gameState = STATE_SETTINGS; // Go back to settings
			}
		}
		else if (gameState == STATE_HELP) {
			// Back button on help page
			if (mx >= 700 && mx <= 850 && my >= 120 && my <= 180) { // Specific back button for help
				gameState = STATE_MENU;
			}
		}
		else if (gameState == STATE_CREDITS) {
			// Back button on credits page
			if (mx >= 1120 && mx <= 1270 && my >= 10 && my <= 80) { // Specific back button for credits
				gameState = STATE_MENU;
			}
		}
		else if (gameState == STATE_MESSAGE) {
			// Click to dismiss message and go to menu
			gameState = STATE_MENU;
		}
	}
}

void iKeyboard(unsigned char key) {
	if (gameState == STATE_PAUSE) {
		if (key == 'r' || key == 'R') {
			// Reset all game variables to restart the level

			heroHealth = 100; heroX = 150; heroY = 190;
			killCount = 0;
			isEnemyAlive = true;
			enemyX = 1280;
			enemyY = 190;
			enemyIndex = 0;
			enemyRespawnCounter = 0;
			isEnemyDying = false;
			mapX = 0; // Reset map position

			gameState = STATE_LEVEL1;
		}
		else if (key == 'h' || key == 'H') {
			// Go to homepage and reset game state
			heroHealth = 100;
			heroX = 150;
			heroY = 190;
			killCount = 0;
			isEnemyAlive = true;
			enemyX = 1280;
			enemyY = 190;
			enemyIndex = 0;
			enemyRespawnCounter = 0;
			isEnemyDying = false;
			mapX = 0; // Reset map position

			gameState = STATE_HOMEPAGE;
			// PlaySound(NULL, NULL, 0); // REMOVED SOUND
		}
	}
	else if (key == 'q' || key == 'Q') { // Global exit key
		exit(0);
	}
}

void iSpecialKeyboard(unsigned char key) {
	// Not explicitly used for game logic, but required by iGraphics
}

void iSpecialKeyboardUp(unsigned char key) {
	// Not explicitly used for game logic, but required by iGraphics
}

// ===================== UPDATE FUNCTIONS (TIMERS) =====================
// In your fixedUpdate() function
void fixedUpdate() {
	// Handle ESC key for pausing/resuming
	bool currEsc = (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
	if (currEsc && !prevEscState) {
		if (gameState == STATE_LEVEL1) gameState = STATE_PAUSE;
		else if (gameState == STATE_PAUSE) gameState = STATE_LEVEL1;
		else if (gameState == STATE_CONTROLS) {
			gameState = STATE_SETTINGS;
		}
		else if (gameState == STATE_SETTINGS || gameState == STATE_HELP || gameState == STATE_CREDITS) {
			gameState = STATE_MENU; // Go back to menu from sub-screens
		}
	}
	prevEscState = currEsc;

	// Game logic only when in STATE_LEVEL1
	if (gameState == STATE_LEVEL1) {
		movementKey(); // Process hero movement based on key presses
	}

	// NEW: Handle R and H keys when in PAUSE state using GetAsyncKeyState
	if (gameState == STATE_PAUSE) {
		static bool prevRState = false; // Static to retain state between calls
		static bool prevHState = false;

		bool currRState = (GetAsyncKeyState('R') & 0x8000) != 0;
		bool currHState = (GetAsyncKeyState('H') & 0x8000) != 0;

		if (currRState && !prevRState) { // Detect R key press
			// Reset all game variables to restart the level
			heroHealth = 100; heroX = 150; heroY = 190;
			killCount = 0;
			isEnemyAlive = true;
			enemyX = 1280;
			enemyY = 190;
			enemyIndex = 0;
			enemyRespawnCounter = 0;
			isEnemyDying = false;
			mapX = 0; // Reset map position

			gameState = STATE_LEVEL1;
		}
		else if (currHState && !prevHState) { // Detect H key press
			// Go to homepage and reset game state
			heroHealth = 100;
			heroX = 150;
			heroY = 190;
			killCount = 0;
			isEnemyAlive = true;
			enemyX = 1280;
			enemyY = 190;
			enemyIndex = 0;
			enemyRespawnCounter = 0;
			isEnemyDying = false;
			mapX = 0; // Reset map position

			gameState = STATE_HOMEPAGE;
			// PlaySound(NULL, NULL, 0); // REMOVED SOUND
		}

		prevRState = currRState;
		prevHState = currHState;
	}

	// Message display timer
	if (gameState == STATE_MESSAGE && showMessage) {
		messageTimer++;
		if (messageTimer > messageDuration) {
			showMessage = false;
			gameState = STATE_MENU; // Go back to menu after message
		}
	}

	// Level intro timer
	if (gameState == STATE_LEVEL_INTRO) {
		introTimer++;
		if (introTimer > introDuration) {
			gameState = STATE_LEVEL1; // Start level after intro
			introTimer = 0; // Reset timer for next time
		}
	}
}

// ===================== MAIN FUNCTION =====================
// ===================== MAIN FUNCTION =====================


int main() {
	srand(time(0)); // Seed random number generator

	// Set up iGraphics timers
	iSetTimer(35, movementUpdate);  // Hero physics updates (jump/fall)
	iSetTimer(40, updateEnemy2);    // Enemy movement and collision
	iSetTimer(20, fixedUpdate);     // General game state updates (ESC, messages, intro)
	iSetTimer(60, updateAnimation); // Hero animation updates

	iInitialize(1280, 720, "Project Title"); // Initialize game window

	// Load all background map images
	map1 = iLoadImage("images\\mapbg1.png");
	map2 = iLoadImage("images\\mapbg2.png");
	map3 = iLoadImage("images\\mapbg3.png");
	map4 = iLoadImage("images\\mapbg4.png");
	map5 = iLoadImage("images\\mapbg5.png");
	map6 = iLoadImage("images\\mapbg6.png");
	map7 = iLoadImage("images\\mapbg7.png");
	map8 = iLoadImage("images\\mapbg8.png");
	map9 = iLoadImage("images\\mapbg9.png");
	map10 = iLoadImage("images\\mapbg10.png");
	map11 = iLoadImage("images\\mapbg11.png");
	map12 = iLoadImage("images\\mapbg12.png");

	// Load the new loading screen image
	
		loadingLevel1Image = iLoadImage("images\\loading-level-1.bmp");

	// Load the pause screen image
	pauseScreenImage = iLoadImage("images\\pause_screen.bmp");

	iStart();

	return 0;
}