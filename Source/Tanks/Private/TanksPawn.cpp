// Copyright 2022 Semyon Nikolaev


#include "TanksPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TanksTurret.h"

ATanksPawn::ATanksPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("StaticMeshComponent");
	BoxCollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = BoxCollisionComponent;

	StaticMeshChassis = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshChassis");
	StaticMeshChassis->SetupAttachment(RootComponent);

	PawnMovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("PawnMovementComponent");
	PawnMovementComponent->SetUpdatedComponent(RootComponent);
}

void ATanksPawn::BeginPlay()
{
	Super::BeginPlay();

	LoadoutTurret();
}

void ATanksPawn::LoadoutTurret()
{
	if (!IsValid(TurretClass))
	{
		return;
	}

	Turret = GetWorld()->SpawnActor<ATanksTurret>(TurretClass);
	Turret->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Turret->SetInstigator(this);
}

void ATanksPawn::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		const FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		const FVector ForwardVector = YawRotator.RotateVector(FVector::ForwardVector * Value);
		PawnMovementComponent->AddInputVector(ForwardVector);
		const FRotator NewRotation = FMath::RInterpTo(RootComponent->GetComponentRotation(), ForwardVector.Rotation(), GetWorld()->DeltaTimeSeconds, 2);
		RootComponent->SetRelativeRotation(NewRotation);
	}
}

void ATanksPawn::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value, 1e-6f))
	{
		const FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		const FVector RightVector = YawRotator.RotateVector(FVector::RightVector * Value);
		PawnMovementComponent->AddInputVector(RightVector);
		const FRotator NewRotation = FMath::RInterpTo(RootComponent->GetComponentRotation(), RightVector.Rotation(), GetWorld()->DeltaTimeSeconds, 2);
		RootComponent->SetRelativeRotation(NewRotation);
	}
}
