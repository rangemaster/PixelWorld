#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "LevelBrick.h"
#include "Player.h"

using namespace std;

bool BrickCollisionVertical(LevelBrick* levelPeace, Player* player);
bool BrickCollisionHorizontal(LevelBrick* levelPeace, Player* player);