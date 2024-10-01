#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TileValue.h"
#include "MinebusterGameState.generated.h"

UCLASS(minimalapi)
class AMinebusterGameState : public AGameStateBase
{
	GENERATED_BODY()

	AMinebusterGameState() = default;

	void ReceivedGameModeClass() override;

public:
	UPROPERTY()
	unsigned int NumTilesX;

	UPROPERTY()
	unsigned int NumTilesY;

	UPROPERTY()
	unsigned int NumMines;

	UPROPERTY()
	TArray<TileValue> Tiles;

private:
	void InitTiles();
};
