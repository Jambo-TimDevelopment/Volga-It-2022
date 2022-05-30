//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "TanksTurret.h"
#include "TanksTurretBomb.generated.h"

/** Turret implementation with explosion bomb */
UCLASS()
class TANKS_API ATanksTurretBomb : public ATanksTurret
{
	GENERATED_BODY()

public:
	virtual void Fire() override;
};
