//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TanksAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Value);

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
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	void Heal() { Health = MaxHealth; }

public:
	UPROPERTY(BlueprintAssignable, Category="Tank|Delegate")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category="Tank|Delegate")
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Attributes)
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Attributes)
	float Health;
};
