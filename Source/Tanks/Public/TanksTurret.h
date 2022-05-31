// Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "GameFramework/Actor.h"
#include "TanksTurret.generated.h"

class ATanksPawn;
class ATanksProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCanFire);

UCLASS(Abstract)
class TANKS_API ATanksTurret : public AActor
{
	GENERATED_BODY()

public:
	ATanksTurret();

	virtual void Tick(float DeltaTime) override;

	virtual void Fire();

	/** Blueprint implementation for visual effects*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnFire(const FVector FireStart, const FVector FireEnd);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnDestroy();

	void SetTargetTurretRotation(FRotator NewTargetRotation) { CurrentTargetTurretRotation = NewTargetRotation; }

	UPROPERTY()
	FOnCanFire OnCanFire;

private:
	UFUNCTION()
	void ResetCooldownFire();

public:
	bool bUseTargetTurretRotation;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Components)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters, meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float RotationSpeed = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters, meta = (ClampMin = 0, UIMin = 0))
	int32 MaxAmmoCount = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters, meta = (ClampMin = 0, UIMin = 0))
	int32 AmmoCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters, meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float TimeToReload;

	bool bCanStartFire = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	float BarrelLength = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	TSubclassOf<ATanksProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Parameters|Fire", meta = (ClampMin = 0, UIMin = 0))
	int32 CountAmmoAtFire = 4;

	UPROPERTY(EditDefaultsOnly, Category="Parameters|Fire", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float FireSpreadHealthAngle;

	UPROPERTY(EditDefaultsOnly, Category="Parameters|Fire", meta = (ClampMin = 0.0f, UIMin = 0.0f))
	float FireDistance = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Parameters)
	float BaseDamage = 30;

private:
	UPROPERTY()
	FTimerHandle FireCooldownTimer;

	FRotator CurrentTargetTurretRotation;
};
