#pragma once

#include "predefs.hpp"
#include <Windows.h>
#include <Gdiplus.h>

#include "defs_n_consts.hpp"

#include "game.hpp"

void DrawGame(Gdiplus::Graphics &, Game &currentGame);
