// Fill out your copyright notice in the Description page of Project Settings.


#include "TileComponent.h"

#include <Components/TextRenderComponent.h>


// Sets default values for this component's properties
UTileComponent::UTileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UTextRenderComponent* textRenderComponent = GetOwner()->FindComponentByTag<UTextRenderComponent>(FName(TEXT("TileText"))))
	{
		textRenderComponent->SetText(FText::FromString(FString::FromInt(1)));
	}

	// ...
}

