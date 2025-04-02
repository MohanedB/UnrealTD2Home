// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TESTGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);

UCLASS(minimalapi)
class ATESTGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATESTGameMode();

	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	virtual void RestartPlayer(AController* NewPlayer) override;

	void IncrementScore();

	void ResetScore();

	void StartTimer();

	void EndTimer();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void PlayerDied(ACharacter* Character);

	UPROPERTY()
	FOnPlayerDiedSignature OnPlayerDied;

private:
	UPROPERTY(VisibleAnywhere, Category = "Score")
	float Score;

	UPROPERTY(VisibleAnywhere, Category = "Timer")
	float Time;

	UPROPERTY(VisibleAnywhere, Category = "Timer")
	bool timerStarted = false;

	UPROPERTY(VisibleAnywhere, Category = "Timer")
	float BestTime;

};



