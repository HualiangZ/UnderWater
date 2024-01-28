// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes.h"

// Sets default values
ANodes::ANodes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANodes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANodes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

