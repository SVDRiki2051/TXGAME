// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Replicated)
	int32 MyPlayerScore;
	
	

public:
	AMyPlayerState();
	virtual void BeginPlay() override;

	

	UFUNCTION()
	void AddPlayerScore(int32 PlayerScore);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
