#ifndef LEVEL3_HPP
#define LEVEL3_HPP

#include <cstdlib>
#include <ctime>
#include <windows.h>

// ====================== FUNCTION PROTOTYPES ======================
void drawHero();
void updateHero();
void drawBoss();
void updateBoss();
bool checkCollision(double hx, double hy, double hw, double hh,
	double ex, double ey, double ew, double eh);

// ====================== HERO VARIABLES ======================
int heroHealth = 100;
double heroX = 150;
double heroY = 126;
const double moveSpeed = 5;

// Hero states
bool facingRight = true;
bool isMoving = false;
bool isJumping = false;
bool isFalling = false;
bool isAttacking = false;

// Physics
double jumpVelocity = 0;
const double gravity = 1.2;
const double jumpStrength = 12;
const double groundLevel = 126;

// Dimensions
const int HERO_WIDTH = 120;
const int HERO_HEIGHT = 140;

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

// Animation indexes
int restIndex = 0, walkIndex = 0, jumpIndex = 0, swordIndex = 0;

// ====================== BOSS VARIABLES ======================
double bossX = 1000;
double bossY = 126;
int bossHealth = 300;
bool bossAlive = true;
bool bossAttacking = false;

int bossAttackCooldown = 0;
const int bossAttackDelay = 60;

// Dimensions
const int BOSS_WIDTH = 160;
const int BOSS_HEIGHT = 180;

// ====================== BOSS ANIMATIONS ======================
int bossFrame = 0;
char bossWalk[33][50] = {

	"images\\walk_boss_1.bmp", "images\\walk_boss_2.bmp", "images\\walk_boss_3.bmp", "images\\walk_boss_4.bmp",
	"images\\walk_boss_5.bmp", "images\\walk_boss_6.bmp", "images\\walk_boss_7.bmp", "images\\walk_boss_8.bmp",
	"images\\walk_boss_9.bmp", "images\\walk_boss_10.bmp", "images\\walk_boss_11.bmp", "images\\walk_boss_12.bmp",
	"images\\walk_boss_13.bmp", "images\\walk_boss_14.bmp", "images\\walk_boss_15.bmp", "images\\walk_boss_16.bmp",
	"images\\walk_boss_17.bmp", "images\\walk_boss_18.bmp", "images\\walk_boss_19.bmp", "images\\walk_boss_20.bmp",
	"images\\walk_boss_21.bmp", "images\\walk_boss_22.bmp", "images\\walk_boss_23.bmp", "images\\walk_boss_24.bmp",
	"images\\walk_boss_25.bmp", "images\\walk_boss_26.bmp", "images\\walk_boss_27.bmp", "images\\walk_boss_28.bmp",
	"images\\walk_boss_29.bmp", "images\\walk_boss_30.bmp", "images\\walk_boss_31.bmp", "images\\walk_boss_32.bmp",
	"images\\walk_boss_33.bmp"
};

char bossAttack[55][50] = {

	"images\\hit_0054_1.bmp", "images\\hit_0053_2.bmp", "images\\hit_0052_3.bmp", "images\\hit_0051_4.bmp", "images\\hit_0050_5.bmp",
	"images\\hit_0049_6.bmp", "images\\hit_0048_7.bmp", "images\\hit_0047_8.bmp", "images\\hit_0046_9.bmp", "images\\hit_0045_10.bmp",
	"images\\hit_0044_11.bmp", "images\\hit_0043_12.bmp", "images\\hit_0042_13.bmp", "images\\hit_0041_14.bmp", "images\\hit_0040_15.bmp",
	"images\\hit_0039_16.bmp", "images\\hit_0038_17.bmp", "images\\hit_0037_18.bmp", "images\\hit_0036_19.bmp", "images\\hit_0035_20.bmp",
	"images\\hit_0034_21.bmp", "images\\hit_0033_22.bmp", "images\\hit_0032_23.bmp", "images\\hit_0031_24.bmp", "images\\hit_0030_25.bmp",
	"images\\hit_0029_26.bmp", "images\\hit_0028_27.bmp", "images\\hit_0027_28.bmp", "images\\hit_0026_29.bmp", "images\\hit_0025_30.bmp",
	"images\\hit_0024_31.bmp", "images\\hit_0023_32.bmp", "images\\hit_0022_33.bmp", "images\\hit_0021_34.bmp", "images\\hit_0020_35.bmp",
	"images\\hit_0019_36.bmp", "images\\hit_0018_37.bmp", "images\\hit_0017_38.bmp", "images\\hit_0016_39.bmp", "images\\hit_0015_40.bmp",
	"images\\hit_0014_41.bmp", "images\\hit_0013_42.bmp", "images\\hit_0012_43.bmp", "images\\hit_0011_44.bmp", "images\\hit_0010_45.bmp",
	"images\\hit_0009_46.bmp", "images\\hit_0008_47.bmp", "images\\hit_0007_48.bmp", "images\\hit_0006_49.bmp", "images\\hit_0005_50.bmp",
	"images\\hit_0004_51.bmp", "images\\hit_0003_52.bmp", "images\\hit_0002_53.bmp", "images\\hit_0001_54.bmp", "images\\hit_0000_55.bmp"

};

// ====================== COLLISION FUNCTION ======================
bool checkCollision(double hx, double hy, double hw, double hh,
	double ex, double ey, double ew, double eh) {
	return !(hx + hw < ex || hx > ex + ew || hy + hh < ey || hy > ey + eh);
}

// ====================== HERO FUNCTIONS ======================
void drawHero() {
	if (isAttacking) {
		if (facingRight) iShowBMP(heroX, heroY, swordRight[swordIndex]);
		else iShowBMP2(heroX, heroY, swordLeft[swordIndex],0);
	}
	else if (isJumping || isFalling) {
		if (facingRight) iShowBMP(heroX, heroY, jumpRight[jumpIndex]);
		else iShowBMP2(heroX, heroY, jumpLeft[jumpIndex],0);
	}
	else if (isMoving) {
		if (facingRight) iShowBMP(heroX, heroY, walkRight[walkIndex]);
		else iShowBMP2(heroX, heroY, walkLeft[walkIndex],0);
	}
	else {
		iShowBMP2(heroX, heroY, restAnim[restIndex],0);
	}

	// Health bar
	iSetColor(255, 0, 0);
	iFilledRectangle(heroX+20, heroY + HERO_HEIGHT + 20, HERO_WIDTH, 8);
	iSetColor(0, 255, 0);
	iFilledRectangle(heroX+20, heroY + HERO_HEIGHT + 20, (heroHealth*HERO_WIDTH) / 100, 8);
}

void updateHero() {
	if (isJumping || isFalling) {
		heroY += jumpVelocity;
		jumpVelocity -= gravity;
		if (heroY <= groundLevel){
			heroY = groundLevel;
			isJumping = false;
			isFalling = false;
			jumpVelocity = 0;
		}
	}

	// Animations
	restIndex = (restIndex + 1) % 6;
	if (isMoving) walkIndex = (walkIndex + 1) % 11;
	if (isJumping || isFalling) jumpIndex = (jumpIndex + 1) % 10;
	if (isAttacking){
		swordIndex++;
		if (swordIndex >= 12){
			swordIndex = 0;
			isAttacking = false;
		}
	}
}

// ====================== BOSS FUNCTIONS ======================
void drawBoss(){
	if (!bossAlive) return;
	if (bossAttacking) iShowBMP2(bossX, bossY, bossAttack[bossFrame],0);
	else iShowBMP2(bossX, bossY, bossWalk[bossFrame],0);

	// Health bar
	iSetColor(255, 0, 0);
	iFilledRectangle(bossX+20, bossY + BOSS_HEIGHT + 20, BOSS_WIDTH, 10);
	iSetColor(0, 255, 0);
	iFilledRectangle(bossX+20, bossY + BOSS_HEIGHT + 20, (bossHealth*BOSS_WIDTH) / 300, 10);
}

void updateBoss(){
	if (!bossAlive) return;

	// Movement towards hero
	if (bossX > heroX + HERO_WIDTH) bossX -= 4;
	else if (bossX < heroX - BOSS_WIDTH) bossX += 2;

	// Frame cycle
	if (bossAttacking) bossFrame = (bossFrame + 1) % 200;
	else bossFrame = (bossFrame + 1) % 1500;

	// Attack cooldown
	if (bossAttackCooldown>0) bossAttackCooldown--;

	// Collision
	if (checkCollision(heroX, heroY, HERO_WIDTH, HERO_HEIGHT, bossX, bossY, BOSS_WIDTH, BOSS_HEIGHT)){
		if (isAttacking){
			bossHealth -= 5;
			if (bossHealth <= 0) bossAlive = false;
			isAttacking = false;
		}
		else if (bossAttackCooldown == 0){
			heroHealth -= 10;
			if (heroHealth<0) heroHealth = 0;
			bossAttackCooldown = bossAttackDelay;
			bossAttacking = true;
		}
	}
	else bossAttacking = false;
}

#endif // LEVEL3_HPP