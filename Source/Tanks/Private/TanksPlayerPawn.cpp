// Copyright 2022 Semyon Nikolaev


#include "TanksPlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathUtility.h"

ATanksPlayerPawn::ATanksPlayerPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("ThirdPersonCamera");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
}

void ATanksPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ATanksPlayerPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATanksPlayerPawn::MoveRight);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATanksPlayerPawn::Fire);
}

void ATanksPlayerPawn::MoveForward(float Value)
{
	Super::MoveForward(Value);
}

void ATanksPlayerPawn::MoveRight(float Value)
{
	Super::MoveRight(Value);
}

void ATanksPlayerPawn::Fire()
{
	Super::Fire();
}
