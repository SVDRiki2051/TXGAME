// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "project2GameMode.generated.h"

UCLASS(minimalapi)
class Aproject2GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	

	Aproject2GameMode();

	virtual void BeginPlay() override;

	void QuitGame();


};



