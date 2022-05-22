// Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "TanksPawn.h"
#include "TanksPlayerPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

/** Only player controlled pawn */
UCLASS(Blueprintable)
class TANKS_API ATanksPlayerPawn : public ATanksPawn
{
	GENERATED_BODY()

public:
	ATanksPlayerPawn(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;

	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TanksPlayerPawn")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TanksPlayerPawn")
	USpringArmComponent* SpringArmComponent;
};
