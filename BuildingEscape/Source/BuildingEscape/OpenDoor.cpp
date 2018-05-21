// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Classes/Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	if (!pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a pressurePlate component"), *GetOwner()->GetName())
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//check the current time in seconds
	float time = GetWorld()->GetTimeSeconds();

	//open the door
	if (TotalMassOnPressurePlate() >= openMass)
	{
		if (closed)
		{
			closed = false;
			OnOpenRequest.Broadcast();
		}
	}
	//close the door
	else
	{
		if (!closed)
		{
			closed = true;
			OnCloseRequest.Broadcast();
		}
	}
}

float UOpenDoor::TotalMassOnPressurePlate()
{
	if (!pressurePlate) return -1;

	float totalMass = 0.f;

	//find all actors on pressure plate
	TArray<AActor*> overlappingActors;
	pressurePlate->GetOverlappingActors(OUT overlappingActors);

	//sum the masses of all found actors
	for (const auto* a : overlappingActors)
	{
		totalMass += a->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return totalMass;
}