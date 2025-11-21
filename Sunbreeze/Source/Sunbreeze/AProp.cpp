// Fill out your copyright notice in the Description page of Project Settings.


#include "AProp.h"

// Sets default values
AAProp::AAProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAProp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

