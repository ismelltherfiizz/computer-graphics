// Fill out your copyright notice in the Description page of Project Settings.


#include "Balloon.h"
#include <Camera/CameraComponent.h>
#include <Components/InputComponent.h>
#include "GameFramework/Controller.h"
#include <GameFramework/DefaultPawn.h>
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ABalloon::ABalloon()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	CameraSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraSpring->SetupAttachment(RootComponent);
	CameraSpring->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraSpring->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Ñamera"));
	Camera->SetupAttachment(CameraSpring, USpringArmComponent::SocketName); 
	Camera->bUsePawnControlRotation = false; 
	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABalloon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABalloon::Move_XAxis(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void ABalloon::Move_YAxis(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		// get forward vector
		Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		GetMovementComponent()->Activate(true);
		
		AddMovementInput(Direction, AxisValue);
	}
}


void ABalloon::Tick(float DeltaTime)
{
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = (GetActorLocation() + (CurrentVelocity * DeltaTime));
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ABalloon::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveX", this, &ABalloon::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &ABalloon::Move_YAxis);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}
 
