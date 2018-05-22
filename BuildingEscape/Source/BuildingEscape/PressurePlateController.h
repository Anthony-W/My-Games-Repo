// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "PressurePlateController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPush);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRelease);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressurePlateController : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UPressurePlateController();

	UPROPERTY(BlueprintAssignable)
	FOnPush OnPush;

	UPROPERTY(BlueprintAssignable)
	FOnRelease OnRelease;

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float openMass = 100.f;

	float TotalMassOnPressurePlate();

	bool pressed = false;
	
};
