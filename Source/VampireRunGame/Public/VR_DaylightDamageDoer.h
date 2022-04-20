// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VR_DaylightDamageDoer.generated.h"

class UBillboardComponent;
class AVR_VampireCharacter;
class AController;

UCLASS()
class VAMPIRERUNGAME_API AVR_DaylightDamageDoer : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* BillboardComponent;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Debug")
	bool bIsDebugging;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (ClampMin = 0.0f))
	float DamageRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (ClampMin = 0.0f))
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage|TraceLength", meta = (ClampMin = 0.0f))
	float TraceLength;

	AController* MyController;

	TSubclassOf<UDamageType> MyDamageType;

	AVR_VampireCharacter* PlayerReference;

	FTimerHandle TimerHandle_DamagePlayer;

public:	
	// Sets default values for this actor's properties
	AVR_DaylightDamageDoer();


public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartDamagingPlayer();

	void DamagePlayer();

	UFUNCTION(BlueprintCallable)
	void StopDamagingPlayer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
