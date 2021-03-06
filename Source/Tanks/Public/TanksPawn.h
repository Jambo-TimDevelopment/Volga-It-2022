// Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "TanksPawn.generated.h"

class UTanksHealthWidgetComponent;
class UTanksAttributeComponent;
class ATanksTurret;

/** Base pawn for player and AI controller*/
UCLASS(Abstract)
class TANKS_API ATanksPawn : public APawn
{
	GENERATED_BODY()

public:
	ATanksPawn(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void LoadoutTurret();

	virtual void MoveForward(float Value);
	virtual void MoveRight(float Value);

	UFUNCTION()
	virtual void Fire();

	UFUNCTION()
	void OnDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Scene Components")
	UBoxComponent* BoxCollisionComponent;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Scene Components")
	ATanksTurret* Turret;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UTanksAttributeComponent* AttributeComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UPawnMovementComponent* PawnMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTanksHealthWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Parameters")
	TSubclassOf<ATanksTurret> TurretClass;
};
