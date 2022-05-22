//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TanksHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API UTanksHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetHealth(float Health);
};
