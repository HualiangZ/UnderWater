// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FishAi.generated.h"

UCLASS()
class UNDERWATER_API AFishAi : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFishAi();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Node")
	TArray<AActor*> nodeArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Vectors")
	TArray<FVector> allVectors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void GetAllNodes();
};
