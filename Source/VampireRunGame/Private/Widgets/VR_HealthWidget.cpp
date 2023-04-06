// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VR_HealthWidget.h"
#include "VR_VampireCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VR_HealthComponent.h"

void UVR_HealthWidget::InitializeWidget()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (IsValid(PlayerCharacter))
	{
		AVR_VampireCharacter* PossibleVampireCharacter = Cast<AVR_VampireCharacter>(PlayerCharacter);

		if (IsValid(PossibleVampireCharacter))
		{
			UVR_HealthComponent* PossibleHealthComponent = PossibleVampireCharacter->GetHealthComponent();

			if (IsValid(PossibleHealthComponent))
			{
				PossibleHealthComponent->OnHealthUpdateDelegate.AddDynamic(this, &UVR_HealthWidget::UpdateHealthPercent);
			}
		}
	}
}

void UVR_HealthWidget::UpdateHealthPercent(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
	HealthColor = FMath::Lerp(EmptyHealthColor, FullHealthColor, HealthPercent);

}
