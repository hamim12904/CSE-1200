#include "iGraphics.h"
#include "level3.hpp"

// ===================== BACKGROUND =====================
char bgImage[50] = "images\\mapboss.bmp";

// ================= GLOBAL ANIMATION FRAMES =================
int heroFrame = 0;        // For idle animation
int heroWalkFrame = 0;    // For walking animation
int heroJumpFrame = 0;    // For jumping animation
int heroSwordFrame = 0;   // For sword attack animation
int bossAttackFrame = 0;  // For boss attacking animation

// ================= KEY STATE FLAGS =================
bool leftPressed = false;
bool rightPressed = false;
bool leftArrow = false;
bool rightArrow = false;

void animateFrames() {
	// Hero idle animation
	heroFrame++;
	if (heroFrame >= 6) heroFrame = 0;

	// Hero walking animation
	if (isMoving) {
		heroWalkFrame++;
		if (heroWalkFrame >= 11) heroWalkFrame = 0;
	}

	// Boss walking animation
	bossFrame++;
	if (bossFrame >= 8) bossFrame = 0;

	// Boss attack animation
	if (bossAttacking) {
		bossAttackFrame++;
		if (bossAttackFrame >= 4) bossAttackFrame = 0;
	}
}

void iDraw() {
	iClear();

	// Draw Background
	iShowBMP(0, 0, bgImage);

	// Draw Hero & Boss
	drawHero();
	drawBoss();

	// Win/Lose messages
	if (!bossAlive) {
		iSetColor(0, 255, 0);
		iText(500, 400, "YOU WIN! Boss defeated!", GLUT_BITMAP_HELVETICA_18);
	}
	if (heroHealth <= 0) {
		iSetColor(255, 0, 0);
		iText(500, 400, "YOU LOSE! Hero is dead!", GLUT_BITMAP_HELVETICA_18);
	}
}

void iKeyboard(unsigned char key) {
	// Attack key
	if (key == 'e' || key == 'E') {
		if (!isAttacking) {
			isAttacking = true;
			swordIndex = 0; // reset attack animation
		}
	}

	// Jump key
	if ((key == 'w' || key == 'W') && !isJumping && !isFalling) {
		isJumping = true;
		jumpVelocity = jumpStrength;
	}

	// Movement keys
	if (key == 'a' || key == 'A') leftPressed = true;
	if (key == 'd' || key == 'D') rightPressed = true;
}

void iKeyboardUp(unsigned char key) {
	if (key == 'a' || key == 'A') leftPressed = false;
	if (key == 'd' || key == 'D') rightPressed = false;
}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_LEFT) leftArrow = true;
	if (key == GLUT_KEY_RIGHT) rightArrow = true;
}

void iSpecialKeyboardUp(unsigned char key) {
	if (key == GLUT_KEY_LEFT) leftArrow = false;
	if (key == GLUT_KEY_RIGHT) rightArrow = false;
}

void iMouseMove(int mx, int my) {}
void iMouse(int button, int state, int mx, int my) {}
void fixedUpdate() {
	// Not needed for your game
}

void iPassiveMouseMove(int mx, int my) {
	// Not needed for your game
}


void iUpdate() {
	// Smooth hero movement
	if (leftPressed || leftArrow) {
		heroX -= moveSpeed;
		facingRight = false;
		isMoving = true;
	}
	else if (rightPressed || rightArrow) {
		heroX += moveSpeed;
		facingRight = true;
		isMoving = true;
	}
	else {
		isMoving = false;
	}

	updateHero();
	updateBoss();
}

int main() {

	iInitialize(1280, 720, "Level 3 - Hero vs Boss");
	iSetTimer(120, animateFrames);  // animation update
	iSetTimer(20, iUpdate);         // movement + fight update

	iStart();
	return 0;
}