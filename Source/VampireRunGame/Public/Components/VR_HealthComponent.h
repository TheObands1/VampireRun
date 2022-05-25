// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VR_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, UVR_HealthComponent*, HealthComponent, AActor*, DamagedActor, float, Damage, const UDamageType*, DamageType, AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdateSignature, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIRERUNGAME_API UVR_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Health|State")
	bool bIsDead;

	UPROPERTY(BlueprintReadWrite, Category = "Health|State")
	bool bIsLowOnHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = 0.0f))
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = 0.0f))
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Owner")
	AActor* MyOwner;

	FTimerHandle TimerHandle_UpdateHealth;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdateSignature OnHealthUpdateDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnDeathSignature OnDeathDelegate;

public:	
	// Sets default values for this component's properties
	UVR_HealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
	void UpdateHealth();

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Health|State")
	bool IsDead() const { return bIsDead; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() { return CurrentHealth; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() { return MaxHealth; };

	bool AddHealth(float HealthToAdd);


		
};
