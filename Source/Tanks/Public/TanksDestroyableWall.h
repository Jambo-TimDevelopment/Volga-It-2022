//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TanksDestroyableWall.generated.h"

class UTanksHealthWidgetComponent;
class UTanksAttributeComponent;
UCLASS()
class TANKS_API ATanksDestroyableWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATanksDestroyableWall();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTanksAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UTanksHealthWidgetComponent* HealthWidgetComponent;
};
