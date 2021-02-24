// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UCLASS()
class PROJECTGHOST_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		float PowerupInterval;

	// Total times players apply the powerup effect
	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		int32 TotalNrOfTicks;

	FTimerHandle TimerHandlePowerUpTick;

	// Total number of ticks applied
	int32 TicksProcessed;

	UFUNCTION()
		void OnTickPowerup();

	UPROPERTY(ReplicatedUsing = OnRep_PowerupActive)
		bool isActive;

	UFUNCTION()
		void Onrep_PowerupActive();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
		void OnPowerupStateChanged(bool newIsActive);

public:	
	void ActivatePowerup(AActor* ActiveFor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
		void OnActivated(AActor* ActiveFor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
		void OnPowerupTicked();

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups")
		void OnExpired();

};
