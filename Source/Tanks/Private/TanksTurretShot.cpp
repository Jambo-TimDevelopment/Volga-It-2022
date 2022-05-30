//  Copyright 2022 Semyon Nikolaev


#include "TanksTurretShot.h"
#include "Tanks.h"
#include "Kismet/GameplayStatics.h"

void ATanksTurretShot::Fire()
{
	if (!bCanStartFire) return;

	Super::Fire();

	for (int BulletIndex = 0; BulletIndex < CountAmmoAtFire; ++BulletIndex)
	{
		FHitResult OutHit;
		FVector ShotStart = GetActorLocation() + GetActorForwardVector() * BarrelLength;
		FVector FireDirection = FMath::VRandCone(GetActorForwardVector(), FireSpreadHealthAngle);
		FireDirection.Z = 0;
		FVector ShotEnd = ShotStart + FireDistance * FireDirection;
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
	}
}