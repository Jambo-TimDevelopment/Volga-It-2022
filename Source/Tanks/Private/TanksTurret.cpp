//  Copyright 2022 Volga-It


#include "TanksTurret.h"

ATanksTurret::ATanksTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
}

void ATanksTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsValid(GetInstigatorController()))
	{
		const FRotator TargetRotation(0.0f, GetInstigatorController()->GetControlRotation().Yaw, 0.0f);
		const FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, RotationSpeed);
		SetActorRotation(CurrentRotation);
	}
}
