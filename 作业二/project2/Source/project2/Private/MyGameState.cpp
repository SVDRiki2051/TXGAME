// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include <Net/UnrealNetwork.h>
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../project2GameMode.h"
#include <Kismet/GameplayStatics.h>
#include "MyPlayerState.h"
#include "MyHUD.h"


AMyGameState::AMyGameState()
{
	T = 0;
	bReplicates = true;
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMyGameState, STime);
	DOREPLIFETIME(AMyGameState, T);
}

void AMyGameState::StartCountdown(int32 StartTime)
{
	if (GetLocalRole() == ROLE_Authority) {
		T = StartTime;

		//UE_LOG(LogTemp, Warning, TEXT("StartCountdown Called! Time: %d"), T);

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &AMyGameState::UpdateTime, 1.0f, true);
		}
	}
}

void AMyGameState::UpdateTime()
{

	//UE_LOG(LogTemp, Warning, TEXT("UpdateCountdown Called! Time: %d"), T);

	if (T > 0)
	{
		T--;
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		// 倒计时结束后的逻辑
		UE_LOG(LogTemp, Warning, TEXT("END GAME"));
		PrintAllPlayerScore();
		
	}
}

void AMyGameState::PrintAllPlayerScore() {
	int32 Sum = 0;
	for (APlayerState* PlayerState : PlayerArray) {
		if (PlayerState) {
			AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState);
			if (MyPlayerState) {
				int32 Score = MyPlayerState->MyPlayerScore;
				Sum += Score;
				UE_LOG(LogTemp, Warning, TEXT("%s 's score: %d"),*MyPlayerState->GetPlayerName(),Score);
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Sum is: %d"), Sum);
}

//void AMyGameState::CheckTime()
//{
//
//	float CurrentTime = GetWorld()->GetTimeSeconds();
//	if (CurrentTime - STime <= 30.0f) {
//		int32 RemainTime = (int32)(31.0f - (CurrentTime - STime));
//		if (T != RemainTime) {
//			UE_LOG(LogTemp, Warning, TEXT("Time is %d"), T);
//			T = RemainTime;
//			if (GEngine)
//			{
//				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, FString::Printf(TEXT("Time: %d"), T));
//			}
//		}
//		UE_LOG(LogTemp, Warning, TEXT("Score"));
//		//UE_LOG(LogTemp, Warning, TEXT("%s 's Score is %d"), *PlayerName, score);
//	}
//	else {
//		Aproject2GameMode* project2GameMode = Cast<Aproject2GameMode>(UGameplayStatics::GetGameMode(this));
//		project2GameMode->QuitGame();
//	}
//}

void AMyGameState::OnRep_CountDownTime()
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString::Printf(TEXT("Time: %d"), T));
	}*/
}