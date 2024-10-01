#include "Minefield.h"

#include "../MinebusterGameState.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"


AMinefield::AMinefield()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMinefield::BeginPlay()
{
	Super::BeginPlay();

	if (!TileMeshes)
	{
		return;
	}
	
	FBoxSphereBounds tileBounds = TileMeshes->GetStaticMesh()->GetBounds();
	FVector tilePos;

	const AMinebusterGameState& gameState = *Cast<AMinebusterGameState>(GetWorld()->GetGameState());
	for (unsigned int indexY = 0; indexY < gameState.NumTilesY; ++indexY)
	{
		tilePos.X = 0.f;

		for (unsigned int indexX = 0; indexX < gameState.NumTilesX; ++indexX)
		{
			TileMeshInstances.Add(TileMeshes->AddInstance(FTransform(tilePos)));
			tilePos.X += tileBounds.GetBox().GetSize().X;

			UTextRenderComponent* textComponent = DuplicateObject(TextTemplate, this);

			const TileValue tileValue = gameState.Tiles[(indexY * gameState.NumTilesX) + indexX];
			textComponent->SetText(FText::FromString(GetTileString(tileValue)));
			textComponent->SetTextRenderColor(GetTileColor(tileValue));
			textComponent->SetVisibility(false);
			textComponent->SetHiddenInGame(false);
			textComponent->SetRelativeLocation(textComponent->GetRelativeLocation() + tilePos);
			textComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);;
			textComponent->RegisterComponent();

			TextComponents.Add(textComponent);
		}

		tilePos.Y += tileBounds.GetBox().GetSize().Y;
	}
}

void AMinefield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMinefield::GetTileCoordinates(FVector testPos, int& outX, int& outY) const
{
	const AMinebusterGameState& gameState = *Cast<AMinebusterGameState>(GetWorld()->GetGameState());

	FVector localPos = UKismetMathLibrary::InverseTransformLocation(TileMeshes->GetComponentTransform(), testPos);
	FVector minBound, maxBound;
	TileMeshes->GetLocalBounds(minBound, maxBound);
	maxBound.X += (maxBound.X - minBound.X) * (gameState.NumTilesX - 1);
	maxBound.Y += (maxBound.Y - minBound.Y) * (gameState.NumTilesY - 1);

	if (localPos.X < minBound.X || localPos.X > maxBound.X || localPos.Y < minBound.Y || localPos.Y > maxBound.Y)
	{
		return false;
	}

	outX = static_cast<int>((localPos.X / (maxBound.X - minBound.X)) * gameState.NumTilesX);
	outY = static_cast<int>((localPos.Y / (maxBound.Y - minBound.Y)) * gameState.NumTilesY);

	return true;
}

TileValue AMinefield::BustTile(int x, int y)
{
	const AMinebusterGameState& gameState = *Cast<AMinebusterGameState>(GetWorld()->GetGameState());

	int tileIndex = (gameState.NumTilesX * y) + x;
	TileValue tile = gameState.Tiles[tileIndex];
	auto& text = *TextComponents[tileIndex];

	if (text.Text.EqualTo(FText::FromString(FString("!"))))
	{
		return TileValue::Value_0;
	}

	if (tile == TileValue::Value_0)
	{
		FloodFill(gameState, x, y);
	}
	else if (!text.IsVisible())
	{
		text.SetVisibility(true);
		PushDownTileMesh(tileIndex);
	}

	return tile;
}

void AMinefield::FlagTile(int x, int y)
{
	const AMinebusterGameState& gameState = *Cast<AMinebusterGameState>(GetWorld()->GetGameState());
	int tileIndex = (gameState.NumTilesX * y) + x;

	auto& text = *TextComponents[tileIndex];
	if (!text.IsVisible())
	{
		text.SetText(FText::FromString(FString("!")));
		text.SetTextRenderColor(FColor::Black);
		text.SetVisibility(true);
	}
	else if (text.Text.EqualTo(FText::FromString(FString("!"))))
	{
		text.SetVisibility(false);
		text.SetText(FText::FromString(GetTileString(gameState.Tiles[tileIndex])));
		text.SetTextRenderColor(GetTileColor(gameState.Tiles[tileIndex]));
	}
}

void AMinefield::FloodFill(const AMinebusterGameState& gameState, int x, int y)
{
	if (x < 0 || x >= static_cast<int>(gameState.NumTilesX) || y < 0 || y >= static_cast<int>(gameState.NumTilesY))
		return;

	int tileIndex = (gameState.NumTilesX * y) + x;
	if (gameState.Tiles[tileIndex] == TileValue::Mine)
		return;

	if (TextComponents[tileIndex]->IsVisible())
		return;

	TextComponents[tileIndex]->SetVisibility(true);
	PushDownTileMesh(tileIndex);

	if (gameState.Tiles[tileIndex] == TileValue::Value_0)
	{
		FloodFill(gameState, x - 1, y - 1);
		FloodFill(gameState, x    , y - 1);
		FloodFill(gameState, x + 1, y - 1);
		FloodFill(gameState, x - 1, y    );
		FloodFill(gameState, x + 1, y    );
		FloodFill(gameState, x - 1, y + 1);
		FloodFill(gameState, x    , y + 1);
		FloodFill(gameState, x + 1, y + 1);
	}
}

void AMinefield::PushDownTileMesh(unsigned int tileIndex)
{
	FTransform transform;
	TileMeshes->GetInstanceTransform(TileMeshInstances[tileIndex], transform);

	transform.AddToTranslation(FVector(0.f, 0.f, -80.f));
	TileMeshes->UpdateInstanceTransform(TileMeshInstances[tileIndex], transform);
}
