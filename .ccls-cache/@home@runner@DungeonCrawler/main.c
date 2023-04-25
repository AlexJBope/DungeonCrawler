
#include "buildRooms.h"
#include "sudoClasses.h"

// defining int arrays

//////////////////////////////////////////////////////////////////
// CURRENT ROOM FUNCTION
// outputs the current room
//////////////////////////////////////////////////////////////////
struct createdRooms findCurrentRoom(struct character Player,
                                    struct createdRoomsList *createdRoomList) {
  struct createdRooms currentRoom;

  // gathered the information for current room
  for (int i = 0; i < createdRoomList->numberOfRooms; i++) {
    if (Player.xCoordinate == createdRoomList->createdRooms[i].xCoordinate &&
        Player.yCoordinate == createdRoomList->createdRooms[i].yCoordinate) {
      currentRoom.xCoordinate = createdRoomList->createdRooms[i].xCoordinate;
      currentRoom.yCoordinate = createdRoomList->createdRooms[i].yCoordinate;
      currentRoom.top = createdRoomList->createdRooms[i].top;
      currentRoom.bottom = createdRoomList->createdRooms[i].bottom;
      currentRoom.left = createdRoomList->createdRooms[i].left;
      currentRoom.right = createdRoomList->createdRooms[i].right;
      currentRoom.content = createdRoomList->createdRooms[i].content;
    }
  }
  return currentRoom;
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// MOVE PLAYER FUNCTION
// takes input from user and changes palyer position
//////////////////////////////////////////////////////////////////

struct character movePlayer(struct character Player,
                            struct createdRooms currentRoom) {

  bool availableDoorways[4] = {false}; // order goes -> top, left, right, bottom
  printf(
      "\n\n----Player Stats---------\n\n  Location: %d,%d\n  Floor: %d  Money"
      ":%d\n\n  "
      "Health "
      ": %d/%d  Attack: %d\n  Defense: %d  Gaurd: "
      "%d\n\n-------------------------\n",
      Player.xCoordinate, Player.yCoordinate, Player.floor, Player.money,
      Player.health, Player.maxHealth, Player.attack, Player.defense,
      Player.guard);
  printf(
      "You look around the room and use your compass to face north.\n\n There "
      "is a "
      "door:\n");
  if (currentRoom.top == true) {
    printf("  North (w) \n");
    availableDoorways[0] = true;
  }
  if (currentRoom.left == true) {
    printf("  West (a) \n");
    availableDoorways[1] = true;
  }
  if (currentRoom.right == true) {
    printf("  East (d) \n");
    availableDoorways[2] = true;
  }
  if (currentRoom.bottom == true) {
    printf("  South (s) \n");
    availableDoorways[3] = true;
  }

  bool processing = true;
  char input;
  printf("\n--Input a direction:--\n");
  while (processing) {
    scanf("%c", &input);
    fflush(stdin);
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF);
    // printf("input is: %c\n", input);

    if ((input == 'w' || input == 'W') && availableDoorways[0] == true) {
      // top or forward
      Player.yCoordinate++;
      processing = false;
    } else if ((input == 'a' || input == 'A') && availableDoorways[1] == true) {
      // left
      Player.xCoordinate--;
      processing = false;
    } else if ((input == 'd' || input == 'D') && availableDoorways[2] == true) {
      // right
      Player.xCoordinate++;
      processing = false;
    } else if ((input == 's' || input == 'S') && availableDoorways[3] == true) {
      // bottom or back
      Player.yCoordinate--;
      processing = false;
    } else {
      // printf("invalid input\n");
    }
  }

  return Player;
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// TAKE INPUT FUNCTION
// player presses any number to conitue
//////////////////////////////////////////////////////////////////

int takeInput(int options) {
  if (options == 0) {
    int input;
    printf("\n(press enter to continue)\n");
    scanf("%*c");
    while (input != '\r' && input != '\n' && input != 'EOF') {
      input = getchar();
    }
    // scanf('%d', &input);
    // fflush(stdin);
    system("clear");
    return 0;

  } else if (options == 1) {
    int input;
    scanf("%d", &input);
    fflush(stdin);
    return input;
  }
  return 0;
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// CLEAR CONTENT
// clears the content of a room once the room has been used
//////////////////////////////////////////////////////////////////

void clearContent(struct createdRoomsList *currentFloor,
                  struct createdRooms currentRoom, int numRooms) {
  for (int i = 0; i < numRooms; i++) {
    if (currentFloor->createdRooms[i].xCoordinate == currentRoom.xCoordinate &&
        currentFloor->createdRooms[i].yCoordinate == currentRoom.yCoordinate) {
      currentFloor->createdRooms[i].content = Empty;
      if (currentRoom.content == Shop)
        currentFloor->createdRooms[i].content = ClossedShop;
      i = numRooms;
    }
  }
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// Check Stats
// prints stats of entity
//////////////////////////////////////////////////////////////////

void checkStatsPlayer(struct character Player, bool stall) {
  system("clear");
  printf("------Player------\n");
  printf("  Health:   %d/%d\n  Defense:  %d\n  Attack:   %d\n", Player.health,
         Player.maxHealth, Player.defense, Player.attack);
  if (stall) {
    takeInput(0);
  }
}
void checkStatsEntity(struct entity enemy, struct character Player) {
  system("clear");
  checkStatsPlayer(Player, false);
  printf("\n------Enemy------\n");
  printf("  Health:   %d/%d\n  Defense:  %d\n  Attack:   %d\n", enemy.health,
         enemy.maxHealth, enemy.defense, enemy.attack);
  takeInput(0);
}
void checkStatsFight(struct entity enemy, struct character Player) {
  printf("-------------------------------------------------\n");
  printf("--------Player                      Enemy--------\n\n");
  printf("Health:  %d/%d                    %d/%d\n", Player.health,
         Player.maxHealth, enemy.health, enemy.maxHealth);
  printf("Attack:    %d                         %d\n", Player.attack,
         enemy.attack);
  printf("Defense:   %d                         %d\n", Player.defense,
         enemy.defense);
  printf("Shield:    %d                         \n", Player.guard);
  printf("-------------------------------------------------\n\n");
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// FIGHT
// fight fight fight fight fight fight fight fight
//////////////////////////////////////////////////////////////////

struct character fight(struct character Player, struct createdRooms currentRoom,
                       struct entity enemy) {
  int input;
  bool playersTurn = true;
  int damage;
  bool shield = false;
  while (Player.alive && enemy.alive) {
    while (playersTurn) {
      system("clear");
      checkStatsFight(enemy, Player);
      printf("Would you like to:\n  Attack -> 1\n  Shield -> 2\n");
      input = takeInput(1);
      switch (input) {
      case 1:
        damage = Player.attack - enemy.defense;
        if (damage < 0) {
          damage = 0;
        }
        enemy.health = enemy.health - damage;
        printf("Attack deals %d damage!", damage);
        playersTurn = false;
        takeInput(0);
        input = 0;
        break;
      case 2:
        printf("You raise your guard!");
        playersTurn = false;
        shield = true;
        takeInput(0);
        input = 0;
        break;
      }
    }

    // exits fight upon death of either party
    if (Player.health < 1) {
      Player.alive = false;
    }
    if (enemy.health < 1) {
      displayArt(4);
      printf("The enemy has been slain!\n");
      takeInput(0);
      enemy.alive = false;
    }

    if (Player.alive == false || enemy.alive == false) {
      return Player;
    }

    int randint = rand() % 9;
    
    checkStatsFight(enemy, Player);
    // creates probabilty windows for enemy choices
    if (randint < 5) {
      damage = enemy.attack - Player.defense;
      if (shield) {
        damage = damage - Player.guard;
        shield = false;
      }
      if (damage < 0) {
        damage = 0;
      }
      Player.health = Player.health - damage;
      printf("The Enemy attacks and deals %d damage!\n", damage);
      takeInput(0);
    } else if (randint == 5){
      damage = ((enemy.attack - (enemy.attack % 2)) / 2) - Player.defense;
      if (shield) {
        damage = damage - Player.guard;
        shield = false;
      }
      if (damage < 0) {
        damage = 0;
      }
      Player.health = Player.health - damage;
      printf("The Enemy stumbles, its attack deals %d damage!\n", damage);
      takeInput(0);
    } else if (randint > 5 && randint < 8) {
      enemy.health = enemy.health + enemy.regen;
      if (enemy.health > enemy.maxHealth) {
        enemy.health = enemy.maxHealth;
      }
      printf("The monster rests and regains it's strength!\n Its health "
             "increases by %d\n",
             enemy.regen);
      takeInput(0);
    } else if (randint == 8) {
      printf("The monster flinches and does nothing!\n");
      takeInput(0);
    } else {
      printf("alex you are either bad at math or coding because the enemy "
             "chose an option that shouldnt exist\n");
      takeInput(0);
    }
    playersTurn = true;

    if (Player.health < 1) {
      Player.alive = false;
    }
    if (enemy.health < 1) {
      displayArt(4);
      printf("The enemy has been slain!\n\n");
      takeInput(0);
      displayArt(5);
      enemy.alive = false;
    }
  }
  return Player;
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// DISPLAY SHOP ITEMS FUNCTION
// displays the shop items
//////////////////////////////////////////////////////////////////

struct character displayShopItems(Package classes, struct character Player) {
  printf("\n\nMoney: %d\n\n", Player.money);
  printf("There are three shop items!\n\n");
  switch (classes.shopItems.rndShopItem1) {
  case 0:
    printf("  1 -> $%d  Life Restore\n", classes.shopItems.lifeRestoreCost);
    break;
  case 1:
    printf("  1 -> $%d  Sword  [+] %d Attack [+]\n",
           classes.shopItems.swordCost, classes.shopItems.sword);
    break;
  case 2:
    printf("  1 -> $%d  Armor  [+] %d Defense [+]\n",
           classes.shopItems.armorCost, classes.shopItems.armor);
    break;
  case 3:
    printf("  1 -> $%d  Book\n", classes.shopItems.bookCost);
    break;
  }
  switch (classes.shopItems.rndShopItem2) {
  case 0:
    printf("  2 -> $%d  Life Restore\n", classes.shopItems.lifeRestoreCost);
    break;
  case 1:
    printf("  2 -> $%d  Sword  [+] %d Attack [+]\n",
           classes.shopItems.swordCost, classes.shopItems.sword);
    break;
  case 2:
    printf("  2 -> $%d  Armor  [+] %d Defense [+]\n",
           classes.shopItems.armorCost, classes.shopItems.armor);
    break;
  case 3:
    printf("  2 -> $%d  Book\n", classes.shopItems.bookCost);
    break;
  }
  switch (classes.shopItems.rndShopItem3) {
  case 0:
    printf("  3 -> $%d  Life Restore\n", classes.shopItems.lifeRestoreCost);
    break;
  case 1:
    printf("  3 -> $%d  Sword  [+] %d Attack [+]\n",
           classes.shopItems.swordCost, classes.shopItems.sword);
    break;
  case 2:
    printf("  3 -> $%d  Armor  [+] %d Defense [+]\n",
           classes.shopItems.armorCost, classes.shopItems.armor);
    break;
  case 3:
    printf("  3 -> $%d  Book\n", classes.shopItems.bookCost);
    break;
  }
  printf("  4 -> save money\n");

  int input;
  bool validInput = false;
  while (validInput == false) {
    input = takeInput(1);
    printf("  You bought ");
    if (input == 1) {
      switch (classes.shopItems.rndShopItem1) {
      case 0:
        if (Player.money >= classes.shopItems.lifeRestoreCost) {
          puts("Life Restore!");
          Player.health = Player.maxHealth;
          Player.money -= classes.shopItems.lifeRestoreCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 1:
        if (Player.money >= classes.shopItems.swordCost) {
          puts(" Sword!");
          Player.attack += classes.shopItems.sword;
          Player.money -= classes.shopItems.swordCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 2:
        if (Player.money >= classes.shopItems.armorCost) {
          puts(" Armor!");
          Player.defense += classes.shopItems.armor;
          Player.money -= classes.shopItems.armorCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 3:
        if (Player.money >= classes.shopItems.bookCost) {
          puts(" Book!");
          printf("you read a book with lore about the game");
          Player.money -= classes.shopItems.bookCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;
      }
    }
    if (input == 2) {
      switch (classes.shopItems.rndShopItem2) {
      case 0:
        if (Player.money >= classes.shopItems.lifeRestoreCost) {
          puts("Life Restore!");
          Player.health = Player.maxHealth;
          Player.money -= classes.shopItems.lifeRestoreCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 1:
        if (Player.money >= classes.shopItems.swordCost) {
          puts(" Sword!");
          Player.attack += classes.shopItems.sword;
          Player.money -= classes.shopItems.swordCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 2:
        if (Player.money >= classes.shopItems.armorCost) {
          puts(" Armor!");
          Player.defense += classes.shopItems.armor;
          Player.money -= classes.shopItems.armorCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 3:
        if (Player.money >= classes.shopItems.bookCost) {
          puts(" Book!");
          printf("you read a book with lore about the game");
          Player.money -= classes.shopItems.bookCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;
      }
    }
    if (input == 3) {
      switch (classes.shopItems.rndShopItem3) {
      case 0:
        if (Player.money >= classes.shopItems.lifeRestoreCost) {
          puts("Life Restore!");
          Player.health = Player.maxHealth;
          Player.money -= classes.shopItems.lifeRestoreCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 1:
        if (Player.money >= classes.shopItems.swordCost) {
          puts(" Sword!");
          Player.attack += classes.shopItems.sword;
          Player.money -= classes.shopItems.swordCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 2:
        if (Player.money >= classes.shopItems.armorCost) {
          puts(" Armor!");
          Player.defense += classes.shopItems.armor;
          Player.money -= classes.shopItems.armorCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;

      case 3:
        if (Player.money >= classes.shopItems.bookCost) {
          puts(" Book!");
          printf("you read a book with lore about the game");
          Player.money -= classes.shopItems.bookCost;
          return Player;
        } else {
          printf("You do not have enough money for this item");
        }
        break;
      }
    } else if (input == 4) {
      printf("nothing and choose to save your money\n");
      return Player;
    } else {
      if (input != 4 && input != 3 && input != 2 && input != 1) {
        puts("invalid response");
      }
    }
  }
  printf("shop did not change player values, invlid input, or something");
  return Player;
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// INTERACT WITH CONTENT FUNCTION
// allows player to interact with whatever content is in the room
//////////////////////////////////////////////////////////////////

struct character roomContentInteract(struct character Player,
                                     struct createdRooms currentRoom,
                                     Package classes,
                                     struct createdRoomsList *createdRoomList,
                                     int numRooms) {

  printf(
      "\n\n----Player Stats---------\n\n  Location: %d,%d\n  Floor: %d  Money"
      ":%d\n\n  "
      "Health "
      ": %d/%d  Attack: %d\n  Defense: %d  Gaurd: "
      "%d\n\n-------------------------\n",
      Player.xCoordinate, Player.yCoordinate, Player.floor, Player.money,
      Player.health, Player.maxHealth, Player.attack, Player.defense,
      Player.guard);
  int input = 0;
  if (currentRoom.content == Empty) {
    printf("\n\n  The Room Is Empty\n\n");
    takeInput(0);
    return Player;

  } else if (currentRoom.content == Ladder) {

    displayArt(9);
    printf("you just found a ladder, you just found a ladder, you just "
           "found a "
           "ladder\n Wonder where it goes?\n");
    printf("   Adventure up the ladder               -> 1\n   Continue "
           "exploring the "
           "current floor  -> 2\n");
    input = takeInput(1);
    bool validInput = false;
    while (validInput == false) {
      if (input == 1) {
        printf("Cool air wafts down as you open the trap door at the top of "
               "the ladder\n");

        Player.ladder = true;
        takeInput(0);
        validInput = true;
      } else if (input == 2) {
        printf("You reject the ladder and conitue to explore\n");
        takeInput(0);
        validInput = true;
      }
    }

  } else if (currentRoom.content == Boss) {
    struct entity enemy;
    enemy = classes.boss;

    switch (enemy.type) {
    case 0:
      printf("You find yourself standing in a large cold room\nBefore you "
             "sleeps a large dragon\n\n");
      break;
    case 1:
      printf("You find yourself in a narrow corridor with a humanoid figure "
             "looming at the end\nIt does not appear to be particularly "
             "interested in you, yet\n\n");
      break;
    case 2:
      printf("A figure looms above you\nIt's rocky body almost mistakable for "
             "the wall itself\n\n");
    }

    bool validInput = false;
    int input;
    while (validInput == false) {
      printf("Would you like to:\n    Fight  -> 1\n    Run    -> 2\n  Check "
             "Stats -> 3\n");
      input = takeInput(1);
      if (input == 1) {
        Player = fight(Player, currentRoom, enemy);
        if (Player.alive == false)
          return Player;
        displayArt(6);
        printf("The slain beast leaves behind an orb of light\nThe power "
               "inside of it lends you its power\n");
        printf("  Increae max health -> 1\n  Increase gaurd    -> 2\n");
        int input2;
        bool processing;
        do {
          input2 = takeInput(1);
          if (input2 == 1) {
            Player.maxHealth += classes.actions.stat_up;
            system("clear");
            displayArt(11);
            printf("  [+]  Max Health has been increased by %d! [+]\n",
                   classes.actions.stat_up);
            processing = false;
          } else if (input2 == 2) {
            Player.guard += classes.actions.stat_up;
            system("clear");
            displayArt(10);
            printf("  [+]  Gaurd has been increased by %d! [+]\n",
                   classes.actions.stat_up);
            processing = false;
          } else {
            printf("please enter 1 or 2");
          }
        } while (processing);
        clearContent(createdRoomList, currentRoom, numRooms);
        validInput = true;
        takeInput(0);

      } else if (input == 2) {
        printf("You are able to sneak away without repercussion\n"),
            validInput = true;
        takeInput(0);

      } else if (input == 3) {
        checkStatsEntity(enemy, Player);
      } else {
        printf("invalid input");
      }
    }

  } else if (currentRoom.content == Enemy) {

    struct entity enemy;

    switch (rand() % 3) {
    case 0:
      // easyEnemy
      enemy = classes.easyEnemies;
      break;
    case 1:
      // mediumEnemy
      enemy = classes.mediumEnemies;
      break;
    case 2:
      // hardEnemy
      enemy = classes.hardEnemies;
      break;
    }

    bool validInput = false;
    while (validInput == false) {
      printf("\n\nAn Enemy stands before you!\n\n  Would you like to:\n    "
             "Fight "
             " -> "
             "1\n    Run    -> 2\n  Check Stats -> 3\n");
      input = takeInput(1);
      if (input == 1) {
        Player = fight(Player, currentRoom, enemy);
        if (Player.alive == false)
          return Player;
        currentRoom.content = Empty;
        displayArt(5);
        printf("You found %d Money!\n", enemy.money);
        Player.money += enemy.money;
        clearContent(createdRoomList, currentRoom, numRooms);
        validInput = true;
        takeInput(0);

      } else if (input == 2) {
        printf("You take %d damage, but you get away!\n", enemy.runDamage);
        Player.health = Player.health - enemy.runDamage;
        validInput = true;
        takeInput(0);

      } else if (input == 3) {
        checkStatsEntity(enemy, Player);
      } else {
        printf("invalid input");
      }
    }

  } else if (currentRoom.content == Modifier) {

    switch (rand() % 4) {
    case 0:
      displayArt(6);
      printf("\nYou found a LifeRestore!\n  [+] Health has been fully "
             "restored! [+]\n");
      Player.health = Player.maxHealth;
      clearContent(createdRoomList, currentRoom, numRooms);
      takeInput(0);
      break;
    case 1:
      displayArt(8);
      printf("\nYou found Steroids!\n  [+] Attack increased by %d [+]\n",
             classes.actions.steriods);
      Player.attack += classes.actions.steriods;
      clearContent(createdRoomList, currentRoom, numRooms);
      takeInput(0);
      break;
    case 2:
      displayArt(5);
      printf("\nYou found %d Money!\n", classes.actions.money);
      Player.money += classes.actions.money;
      clearContent(createdRoomList, currentRoom, numRooms);
      takeInput(0);
      break;
    case 3:
      displayArt(5);
      printf("\nYou found %d Money!\n", classes.actions.money);
      Player.money += classes.actions.money;
      clearContent(createdRoomList, currentRoom, numRooms);
      takeInput(0);
      break;
    }

  } else if (currentRoom.content == Shop) {
    displayArt(7);
    puts("    Welcome to the Shop!\n");
    takeInput(0);
    int moneyBeforeShop = Player.money;
    Player = displayShopItems(classes, Player);
    takeInput(0);
    if (Player.money != moneyBeforeShop)
      clearContent(createdRoomList, currentRoom, numRooms);

  } else if (currentRoom.content == ClossedShop) {
    displayArt(7);
    puts("    The Shop is closed\n");
    takeInput(0);
  } else if (currentRoom.content == Chest) {
    displayArt(0);
    printf("---------You found a Chest!---------\n");
    takeInput(0);
    switch (rand() % 3) {
    case 0:
      printf("\nYou found a LifeRestore!\n  [+] Health fully restored! [+]\n");
      Player.health = Player.maxHealth;
      takeInput(0);
      break;
    case 1:
      displayArt(1);
      printf("\nYou found a Sword!\n  [+] Attack increased by %d [+]\n",
             classes.actions.sword);
      Player.attack += classes.actions.sword;
      takeInput(0);
      break;
    case 2:
      // display armor
      printf("\nYou found Armor!\n  [+] Defense increased by %d [+]\n",
             classes.actions.armor);
      Player.defense += classes.actions.armor;
      takeInput(0);
      break;
    }
    clearContent(createdRoomList, currentRoom, numRooms);
  } else {
    printf("error, content in room x: %dy:%d, is not valid",
           currentRoom.xCoordinate, currentRoom.yCoordinate);
    takeInput(0);
  }

  return Player;
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// DISCOVER ROOM FUNCTION
// marks a room as discovered
//////////////////////////////////////////////////////////////////

void discoverRoom(struct createdRoomsList *currentFloor,
                  struct createdRooms currentRoom, int numRooms) {
  for (int i = 0; i < numRooms; i++) {
    if (currentFloor->createdRooms[i].xCoordinate == currentRoom.xCoordinate &&
        currentFloor->createdRooms[i].yCoordinate == currentRoom.yCoordinate) {
      currentFloor->createdRooms[i].discovered = true;
      i = numRooms;
    }
  }
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// DISPLAY ART FUNCTION
// call functions to display art
//////////////////////////////////////////////////////////////////
typedef enum {
  chest,
  sword,
  enemy,
  boss,
  death,
  money,
  bottle,
  shop,
  steroids,
  ladder,
  shield,
  heart
} chooseArt;

int displayArt(chooseArt choice) {
  switch (choice) {
  case chest:
    printf("                                      \n");
    printf("         _______________              \n");
    printf("       |\\   \\\\    \\\\    \\       \n");
    printf("       | \\   \\\\     \\\\   \\      \n");
    printf("       |\\|____||_____||___|          \n");
    printf("       | |       | |      |           \n");
    printf("       \\ |       |-|      |          \n");
    printf("        \\|________________|          \n");
    printf("                                      \n");
    break;
  case sword:
    printf("                                      \n");
    printf("           /| _________________       \n");
    printf("     O|===|* >________________/       \n");
    printf("           \\|                        \n");
    printf("                                      \n");
    break;

  case bottle:
    printf("                                      \n");
    printf("      _____       \n");
    printf("     `.___,'      \n");
    printf("      (___)       \n");
    printf("      <   >       \n");
    printf("       ) (        \n");
    printf("      /`-.\\      \n");
    printf("     /     \\     \n");
    printf("    / _    _\\    \n");
    printf("   :,' `-.' `:    \n");
    printf("   |         |    \n");
    printf("   :         ;    \n");
    printf("    \\       /    \n");
    printf("     `.___.'      \n");
    break;

  case boss:
    printf("                                      \n");
    printf("                                      \n");
    printf("                                      \n");
    printf("                                      \n");
    printf("                                      \n");
    printf("                                      \n");
    printf("                                      \n");
    printf("                                      \n");
    printf("                                      \n");
    break;

  case death:
    printf("             \n");
    printf("  .-\"\"\"-.    \n");
    printf(" / _   _ \\   \n");
    printf(" |(_' '_)|   \n");
    printf(" `-. ^ .-'   \n");
    printf("   |||||     \n");
    printf("   `---'     \n");
    printf("             \n");
    break;

  case money:
    printf("                  _______________                  \n");
    printf("      __,.,---'''''              '''''---..._      \n");
    printf("   ,-'             .....:::''::.:            '`-.  \n");
    printf("  '           ...:::.....       '                  \n");
    printf("              ''':::'''''       .               ,  \n");
    printf("  |'-.._           ''''':::..::':          __,,-   \n");
    printf("   '-.._''`---.....______________.....---''__,,-   \n");
    printf("        ''`---........................---''        \n");
    printf("                                                   \n");
    break;

  case shop:
    printf("                                      \n");
    printf("   ____________________________________________________   \n");
    printf("  |____________________________________________________|  \n");
    printf("  | __     __   ____   ___ ||  ____    ____     _  __  |  \n");
    printf("  ||  |__ |--|_| || |_|   |||_|**|*|__|+|+||___| ||  | |  \n");
    printf("  ||==|^^||--| |=||=| |=*=||| |~~|~|  |=|=|| | |~||==| |  \n");
    printf("  ||  |##||  | | || | |RUN|||-|  | |==|+|+||-|-|~||__| |  \n");
    printf("  ||__|__||__|_|_||_|_|___|||_|__|_|__|_|_||_|_|_||__|_|  \n");
    printf("  ||_______________________||__________________________|  \n");
    printf("  | _____________________  ||      __   __  _  __    _ |  \n");
    printf("  ||=|=|=|=|=|=|=|=|=|=|=| __..\\/ |  |_|  ||#||==|  / /|  \n");
    printf("  || | | | | | | | | | | |/\\ \\  \\\\|++|=|  || ||==| / / |  \n");
    printf("  ||_|_|_|_|_|_|_|_|_|_|_/_/\\_.___\\__|_|__||_||__|/_/__|  \n");
    printf("  |____________________ /\\~()/()~//\\ __________________|  \n");
    printf("  | __   __    _  _     \\_  (_ .  _/ _    ___     _____|  \n");
    printf("  ||~~|_|..|__| || |_ _   \\ //\\\\ /  |=|__|~|~|___| | | |  \n");
    printf("  ||--|+|^^|==|1||2| | |__/\\ __ /\\__| |==|x|x|+|+|=|=|=|  \n");
    printf("  ||__|_|__|__|_||_|_| /  \\ \\  / /  \\_|__|_|_|_|_|_|_|_|  \n");
    printf("  |_________________ _/    \\/\\/\\/    \\_ _______________|  \n");
    printf("  | _____   _   __  |/      \\../     \\|  __   __   ___|| \n");
    printf("  ||_____|_| |_|##|_||   |   \\/ __|   ||_|==|_|++|_|-|||  \n");
    printf("  ||______||=|#|--| |\\   \\   o    /   /| |  |~|  | | |||  \n");
    printf("  ||______||_|_|__|_|_\\   \\  o   /   /_|_|__|_|__|_|_|||  \n");
    printf("  |_________ __________\\___\\____/___/___________ ______|  \n");
    printf("  |__    _  /    ________     ______           /| _ _ _|  \n");
    printf("  |\\ \\  |=|/   //    /| //   /  /  / |        / ||%|%|%|  \n");
    printf("  | \\/\\ |*/  .//____//.//   /__/__/ (_)      /  ||=|=|=|  \n");
    printf("__|  \\/\\|/   /(____|/ //                    /  /||~|~|~|__\n");
    printf("  |___\\_/   /________//   ________         /  / ||_|_|_|  \n");
    printf("  |___ /   (|________/   |\\_______\\       /  /| |______|  \n");
    printf("      /                  \\|________)     /  / | |         \n");
    printf("                                                   \n");
    break;

  case steroids:
    printf("                         \n");
    printf(" |___|________|_         \n");
    printf(" |___|________|_|-----   \n");
    printf(" |   |        |      .  \n");
    printf("                    .    \n");
    printf("                      .  \n");
    printf("                   .     \n");
    printf("                         \n");
    break;

  case ladder:
    printf("                \n");
    printf("      ╬═╬       \n");
    printf("      ╬═╬       \n");
    printf("      ╬═╬       \n");
    printf("      ╬═╬       \n");
    printf("      ╬═╬       \n");
    printf("      ╬═╬       \n");
    printf("                \n");
    break;

  case shield:
    printf("                                      \n");
    printf("           |`-._/\\_.-`|               \n");
    printf("           |    ||    |               \n");
    printf("           |___o()o___|               \n");
    printf("           |__((<>))__|               \n");
    printf("           \\   o\\/o   /               \n");
    printf("            \\   ||   /                \n");
    printf("             \\  ||  /                 \n");
    printf("              '.||.'                  \n");
    printf("                ``                    \n");
    printf("                                      \n");
    break;

  case heart:
    printf("                        \n");
    printf("        ,d88b.d88b,     \n");
    printf("        88888888888     \n");
    printf("        `Y8888888Y'     \n");
    printf("          `Y888Y'       \n");
    printf("            `Y'         \n");
    printf("                        \n");
  }

  return 0;
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

struct createdRoomsList *currentFloor;
Package classes;
struct character Player;
struct createdRooms currentRoom;
bool floorLoop;
bool gameLoop;

//////////////////////////////////////////////////////////////////
// START MAIN
//////////////////////////////////////////////////////////////////
int main(void) {
  system("clear");

  Player = buildPlayer(0);

  gameLoop = true;
  while (gameLoop) {

    currentFloor = buildRooms();
    Player.xCoordinate = 0;
    Player.yCoordinate = 0;
    Player.floor += 1;

    classes = psuedoClasses(Player.floor);
    
    floorLoop = true;
    while (floorLoop) {

      // Player.xCoordinate = -4; // FOR TEST PURPOSES
      // Player.yCoordinate = 2; // FOR TEST PURPOSES

      currentRoom = findCurrentRoom(Player, currentFloor);
      Player = roomContentInteract(Player, currentRoom, classes, currentFloor,
                                   currentFloor->numberOfRooms);
      // printf("finishing content interaction\n");
      if (Player.ladder == false && Player.alive) {
        showRooms(currentFloor->createdRooms, currentFloor->numberOfRooms, 2,
                  currentRoom);
        Player = movePlayer(Player, currentRoom);
        currentRoom = findCurrentRoom(Player, currentFloor);
        discoverRoom(currentFloor, currentRoom, currentFloor->numberOfRooms);
      } else if (Player.ladder == true) {
        Player.ladder = false;
        system("clear");
        puts("\n\n\n      *ladder noises*    \n\n\n");
        takeInput(0);
        floorLoop = false;
      } else if (Player.alive == false) {
        system("clear");
        puts("\n\n\n      you died :)");
        takeInput(0);
        floorLoop = false;
        gameLoop = false;
      } else {
        puts("error in main loop player somehow isnt dead and isnt on a "
             "ladder "
             "yet isn't in the loop");
      }

      system("clear");
    }
    free(currentFloor->createdRooms);
    free(currentFloor);
    // free(buildRooms());
    // free(currentFloor->numberOfRooms);
  }

  puts("game lore becuase ur dead and you learn stuff because of it, maybe "
       "learn based off of floor? idk idc");

  return 0;
}
//////////////////////////////////////////////////////////////////
///////////////////////////END MAIN///////////////////////////////
//////////////////////////////////////////////////////////////////