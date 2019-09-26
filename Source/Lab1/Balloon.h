// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "Balloon.generated.h"

UCLASS()
class LAB1_API ABalloon : public ADefaultPawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	FVector Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraSpring;

public:
	// Sets default values for this pawn's properties
	ABalloon();

protected:
	virtual void BeginPlay() override;


	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	USceneComponent* VisibleComponent;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

};
