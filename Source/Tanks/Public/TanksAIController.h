//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TanksAIPawn.h"
#include "TanksAIController.generated.h"

class UAISense;

/**
 * 
 */
UCLASS()
class TANKS_API ATanksAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATanksAIController();

	virtual void SetPawn(APawn* InPawn) override;

	virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;

protected:
	AActor* GetClosestSensedActor(TSubclassOf<UAISense> SenseClass);

private:
	TWeakObjectPtr<ATanksAIPawn> CachedAiPawn;
};
