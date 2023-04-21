#include <stdio.h>
#include "sudoClasses.h"

struct package psuedoClasses(int difficulty) {

  // player stats
  struct charecter Player;
  Player.defense = 100;  // defense
  Player.strength = 100; // strength
  Player.attack = 100;   // attack
  Player.xCoordinate = 0;
  Player.yCoordinate = 0;

  // easy enemy stats
  struct entity easyEnemies;
  easyEnemies.health = 100;   // health
  easyEnemies.defense = 100;  // defense
  easyEnemies.strength = 100; // strength

  // medium enemy stats
  struct entity mediumEnemies;
  mediumEnemies.health = 100;   // health
  mediumEnemies.defense = 100;  // defense
  mediumEnemies.strength = 100; // strength

  // hard enemy stats
  struct entity hardEnemies;
  hardEnemies.health = 100;   // health
  hardEnemies.defense = 100;  // defense
  hardEnemies.strength = 100; // strength

  // boss stats
  struct entity boss;
  boss.health = 100;   // health
  boss.defense = 100;  // defense
  boss.strength = 100; // strength

  // modifiers
  struct actions modifiers;
  modifiers.life_up = 100;
  modifiers.life_fill = 100;
  modifiers.stat_up = 100;

  // rooms  Probably isn't needed?? we need to decide
  struct rooms roomTypes;
  roomTypes.ladder = 100;
  roomTypes.enemy = 100;
  roomTypes.boss = 100;

  Package package;
  package.Player = Player;
  package.easyEnemies = easyEnemies;
  package.mediumEnemies = mediumEnemies;
  package.hardEnemies = hardEnemies;
  package.boss = boss;
  package.actions = modifiers;
  package.rooms = roomTypes;

  return package;
} // end function psuedoClasses