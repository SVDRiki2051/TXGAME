// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActortest.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyActortest::AMyActortest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AMyActortest::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) 
	{
		Health = 500.0f;
	}

}

void AMyActortest::GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyActortest, Health);
}

// Called every frame
void AMyActortest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Server Health:%f"), Health);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Client Health:%f"), Health);
	}

}

