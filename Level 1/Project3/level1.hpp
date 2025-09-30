#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include <cstdlib>   // for rand()
#include <ctime>     // for srand()
#include <windows.h> // for mciSendString if needed

// ====================== HERO VARIABLES ======================
int heroHealth = 100;
bool isHeroDamaged = false;

double heroX = 150;
double heroY = 190;

int killCount = 0;               // total enemies killed
const int requiredKills = 10;    // needed to pass level

int mapX = 0;
int platformX = 0;


// Hero States
int charIndex = 0;
bool idlePosition = true;
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
const double groundLevel = heroY;
const double moveSpeed = 3;

// Dimensions
const int HERO_WIDTH = 80;
const int HERO_HEIGHT = 100;

const int ENEMY_WIDTH = 80;
const int ENEMY_HEIGHT = 100;


// ====================== HERO ANIMATIONS ======================
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
	"images\\sword right _0011_sword right 1.bmp", "images\\sword right _0010_sword right 2.bmp",
	"images\\sword right _0009_sword right 3.bmp", "images\\sword right _0008_sword right 4.bmp",
	"images\\sword right _0007_sword right 5.bmp", "images\\sword right _0006_sword right 6.bmp",
	"images\\sword right _0005_sword right 7.bmp", "images\\sword right _0004_sword right 8.bmp",
	"images\\sword right _0003_sword right 9.bmp", "images\\sword right _0002_sword right 10.bmp",
	"images\\sword right _0001_sword right 11.bmp", "images\\sword right _0000_sword right 12.bmp"
};

char swordLeft[12][100] = {
	"images\\sword left_0011_sword right 1.bmp", "images\\sword left_0010_sword right 2.bmp",
	"images\\sword left_0009_sword right 3.bmp", "images\\sword left_0008_sword right 4.bmp",
	"images\\sword left_0007_sword right 5.bmp", "images\\sword left_0006_sword right 6.bmp",
	"images\\sword left_0005_sword right 7.bmp", "images\\sword left_0004_sword right 8.bmp",
	"images\\sword left_0003_sword right 9.bmp", "images\\sword left_0002_sword right 10.bmp",
	"images\\sword left_0001_sword right 11.bmp", "images\\sword left_0000_sword right 12.bmp",
};


// ====================== ENEMY VARIABLES ======================
double enemyX = 1280;
double enemyY = 190;
int enemyIndex = 0;
const double enemySpeed = 4;

bool isEnemyAlive = true;
bool isEnemyDying = false;

int enemyRespawnCounter = 0;
const int enemyRespawnTime = 75; // frames before respawn

// enemy walk animation
char enemyWalk[12][50] = {
	"images\\mob 1.bmp", "images\\mob 2.bmp", "images\\mob 3.bmp", "images\\mob 4.bmp",
	"images\\mob 5.bmp", "images\\mob 6.bmp", "images\\mob 7.bmp", "images\\mob 8.bmp",
	"images\\mob 9.bmp", "images\\mob 10.bmp", "images\\mob 11.bmp", "images\\mob 12.bmp"
};


// ====================== COLLISION FUNCTION ======================
// General collision detection (rectangular bounding box)
bool checkCollision(double hx, double hy, double hw, double hh,
	double ex, double ey, double ew, double eh) {
	return !(hx + hw < ex ||   // hero is left of enemy
		hx > ex + ew ||   // hero is right of enemy
		hy + hh < ey ||   // hero is below enemy
		hy > ey + eh);    // hero is above enemy
}




// ====================== HERO FUNCTIONS ======================
void movementDraw() {
	if (isAttacking) {
		if (facingRight)
			iShowBMP2(heroX, heroY, swordRight[swordIndex], 0);
		else
			iShowBMP2(heroX, heroY, swordLeft[swordIndex], 0);
	}
	else if (isResting) {
		iShowBMP2(heroX, heroY, restAnim[restIndex], 0);
	}
	else if (isJumping || isFalling) {
		if (facingRight)
			iShowBMP2(heroX, heroY, jumpRight[jumpIndex], 0);
		else
			iShowBMP2(heroX, heroY, jumpLeft[jumpIndex], 0);
	}
	else if (isMoving) {
		if (facingRight)
			iShowBMP2(heroX, heroY, walkRight[charIndex], 0);
		else
			iShowBMP2(heroX, heroY, walkLeft[charIndex], 0);
	}
	else {
		iShowBMP2(heroX, heroY, restAnim[1], 0);
	}



	// 🔹 Draw Hero Health Bar
	iSetColor(255, 0, 0);
	iFilledRectangle(heroX + 50, heroY + HERO_HEIGHT + 50, HERO_WIDTH, 8);
	iSetColor(0, 255, 0);
	iFilledRectangle(heroX + 50, heroY + HERO_HEIGHT + 50, (heroHealth * HERO_WIDTH) / 100, 8);

	// 🔹 Draw Kill Counter
	char killText[50];
	sprintf_s(killText, "Kills: %d / %d", killCount, requiredKills);
	iSetColor(255, 255, 255);
	iText(1100, 680, killText, GLUT_BITMAP_HELVETICA_18);
}

void updateAnimation() {
	if (isMoving) {
		charIndex = (charIndex + 1) % 11;
	}
	if (isResting) {
		restIndex = (restIndex + 1) % 6;
	}
	if (isAttacking) {
		swordIndex++;
		if (swordIndex >= 12) {  // attack finished
			swordIndex = 0;
			isAttacking = false;
		}
	}
	if (isJumping || isFalling) {
		if (jumpIndex < 9) jumpIndex++;
	}
}


/*
void movementKey() {
isMoving = false;

if (!isAttacking) {
if (isKeyPressed('a') || isKeyPressed('A')) {
heroX -= moveSpeed;
isMoving = true;
facingRight = false;
isResting = false;
}
if (isKeyPressed('d') || isKeyPressed('D')) {
heroX += moveSpeed;
isMoving = true;
facingRight = true;
isResting = false;
mapX -= 2;
}
if ((isKeyPressed('w') || isKeyPressed('W')) && !isJumping && !isFalling) {
isJumping = true;
jumpVelocity = jumpStrength;
jumpIndex = 0;
isResting = false;
}
if ((isKeyPressed('s') || isKeyPressed('S')) && !isJumping && !isFalling) {
isFalling = true;
jumpVelocity = -fallSpeed;
jumpIndex = 0;
isResting = false;
}
if (isKeyPressed('e') || isKeyPressed('E')) {
isAttacking = true;
swordIndex = 0;
isResting = false;
}
}

if (!isMoving && !isAttacking && !isJumping && !isFalling) {
isResting = true;
}
else {
isResting = false;
}

if (!isMoving && !isAttacking && !isResting) {
charIndex = 0;
}
}
*/

void movementKey() {
	isMoving = false;

	if (!isAttacking) {
		// Move Left
		if (isKeyPressed('a') || isKeyPressed('A')) {
			if (heroX > 300) {
				// hero can move left freely until near screen edge
				heroX -= moveSpeed;
			}
			else if (mapX < 0) {
				// scroll map right only if background still available
				mapX += moveSpeed;
				enemyX += moveSpeed; // shift enemies too
			}
			isMoving = true;
			facingRight = false;
			isResting = false;
		}

		// Move Right
		if (isKeyPressed('d') || isKeyPressed('D')) {
			if (heroX < 800) {
				// hero can move right freely until near right edge
				heroX += moveSpeed;
			}
			else {
				// scroll map left when hero is at right side
				mapX -= moveSpeed;
				enemyX -= moveSpeed;
			}
			isMoving = true;
			facingRight = true;
			isResting = false;
		}

		// Jump
		if ((isKeyPressed('w') || isKeyPressed('W')) && !isJumping && !isFalling) {
			isJumping = true;
			jumpVelocity = jumpStrength;
			jumpIndex = 0;
			isResting = false;
		}

		// Drop down
		if ((isKeyPressed('s') || isKeyPressed('S')) && !isJumping && !isFalling) {
			isFalling = true;
			jumpVelocity = -fallSpeed;
			jumpIndex = 0;
			isResting = false;
		}

		// Attack
		if (isKeyPressed('e') || isKeyPressed('E')) {
			isAttacking = true;
			swordIndex = 0;
			isResting = false;
		}
	}

	if (!isMoving && !isAttacking && !isJumping && !isFalling) {
		isResting = true;
	}
	else {
		isResting = false;
	}

	if (!isMoving && !isAttacking && !isResting) {
		charIndex = 0;
	}
}


void movementUpdate() {
	if (isJumping || isFalling) {
		heroY += jumpVelocity;
		jumpVelocity -= gravity;

		if (heroY <= groundLevel) {
			heroY = groundLevel;
			isJumping = false;
			isFalling = false;
			jumpVelocity = 0;
			jumpIndex = 0;
		}
	}
}


// ====================== ENEMY FUNCTIONS ======================
void respawnEnemy() {
	enemyX = 1280 + rand() % 300;
	enemyY = 190;
	isEnemyAlive = true;
}

void drawEnemy() {
	if (isEnemyAlive) {
		iShowBMP2(enemyX, enemyY, enemyWalk[enemyIndex], 255);
	}
}

void updateEnemy2() {
	if (!isEnemyAlive) {
		enemyRespawnCounter++;
		if (enemyRespawnCounter > enemyRespawnTime) {
			enemyRespawnCounter = 0;
			respawnEnemy();
		}
		return;
	}

	enemyX -= enemySpeed;
	enemyIndex = (enemyIndex + 1) % 12;

	if (enemyX < -100) {
		isEnemyAlive = false;
		return;
	}

	if (checkCollision(heroX, heroY, HERO_WIDTH, HERO_HEIGHT,
		enemyX, enemyY, ENEMY_WIDTH, ENEMY_HEIGHT)) {

		if (isAttacking) {
			isEnemyAlive = false;
			enemyRespawnCounter = 0;
			killCount++;
		}
		else {
			if (!isHeroDamaged) {
				heroHealth -= 10;
				if (heroHealth < 0) heroHealth = 0;
				isHeroDamaged = true;
			}
		}
	}
	else {
		isHeroDamaged = false;
	}
}

#endif
