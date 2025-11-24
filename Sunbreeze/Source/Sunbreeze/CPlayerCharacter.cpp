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
	FCollisionQueryParams params;
	bool hit;

	FVector startPoint = GetActorLocation();
	FVector endPoint;
	float sightLength = 100.0f;


	endPoint = startPoint + GetActorForwardVector() * sightLength;

	params.AddIgnoredActor(this);


	// DEBUG START
	DrawDebugBox(GetWorld(), startPoint, BoxExtend, FColor::Red, false);
	DrawDebugBox(GetWorld(), endPoint, BoxExtend, FColor::Green, false);
	DrawDebugLine(GetWorld(), startPoint, endPoint, FColor::Blue, false);
	// END DEBUG


	hit = GetWorld()->SweepSingleByChannel(
		hitResult,
		startPoint,
		endPoint,
		GetActorRotation().Quaternion(),
		ECC_Visibility,
		FCollisionShape::MakeBox(BoxExtend),
		params
	);

	if (hit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *hitResult.GetActor()->GetName());
		return hitResult.GetActor();
	}

	return nullptr;
}

void ACPlayerCharacter::MoveCharacter(const FVector2D& Input)
{
	const double X = Input.X;
	const double Y = Input.Y;

	if (X == 0 && Y == 0) { return; }

	float TargetYaw = 0.f;

	if (X == 1) {
		TargetYaw = 0.f;
	}
	else if (X == -1) {
		TargetYaw = 180.f;
	}

	if (Y == 1) {
		TargetYaw = 90.f;
	}
	else if (Y == -1) {
		TargetYaw = 270.f;
	}

	SetActorRotation(FRotator(0, TargetYaw, 0));
	AddMovementInput(GetActorForwardVector(), 1.f);
}
