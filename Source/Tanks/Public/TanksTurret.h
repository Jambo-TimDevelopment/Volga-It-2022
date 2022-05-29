// Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "TanksTurret.generated.h"

class ATanksProjectile;

UCLASS(Abstract)
class TANKS_API ATanksTurret : public AActor
{
	GENERATED_BODY()

public:
	ATanksTurret();

	virtual void Tick(float DeltaTime) override;

	virtual void StartFire();

	virtual void StopFire();

	/** Blueprint implementation for visual effects*/
	UFUNCTION(BlueprintImplementableEvent)
	void OnFire(const FVector FireStart, const FVector FireEnd);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnDestroy();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	float RotationSpeed = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	int32 MaxAmmoCount = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	int32 AmmoCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	float TimeToReload;

	bool bCanStartFire = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	float BarrelLength = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	TSubclassOf<ATanksProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Parameters|Fire")
	int32 CountAmmoAtFire = 4;

	UPROPERTY(EditDefaultsOnly, Category="Parameters|Fire")
	float FireSpreadHealthAngle;

	UPROPERTY(EditDefaultsOnly, Category="Parameters|Fire")
	float FireDistance = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	float BaseDamage = 30;

private:
	UPROPERTY()
	FTimerHandle FireCooldownTimer;
};
