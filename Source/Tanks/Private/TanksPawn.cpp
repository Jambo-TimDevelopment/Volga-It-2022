// Copyright 2022 Semyon Nikolaev


#include "TanksPawn.h"
#include "TanksAttributeComponent.h"
#include "TanksHealthWidgetComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "TanksTurret.h"

ATanksPawn::ATanksPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("StaticMeshComponent");
	BoxCollisionComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = BoxCollisionComponent;

	PawnMovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>("PawnMovementComponent");
	PawnMovementComponent->SetUpdatedComponent(RootComponent);

	AttributeComponent = CreateDefaultSubobject<UTanksAttributeComponent>("AttributeComponent");

	HealthWidgetComponent = CreateDefaultSubobject<UTanksHealthWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(BoxCollisionComponent);
}

void ATanksPawn::BeginPlay()
{
	Super::BeginPlay();

	LoadoutTurret();

	OnTakeRadialDamage.AddDynamic(AttributeComponent, &UTanksAttributeComponent::OnTakeRadialDamage);
	OnTakePointDamage.AddDynamic(AttributeComponent, &UTanksAttributeComponent::OnTakePointDamage);
	AttributeComponent->OnHealthChanged.AddDynamic(HealthWidgetComponent, &UTanksHealthWidgetComponent::SetNewHealthToWidget);
	AttributeComponent->OnDeath.AddDynamic(this, &ATanksPawn::OnDeath);
}

void ATanksPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	AttributeComponent->OnDeath.RemoveAll(this);
	AttributeComponent->OnHealthChanged.RemoveAll(this);
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
	if (!FMath::IsNearlyZero(Value, 1e-6f) && AttributeComponent->IsLive())
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
	if (!FMath::IsNearlyZero(Value, 1e-6f) && AttributeComponent->IsLive())
	{
		const FRotator YawRotator(0.0f, GetControlRotation().Yaw, 0.0f);
		const FVector RightVector = YawRotator.RotateVector(FVector::RightVector * Value);
		PawnMovementComponent->AddInputVector(RightVector);
		const FRotator NewRotation = FMath::RInterpTo(RootComponent->GetComponentRotation(), RightVector.Rotation(), GetWorld()->DeltaTimeSeconds, 2);
		RootComponent->SetRelativeRotation(NewRotation);
	}
}

void ATanksPawn::Fire()
{
	if (IsValid(Turret) && AttributeComponent->IsLive())
	{
		Turret->Fire();
	}
}

void ATanksPawn::OnDeath()
{
	HealthWidgetComponent->DestroyComponent();
	AttributeComponent->OnDeath.RemoveAll(this);
	AttributeComponent->OnHealthChanged.RemoveAll(this);
	GetController()->StopMovement();
}
