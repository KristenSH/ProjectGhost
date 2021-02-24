// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameStateBase.h"
#include "Net/UnrealNetwork.h"

void ASGameStateBase::OnRep_WaveState(EWaveState OldState)
{
	WaveStateChanged(WaveState, OldState);
}

void ASGameStateBase::SetWaveState(EWaveState NewState)
{
	if (HasAuthority())
	{
		EWaveState OldState = WaveState;

		WaveState = NewState;

		//Call on Server
		OnRep_WaveState(OldState);
	}
}

void ASGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASGameStateBase, WaveState);
}