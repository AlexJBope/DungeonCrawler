#include "buildRooms.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialize/

// index + 1 == amount of doors, value is the amount of that room
int roomsToCreate[AMOUNT_ROOMS] = {
    0}; //{0,1,3,4} would mean  of 1 door rooms, 1 two door room, 3 three door
        // rooms, and 4 four door rooms

struct createdRooms createdRooms[MAGIC_NUMBER];

int randint(int n);
int numRoomsGenerated;
int randNum;
int numRooms;

//////////////////////////////////////////////////////////////////
// BUILD ROOMS FUNCTION
// this function creates the map for the game
//////////////////////////////////////////////////////////////////
int buildRooms(void) {
  srand(time(NULL));
  struct openDoor openDoors[MAGIC_NUMBER] = {0};

  for (int i = 0; i < MAGIC_NUMBER; i++) {
    createdRooms[i].xCoordinate = 0;
    createdRooms[i].yCoordinate = 0;
  }

  for (int i = 1; i < AMOUNT_ROOMS; i++) {
    // this balances the amount of rooms of each type
    randNum = (rand() % 4) + 1;
    roomsToCreate[i] = randNum;
    numRooms += randNum;
    printf("amount of  %d door rooms: %d\n", i + 1,
           roomsToCreate[i]); // error checking
  }

  //  starting room
  numRooms ++; //add for strating room
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

    printf("\n ---NEW LOOP--- \nlength of the createdRooms: %zu\n", numRooms);


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

    printf("amount open door: %d\n\n", amountOpenDoors);
    
    int nextOpenDoor = (rand() % amountOpenDoors);

    createdRooms[i].xCoordinate = openDoors[nextOpenDoor].xCoordinate;
    createdRooms[i].yCoordinate = openDoors[nextOpenDoor].yCoordinate;

    printf(
        "\ni=%d, opendoors=%d, are there more rooms? %d\n\n",
        i, amountOpenDoors, areThereRoomsToCreate);
    printf("next room: %d\n # doors: %d\n amount room type: %d\n\n", nextRoom,
           nextRoom + 1, roomsToCreate[nextRoom]);
    printf("next open door: %d\n x: %d\n y: %d\n doorside: %d\n\n",
           nextOpenDoor, openDoors[nextOpenDoor].xCoordinate,
           openDoors[nextOpenDoor].yCoordinate);

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
        printf("door added to top\n");
      } else if (createdRooms[i].left != true) {
        createdRooms[i].left = true;
        printf("door added to left\n");
      } else if (createdRooms[i].right != true) {
        createdRooms[i].right = true;
        printf("door added to right\n");
      } else if (createdRooms[i].bottom != true) {
        createdRooms[i].bottom = true;
        printf("door added to bottom\n");
      }

    }

    printf("numRooms: %d\n", numRooms);
    showRooms(createdRooms, numRooms, 0);
  }


  //now to cap off all of the doorways to nothing
  amountOpenDoors = checkOpenDoors(createdRooms, openDoors, numRooms);
  printf("amount doorways to cap off: %d\n", amountOpenDoors);
  int preCapNumRooms = numRooms;
  int newNumRooms = preCapNumRooms + amountOpenDoors;
  printf("precapNumRooms:%d, newNumRooms:%d, numRooms:%d \n", preCapNumRooms, newNumRooms, numRooms);
  int j = 0;
  for (int i = preCapNumRooms; i < newNumRooms; i++){
    createdRooms[i].xCoordinate = openDoors[j].xCoordinate;
    createdRooms[i].yCoordinate = openDoors[j].yCoordinate;
    if(openDoors[j].sideWithDoor == top){
      createdRooms[i].top = true;
    }else if (openDoors[j].sideWithDoor == bottom){
      createdRooms[i].bottom = true;
    }else if (openDoors[j].sideWithDoor == left){
      createdRooms[i].left = true;
    }else if ( openDoors[j].sideWithDoor == right){
      createdRooms[i].right = true;
    }
    numRooms ++;
    j++;
  }

  showRooms(createdRooms, numRooms, 0);
  return 0;
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

    printf("open doors:\n");
  for (int i = 0; i < MAGIC_NUMBER; i++) {
    if (i < numRooms) {
      printf(" %d- x:%d ,y:%d\n", i, openDoors[i].xCoordinate,
             openDoors[i].yCoordinate != 0);
    }
  }

  //now check for places with two doorways to them
  

  
  return amountOpenDoors;
}
//////////////////////////////////////////////////////////////////
////////////////////////END FUNCTION//////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
// SHOW ROOMS FUNCTION
// this function visualizes the map for the player
//////////////////////////////////////////////////////////////////
int showRooms(struct createdRooms createdRooms[], int numRooms, int display) {

  printf("SHOW ROOMS FUNCT:--------------------------------\n");

  int stringMap[MAP_SIZE][MAP_SIZE] = {0};

  for (int i = 0; i < numRooms; i++) {
    printf(" %d- x:%d y:%d top:%d bottom:%d left:"
           "%d right:%d\n",
           i, createdRooms[i].xCoordinate, createdRooms[i].yCoordinate,
           createdRooms[i].top, createdRooms[i].bottom, createdRooms[i].left,
           createdRooms[i].right);

    int mapX = createdRooms[i].xCoordinate + 5;
    int mapY = createdRooms[i].yCoordinate;
    stringMap[mapX][mapY] = 8;
  }

  for (int i = 0; i < MAP_SIZE; i++) {
    printf("\n");
    for (int j = 0; j < MAP_SIZE; j++) {
      if(display == 0){
      printf("%d ", stringMap[j][i]);
      }
      if(display == 1){
      printf("(%d,%d):%d ",i,j,stringMap[j][i]);
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