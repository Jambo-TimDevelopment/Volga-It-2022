//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "TanksTurret.h"
#include "TanksTurretShot.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, BlueprintType)
class TANKS_API ATanksTurretShot : public ATanksTurret
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

	virtual void StopFire() override;
};
