// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerZone.h"
#include "TESTCharacter.h"
#include "TESTGameMode.h"

// Sets default values
ATimerZone::ATimerZone()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ATimerZone::OnOverlapBegin);
}

void ATimerZone::BeginPlay()
{
	Super::BeginPlay();

}

void ATimerZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("This appears on overlapping"));

	if (OtherActor)
	{
		ATESTCharacter* Character = Cast<ATESTCharacter>(OtherActor);

		if (Character)
		{
			if (UWorld* World = GetWorld())
			{
				ATESTGameMode* GameMode = Cast<ATESTGameMode>(World->GetAuthGameMode());

				if (GameMode)
				{
					if (startTimer)
					{
						GameMode->StartTimer();
					}
					else
					{
						GameMode->EndTimer();
					}
				}
			}
		}
	}
}

void ATimerZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}