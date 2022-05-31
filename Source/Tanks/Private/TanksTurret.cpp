//  Copyright 2022 Volga-It


#include "TanksTurret.h"

#include "Tanks.h"
#include "TanksAttributeComponent.h"
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

void ATanksTurret::ResetCooldownFire()
{
	if (IsValid(this))
	{
		bCanStartFire = true;
		OnCanFire.Broadcast();
	}
}
