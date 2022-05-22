// Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TanksTurret.generated.h"

class ATanksProjectile;

UCLASS(Blueprintable, BlueprintType)
class TANKS_API ATanksTurret : public AActor
{
	GENERATED_BODY()

public:
	ATanksTurret();

	virtual void Tick(float DeltaTime) override;

	virtual void StartFire()
	{
	}

	virtual void StopFire()
	{
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	float RotationSpeed = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	int32 MaxAmmoCount = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	int32 AmmoCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	TSubclassOf<ATanksProjectile> ProjectileClass;
};
