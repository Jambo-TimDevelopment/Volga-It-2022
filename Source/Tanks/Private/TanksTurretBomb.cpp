//  Copyright 2022 Semyon Nikolaev

#include "TanksTurretBomb.h"
#include "TanksProjectile.h"

void ATanksTurretBomb::StartFire()
{
	if (!bCanStartFire) return;

	Super::StartFire();

	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * BarrelLength;
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ActorSpawnParams.Instigator = GetInstigator();

	ATanksProjectile* Projectile = GetWorld()->SpawnActor<ATanksProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	if (IsValid(Projectile)) Projectile->SetBaseDamage(BaseDamage);
	OnFire(SpawnLocation, SpawnLocation);
}

void ATanksTurretBomb::StopFire()
{
}
