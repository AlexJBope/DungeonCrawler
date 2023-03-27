#ifndef SUDO_CLASSES_H
#define  SUDO_CLASSES_H

#include <stdbool.h>

// Initialize/
#define AMOUNT_ROOMS 4
// I have no idea how to figure out the exact size of the array, so 100 is a
// magic number >> the needed size of the array
#define MAGIC_NUMBER 100
#define SIDES_IN_A_ROOM 4
#define MAP_SIZE 10

// enum roomTypes {oneDoor, twoDoors, threeDoors, fourDoors} roomTypes;
struct createdRooms {
  int amountDoors; // might not be necesiry
  int xCoordinate;
  int yCoordinate;
  bool top;
  bool bottom;
  bool left;
  bool right;
  //enum content; // for room type, boss, shop, chest, etc
};

typedef enum {top,bottom,left,right} SideWithDoor;
// coordinates for places where a room needs to go because there is an empty
// doorway
struct openDoor {
  int xCoordinate;
  int yCoordinate;
  SideWithDoor sideWithDoor;
};

int buildRooms(void);
//int checkOpenDoors(struct createdRooms roomList[], struct openDoor openDoors[],size_t numRooms);
int showRooms(struct createdRooms createdRooms[], int numRooms, int display);

#endif
