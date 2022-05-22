//  Copyright 2022 Semyon Nikolaev


#include "TanksHealthWidgetComponent.h"
#include "TanksHealthWidget.h"

void UTanksHealthWidgetComponent::SetNewHealthToWidget(float NewHealth)
{
	if(Cast<UTanksHealthWidget>(GetWidget()))
	{
		Cast<UTanksHealthWidget>(GetWidget())->SetHealth(NewHealth);
	}
}
