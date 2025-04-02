// Copyright Epic Games, Inc. All Rights Reserved.

#include "TESTGameMode.h"
#include "TESTCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "item.h"
#include "Engine.h"


ATESTGameMode::ATESTGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
}

void ATESTGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
	Time = 0.0f;
	timerStarted = false;
	Score = 0;


	for (TActorIterator<AItem> It(GetWorld()); It; ++It)
	{
		(*It)->RespawnItem();
	}

}

void ATESTGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &ATESTGameMode::PlayerDied);
	}
}

void ATESTGameMode::PlayerDied(ACharacter* Character)
{
	AController* CharacterController = Character->GetController();
	RestartPlayer(CharacterController);
}

void ATESTGameMode::IncrementScore()
{
	Score += 1;
}

void ATESTGameMode::ResetScore()
{
	Score = 0;
}

void ATESTGameMode::StartTimer()
{
	if (timerStarted == false) {
	
	Time = 0.0f;
	timerStarted = true;
	}
}

void ATESTGameMode::EndTimer()
{
	timerStarted = false;

	if (Time > 0.0f && Time <= BestTime || BestTime == 0.0f)
	{
		BestTime = Time;
	}
}

void ATESTGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (timerStarted)
	{
		Time += DeltaTime;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 2.0f, FColor::Emerald, FString::Printf(TEXT("Score: %f"), Score));
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Emerald, FString::Printf(TEXT("Time: %f"), Time));
		GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Emerald, FString::Printf(TEXT("Best Time: %f"), BestTime));
	}

}
