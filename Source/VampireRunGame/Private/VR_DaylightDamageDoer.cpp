// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_DaylightDamageDoer.h"
#include "Components/BillboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VR_VampireCharacter.h"
#include "VampireRunGame/VampireRunGame.h"
#include "DrawDebugHelpers.h"

// Sets default values
AVR_DaylightDamageDoer::AVR_DaylightDamageDoer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));

	DamageRate = 0.5f;
	Damage = 50.0f;
	TraceLength = 1000.0f;
	bIsDebugging = false;
	DistanceFromPlayer = 800.0f;

}

// Called when the game starts or when spawned
void AVR_DaylightDamageDoer::BeginPlay()
{
	Super::BeginPlay();

	PlayerReference = Cast<AVR_VampireCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void AVR_DaylightDamageDoer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(PlayerReference))
	{
		FVector PlayerLocation = PlayerReference->GetActorLocation();

		SetActorLocation(FVector((PlayerLocation.X + DistanceFromPlayer), PlayerLocation.Y, GetActorLocation().Z));
	}

}

void AVR_DaylightDamageDoer::StartDamagingPlayer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DamagePlayer, this, &AVR_DaylightDamageDoer::DamagePlayer, DamageRate, true);
}

void AVR_DaylightDamageDoer::DamagePlayer()
{
	FVector ShotDirection = GetActorRotation().Vector();

	//ShotDirection*TraceLenght is substracted from the location because the shot has to come towards the player
	FVector TraceEnd = GetActorLocation() - (ShotDirection * TraceLength);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	FHitResult HitResult;
	bool bDidLineTraceHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), TraceEnd, COLLISION_DAYLIGHTDAMAGE, QueryParams);

	if (bDidLineTraceHit)
	{
		//Make Damage
		AActor* HitActor = HitResult.GetActor();
		AVR_VampireCharacter* PossiblePlayerCharacter = Cast<AVR_VampireCharacter>(HitActor);
		
		if (IsValid(PossiblePlayerCharacter))
		{
			UGameplayStatics::ApplyDamage(PossiblePlayerCharacter, Damage, MyController, this, MyDamageType);
		}
	}

	if (bIsDebugging)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, FColor::Red, false, 1.0f, 0.0f, 10.0f);
	}

}

void AVR_DaylightDamageDoer::StopDamagingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_DamagePlayer);
}

