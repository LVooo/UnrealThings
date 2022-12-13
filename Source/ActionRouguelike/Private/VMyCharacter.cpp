// Fill out your copyright notice in the Description page of Project Settings.


#include "VMyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVMyCharacter::AVMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true; // use springCamera control
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true; // set character movement rotate

	bUseControllerRotationYaw = false; // disable user yaw control
}

// Called when the game starts or when spawned
void AVMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
}

void AVMyCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation(); // camera control
	ControlRot.Pitch = 0.0f; // set x and z axis = 0, just keep horizontal moving
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), Value);
}

void AVMyCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up£¨Blue£©

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y); // Rotation of our character instead of rotation of our camera

	AddMovementInput(RightVector, Value);
}