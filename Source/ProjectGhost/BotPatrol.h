// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BotPatrol.generated.h"

class UHealthComponent;
class USphereComponent;
class USoundCue;

UCLASS()
class PROJECTGHOST_API ABotPatrol : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABotPatrol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UFUNCTION()
	void HandleTakeDamage(UHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType,
		class AController* InstigatedBy, AActor* DamageCauser);

	FVector GetNextPathPoint();

	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		float MovementForce;

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		bool bUseVelocityChange;

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		float RequiredDistanceToTarget;

	// Dynamic material to pulse on damage
	UMaterialInstanceDynamic* MatInst;

	void SelfDestruct();

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
	UParticleSystem* ExplosionEffect;

	bool bExploded;

	bool bStartedSelfDestruction;

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		float ExplosionRadius;

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		float ExplosionDamage;

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		float SelfDamageInterval;

	FTimerHandle TimerHandle_SelfDamage;

	void DamageSelf();

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		USoundCue* SelfDestructSound;

	UPROPERTY(EditDefaultsOnly, Category = "BotPatrol")
		USoundCue* ExplodeSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	void OnCheckNearbyBots();

	int32 PowerLevel;

	FTimerHandle TimerHandle_RefreshPath;

	void RefreshPath();
};
