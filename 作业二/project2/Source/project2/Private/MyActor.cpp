#include "MyActor.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	bReplicates = true;
}

void AMyActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AMyActor, Armor);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(HasAuthority())
	{
		Armor = FMath::Rand();
	}
}

void AMyActor::OnRep_Armor()
{
	//server
	if (HasAuthority()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Server Armor:%f"), Armor);
	}
	//Client
	else {
		UE_LOG(LogTemp, Warning, TEXT("Client Armor:%f"), Armor);
	}
}

