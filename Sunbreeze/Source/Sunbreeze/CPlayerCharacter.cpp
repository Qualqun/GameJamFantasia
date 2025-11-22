// Fill out your copyright notice in the Description page of Project Settings.

#include "CPlayerCharacter.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "IPushable.h"
// Sets default values
ACPlayerCharacter::ACPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPlayerCharacter::Push()
{
	UE_LOG(LogTemp, Warning, TEXT("Push"));
}

void ACPlayerCharacter::Carry()
{
	UE_LOG(LogTemp, Warning, TEXT("Push"));
}

FVector2D ACPlayerCharacter::GetCharacterPosition(const float& _gridSize) const
{
	FVector3d location = GetActorLocation();
	return FVector2D(FMath::GridSnap(location.X, _gridSize), FMath::GridSnap(location.Y, _gridSize));
}

AActor* ACPlayerCharacter::CheckSight()
{
	float sightLength = 100.0f;

	FVector startPoint = GetActorLocation();
	FVector endPoint = startPoint + GetActorForwardVector() * sightLength;

	DrawDebugLine(GetWorld(), startPoint, endPoint, FColor::Magenta, false, 0.0f);

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool hit = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startPoint,
		endPoint,
		ECC_Visibility,
		params
	);

	if (hit)
	{
		return hitResult.GetActor();

		if (showDebug)
		{
			DrawDebugPoint(GetWorld(), hitResult.ImpactPoint, 10.0f, FColor::Green, false, 2.0f);
		}
	}
	return nullptr;
}

void ACPlayerCharacter::MoveCharacter(const FVector2D& Input)
{
	const double X = Input.X;  
	const double Y = Input.Y; 

	if (X == 0 && Y == 0) { return; }
		

	float TargetYaw = GetActorRotation().Yaw;
	if (X == 1) {
		TargetYaw = 180.0f;
	}      
	else if (X == -1) { 
		TargetYaw = 0.f; 
	}

	if (Y == 1) {
		TargetYaw = 90.f;
	}
	else if (Y == -1) {
		TargetYaw = 270.f;
	}

	SetActorRotation(FRotator(0.f, TargetYaw, 0.f));
	AddMovementInput(GetActorForwardVector(), 1.f);
}
