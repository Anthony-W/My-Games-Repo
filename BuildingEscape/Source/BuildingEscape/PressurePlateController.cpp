// Fill out your copyright notice in the Description page of Project Settings.

#include "PressurePlateController.h"
#include "Classes/Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UPressurePlateController::UPressurePlateController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPressurePlateController::BeginPlay()
{
	Super::BeginPlay();

	if (!pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a pressurePlate component"), *GetOwner()->GetName())
	}
	
}


// Called every frame
void UPressurePlateController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//open the door
	if (TotalMassOnPressurePlate() < openMass)
	{
		if (pressed)
		{
			pressed = false;
			OnRelease.Broadcast();
		}
	}
	//close the door
	else
	{
		if (!pressed)
		{
			pressed = true;
			OnPush.Broadcast();
		}
	}
}

float UPressurePlateController::TotalMassOnPressurePlate()
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