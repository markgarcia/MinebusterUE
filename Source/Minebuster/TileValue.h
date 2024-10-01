#pragma once

#include "CoreMinimal.h"

UENUM()
enum class TileValue
{
	Mine = -1,
	Value_0 = 0,
	Value_1 = 1,
	Value_2 = 2,
	Value_3 = 3,
	Value_4 = 4,
	Value_5 = 5,
	Value_6 = 6,
	Value_7 = 7,
	Value_8 = 8,
};


FString GetTileString(TileValue tile);
FColor GetTileColor(TileValue tile);