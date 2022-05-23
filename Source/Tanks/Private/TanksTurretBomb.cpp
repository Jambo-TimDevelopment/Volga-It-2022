//  Copyright 2022 Semyon Nikolaev

#include "TanksTurretBomb.h"
#include "TanksProjectile.h"

void ATanksTurretBomb::StartFire()
{
	Super::StartFire();

	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50;
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParams.Instigator = GetInstigator();

	GetWorld()->SpawnActor<ATanksProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
}

void ATanksTurretBomb::StopFire()
{
}
