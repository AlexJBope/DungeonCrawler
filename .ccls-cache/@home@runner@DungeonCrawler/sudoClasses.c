#include "sudoClasses.h"


struct character buildPlayer(int chooseCharecter){
  // player stats
  struct character Player;
  //balancing
  Player.health = 100;
  Player.maxHealth = Player.health;
  Player.defense = 15;
  Player.attack = 25;
  Player.guard = 15;
  Player.money = 0;
  Player.strength = 30; // NOT USED
  //logic
  Player.xCoordinate = 0;
  Player.yCoordinate = 0;
  Player.alive = true;
  Player.ladder = false;
  Player.floor = 0;
  return Player;
}


Package psuedoClasses(int difficulty) {
  
  // easy enemy stats
  struct entity easyEnemies;
  easyEnemies.maxHealth = 10 + (difficulty*10);
  easyEnemies.health = easyEnemies.maxHealth;    // health
  easyEnemies.defense = 0 + (difficulty*5);    // defense
  easyEnemies.strength = 0 + (difficulty*10);  // strength
  easyEnemies.attack = 10 + (difficulty*10);    // attack
  easyEnemies.regen = 0 + (difficulty*5);     // regen
  easyEnemies.runDamage = 0 + (difficulty*10); // runDamage 
  easyEnemies.money = 5 + (difficulty*5);     // money
  //logic
  easyEnemies.alive = true;


  // medium enemy stats
  int mediumIncrement = 5;
  struct entity mediumEnemies;
  mediumEnemies.maxHealth = easyEnemies.health + mediumIncrement;
  mediumEnemies.health = mediumEnemies.maxHealth;       // health
  mediumEnemies.defense = easyEnemies.defense + mediumIncrement;     // defense
  mediumEnemies.strength = easyEnemies.strength + mediumIncrement;   // strength
  mediumEnemies.attack = easyEnemies.attack + mediumIncrement;       // attack
  mediumEnemies.regen = easyEnemies.regen + mediumIncrement;         // regen
  mediumEnemies.runDamage = easyEnemies.runDamage + mediumIncrement; // runDamage
  mediumEnemies.money = easyEnemies.money + mediumIncrement;         // money
  mediumEnemies.alive = true;

  
  // hard enemy stats
  int hardIncrement = 10;
  struct entity hardEnemies;
  hardEnemies.maxHealth = easyEnemies.health + hardIncrement;
  hardEnemies.health = hardEnemies.maxHealth;         // health
  hardEnemies.defense = easyEnemies.defense + hardIncrement;     // defense
  hardEnemies.strength = easyEnemies.strength + hardIncrement;   // strength
  hardEnemies.attack = easyEnemies.attack + hardIncrement;       // attack
  hardEnemies.regen = easyEnemies.regen + hardIncrement;         // regen
  hardEnemies.runDamage = easyEnemies.runDamage + hardIncrement; // runDamage
  hardEnemies.money = easyEnemies.money + hardIncrement;         // money
  hardEnemies.alive = true;
  


  // boss stats
  struct entity boss;
  boss.maxHealth = 40 + (difficulty*10);
  boss.health = boss.maxHealth;   // health
  boss.defense = 10 + (difficulty*10);  // defense
  boss.attack = 30 + (difficulty*10);
  boss.strength = 100 + (difficulty*10); // strength
  boss.regen = 10 + (difficulty*5);     // regen
  boss.runDamage = 0;
  // logic
  boss.alive = true;
  boss.type = rand() % 3;

  // modifiers
  struct actions modifiers;
  modifiers.life_up = 10;
  modifiers.steriods = 5;
  modifiers.stat_up = 10;
  modifiers.sword = 5;
  modifiers.armor = 5;
  modifiers.money = 10;

  
  struct shop shopItems;
  shopItems.armor = 10;
  shopItems.armorCost = 50;
  shopItems.sword = 10;
  shopItems.swordCost = 50;
  shopItems.lifeRestoreCost = 75;
  shopItems.bookCost = 20;
  shopItems.rndShopItem1 = rand() % 4;
  shopItems.rndShopItem2 = rand() % 4;
  shopItems.rndShopItem3 = rand() % 4;
  
  

  Package package;
  package.easyEnemies = easyEnemies;
  package.mediumEnemies = mediumEnemies;
  package.hardEnemies = hardEnemies;
  package.boss = boss;
  package.actions = modifiers;
  package.shopItems = shopItems;

  return package;
} // end function psuedoClasses