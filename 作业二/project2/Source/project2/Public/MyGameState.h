// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMyGameState();

	/*UPROPERTY(Replicated)
	float STime;*/

	UPROPERTY(ReplicatedUsing = OnRep_CountDownTime, BlueprintReadOnly, Category = "GameState")
	int32 T;



public:
	
	//virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_CountDownTime();

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void StartCountdown(int32 StartTime);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void UpdateTime();

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void PrintAllPlayerScore();

	//¶¨Ê±Æ÷¾ä±ú
	FTimerHandle CountdownTimerHandle;
};
