// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VR_VampireCharacter.generated.h"

class UVR_HealthComponent;

UCLASS()
class VAMPIRERUNGAME_API AVR_VampireCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UVR_HealthComponent* VampireHealthComponent;

public:
	// Sets default values for this character's properties
	AVR_VampireCharacter();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float FowardAxisValue;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float RightAxisValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float AxisValue);

	void MoveFoward(float AxisValue);

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UVR_HealthComponent* GetHealthComponent() { return VampireHealthComponent; };

};
