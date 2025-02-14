// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "MyGameState.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"

void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawCountdown();
}

void AMyHUD::DrawCountdown()
{
    AMyGameState* MyGameState = GetWorld()->GetGameState<AMyGameState>();
    if (MyGameState)
    {
        FString CountdownText = FString::Printf(TEXT("Time : %d"), MyGameState->T);
        DrawText(CountdownText, FColor::Red, 50, 50, nullptr, 2.0f);
    }
}