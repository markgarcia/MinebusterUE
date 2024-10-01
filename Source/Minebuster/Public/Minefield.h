// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../TileValue.h"
#include "Minefield.generated.h"

UCLASS()
class MINEBUSTER_API AMinefield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinefield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetTileCoordinates(FVector testPos, int& outX, int& outY) const;
	TileValue BustTile(int x, int y);
	void FlagTile(int x, int y);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInstancedStaticMeshComponent* TileMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTextRenderComponent* TextTemplate;

private:
	void FloodFill(const class AMinebusterGameState& gameState, int x, int y);
	void PushDownTileMesh(unsigned int tileIndex);

	TArray<int32> TileMeshInstances;
	TArray<UTextRenderComponent*> TextComponents;
};
