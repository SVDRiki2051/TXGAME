// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cube.generated.h"

UCLASS()
class PROJECT2_API ACube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACube();
	UPROPERTY(Category = StaticMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category="PARA")
	uint32 HitCount;

	UPROPERTY(EditAnywhere, Category = "PARA")
	float Y;

	UPROPERTY(Replicated)
	int32 X;

	UPROPERTY(Replicated)
	int32 SpecialCount;

	UPROPERTY(ReplicatedUsing=OnRep_Color)
    FLinearColor Color;

	FTimerHandle IfSpecialTimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	void IfSpecial();

	UFUNCTION(BlueprintCallable, Category = "Color")
	void SetColor(FLinearColor NewColor);

	UFUNCTION()
	void OnRep_Color();
	
	static int32 CountCubesInWorld(UWorld* World);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
