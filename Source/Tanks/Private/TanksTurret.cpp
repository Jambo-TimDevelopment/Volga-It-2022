//  Copyright 2022 Volga-It


#include "TanksTurret.h"

#include "Tanks.h"
#include "TanksPlayerPawn.h"

ATanksTurret::ATanksTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
}

void ATanksTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(GetInstigatorController()) && !bUseTargetTurretRotation)
	{
		const FRotator TargetRotation(0.0f, GetInstigatorController()->GetControlRotation().Yaw, 0.0f);
		const FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);
		SetActorRotation(CurrentRotation);
	}
	else
	{
		const FRotator TargetRotation(0.0f, CurrentTargetTurretRotation.Yaw, 0.0f);
		const FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);
		SetActorRotation(CurrentRotation);
	}
}

void ATanksTurret::Fire()
{
	if (!bCanStartFire) return;

	bCanStartFire = false;

	GetWorld()->GetTimerManager().ClearTimer(FireCooldownTimer);
	
	GetWorld()->GetTimerManager().SetTimer(FireCooldownTimer, this, &ATanksTurret::ResetCooldownFire, TimeToReload, false);
}


AActor* ATanksTurret::OnSearching(float Length, float HealthConeAngleWidth, int32 SearchingIntensive)
{
	for (int Index = 0; Index < SearchingIntensive; ++Index)
	{
		FHitResult OutHit;
		FVector ShotStart = GetActorLocation() + GetActorForwardVector() * BarrelLength;
		FVector FireDirection = FMath::VRandCone(GetActorForwardVector(), HealthConeAngleWidth);
		FireDirection.Z = 0;
		FVector ShotEnd = ShotStart + Length * FireDirection;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetInstigator());
		FCollisionResponseParams ResponseParam;

		if (GetWorld()->LineTraceSingleByChannel(OutHit, ShotStart, ShotEnd, ECC_Bullet, Params, ResponseParam))
		{
			if (Cast<ATanksPlayerPawn>(OutHit.GetActor()))
				return OutHit.GetActor();
		}
	}

	return nullptr;
}

void ATanksTurret::ResetCooldownFire()
{
	if (IsValid(this))
	{
		bCanStartFire = true;
		OnCanFire.Broadcast();
	}
}
