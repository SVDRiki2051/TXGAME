// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include <Net/UnrealNetwork.h>
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../project2GameMode.h"
#include <Kismet/GameplayStatics.h>

AMyPlayerState::AMyPlayerState() 
{
	MyPlayerScore = 0;

	bReplicates = true;

}

void AMyPlayerState::BeginPlay() 
{
	Super::BeginPlay();

}



void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, MyPlayerScore);
	
}





void AMyPlayerState::AddPlayerScore(int32 PlayerScore)
{
	MyPlayerScore += PlayerScore;
}


