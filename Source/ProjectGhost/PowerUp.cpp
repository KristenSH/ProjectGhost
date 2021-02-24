// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APowerUp::APowerUp()
{
	PowerupInterval = 0.0f;
	TotalNrOfTicks = 0;
	
	isActive = false;

	SetReplicates(true);
}

void APowerUp::OnTickPowerup()
{
	TicksProcessed++;

	OnPowerupTicked();

	if (TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();

		isActive = false;
		Onrep_PowerupActive();

		// Delete timer
		GetWorldTimerManager().ClearTimer(TimerHandlePowerUpTick);
	}
}

void APowerUp::Onrep_PowerupActive()
{
	OnPowerupStateChanged(isActive);
}

void APowerUp::ActivatePowerup(AActor* ActiveFor)
{
	OnActivated(ActiveFor);
	
	isActive = true;
	Onrep_PowerupActive();

	if (PowerupInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandlePowerUpTick, this, &APowerUp::OnTickPowerup, PowerupInterval, true);
	}
	else
	{
		OnTickPowerup();
	}
}

void APowerUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APowerUp, isActive);
}