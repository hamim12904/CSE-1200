#ifndef LEVEL3_HPP
#define LEVEL3_HPP

#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "iGraphics.h"
#include "level1.hpp" // reuse hero variables and functions

// ====================== LEVEL 3 VARIABLES ======================
int bossX = 1200; // initial boss position
int bossY = 190;

int bossIndex = 0;       // walk animation frame
int bossAttackIndex = 0; // attack animation frame

const double bossSpeed = 2.0;

bool isBossAlive = true;
bool isBossAttacking = false;
bool bossHitDone = false; // track one hit per attack

int heroHitsTaken = 0; // boss hits on hero
const int maxHeroHits = 5;

int bossHealth = 15;   // hero hits to kill boss

// ====================== BOSS ANIMATIONS ======================
// 33 frames walk animation
char bossWalk[33][50] = {
	"images\\boss_walk_1.bmp", "images\\boss_walk_2.bmp", "images\\boss_walk_3.bmp",
	"images\\boss_walk_4.bmp", "images\\boss_walk_5.bmp", "images\\boss_walk_6.bmp",
	"images\\boss_walk_7.bmp", "images\\boss_walk_8.bmp", "images\\boss_walk_9.bmp",
	"images\\boss_walk_10.bmp", "images\\boss_walk_11.bmp", "images\\boss_walk_12.bmp",
	"images\\boss_walk_13.bmp", "images\\boss_walk_14.bmp", "images\\boss_walk_15.bmp",
	"images\\boss_walk_16.bmp", "images\\boss_walk_17.bmp", "images\\boss_walk_18.bmp",
	"images\\boss_walk_19.bmp", "images\\boss_walk_20.bmp", "images\\boss_walk_21.bmp",
	"images\\boss_walk_22.bmp", "images\\boss_walk_23.bmp", "images\\boss_walk_24.bmp",
	"images\\boss_walk_25.bmp", "images\\boss_walk_26.bmp", "images\\boss_walk_27.bmp",
	"images\\boss_walk_28.bmp", "images\\boss_walk_29.bmp", "images\\boss_walk_30.bmp",
	"images\\boss_walk_31.bmp", "images\\boss_walk_32.bmp", "images\\boss_walk_33.bmp"
};

// 55 frames sword attack
char bossAttack[55][50] = {
	"images\\boss_attack_1.bmp", "images\\boss_attack_2.bmp", "images\\boss_attack_3.bmp",
	"images\\boss_attack_4.bmp", "images\\boss_attack_5.bmp", "images\\boss_attack_6.bmp",
	"images\\boss_attack_7.bmp", "images\\boss_attack_8.bmp", "images\\boss_attack_9.bmp",
	"images\\boss_attack_10.bmp", "images\\boss_attack_11.bmp", "images\\boss_attack_12.bmp",
	"images\\boss_attack_13.bmp", "images\\boss_attack_14.bmp", "images\\boss_attack_15.bmp",
	"images\\boss_attack_16.bmp", "images\\boss_attack_17.bmp", "images\\boss_attack_18.bmp",
	"images\\boss_attack_19.bmp", "images\\boss_attack_20.bmp", "images\\boss_attack_21.bmp",
	"images\\boss_attack_22.bmp", "images\\boss_attack_23.bmp", "images\\boss_attack_24.bmp",
	"images\\boss_attack_25.bmp", "images\\boss_attack_26.bmp", "images\\boss_attack_27.bmp",
	"images\\boss_attack_28.bmp", "images\\boss_attack_29.bmp", "images\\boss_attack_30.bmp",
	"images\\boss_attack_31.bmp", "images\\boss_attack_32.bmp", "images\\boss_attack_33.bmp",
	"images\\boss_attack_34.bmp", "images\\boss_attack_35.bmp", "images\\boss_attack_36.bmp",
	"images\\boss_attack_37.bmp", "images\\boss_attack_38.bmp", "images\\boss_attack_39.bmp",
	"images\\boss_attack_40.bmp", "images\\boss_attack_41.bmp", "images\\boss_attack_42.bmp",
	"images\\boss_attack_43.bmp", "images\\boss_attack_44.bmp", "images\\boss_attack_45.bmp",
	"images\\boss_attack_46.bmp", "images\\boss_attack_47.bmp", "images\\boss_attack_48.bmp",
	"images\\boss_attack_49.bmp", "images\\boss_attack_50.bmp", "images\\boss_attack_51.bmp",
	"images\\boss_attack_52.bmp", "images\\boss_attack_53.bmp", "images\\boss_attack_54.bmp",
	"images\\boss_attack_55.bmp"
};

// ====================== LEVEL 3 FUNCTIONS ======================
void drawBoss() {
	if (!isBossAlive) return;

	if (isBossAttacking) {
		iShowBMP2(bossX, bossY, bossAttack[bossAttackIndex], 0);
		bossAttackIndex++;
		if (bossAttackIndex >= 55) {
			bossAttackIndex = 0;
			isBossAttacking = false;
			bossHitDone = false;
			bossX += 150; // move back after attack
		}
	}
	else {
		iShowBMP2(bossX, bossY, bossWalk[bossIndex], 0);
		bossIndex = (bossIndex + 1) % 33;
	}

	// Draw Boss Health Bar
	iSetColor(255, 0, 0);
	iFilledRectangle(bossX, bossY + 120, 120, 10);
	iSetColor(0, 255, 0);
	iFilledRectangle(bossX, bossY + 120, (bossHealth * 120) / 15, 10);
}

void updateBoss() {
	if (!isBossAlive) return;

	// Boss walks toward hero if far
	if (!isBossAttacking && abs(heroX - bossX) > 80) {
		if (bossX > heroX) bossX -= bossSpeed;
		else bossX += bossSpeed;
	}

	// Boss attacks when near hero
	if (!isBossAttacking && abs(heroX - bossX) <= 80) {
		isBossAttacking = true;
		bossAttackIndex = 0;
	}

	// Deal damage to hero once per attack
	if (isBossAttacking && !bossHitDone && bossAttackIndex == 30) {
		heroHitsTaken++;
		heroHealth -= 15;
		if (heroHealth < 0) heroHealth = 0;
		bossHitDone = true;
	}

	// Hero attacks boss
	if (isAttacking && checkCollision(heroX, heroY, HERO_WIDTH, HERO_HEIGHT,
		bossX, bossY, 120, 120)) { // boss hitbox
		bossHealth--;
		if (bossHealth <= 0) {
			isBossAlive = false;
		}
	}

	// Check hero death
	if (heroHitsTaken >= maxHeroHits || heroHealth <= 0) {
		sprintf_s(messageText, 50, "Hero died! Level failed.");
		showMessage = true;
		messageTimer = 0;
		gameState = STATE_MESSAGE;
	}

	// Check boss death
	if (!isBossAlive) {
		sprintf_s(messageText, 50, "Game Completed!");
		showMessage = true;
		messageTimer = 0;
		gameState = STATE_MESSAGE;
	}
}

#endif
