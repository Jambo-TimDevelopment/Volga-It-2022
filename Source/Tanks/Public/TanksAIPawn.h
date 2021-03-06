//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "TanksPawn.h"
#include "TanksAIPawn.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Searching,
	Firing,
};

/** Base pawn for AI */
UCLASS(BlueprintType, Blueprintable)
class TANKS_API ATanksAIPawn : public ATanksPawn
{
	GENERATED_BODY()

public:
	ATanksAIPawn(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual FVector GetPawnViewLocation() const override;

	virtual FRotator GetViewRotation() const override;

	void SetCurrentTarget(AActor* NewTarget);

private:
	void SearchingMovement(float DeltaTime);
	void FiringMovement(float DeltaTime);

	void SetCurrentAIState(EAIState NewState);

	void GenerateNewSearchPoint() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Firing", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float MaxLengthToTargetInFiring = 3000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Firing")
	float MaxFiringLeftAngle = -180.0f;

	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Firing")
	float MaxFiringRightAngle = 180.0f;

	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Firing")
	bool bClampFiringDirection = false;
	
	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Searching", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float TimeToSearchNewPoint = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Searching", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float MaxLengthToTargetInSearching = 3000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Searching", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float MaxHealthConeAngleForSearching = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category="Paramaters|Searching", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	int32 SearchingIntensive = 7;

private:
	EAIState CurrentAIState = EAIState::Searching;

	UPROPERTY()
	FTimerHandle SearchNewPointTimer;

	TWeakObjectPtr<ATanksPawn> CurrentTarget;
};
