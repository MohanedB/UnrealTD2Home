// Fill out your copyright notice in the Description page of Project Settings.


#include "KillPlayer.h"
#include "TESTCharacter.h"

// Sets default values for this component's properties
UKillPlayer::UKillPlayer()
{

}


// Called when the game starts
void UKillPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Mesh = Owner->FindComponentByClass<UStaticMeshComponent>();

		if (Mesh)
		{
			Mesh->OnComponentHit.AddDynamic(this, &UKillPlayer::OnHit);
		}
	}
}

void UKillPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		ATESTCharacter* Character = Cast<ATESTCharacter>(OtherActor);
		if (Character)
		{
			Character->CallRestartPlayer();
		}
	}
}
