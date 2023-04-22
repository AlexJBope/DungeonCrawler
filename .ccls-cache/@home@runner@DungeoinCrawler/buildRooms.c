#include "buildRooms.h"

// Initialize/

// index + 1 == amount of doors, value is the amount of that room
int roomsToCreate[AMOUNT_ROOMS] = {0};
// rooms, and 4 four door rooms

struct createdRooms createdRooms[MAGIC_NUMBER];

int randint(int n);
int numRoomsGenerated;
int randNum;
size_t numRooms;

//////////////////////////////////////////////////////////////////
// BUILD ROOMS FUNCTION
// this function creates the map for the game
//////////////////////////////////////////////////////////////////
struct createdRoomsList *buildRooms(void) {

  srand(time(NULL));
  //srand(5);
  struct openDoor openDoors[MAGIC_NUMBER] = {0};

  for (int i = 1; i < AMOUNT_ROOMS; i++) {
    // this balances the amount of rooms of each type
    randNum = (rand() % 4) + 1;
    roomsToCreate[i] = randNum;
    numRooms += randNum;
    // printf("amount of  %d door rooms: %d\n", i + 1,
    //        roomsToCreate[i]); // error checking
  }

  //  starting room
  numRooms++; // add for strating room
  createdRooms[0].xCoordinate = 0;
  createdRooms[0].yCoordinate = 0;
  createdRooms[0].top = true;
  createdRooms[0].bottom = false;
  createdRooms[0].right = false;
  createdRooms[0].left = false;

  int amountOpenDoors = 0;

  for (int i = 1; i < numRooms; i++) {

    int nextRoom = (rand() % 3) + 1;

    // makes sure next Room is an index for a room type that still needs to be
    // created, this may create an infinite loop as currently written
    // while (roomsToCreate[nextRoom] == 0) {
    //   int nextRoom = (rand() % 3) + 1;
    // }

    // printf("\n ---NEW LOOP--- \nlength of the createdRooms: %zu\n",
    // numRooms);

    amountOpenDoors = checkOpenDoors(createdRooms, openDoors, numRooms);

    // for (int i = 0; i < numRooms; i++) {
    //   struct openDoor openDoor = openDoors[i];
    //   printf("x: %d, y: %d\n", openDoor.xCoordinate, openDoor.yCoordinate);
    // }

    bool areThereRoomsToCreate = false;
    if (roomsToCreate[0] != 0 || roomsToCreate[1] != 0 ||
        roomsToCreate[2] != 0 || roomsToCreate[3] != 0) {
      areThereRoomsToCreate = true;
    }

    // need to write checks to make sure there are open doors
    // if (amountOpenDoors == 0 && areThereRoomsToCreate == true) {
    //   i = 1;
    //   printf("LOOP HAS BEEN RESET\n");
    //   // might need to resest some arrays, not sure though
    // } else {

    // printf("amount open door: %d\n\n", amountOpenDoors);

    int nextOpenDoor = (rand() % amountOpenDoors);

    createdRooms[i].xCoordinate = openDoors[nextOpenDoor].xCoordinate;
    createdRooms[i].yCoordinate = openDoors[nextOpenDoor].yCoordinate;

    // printf("\ni=%d, opendoors=%d, are there more rooms? %d\n\n", i,
    //        amountOpenDoors, areThereRoomsToCreate);
    // printf("next room: %d\n # doors: %d\n amount room type: %d\n\n",
    // nextRoom,
    //        nextRoom + 1, roomsToCreate[nextRoom]);

    // the door we know has to exist
    if (openDoors[nextOpenDoor].sideWithDoor == top) {
      createdRooms[i].top = true;
    } else if (openDoors[nextOpenDoor].sideWithDoor == bottom) {
      createdRooms[i].bottom = true;
    } else if (openDoors[nextOpenDoor].sideWithDoor == left) {
      createdRooms[i].left = true;
    } else if (openDoors[nextOpenDoor].sideWithDoor == right) {
      createdRooms[i].right = true;
    }

    for (int j = 0; j < nextRoom; j++) {
      // this does not truly randomize but its good enough for now, up prob
      // should be prioritized but left shouldn't be priotized over right
      if (createdRooms[i].top != true) {
        createdRooms[i].top = true;
        // printf("door added to top\n");
      } else if (createdRooms[i].left != true) {
        createdRooms[i].left = true;
        // printf("door added to left\n");
      } else if (createdRooms[i].right != true) {
        createdRooms[i].right = true;
        // printf("door added to right\n");
      } else if (createdRooms[i].bottom != true) {
        createdRooms[i].bottom = true;
        // printf("door added to bottom\n");
      }
    }

    // printf("numRooms: %zu\n", numRooms);
    // showRooms(createdRooms, numRooms, 0);
  }

  // now to cap off all of the doorways to nothing
  amountOpenDoors = checkOpenDoors(createdRooms, openDoors, numRooms);

  // printf("amount doorways to cap off: %d\n", amountOpenDoors);
  int preCapNumRooms = numRooms;
  int newNumRooms = preCapNumRooms + amountOpenDoors;
  // printf("precapNumRooms:%d, newNumRooms:%d\n", preCapNumRooms, newNumRooms);
  int j = 0;
  for (int i = preCapNumRooms; i < newNumRooms; i++) {
    createdRooms[i].xCoordinate = openDoors[j].xCoordinate;
    createdRooms[i].yCoordinate = openDoors[j].yCoordinate;
    if (openDoors[j].sideWithDoor == top) {
      createdRooms[i].top = true;
    } else if (openDoors[j].sideWithDoor == bottom) {
      createdRooms[i].bottom = true;
    } else if (openDoors[j].sideWithDoor == left) {
      createdRooms[i].left = true;
    } else if (openDoors[j].sideWithDoor == right) {
      createdRooms[i].right = true;
    }
    numRooms++;
    j++;
  }

  // showRooms(createdRooms, numRooms, 0);

  // fix all the problems

  bool indexToRemove[MAGIC_NUMBER] = {false};

  int finalNumRooms = 0;
  struct createdRooms *finalCreatedRooms =
      malloc(sizeof(struct createdRooms) * numRooms);
  // printf("num room: %zu \n", numRooms);

  for (int i = 0; i < numRooms; i++) {
    bool skip = false;

    for (int j = 0; j < finalNumRooms; j++) {
      if (createdRooms[i].xCoordinate == finalCreatedRooms[j].xCoordinate &&
          createdRooms[i].yCoordinate == finalCreatedRooms[j].yCoordinate)
        skip = true;
    }
    // printf("skip: %d, i: %d\n", skip, i);

    if (skip == false) {
      finalCreatedRooms[finalNumRooms++] = createdRooms[i];
    }
  }

  // showRooms(finalCreatedRooms, finalNumRooms, 0);

  // close doors that lead to walls
  closeDoorsToWalls(finalCreatedRooms, finalNumRooms);

  printf("\n\nTHIS IS THE FINAL MAP\n\n");
  showRooms(finalCreatedRooms, finalNumRooms, 0);

  fillRooms(finalCreatedRooms, finalNumRooms);

  struct createdRoomsList *createdRoomsList =
      malloc(sizeof(struct createdRoomsList));

  if (createdRoomsList == NULL) {
    exit(0);
  }
  createdRoomsList->numberOfRooms = finalNumRooms;
  createdRoomsList->createdRooms = finalCreatedRooms;

  return createdRoomsList;
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// CHECK OPEN DOORS FUNCTION
// checks map as its being built to see which doorways are open for new rooms to
// necessary for buildRooms function
//////////////////////////////////////////////////////////////////
int checkOpenDoors(struct createdRooms createdRooms[],
                   struct openDoor openDoors[], size_t numRooms) {

  for (int i = 0; i < MAGIC_NUMBER; i++) {
    openDoors[i].xCoordinate = 0;
    openDoors[i].yCoordinate = 0;
  }

  int amountOpenDoors = 0;

  bool roomExists = false;

  for (int i = 0; i < numRooms; i++) {
    if (createdRooms[i].top == true) {
      // printf("top is true for index %d\n", i);
      int potXCoordinate = createdRooms[i].xCoordinate;
      int potYCoordinate = createdRooms[i].yCoordinate + 1;
      for (int i = 0; i < numRooms; i++) {
        if (createdRooms[i].xCoordinate == potXCoordinate &&
            createdRooms[i].yCoordinate == potYCoordinate) {
          roomExists = true;
        }
      }
      if (roomExists == false) {
        openDoors[amountOpenDoors].xCoordinate = potXCoordinate;
        openDoors[amountOpenDoors].yCoordinate = potYCoordinate;
        openDoors[amountOpenDoors].sideWithDoor = bottom;
        amountOpenDoors++;
      }
      roomExists = false; // resets for next checks
    }

    if (createdRooms[i].bottom == true) {
      // printf("bottom is true for index %d\n", i);
      int potXCoordinate = createdRooms[i].xCoordinate;
      int potYCoordinate = createdRooms[i].yCoordinate - 1;
      for (int i = 0; i < numRooms; i++) {
        if (createdRooms[i].xCoordinate == potXCoordinate &&
            createdRooms[i].yCoordinate == potYCoordinate) {
          roomExists = true;
        }
      }
      if (roomExists == false) {
        openDoors[amountOpenDoors].xCoordinate = potXCoordinate;
        openDoors[amountOpenDoors].yCoordinate = potYCoordinate;
        openDoors[amountOpenDoors].sideWithDoor = top;
        amountOpenDoors++;
      }
      roomExists = false; // resets for next checks
    }

    if (createdRooms[i].left == true) {
      // printf("left is true for index %d\n", i);
      int potXCoordinate = createdRooms[i].xCoordinate - 1;
      int potYCoordinate = createdRooms[i].yCoordinate;
      for (int i = 0; i < numRooms; i++) {
        if (createdRooms[i].xCoordinate == potXCoordinate &&
            createdRooms[i].yCoordinate == potYCoordinate) {
          roomExists = true;
        }
      }
      if (roomExists == false) {
        openDoors[amountOpenDoors].xCoordinate = potXCoordinate;
        openDoors[amountOpenDoors].yCoordinate = potYCoordinate;
        openDoors[amountOpenDoors].sideWithDoor = right;
        amountOpenDoors++;
      }
      roomExists = false; // resets for next checks
    }

    if (createdRooms[i].right == true) {
      // printf("right is true for index %d\n", i);
      int potXCoordinate = createdRooms[i].xCoordinate + 1;
      int potYCoordinate = createdRooms[i].yCoordinate;
      for (int i = 0; i < numRooms; i++)
        if (createdRooms[i].xCoordinate == potXCoordinate &&
            createdRooms[i].yCoordinate == potYCoordinate) {
          roomExists = true;
        }
      if (roomExists == false) {
        openDoors[amountOpenDoors].xCoordinate = potXCoordinate;
        openDoors[amountOpenDoors].yCoordinate = potYCoordinate;
        openDoors[amountOpenDoors].sideWithDoor = left;
        amountOpenDoors++;
      }
      roomExists = false;
    }
  }
  // for (int i = 0; i < MAGIC_NUMBER; i++) {
  //   if (openDoors[i].xCoordinate != 0 || openDoors[i].yCoordinate != 0) {
  //     amountOpenDoors++;
  //   }

  // printf("open room %d xCoordinate: %d yCoordinate: %d\n", i,
  //         openDoors[i].xCoordinate,
  //         openDoors[i].yCoordinate); // debugger code

  // printf("open doors:\n");
  // for (int i = 0; i < MAGIC_NUMBER; i++) {
  //   if (i < numRooms) {
  //     printf(" %d- x:%d ,y:%d\n", i, openDoors[i].xCoordinate,
  //            openDoors[i].yCoordinate != 0);
  //   }
  // }

  return amountOpenDoors;
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// CLOSE DOORS TO WALLS
// checks map as its being built to see which doorways lead to walls
// necessary for buildRooms function
//////////////////////////////////////////////////////////////////
int closeDoorsToWalls(struct createdRooms createdRooms[], size_t numRooms) {

  bool roomExists = false;

  for (int i = 0; i < numRooms; i++) {
    if (createdRooms[i].top == true) {
      int potXCoordinate = createdRooms[i].xCoordinate;
      int potYCoordinate = createdRooms[i].yCoordinate + 1;
      for (int j = 0; j < numRooms; j++) {
        if (createdRooms[j].xCoordinate == potXCoordinate &&
            createdRooms[j].yCoordinate == potYCoordinate) {
          roomExists = true;
          if (roomExists == true) {
            if (createdRooms[j].bottom != true) {
              createdRooms[i].top = false;
            }
            roomExists = false; // resets for next checks
          }
        }
      }
    }

    if (createdRooms[i].bottom == true) {
      int potXCoordinate = createdRooms[i].xCoordinate;
      int potYCoordinate = createdRooms[i].yCoordinate - 1;
      for (int j = 0; j < numRooms; j++) {
        if (createdRooms[j].xCoordinate == potXCoordinate &&
            createdRooms[j].yCoordinate == potYCoordinate) {
          roomExists = true;
          if (roomExists == true) {
            if (createdRooms[j].top != true) {
              createdRooms[i].bottom = false;
            }
            roomExists = false; // resets for next checks
          }
        }
      }
    }

    if (createdRooms[i].left == true) {
      int potXCoordinate = createdRooms[i].xCoordinate - 1;
      int potYCoordinate = createdRooms[i].yCoordinate;
      for (int j = 0; j < numRooms; j++) {
        if (createdRooms[j].xCoordinate == potXCoordinate &&
            createdRooms[j].yCoordinate == potYCoordinate) {
          roomExists = true;
          if (roomExists == true) {
            if (createdRooms[j].right != true) {
              createdRooms[i].left = false;
            }
            roomExists = false; // resets for next checks
          }
        }
      }
    }

    if (createdRooms[i].right == true) {
      int potXCoordinate = createdRooms[i].xCoordinate + 1;
      int potYCoordinate = createdRooms[i].yCoordinate;
      for (int j = 0; j < numRooms; j++) {
        if (createdRooms[j].xCoordinate == potXCoordinate &&
            createdRooms[j].yCoordinate == potYCoordinate) {
          roomExists = true;
          if (roomExists == true) {
            if (createdRooms[j].left != true) {
              createdRooms[i].right = false;
            }
            roomExists = false; // resets for next checks
          }
        }
      }
    }
  }

  return 0;
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// FILL ROOMS FUNCTION
// this function fills the rooms with items and enemies
//////////////////////////////////////////////////////////////////
int fillRooms(struct createdRooms createdRooms[], int numRooms) {
  int amountEnemies;
  int amountModifiers;
  int openRooms;
  int necessaryRooms;
  int thirdOfOpenRooms;
  necessaryRooms = 5; // ladder, boss, chest, shop, and starting room
  openRooms = numRooms - necessaryRooms;
  //printf("amount open rooms: %d\n", openRooms);
  thirdOfOpenRooms = (openRooms - (openRooms % 3)) / 3;
  //printf("third of open Rooms: %d\n", thirdOfOpenRooms);
  amountEnemies = thirdOfOpenRooms;
  amountModifiers = thirdOfOpenRooms;
  openRooms = openRooms - amountEnemies - amountModifiers;

  int roomIndexes[numRooms]; 
  // numRooms - 1 accounts for starting room
  for (int i = 0; i < numRooms - 1; i++) {
    roomIndexes[i] = i + 1;
  }
  
  for (int i = 0; i < 1000; i++) { // mixes the array randomly 1000 times to get
                                   // a random order of numbers
    int rng1 = rand() % (numRooms - 1);
    int rng2 = rand() % (numRooms - 1);
    int a = roomIndexes[rng1];
    int b = roomIndexes[rng2];
    roomIndexes[rng1] = b;
    roomIndexes[rng2] = a;
  }
  //first Room
  createdRooms[0].content = Empty;

  int index = 0;

  printf("ladder is in x:%d,y%d\n",createdRooms[roomIndexes[index]].xCoordinate,createdRooms[roomIndexes[index]].yCoordinate);
  createdRooms[roomIndexes[index++]].content = Ladder;
  printf("shop is in x:%d,y%d\n",createdRooms[roomIndexes[index]].xCoordinate,createdRooms[roomIndexes[index]].yCoordinate);
  createdRooms[roomIndexes[index++]].content = Shop;
  printf("boss is in x:%d,y%d\n",createdRooms[roomIndexes[index]].xCoordinate,createdRooms[roomIndexes[index]].yCoordinate);
  createdRooms[roomIndexes[index++]].content = Boss;
  printf("chest is in x:%d,y%d\n",createdRooms[roomIndexes[index]].xCoordinate,createdRooms[roomIndexes[index]].yCoordinate);
  createdRooms[roomIndexes[index++]].content = Chest;

  for (int i = 0; i < amountEnemies; i++){
    createdRooms[roomIndexes[index++]].content = Enemy;
  }

  for(int i = 0; i < amountModifiers; i++){
    createdRooms[roomIndexes[index++]].content = Modifier;
  }

  for (int i = 0; i < openRooms; i++){
    createdRooms[roomIndexes[index++]].content = Empty;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// SHOW ROOMS FUNCTION
// this function visualizes the map for the player
//////////////////////////////////////////////////////////////////
int showRooms(struct createdRooms createdRooms[], int numRooms, int display) {

  printf("\nSHOW ROOMS FUNCT:--------------------------------\n");

  int stringMap[MAP_SIZE][MAP_SIZE] = {0};

  for (int i = 0; i < numRooms; i++) {
    if (display == 1) {
      printf(" %d- x:%d y:%d top:%d bottom:%d left:"
             "%d right:%d\n",
             i, createdRooms[i].xCoordinate, createdRooms[i].yCoordinate,
             createdRooms[i].top, createdRooms[i].bottom, createdRooms[i].left,
             createdRooms[i].right);
    }

    int mapX = createdRooms[i].xCoordinate + 5;
    int mapY = createdRooms[i].yCoordinate;
    stringMap[mapX][mapY] = 8;
  }

  for (int i = 0; i < MAP_SIZE; i++) {
    printf("\n");
    for (int j = 0; j < MAP_SIZE; j++) {
      if (display == 0) {
        printf("%d ", stringMap[j][i]);
      }
      if (display == 1) {
        printf("(%d,%d):%d ", i, j, stringMap[j][i]);
      }
    }

    printf("\n");
  }

  printf("-------------------------------------------\n");

  return 0;
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////