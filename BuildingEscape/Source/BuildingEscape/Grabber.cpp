// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	FindInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!physicsHandle) return;

	if (physicsHandle->GrabbedComponent)
	{
		FVector lineEnd = GetReachLineEnd();

		physicsHandle->SetTargetLocation(lineEnd);
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a PhysicsHandleComponent"), *GetOwner()->GetName())
	}
}

void UGrabber::FindInputComponent()
{
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (inputComponent)
	{
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s does not have a UInputComponent"), *GetOwner()->GetName())
	}
}

FVector UGrabber::GetReachLineEnd()
{
	///get the viewpoint location and rotation
	FVector viewLocation;
	FRotator viewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewLocation, OUT viewRotation);

	FVector lineEnd = viewLocation + (reach * viewRotation.Vector());

	return lineEnd;
}

FVector UGrabber::GetReachLineStart()
{
	///get the viewpoint location and rotation
	FVector viewLocation;
	FRotator viewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewLocation, OUT viewRotation);

	return viewLocation;
}

void UGrabber::Grab()
{
	if (!physicsHandle) return;

	auto hitResult = GetFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	if (actorHit)
	{
		physicsHandle->GrabComponent(componentToGrab, NAME_None, actorHit->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	if (!physicsHandle) return;

	physicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///get the start and end of reach line
	FVector lineStart = GetReachLineStart();
	FVector lineEnd = GetReachLineEnd();

	///setup query parameters
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	///raycast
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		lineStart,
		lineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams
	);

	return hit;
}