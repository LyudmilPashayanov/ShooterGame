// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	SetupInputSystem();
}

void AShooterCharacter::SetupInputSystem()
{
	if (GetController())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AShooterCharacter::MoveForwardCallback);
		EnhancedInputComponent->BindAction(MoveSideAction, ETriggerEvent::Triggered, this, &AShooterCharacter::MoveSideCallback);
		EnhancedInputComponent->BindAction(LookPitchAction, ETriggerEvent::Triggered, this, &AShooterCharacter::LookPitchCallback);
		EnhancedInputComponent->BindAction(LookYawAction, ETriggerEvent::Triggered, this, &AShooterCharacter::LookYawCallback);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AShooterCharacter::JumpCallback);
	}
}

void AShooterCharacter::MoveForwardCallback(const FInputActionValue& Value) // moving W and S
{
	float forwardValue = Value.Get<float>();
	AddMovementInput(GetActorForwardVector() * forwardValue);
}

void AShooterCharacter::MoveSideCallback(const FInputActionValue& Value) // moving D and A
{
	float SideValue = Value.Get<float>();
	AddMovementInput(GetActorRightVector() * SideValue);
}

void AShooterCharacter::LookPitchCallback(const FInputActionValue& Value) //Looking up and down
{
	float pitchValue = Value.Get<float>();
	AddControllerPitchInput(pitchValue);
}

void AShooterCharacter::LookYawCallback(const FInputActionValue& Value) //Looking left and right
{
	float yawValue = Value.Get<float>();
	AddControllerYawInput(yawValue);
}

void AShooterCharacter::JumpCallback(const FInputActionValue& Value) // jump
{
	Jump();
}