//  Copyright 2022 Semyon Nikolaev


#include "TanksAIController.h"
#include "TanksAIPawn.h"
#include "TanksAttributeComponent.h"
#include "TanksPlayerPawn.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

ATanksAIController::ATanksAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void ATanksAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (IsValid(InPawn))
	{
		checkf(InPawn->IsA<ATanksAIPawn>(), TEXT("ATanksAIController::SetPawn InPawn always ATanksAIPawn"))
		CachedAiPawn = StaticCast<ATanksAIPawn*>(InPawn);
	}
}

void ATanksAIController::ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	Super::ActorsPerceptionUpdated(UpdatedActors);

	if (!CachedAiPawn.IsValid())
	{
		return;
	}

	AActor* ClosestActor = GetClosestSensedActor(UAISense_Sight::StaticClass());
	ATanksPlayerPawn* PlayerPawn = Cast<ATanksPlayerPawn>(ClosestActor);
	if(!IsValid(PlayerPawn))
	{
		return;
	}
	CachedAiPawn->SetCurrentTarget(ClosestActor);
	if(IsValid(ClosestActor) && CachedAiPawn->AttributeComponent->IsLive() && PlayerPawn->AttributeComponent->IsLive())
	{
		MoveToActor(ClosestActor);
	}
}

AActor* ATanksAIController::GetClosestSensedActor(TSubclassOf<UAISense> SenseClass)
{
	if (!IsValid(GetPawn())) return nullptr;

	TArray<AActor*> SensedActors;
	PerceptionComponent->GetCurrentlyPerceivedActors(SenseClass, SensedActors);
	AActor* ClosestActor = nullptr;
	float MinSquaredDistance = FLT_MAX;
	FVector PawnLocation = GetPawn()->GetActorLocation();

	for (AActor* SeenActor : SensedActors)
	{
		float CurrentSquaredDistance = (PawnLocation - SeenActor->GetActorLocation()).SizeSquared();
		if (CurrentSquaredDistance < MinSquaredDistance)
		{
			MinSquaredDistance = CurrentSquaredDistance;
			ClosestActor = SeenActor;
		}
	}

	return ClosestActor;
}
