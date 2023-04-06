// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VR_VampireCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBloodUpdateSignature, float, CurrentBlood, float, MaxBlood);

class UVR_HealthComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class VAMPIRERUNGAME_API AVR_VampireCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UVR_HealthComponent* VampireHealthComponent;

public:
	// Sets default values for this character's properties
	AVR_VampireCharacter();

public:
	//Delegates
	UPROPERTY(BlueprintAssignable)
	FOnBloodUpdateSignature OnBloodUpdateDelegate;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blood")
	bool bIsLowOnBlood;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float FowardAxisValue;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float RightAxisValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blood")
	float CurrentBloodAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blood")
	float MaxBloodAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blood")
	float BloodLossRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blood")
	float BloodLossAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blood")
	float DamageDueToLowBlood;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Blood")
	float DamageDueToLowBloodRate;

	TSubclassOf<UDamageType> MyDamageType;

	FTimerHandle TimerHandle_ReduceBloodAmount;

	FTimerHandle TimerHandle_DamageSelfDueToLowBlood;

	FTimerHandle TimerHandle_UpdateInitialBloodAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float AxisValue);

	void MoveFoward(float AxisValue);

	void ReduceBloodAmount();

	void DamageSelfDueToLowBlood();

	void ActivateBloodLossTimer();

	void UpdateBloodAmount();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddBlood(float BloodToAdd);

	float GetCurrentBloodAmount() { return CurrentBloodAmount; };

	float GetMaxBloodAmount() { return MaxBloodAmount; };

	bool GetIsLowOnBlood() { return bIsLowOnBlood; };

	UVR_HealthComponent* GetHealthComponent() { return VampireHealthComponent; };

};
