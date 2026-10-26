#include "serialize_custom.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <math.h>
#include <time.h>

typedef struct P player;
typedef struct T treasure;

void new_game();
void save_game(player p, treasure t);

void print_board(player p);

void play_game(player p, treasure t);
void load_game();
