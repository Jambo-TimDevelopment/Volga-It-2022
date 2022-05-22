//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TanksAttributeComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKS_API UTanksAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTanksAttributeComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable)
	bool IsLive() { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void Heal() { Health = MaxHealth; }

public:
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Attributes)
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Attributes)
	float Health;
};
