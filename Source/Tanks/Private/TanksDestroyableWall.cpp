//  Copyright 2022 Semyon Nikolaev


#include "TanksDestroyableWall.h"
#include "TanksAttributeComponent.h"
#include "TanksHealthWidgetComponent.h"

ATanksDestroyableWall::ATanksDestroyableWall()
{
	HealthWidgetComponent = CreateDefaultSubobject<UTanksHealthWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(RootComponent);

	AttributeComponent = CreateDefaultSubobject<UTanksAttributeComponent>("AttributeComponent");
}

void ATanksDestroyableWall::BeginPlay()
{
	Super::BeginPlay();

	OnTakeRadialDamage.AddDynamic(AttributeComponent, &UTanksAttributeComponent::OnTakeDamage);
	AttributeComponent->OnHealthChanged.AddDynamic(HealthWidgetComponent, &UTanksHealthWidgetComponent::SetNewHealthToWidget);
	AttributeComponent->OnDeath.AddDynamic(this, &ATanksDestroyableWall::OnDeath);
}

void ATanksDestroyableWall::OnDeath()
{
	//HealthWidgetComponent->DestroyComponent();
	AttributeComponent->OnDeath.RemoveAll(this);
	AttributeComponent->OnHealthChanged.RemoveAll(this);
}
