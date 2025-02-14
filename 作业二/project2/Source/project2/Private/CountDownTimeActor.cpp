// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDownTimeActor.h"



// Sets default values
ACountDownTimeActor::ACountDownTimeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACountDownTimeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACountDownTimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

