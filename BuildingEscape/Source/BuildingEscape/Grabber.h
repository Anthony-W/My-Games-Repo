// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float reach = 100.f;

	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* inputComponent = nullptr;

	void FindPhysicsHandleComponent();

	void FindInputComponent();

	//raycast and grab what is in reach
	void Grab();

	//release grabbed object
	void Release();
	
	//return hit for first physis body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
