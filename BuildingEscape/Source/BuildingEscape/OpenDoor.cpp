// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


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

	initialAngle = GetOwner()->GetActorRotation().Yaw;

	actorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(actorThatOpens))
		OpenDoor();
	else
		CloseDoor();
}

void UOpenDoor::OpenDoor()
{
	AActor *owner = GetOwner();

	FRotator newRotation = FRotator(0.f, initialAngle+60, 0.f);

	owner->SetActorRotation(newRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor *owner = GetOwner();

	FRotator newRotation = FRotator(0.f, initialAngle, 0.f);

	owner->SetActorRotation(newRotation);
}

