#include "sudoClasses.h"

Package psuedoClasses(int difficulty) {

  // player stats
  struct character Player;
  Player.health = 100;  // health
  Player.maxHealth = Player.health;
  Player.defense = 15;  // defense
  Player.strength = 30; // strength
  Player.attack = 40;   // attack
  Player.guard = 15;
  Player.money = 0;
  Player.xCoordinate = 0;
  Player.yCoordinate = 0;
  Player.alive = true;

  // easy enemy stats
  struct entity easyEnemies;
  easyEnemies.maxHealth = 30;
  easyEnemies.health = easyEnemies.maxHealth;    // health
  easyEnemies.defense = 5;    // defense
  easyEnemies.strength = 10;  // strength
  easyEnemies.attack = 10;    // attack
  easyEnemies.regen = 15;     // regen
  easyEnemies.runDamage = 15; // runDamage 
  easyEnemies.money = 10;     // money
  easyEnemies.alive = true;

  // medium enemy stats
  struct entity mediumEnemies;
  mediumEnemies.maxHealth = easyEnemies.health + 10;
  mediumEnemies.health = mediumEnemies.maxHealth;       // health
  mediumEnemies.defense = easyEnemies.defense + 10;     // defense
  mediumEnemies.strength = easyEnemies.strength + 10;   // strength
  mediumEnemies.attack = easyEnemies.attack + 10;       // attack
  mediumEnemies.regen = easyEnemies.regen + 10;         // regen
  mediumEnemies.runDamage = easyEnemies.runDamage + 10; // runDamage
  mediumEnemies.money = easyEnemies.money + 10;         // money
  mediumEnemies.alive = true;
  
  // hard enemy stats
  struct entity hardEnemies;
  hardEnemies.maxHealth = easyEnemies.health + 10;
  hardEnemies.health = hardEnemies.maxHealth;         // health
  hardEnemies.defense = easyEnemies.defense + 15;     // defense
  hardEnemies.strength = easyEnemies.strength + 15;   // strength
  hardEnemies.attack = easyEnemies.attack + 15;       // attack
  hardEnemies.regen = easyEnemies.regen + 15;         // regen
  hardEnemies.runDamage = easyEnemies.runDamage + 15; // runDamage
  hardEnemies.money = easyEnemies.money + 15;         // money
  hardEnemies.alive = true;
  
  //run away damage
  //runAwayDamage = 30;

  // boss stats
  struct entity boss;
  boss.maxHealth = 100;
  boss.health = boss.maxHealth;   // health
  boss.defense = 20;  // defense
  boss.attack = 30;
  boss.strength = 100; // strength
  boss.regen = 20;     // regen
  boss.alive = true;

  // modifiers
  struct actions modifiers;
  modifiers.life_up = 10;
  modifiers.steriods = 10;
  modifiers.stat_up = 10;

  // rooms  Probably isn't needed?? we need to decide
  struct rooms roomTypes;
  roomTypes.ladder = 100;
  roomTypes.enemy = 100;
  roomTypes.boss = 100;

  Package package;
  //package.runDamage = runAwayDamage;
  package.Player = Player;
  package.easyEnemies = easyEnemies;
  package.mediumEnemies = mediumEnemies;
  package.hardEnemies = hardEnemies;
  package.boss = boss;
  package.actions = modifiers;
  package.rooms = roomTypes;

  return package;
} // end function psuedoClasses