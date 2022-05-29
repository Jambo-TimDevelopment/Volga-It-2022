//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "TanksTurret.h"
#include "TanksTurretBurst.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, BlueprintType)
class TANKS_API ATanksTurretBurst : public ATanksTurret
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

	virtual void StopFire() override;

private:
	void MakeShot();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters|Burst")
	float TimeToReloadBurst = 0.5f;

private:
	UPROPERTY()
	FTimerHandle BurstCooldownTimer;
	
	int32 CurrentCountAmmoAtFire;
};
