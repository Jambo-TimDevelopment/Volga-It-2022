//  Copyright 2022 Semyon Nikolaev


#include "TanksTurretBurst.h"
#include "Tanks.h"
#include "Kismet/GameplayStatics.h"

void ATanksTurretBurst::StartFire()
{
	if (!bCanStartFire) return;

	Super::StartFire();

	CurrentCountAmmoAtFire = CountAmmoAtFire;
	GetWorld()->GetTimerManager().ClearTimer(BurstCooldownTimer);

	MakeShot();

	GetWorld()->GetTimerManager().SetTimer(BurstCooldownTimer, this, &ATanksTurretBurst::MakeShot, TimeToReloadBurst, false);
}

void ATanksTurretBurst::StopFire()
{
	Super::StopFire();
}

void ATanksTurretBurst::MakeShot()
{
	FHitResult OutHit;
	FVector ShotStart = GetActorLocation() + GetActorForwardVector() * BarrelLength;
	FVector ShotEnd = ShotStart + FireDistance * FMath::VRandCone(GetActorForwardVector(), FireSpreadHealthAngle);
	ShotEnd.Z = ShotStart.Z;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FCollisionResponseParams ResponseParam;
	if (GetWorld()->LineTraceSingleByChannel(OutHit, ShotStart, ShotEnd, ECC_Bullet, Params, ResponseParam))
	{
		TArray<AActor*> IgnoredActors;
		AActor* DamageCauser = GetInstigator();
		AController* Controller = GetInstigatorController();
		UGameplayStatics::ApplyPointDamage(OutHit.GetActor(), BaseDamage, GetActorLocation(), OutHit, Controller, DamageCauser, UDamageType::StaticClass());
	}

	OnFire(ShotStart, ShotEnd);

	CurrentCountAmmoAtFire--;
	if (CurrentCountAmmoAtFire != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(BurstCooldownTimer, this, &ATanksTurretBurst::MakeShot, TimeToReloadBurst, false);
	}
}
