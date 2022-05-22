//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TanksHealthWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UTanksHealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetNewHealthToWidget(float NewHealth);
};