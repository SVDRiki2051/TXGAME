// Copyright Epic Games, Inc. All Rights Reserved.

#include "project2GameMode.h"
#include "project2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "public/MyPlayerState.h"
#include <Kismet/GameplayStatics.h>
#include "public/MyGameStateBase.h"
#include "public/MyGameState.h"

Aproject2GameMode::Aproject2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerStateClass = AMyPlayerState::StaticClass();

	GameStateClass = AMyGameStateBase::StaticClass();
}

void Aproject2GameMode::BeginPlay()
{
	Super::BeginPlay();

	AMyGameState* MyGameState = GetGameState<AMyGameState>();
	if (MyGameState)
	{
		MyGameState->StartCountdown(20); 
	}
}

void Aproject2GameMode::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	AMyGameState* MyGameState = GetGameState<AMyGameState>();

	if (PlayerController || MyGameState->T < 0)
	{
		UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
	}
}



