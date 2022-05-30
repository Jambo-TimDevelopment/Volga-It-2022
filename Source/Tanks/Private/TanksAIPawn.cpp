//  Copyright 2022 Semyon Nikolaev


#include "TanksAIPawn.h"

#include "TanksTurret.h"

ATanksAIPawn::ATanksAIPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATanksAIPawn::BeginPlay()
{
	Super::BeginPlay();

	Turret->bUseTargetTurretRotation = true;
	SetCurrentAIState(EAIState::Searching);
}

void ATanksAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentAIState)
	{
	case EAIState::Firing:
		{
			FiringMovement(DeltaTime);
			break;
		}
	case EAIState::Searching:
		{
			SearchingMovement(DeltaTime);
			break;
		}
	}
}

void ATanksAIPawn::SetCurrentTarget(AActor* NewTarget)
{
	CurrentTarget = NewTarget;
	const EAIState NewAIState = IsValid(NewTarget) ? EAIState::Firing : EAIState::Searching;
	SetCurrentAIState(NewAIState);
}

void ATanksAIPawn::SearchingMovement(float DeltaTime)
{
	AActor* SearchingTarget = Turret->OnSearching(MaxLengthToTargetInSearching, MaxHealthConeAngleForSearching, SearchingIntensive);
	if (IsValid(SearchingTarget))
	{
		SetCurrentTarget(SearchingTarget);
	}
}

void ATanksAIPawn::FiringMovement(float DeltaTime)
{
	if (!CurrentTarget.IsValid())
	{
		SetCurrentAIState(EAIState::Searching);
		return;
	}

	const FVector TargetDirection = CurrentTarget->GetActorLocation() - GetActorLocation();
	const float LengthToTarget = TargetDirection.Length();
	if (LengthToTarget > MaxLengthToTargetInFiring)
	{
		SetCurrentAIState(EAIState::Searching);
		return;
	}

	const FRotator TargetRotation = TargetDirection.Rotation();
	Turret->SetTargetTurretRotation(TargetRotation);
}

void ATanksAIPawn::SetCurrentAIState(EAIState NewState)
{
	CurrentAIState = NewState;

	if (CurrentAIState == EAIState::Firing)
	{
		Fire();
		Turret->OnCanFire.AddUniqueDynamic(this, &ATanksAIPawn::Fire);
		GetWorld()->GetTimerManager().ClearTimer(SearchNewPointTimer);
	}
	else if (CurrentAIState == EAIState::Searching)
	{
		Turret->OnCanFire.RemoveDynamic(this, &ATanksAIPawn::Fire);

		GetWorld()->GetTimerManager().SetTimer(SearchNewPointTimer, this, &ATanksAIPawn::GenerateNewSearchPoint, TimeToSearchNewPoint, true);
	}
}

void ATanksAIPawn::GenerateNewSearchPoint() const
{
	const float Yaw = FMath::FRandRange(-180.f, 180.f);
	const FRotator NewPointFRotator(0.0f, Yaw, 0.0f);
	Turret->SetTargetTurretRotation(NewPointFRotator);
}
