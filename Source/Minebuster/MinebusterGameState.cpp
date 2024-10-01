#include "MinebusterGameState.h"

#include "MinebusterWorldSettings.h"


void AMinebusterGameState::ReceivedGameModeClass()
{
	Super::ReceivedGameModeClass();

	const auto& worldSettings = *Cast<AMinebusterWorldSettings>(GetWorld()->GetWorldSettings());
	NumTilesX = worldSettings.NumTilesX;
	NumTilesY = worldSettings.NumTilesY;
	NumMines = worldSettings.NumMines;

	InitTiles();
}

void AMinebusterGameState::InitTiles()
{
	Tiles.SetNumZeroed(NumTilesX * NumTilesY, true);
	
	unsigned int numMinesPlaced = 0;
	while (numMinesPlaced != NumMines)
	{
		int index = FMath::RandRange(0, (NumTilesX * NumTilesY) - 1);
		if (Tiles[index] == TileValue::Mine)
		{
			continue;
		}

		Tiles[index] = TileValue::Mine;
		++numMinesPlaced;
	}

	auto incrementTile = [&](int x, int y)
		{
			if (x < 0 || x >= static_cast<int>(NumTilesX) || y < 0 || y >= static_cast<int>(NumTilesY))
				return;

			int index = (y * NumTilesX) + x;
			if (Tiles[index] != TileValue::Mine)
			{
				Tiles[index] = static_cast<TileValue>(static_cast<int>(Tiles[index]) + 1);
			}
		};

	for (unsigned int y = 0; y < NumTilesY; ++y)
	{
		for (unsigned int x = 0; x < NumTilesX; ++x)
		{
			unsigned int index = (y * NumTilesX) + x;
			if (Tiles[index] == TileValue::Mine)
			{
				incrementTile(x - 1, y - 1);
				incrementTile(x    , y - 1);
				incrementTile(x + 1, y - 1);
				incrementTile(x - 1, y    );
				incrementTile(x + 1, y    );
				incrementTile(x - 1, y + 1);
				incrementTile(x    , y + 1);
				incrementTile(x + 1, y + 1);
			}
		}
	}
}