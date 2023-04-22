#ifndef SUDO_CLASSES_H
#define SUDO_CLASSES_H

// defining enum arrays
typedef enum { easy, medium, hard } Enemies; // enemy types

// defining int arrays
struct charecter {
  int health;
  int defense;
  int strength;
  int attack;
  int xCoordinate;
  int yCoordinate;
};
struct entity {
  int health;
  int defense;
  int strength;
  int attack;
};

struct actions {
  int life_up;
  int life_fill;
  int stat_up;
};

struct rooms {
  int ladder;
  int enemy;
  int boss;
};

typedef struct package {
  struct charecter Player;
  struct entity easyEnemies;
  struct entity mediumEnemies;
  struct entity hardEnemies;
  struct entity boss;
  struct actions actions;
  struct rooms rooms;
} Package;

struct package psuedoClasses(int difficulty);

#endif