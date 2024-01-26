// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetActive(0);
	Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Head");
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Camera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("%d"), isSwimming);
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveBack"), this, &AMyPlayer::MoveBack);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyPlayer::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyPlayer::Jump);
}
void AMyPlayer::MoveRight(float value) {
	AddMovementInput(GetActorRightVector() * value);
}

void AMyPlayer::MoveForward(float value) {
	if (isSwimming) {
		if (GetCharacterMovement()->IsSwimming() == false) {
			GetCharacterMovement()->SetMovementMode(MOVE_Swimming);
		}
		AddMovementInput(Camera->GetForwardVector() * value);
	}
	else {
		AddMovementInput(GetActorForwardVector() * value);
	}
	
}
void AMyPlayer::MoveBack(float value) {
	if (isSwimming) {
		AddMovementInput(Camera->GetForwardVector() * value);
	}
	else {
		AddMovementInput(GetActorForwardVector() * value);
	}
}

