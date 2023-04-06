// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_VampireCharacter.h"
#include "Components/VR_HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVR_VampireCharacter::AVR_VampireCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponentComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	SpringArmComponent->TargetArmLength = 800.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));
	SpringArmComponent->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCameraComponent"));
	TopDownCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	VampireHealthComponent = CreateDefaultSubobject<UVR_HealthComponent>(TEXT("VampireHealthComponent"));

	FowardAxisValue = 0;
	RightAxisValue = 0;
	BloodLossRate = 1.0f;
	BloodLossAmount = 20.0f;
	DamageDueToLowBlood = 5.0f;
	DamageDueToLowBloodRate = 0.7f;
	MaxBloodAmount = 100.0f;
	CurrentBloodAmount = MaxBloodAmount;
}

// Called when the game starts or when spawned
void AVR_VampireCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentBloodAmount = MaxBloodAmount;

	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateInitialBloodAmount, this, &AVR_VampireCharacter::UpdateBloodAmount, 0.2f, false);
	ActivateBloodLossTimer();
}

void AVR_VampireCharacter::MoveRight(float AxisValue)
{
	//AddMovementInput(GetActorRightVector() * AxisValue); (for the wanted movement, this cannot be used, as camera is not being controlled by mouse)
	FowardAxisValue = AxisValue;
}

void AVR_VampireCharacter::MoveFoward(float AxisValue)
{
	//AddMovementInput(GetActorForwardVector() * AxisValue);
	RightAxisValue = AxisValue;
}

void AVR_VampireCharacter::ReduceBloodAmount()
{
	CurrentBloodAmount = FMath::Clamp((CurrentBloodAmount - BloodLossAmount), 0.0f, MaxBloodAmount);
	OnBloodUpdateDelegate.Broadcast(CurrentBloodAmount, MaxBloodAmount);

	if (CurrentBloodAmount == 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ReduceBloodAmount);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_DamageSelfDueToLowBlood, this, &AVR_VampireCharacter::DamageSelfDueToLowBlood, DamageDueToLowBloodRate, true);
	}
}

void AVR_VampireCharacter::DamageSelfDueToLowBlood()
{
	if (CurrentBloodAmount == 0)
	{
		UGameplayStatics::ApplyDamage(this, DamageDueToLowBlood, GetController(), this, MyDamageType);
	}
	else //if player somehow gets more blood, stop damaging yourself and start, eventually, losing blood.
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_DamageSelfDueToLowBlood);
		ActivateBloodLossTimer();
	}
}

void AVR_VampireCharacter::ActivateBloodLossTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ReduceBloodAmount, this, &AVR_VampireCharacter::ReduceBloodAmount, BloodLossRate, true, 3.0f);
}

void AVR_VampireCharacter::UpdateBloodAmount()
{
	OnBloodUpdateDelegate.Broadcast(CurrentBloodAmount, MaxBloodAmount);
}

// Called every frame
void AVR_VampireCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVR_VampireCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &AVR_VampireCharacter::MoveRight);

	PlayerInputComponent->BindAxis("MoveFoward", this, &AVR_VampireCharacter::MoveFoward);

}

void AVR_VampireCharacter::AddBlood(float BloodToAdd)
{
	if (BloodToAdd < 0)
	{
		return;
	}
	else
	{
		CurrentBloodAmount = FMath::Clamp((CurrentBloodAmount + BloodToAdd), 0.0f, MaxBloodAmount);
		OnBloodUpdateDelegate.Broadcast(CurrentBloodAmount, MaxBloodAmount);
	}
}

