// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "TESTCharacter.h"
#include "TESTGameMode.h"

// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::RespawnItem() {

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("This appears on overlapping"));

	if (OtherActor)
	{
		ATESTCharacter* Character = Cast<ATESTCharacter>(OtherActor);

		if (Character)
		{
			if (UWorld* World = GetWorld())
			{
				ATESTGameMode* GameMode = Cast<ATESTGameMode>(World -> GetAuthGameMode());

				if (GameMode)
				{
					GameMode->IncrementScore();
				    SetActorHiddenInGame(true);
					SetActorEnableCollision(false);

					
				}
			}
		}
	}

}

