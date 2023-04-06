// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VR_BloodBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRERUNGAME_API UVR_BloodBarWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float BloodPercent;

protected:
	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void UpdateBloodPercent(float CurrentBlood, float MaxBlood);
	
};
