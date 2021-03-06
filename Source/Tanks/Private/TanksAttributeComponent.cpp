//  Copyright 2022 Semyon Nikolaev


#include "TanksAttributeComponent.h"

UTanksAttributeComponent::UTanksAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTanksAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTanksAttributeComponent::TakeDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
	OnHealthChanged.Broadcast(GetHealthPercent());
	if(FMath::IsNearlyZero(Health))
	{
		OnDeath.Broadcast();
	}
}

void UTanksAttributeComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	TakeDamage(Damage);
}

void UTanksAttributeComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	TakeDamage(Damage);
}
