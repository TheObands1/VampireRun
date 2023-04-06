// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VR_HealthComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UVR_HealthComponent::UVR_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
	// ...
}


// Called when the game starts
void UVR_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	MyOwner = GetOwner();

	if (IsValid(MyOwner))
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UVR_HealthComponent::TakingDamage);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateHealth, this, &UVR_HealthComponent::UpdateHealth, 0.2f, false);
	
}

void UVR_HealthComponent::TakingDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0.0f)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);

	CurrentHealth <= (MaxHealth / 2) ? bIsLowOnHealth = true : bIsLowOnHealth = false;

	if (CurrentHealth == 0.0f)
	{
		bIsDead = true;
		OnDeathDelegate.Broadcast();
	}

	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	OnHealthUpdateDelegate.Broadcast(CurrentHealth, MaxHealth);
}

void UVR_HealthComponent::UpdateHealth()
{
	OnHealthUpdateDelegate.Broadcast(CurrentHealth, MaxHealth);
}

bool UVR_HealthComponent::AddHealth(float HealthToAdd)
{
	if (bIsDead)
	{
		return false;
	}

	if (CurrentHealth == MaxHealth)
	{
		return false;
	}

	CurrentHealth = FMath::Clamp((CurrentHealth + HealthToAdd), 0.0f, MaxHealth);
	OnHealthUpdateDelegate.Broadcast(CurrentHealth, MaxHealth);

	return true;
}


// Called every frame
/*
void UVR_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
*/

