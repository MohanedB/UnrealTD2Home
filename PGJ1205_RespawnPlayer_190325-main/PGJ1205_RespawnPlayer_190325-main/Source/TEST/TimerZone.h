// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TimerZone.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API ATimerZone : public ATriggerBox
{
	GENERATED_BODY()

public:
	ATimerZone();

	UPROPERTY(VisibleAnywhere, Category = "Settings")
	UStaticMeshComponent* Mesh;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Timer")
	bool startTimer;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
