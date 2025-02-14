// Fill out your copyright notice in the Description page of Project Settings.


#include "testcb.h"


// Sets default values
Atestcb::Atestcb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void Atestcb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Atestcb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


