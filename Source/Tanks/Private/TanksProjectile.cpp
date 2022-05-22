//  Copyright 2022 Semyon Nikolaev


#include "TanksProjectile.h"
#include "Tanks.h"
#include "Kismet/GameplayStatics.h"

ATanksProjectile::ATanksProjectile()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ATanksProjectile::OnOverlapBegin);
	RootComponent = CapsuleComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->InitialSpeed = 7000.0f;
}

void ATanksProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor->GetInstigator()) && IsValid(GetInstigator()) && OtherActor->GetInstigator() == GetInstigator())
	{
		return;
	}

	const TArray<AActor*> IgnoredActors;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, GetActorForwardVector(), DamageRadius, UDamageType::StaticClass(), IgnoredActors, this, nullptr, false, ECC_Bullet);
	this->Destroy();

}
