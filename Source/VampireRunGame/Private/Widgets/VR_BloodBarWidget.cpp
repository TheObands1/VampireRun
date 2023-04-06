// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/VR_BloodBarWidget.h"
#include "VR_VampireCharacter.h"
#include "Kismet/GameplayStatics.h"

void UVR_BloodBarWidget::InitializeWidget()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (IsValid(PlayerCharacter))
	{
		AVR_VampireCharacter* PossibleVampireCharacter = Cast<AVR_VampireCharacter>(PlayerCharacter);

		if (IsValid(PossibleVampireCharacter))
		{
			PossibleVampireCharacter->OnBloodUpdateDelegate.AddDynamic(this, &UVR_BloodBarWidget::UpdateBloodPercent);
		}
	}
}

void UVR_BloodBarWidget::UpdateBloodPercent(float CurrentBlood, float MaxBlood)
{
	BloodPercent = CurrentBlood / MaxBlood;
}
