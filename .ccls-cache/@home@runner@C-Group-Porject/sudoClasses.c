#include <stdio.h>

// ??? couldn't figure out
//// enum entity_statistics {health, defense, strength, attack}; 
//// enum statistic_modifiers {life_up, life_fill, defense_up, strength_up}; 
//// enum rooms {ladder, enemy, boss}; 
//// enum items {boots, sword, shield};



// defining int arrays
int player[4] = {1,1,1,1}; // health, defense, strength, attack
int easyEnemies[3] = {1,1,1}; // health, defense, strength
int mediumEnemies[3] = {1,1,1}; // health, defense, strength
int hardEnemies[3] = {1,1,1}; // health, defense, strength
int boss[3] = {1,1,1}; // health, defense, strength
int modifiers[3] = {1,1,1}; // life_up, life_fill, stat_up
int roomTypes[3] = {1,1,1}; // ladder, enemy, boss

int psuedoClasses(int difficulty) {
  
  //player stats
  player[0] = 100; // health
  player[1] = 100; // defense
  player[2] = 100; // strength
  player[3] = 100; // attack

  //easy enemy stats
  easyEnemies[0] = 100; // health
  easyEnemies[1] = 100; // defense
  easyEnemies[2] = 100; // strength

  //medium enemy stats
  mediumEnemies[0] = 100; // health
  mediumEnemies[1] = 100; // defense
  mediumEnemies[2] = 100; // strength

  // hard enemy stats
  hardEnemies[0] = 100; // health
  hardEnemies[1] = 100; // defense
  hardEnemies[2] = 100; // strength

  // boss stats
  boss[0] = 100; // health
  boss[1] = 100; // defense
  boss[2] = 100; // strength

  // modifiers
  modifiers[0] = 100; // life_up
  modifiers[1] = 100; // life_fill
  modifiers[2] = 100; // stat_fill

  // rooms  Probably isn't needed?? we need to decide
  roomTypes[0] = 100; // ladder
  roomTypes[1] = 100; // enemy
  roomTypes[2] = 100; // boss
  
  return 0;  
} // end function psuedoClasses

