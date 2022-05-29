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
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetNewHealthToWidget(float NewHealth);

protected:
	UPROPERTY(EditDefaultsOnly, Category=Property)
	bool bAlwaysVisible;

	UPROPERTY(EditDefaultsOnly, Category=Property)
	float HideCooldownTime = 3.0f;

private:
	UPROPERTY()
	FTimerHandle HideCooldownTimer;
};
