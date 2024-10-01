#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "MinebusterWorldSettings.generated.h"

/**
 * 
 */
UCLASS()
class MINEBUSTER_API AMinebusterWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	unsigned int NumTilesX;

	UPROPERTY(EditAnywhere)
	unsigned int NumTilesY;

	UPROPERTY(EditAnywhere)
	unsigned int NumMines;
};
