// Fill out your copyright notice in the Description page of Project Settings.


#include "FishAi.h"
#include "Nodes.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AFishAi::AFishAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFishAi::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFishAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFishAi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFishAi::GetAllNodes() {
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANodes::StaticClass(), nodeArray);
	for (AActor* n : nodeArray) {
		ANodes* node = Cast<ANodes>(n);
		nodeArray.Add(node);
	}
	int a = allVectors.Num();
}