#include "buildRooms.h"
#include "sudoClasses.h"
#include <stdbool.h>
#include <stdio.h>

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
  printf("player x :%d, y:%d\n", Player.xCoordinate, Player.yCoordinate);
  printf("You look around the room and use your compass to face north.\n\n There "
         "is a "
         "door:\n");
  if (currentRoom.top == true) {
    printf("  Forward \n");
    availableDoorways[0] = true;
  }
  if (currentRoom.left == true) {
    printf("  Left \n");
    availableDoorways[1] = true;
  }
  if (currentRoom.right == true) {
    printf("  Right \n");
    availableDoorways[2] = true;
  }
  if (currentRoom.bottom == true) {
    printf("  Behind \n");
    availableDoorways[3] = true;
  }

  bool processing = true;
  char input;
  printf("\nInput a direction:\n");
  while (processing) {
    scanf("%c", &input);
    fflush(stdin);
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF);
    // printf("input is: %c\n", input);

    if (input == 'w' && availableDoorways[0] == true) {
      // top or forward
      Player.yCoordinate++;
      processing = false;
    } else if (input == 'a' && availableDoorways[1] == true) {
      // left
      Player.xCoordinate--;
      processing = false;
    } else if (input == 'd' && availableDoorways[2] == true) {
      // right
      Player.xCoordinate++;
      processing = false;
    } else if (input == 's' && availableDoorways[3] == true) {
      // bottom or back
      Player.yCoordinate--;
      processing = false;
    } else {
      //printf("invalid input\n");
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
  printf("  Health:   %d/%d\n  Defense:  %d\n  Attack:   %d\n",
         Player.health, Player.maxHealth, Player.defense, Player.attack);
  if (stall) {
    takeInput(0);
  }
}
void checkStatsEntity(struct entity enemy, struct character Player) {
  system("clear");
  checkStatsPlayer(Player, false);
  printf("\n------Enemy------\n");
  printf("  Health:   %d/%d\n  Defense:  %d\n  Attack:   %d\n",
         enemy.health, enemy.maxHealth, enemy.defense, enemy.attack);
  takeInput(0);
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
      printf("Would you like to:\n  Attack -> 1\n  Shield -> 2\n Check Stats "
             "-> 3\n");
      input = takeInput(1);
      switch (input) {
      case 1:
        damage = Player.attack - enemy.defense;
        if (damage < 0){damage = 0;}
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
      case 3:
        checkStatsEntity(enemy, Player);
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

    int randint;
    randint = rand() % 9;
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
    } else if (randint > 4 && randint < 8) {
      enemy.health = enemy.health + enemy.regen;
      if (enemy.health > enemy.maxHealth){
        enemy.health = enemy.maxHealth;
      }
      printf("The monster rests and regains it's strength!\n It's health "
             "increases by %d\n",
             enemy.regen);
      takeInput(0);
    } else if (randint == 8) {
      printf("The monster flinches and does nothing!\n");
      takeInput(0);
    } else {
      printf("alex you are either bad at math or coding becuase the enemy "
             "chose an option that shouldnt exits\n");
      takeInput(0);
    }
    playersTurn = true;

    if (Player.health < 1) {
      Player.alive = false;
    }
    if (enemy.health < 1){
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
// INTERACT WITH CONTENT FUNCTION
// allows player to interact with whatever content is in the room
//////////////////////////////////////////////////////////////////

struct character roomContentInteract(struct character Player,
                                     struct createdRooms currentRoom,
                                     Package classes,
                                     struct createdRoomsList *createdRoomList,
                                     int numRooms) {
  int input = 0;
  if (currentRoom.content == Empty) {
    printf("\n\n------------The Room Is Empty------------\n\n");
    takeInput(0);
    return Player;

  } else if (currentRoom.content == Ladder) {

    // idk how we try and change floors, maybe add a flag to the player i guess
    displayArt(9);
    printf("you just found a ladder, you just found a ladder, you just found a "
           "ladder\n Wonder where it goes?\n");
    printf("   Adventure up the ladder               -> 1\n   Continue exploring the "
           "current floor  -> 2\n");
    input = takeInput(1);
    bool validInput = false;
    while (validInput == false) {
      if (input == 1) {
        printf("Cool air wafts down as you open the trap door at the top of "
               "the ladder\n");
        printf("Ladder is still broken\n");
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

    switch(rand() % 3){
    case 0:
    printf("You find yourself standing in a large cold room\nBefore you sleeps a large dragon\n\n");
    break;
    case 1:
    printf("You find yourself in a narrow corridor with a humanoid figure looming at the end\nIt does not appear to be particularly interested in you, yet\n\n");
    break;
    case 2:
    printf("A figure looms above you\nIt's rocky body almost mistakable for the wall itself\n\n");
    }

    bool validInput = false;
    int input;
    while(validInput == false){
    printf("Would you like to:\n    Fight  -> 1\n    Run    -> 2\n  Check Stats -> 3\n");
    input = takeInput(1);
    if (input == 1) {
        Player = fight(Player, currentRoom, enemy);
        displayArt(6);
        printf("The slain beast leaves behind an orb of light\nThe power inside of it ends you power\n");
        printf("  Increae max health -> 1\n  Increase gaurd    -> 2\n");
        int input2;
        do {
          input2 = takeInput(1);
          if (input2 == 1){
            Player.maxHealth += classes.actions.stat_up;
          }else if(input2 == 2){
            Player.guard += classes.actions.stat_up;
          }else{
            printf("please enter 1 or 2");
          }
        } while(input2 != 1 || input2 != 2);
        clearContent(createdRoomList, currentRoom, numRooms);
        validInput = true;
        takeInput(0);

      } else if (input == 2) {
        printf("You take %d damage, but you get away!\n", enemy.runDamage);
        Player.health = Player.health - enemy.runDamage;
        validInput = true;
        takeInput(0);

      } else if (input == 3) {
        checkStatsPlayer(Player, true);
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
      printf(
          "\n\nAn Enemy stands before you!\n\n  Would you like to:\n    Fight "
          " -> "
          "1\n    Run    -> 2\n  Check Stats -> 3\n");
      input = takeInput(1);
      if (input == 1) {
        Player = fight(Player, currentRoom, enemy);
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
        checkStatsPlayer(Player, true);
      } else {
        printf("invalid input");
      }
    }

  } else if (currentRoom.content == Modifier) {

    switch (rand() % 2) {
    case 0:
      displayArt(6);
      printf("\nYou found a LifeRestore!\n  [+] Health has been fully restored! [+]\n");
      Player.health = Player.maxHealth;
      clearContent(createdRoomList, currentRoom, numRooms);
      takeInput(0);
      break;
    case 1:
      displayArt(8);
      printf("\nYou found steroids!\n  [+] Attack increased by %d [+]\n",
             classes.actions.steriods);
      Player.strength += classes.actions.steriods;
      clearContent(createdRoomList, currentRoom, numRooms);
      takeInput(0);
      break;
    }

  } else if (currentRoom.content == Shop) {
    displayArt(7);
    printf("The Shop is currently Closed");
    takeInput(0);

  } else if (currentRoom.content == Chest) {
    displayArt(0);
    printf("---------You found a Chest!---------\n");
    takeInput(0);
    switch (rand() % 2) {
    case 1:
      printf("\nYou found a LifeUp!\n  [+] Health increased by %d [+]\n",
             classes.actions.life_up);
      takeInput(0);
      break;
    case 0:
      displayArt(1);
      printf("\nYou found a Sword!\n  [+] Attack increased by %d [+]\n",
             classes.actions.steriods);
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
// ART FUNCTION
// call functions to display art
//////////////////////////////////////////////////////////////////
typedef enum {chest, sword, enemy, boss, death, money, bottle, shop, steroids, ladder, shield} chooseArt;

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
   
    printf("           |`-._/\_.-`|               \n");
    printf("           |    ||    |               \n");
    printf("           |___o()o___|               \n");
    printf("           |__((<>))__|               \n");
    printf("           \   o\/o   /               \n");
    printf("            \   ||   /                \n");
    printf("             \  ||  /                 \n");
    printf("              '.||.'                  \n");
    printf("                ``                    \n");
    break;

  }
     
     return 0;
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// START MAIN
//////////////////////////////////////////////////////////////////
int main(void) {

  struct createdRoomsList *currentFloor;

  Package classes;
  classes = psuedoClasses(1);

  struct character Player = classes.Player;

  bool gameLoop = true;
  while (gameLoop) {

    currentFloor = buildRooms();
    struct createdRooms currentRoom;

    // fill rooms with things

    bool floorLoop = true;
    while (floorLoop) {

      currentRoom = findCurrentRoom(Player, currentFloor);
      Player = roomContentInteract(Player, currentRoom, classes, currentFloor,
                                   currentFloor->numberOfRooms);
      Player = movePlayer(Player, currentRoom);
      system("clear");
    }
  }

  free(currentFloor->createdRooms);
  free(currentFloor);
  return 0;
}
//////////////////////////////////////////////////////////////////
///////////////////////////END MAIN///////////////////////////////
//////////////////////////////////////////////////////////////////