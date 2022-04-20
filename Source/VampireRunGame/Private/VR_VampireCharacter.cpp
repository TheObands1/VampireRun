// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_VampireCharacter.h"

// Sets default values
AVR_VampireCharacter::AVR_VampireCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVR_VampireCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVR_VampireCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AVR_VampireCharacter::MoveFoward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
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
