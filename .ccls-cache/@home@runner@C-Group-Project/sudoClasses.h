#ifndef SUDO_CLASSES_H
#define SUDO_CLASSES_H


#include <stdio.h>
#include <stdbool.h>

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
};

struct actions {
  int life_up;
  int steriods;
  int stat_up;
};

struct rooms {
  int ladder;
  int enemy;
  int boss;
};

//int runAwayDamage;

typedef struct {
  struct character Player;
  struct entity easyEnemies;
  struct entity mediumEnemies;
  struct entity hardEnemies;
  struct entity boss;
  struct actions actions;
  struct rooms rooms;
  //int runDamage;
} Package;



Package psuedoClasses(int difficulty);

#endif