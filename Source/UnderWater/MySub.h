// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MySub.generated.h"

UCLASS()
class UNDERWATER_API AMySub : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMySub();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ArrowExit")
	class UArrowComponent* ArrowExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxColli")
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Swim")
	bool isSwimming = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveBack(float value);
	void MoveRight(float value);
	
	void ExitSub();

	UFUNCTION()
	void Overlap(UPrimitiveComponent* Overlapped, AActor* otherActor, UPrimitiveComponent* otherComp, int32 othrBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	UFUNCTION()
	void OverlapEnd(class UPrimitiveComponent* Overlapped, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 othrBodyIndex);
};
