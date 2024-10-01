#include "TileValue.h"

FString GetTileString(TileValue tile)
{
	if (tile == TileValue::Mine)
	{
		return "*";
	}
	else if (tile == TileValue::Value_0)
	{
		return "";
	}
	else
	{
		return FString::FromInt(static_cast<int>(tile));
	}
}

FColor GetTileColor(TileValue tile)
{
	switch (tile)
	{
	case TileValue::Mine:
		return FColor::Black;

	case TileValue::Value_0:
		return FColor::White;

	case TileValue::Value_1:
		return FColor::Blue;

	case TileValue::Value_2:
		return FColor::Green;

	case TileValue::Value_3:
		return FColor::Red;

	case TileValue::Value_4:
		return FColor::Purple;

	case TileValue::Value_5:
		return FColor(70, 20, 10);

	case TileValue::Value_6:
		return FColor::Turquoise;

	case TileValue::Value_7:
		return FColor::Black;

	case TileValue::Value_8:
		return FColor(80, 80, 80);
	}

	return FColor::White;
}
