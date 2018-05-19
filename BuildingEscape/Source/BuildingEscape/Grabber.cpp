// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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


}

void UGrabber::FindPhysicsHandleComponent()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle)
	{
		//we have a physics handle
	}
	else
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

void UGrabber::Grab()
{
	GetFirstPhysicsBodyInReach();
}

void UGrabber::Release()
{

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///get the viewpoint location and rotation
	FVector viewLocation;
	FRotator viewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewLocation, viewRotation);

	///draw debug line
	FVector lineEnd = viewLocation + (reach * viewRotation.Vector());
	DrawDebugLine(GetWorld(), viewLocation, lineEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	///setup query parameters
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());

	///raycast
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		hit,
		viewLocation,
		lineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams
	);

	return hit;
}