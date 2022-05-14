// Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TanksTurret.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TANKS_API ATanksTurret : public AActor
{
	GENERATED_BODY()

public:
	ATanksTurret();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Parameters")
	float RotationSpeed = 3;
};
