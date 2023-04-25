#ifndef SUDO_CLASSES_H
#define SUDO_CLASSES_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// defining enum arrays
typedef enum { easy, medium, hard } Enemies; // enemy types

// defining int arrays
struct character {
  int health;
  int maxHealth;
  int defense;
  int strength;
  int attack;
  int money;
  int guard;
  int xCoordinate;
  int yCoordinate;
  bool alive;
  bool ladder;
  int floor;
};

struct entity {
  int health;
  int maxHealth;
  int defense;
  int strength;
  int attack;
  int regen;
  int runDamage;
  int money;
  bool alive;
  int type;
};

struct actions {
  int life_up;
  int steriods;
  int stat_up;
  int armor;
  int sword;
  int money;
};

struct shop{
  int rndShopItem1;
  int rndShopItem2;
  int rndShopItem3;
  int sword;
  int swordCost;
  int armor;
  int armorCost;
  int bookCost;
  int lifeRestoreCost;
};


//int runAwayDamage;

typedef struct {
  struct entity easyEnemies;
  struct entity mediumEnemies;
  struct entity hardEnemies;
  struct entity boss;
  struct actions actions;
  struct shop shopItems;
} Package;


struct character buildPlayer();
Package psuedoClasses(int difficulty);

#endif