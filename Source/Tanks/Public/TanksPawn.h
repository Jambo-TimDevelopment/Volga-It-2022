// Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "TanksPawn.generated.h"

class ATanksTurret;
/** Base pawn for player and AI controller*/
UCLASS(Abstract)
class TANKS_API ATanksPawn : public APawn
{
	GENERATED_BODY()

public:
	ATanksPawn(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
protected:
	virtual void MoveForward(float Value);

	virtual void MoveRight(float Value);

	virtual void LoadoutTurret();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UPawnMovementComponent* PawnMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* StaticMeshChassis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	ATanksTurret* Turret;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	TSubclassOf<ATanksTurret> TurretClass;
};