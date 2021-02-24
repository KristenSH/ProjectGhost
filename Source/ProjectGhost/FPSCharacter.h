// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "Weapon.h"
#include "Net/UnrealNetwork.h"
#include "FPSCharacter.generated.h"

class AWeapon;
class USpringArmComponent;
class UHealthComponent;

UCLASS()
class PROJECTGHOST_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BeginCrouch();

	void EndCrouch();

	// Zoom properties
	bool canZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float ZoomedFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100))
		float ZoomedInterpSpeed;

	float DefaultFOV;

	void BeginZoom();

	void EndZoom();

	UPROPERTY(Replicated)
		AWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		TSubclassOf<AWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
		FName WeaponAttachSocketName;

	UFUNCTION()
		void OnHealthChanged(UHealthComponent* OwningHealthComp, float Health, float HealtDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
		bool Died;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Move Forward and backward
	UFUNCTION()
		void MoveForward(float value);

	// Move right and left
	UFUNCTION()
		void MoveRight(float value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	// Fire Shot
	UFUNCTION()
		void StartFire();
	
	// Stop fire
	UFUNCTION()
		void StopFire();


	// FPS Camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleAnywhere)
		UHealthComponent* HealthComp;


	//// Gun muzzle's offset from the camera location.
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	FVector MuzzleOffset;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//	float TimeBetweenShots;

	//UPROPERTY(EditDefaultsOnly, Category = Weapon)
	//	TSubclassOf<UDamageType> DamageType;

	//FTimerHandle InputTimeHandle;

};
