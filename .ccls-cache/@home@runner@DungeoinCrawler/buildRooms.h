#ifndef BUILD_ROOMS_H
#define BUILD_ROOMS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Initialize/
#define AMOUNT_ROOMS 4
// I have no idea how to figure out the exact size of the array, so 100 is a
// magic number >> the needed size of the array
#define MAGIC_NUMBER 100
#define SIDES_IN_A_ROOM 4
#define MAP_SIZE 10


typedef enum content {
  Empty,
  Ladder,
  Boss,
  Enemy,
  Modifier,
  Shop,
  ClossedShop,
  Chest
} Content;

// enum roomTypes {oneDoor, twoDoors, threeDoors, fourDoors} roomTypes;
struct createdRooms {
  int amountDoors; // might not be necesiry
  int xCoordinate;
  int yCoordinate;
  bool top;
  bool bottom;
  bool left;
  bool right;
  Content content; // for room type, boss, shop, chest, etc
  bool discovered;
};

typedef enum { top, bottom, left, right } SideWithDoor;
// coordinates for places where a room needs to go because there is an empty
// doorway
struct openDoor {
  int xCoordinate;
  int yCoordinate;
  SideWithDoor sideWithDoor;
};

// typedef struct floorMap{

struct createdRoomsList{
  struct createdRooms *createdRooms;
  int numberOfRooms;
};

// }

struct createdRoomsList *buildRooms(void);
int checkOpenDoors(struct createdRooms roomList[], struct openDoor openDoors[],
                   size_t numRooms);
int showRoomsDebug(struct createdRooms createdRooms[], int numRooms, int display);
void showRooms(struct createdRooms createdRooms[], int numRooms, int display, struct createdRooms currentRoom);
int closeDoorsToWalls(struct createdRooms createdRooms[], size_t numRooms);
int fillRooms(struct createdRooms createdRooms[], int numRooms);

#endif
