// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
    HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
    HealthComp->OnHealthChanged.AddDynamic(this, &AExplosiveBarrel::OnHealthChanged);

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetSimulatePhysics(true);

    MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
    RootComponent = MeshComp;

    RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
    RadialForceComp->SetupAttachment(MeshComp);
    RadialForceComp->Radius = 250;
    RadialForceComp->bImpulseVelChange = true;
    RadialForceComp->bAutoActivate = false;
    RadialForceComp->bIgnoreOwningActor = true;

    ExplosionImpulse = 400;

    SetReplicates(true);
    SetReplicateMovement(true);
}

void AExplosiveBarrel::OnHealthChanged(UHealthComponent* OwningHealthCom, float Health, float HealthDelta, const class UDamageType* DamageType,
    class AController* InstigatedBy, AActor* DamageCauser)
{
    if (bExploded)
    {
        // it already exploded
        return;
    }

    if (Health <= 0.0f)
    {
        bExploded = true;
        OnRep_Exploded();

        FVector BoostIntensity = FVector::UpVector * ExplosionImpulse;
        MeshComp->AddImpulse(BoostIntensity, NAME_None, true);

        RadialForceComp->FireImpulse();
    }
}

void AExplosiveBarrel::OnRep_Exploded()
{
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
    MeshComp->SetMaterial(0, ExplosionMaterial);
}

void AExplosiveBarrel::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AExplosiveBarrel, bExploded);
}