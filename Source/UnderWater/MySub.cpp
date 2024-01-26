// Fill out your copyright notice in the Description page of Project Settings.


#include "MySub.h"
#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMySub::AMySub()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	Camera->SetupAttachment(GetRootComponent());
	//Camera->SetActive(0);
	//Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Head");
	Camera->bUsePawnControlRotation = true;

	ArrowExit = CreateDefaultSubobject<UArrowComponent>(TEXT("ExitArrow"));
	ArrowExit->SetupAttachment(GetRootComponent());

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColli"));
	Box->SetupAttachment(GetMesh());
	Box->OnComponentBeginOverlap.AddDynamic(this, &AMySub::Overlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AMySub::OverlapEnd);
	
}

// Called when the game starts or when spawned
void AMySub::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AMySub::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("%d"), GetCharacterMovement()->IsSwimming());
}

// Called to bind functionality to input
void AMySub::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMySub::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveBack"), this, &AMySub::MoveBack);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMySub::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMySub::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMySub::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("EnterSub"), IE_Pressed, this, &AMySub::ExitSub);
}

void AMySub::MoveRight(float value) {
	AddMovementInput(GetActorRightVector() * value);
}

void AMySub::MoveForward(float value) {

	if (isSwimming) {
		if (GetCharacterMovement()->IsSwimming() == false) {
			GetCharacterMovement()->SetMovementMode(MOVE_Swimming);
		}
		AddMovementInput(Camera->GetForwardVector() * value);
	}


}
void AMySub::MoveBack(float value) {

	if (isSwimming) {
		AddMovementInput(Camera->GetForwardVector() * value);
	}

}

void AMySub::Overlap(UPrimitiveComponent* Overlapped, AActor* otherActor, UPrimitiveComponent* otherComp, int32 othrBodyIndex, bool bFromSweep, const FHitResult& sweepResult) {
	if (AMyPlayer* player = Cast<AMyPlayer>(otherActor)) {
		player->canEnter = true;
		//UE_LOG(LogTemp, Warning, TEXT("true"));
	}

}

void AMySub::OverlapEnd(UPrimitiveComponent* Overlapped, AActor* otherActor, UPrimitiveComponent* otherComp, int32 othrBodyIndex) {
	if (AMyPlayer* player = Cast<AMyPlayer>(otherActor)) {
		player->canEnter = false;
	}

}


void AMySub::ExitSub() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayer::StaticClass(), FoundActors);
	for (AActor* r : FoundActors) {
		AMyPlayer* Player = Cast<AMyPlayer>(r);
		AController* temp = GetController();
		Player->SetActorEnableCollision(true);
		Player->SetActorHiddenInGame(false);
		Player->SetActorLocation(ArrowExit->GetComponentLocation());
		temp->UnPossess();
		temp->Possess(Player);
	}

}

