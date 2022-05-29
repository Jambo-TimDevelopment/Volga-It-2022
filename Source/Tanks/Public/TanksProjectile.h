//  Copyright 2022 Semyon Nikolaev

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Field/FieldSystemActor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TanksProjectile.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TANKS_API ATanksProjectile : public AFieldSystemActor
{
	GENERATED_BODY()

public:
	ATanksProjectile();

	void SetBaseDamage(const float NewBaseDamage) { BaseDamage = NewBaseDamage; }

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	float DamageRadius = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	bool bInstigatorIgnoreDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	float ForceMultiply = 100.0f;

private:
	float BaseDamage;
};
