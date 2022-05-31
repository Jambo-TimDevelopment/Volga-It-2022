//  Copyright 2022 Semyon Nikolaev


#include "TanksHealthWidgetComponent.h"
#include "TanksHealthWidget.h"

void UTanksHealthWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!bAlwaysVisible && IsValid(GetWidget())) GetWidget()->SetVisibility(ESlateVisibility::Hidden);
}

void UTanksHealthWidgetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(HideCooldownTimer);

	Super::EndPlay(EndPlayReason);
}

void UTanksHealthWidgetComponent::SetNewHealthToWidget(float NewHealth)
{
	if (!Cast<UTanksHealthWidget>(GetWidget()))
	{
		return;
	}

	Cast<UTanksHealthWidget>(GetWidget())->SetHealth(NewHealth);
	if (!bAlwaysVisible)
	{
		GetWidget()->SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetTimerManager().ClearTimer(HideCooldownTimer);
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([&]() { if (IsValid(this)) this->GetWidget()->SetVisibility(ESlateVisibility::Hidden); });
		GetWorld()->GetTimerManager().SetTimer(HideCooldownTimer, TimerDelegate, HideCooldownTime, false);
	}
}
