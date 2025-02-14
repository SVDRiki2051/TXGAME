// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"
#include "../project2Projectile.h"
#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include <Net/UnrealNetwork.h>
#include <project2/project2GameMode.h>
#include <MyPlayerState.h>

// Sets default values
ACube::ACube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ACube::OnHit);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);
	RootComponent = StaticMeshComponent;
	bReplicates = true;

	UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
	if (Material)
	{
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
		if (DynamicMaterial)
		{
			DynamicMaterial->GetVectorParameterValue(FName("Color"), Color);
		}
	}
}

// Called when the game starts or when spawned
void ACube::BeginPlay()
{
	Super::BeginPlay();
	HitCount = 0;
	Y = 0.5f;
	X = 10;
	if (HasAuthority())
	{
		UWorld* World = GetWorld();
		if (World == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid World!"));
			return;
		}
		SpecialCount = CountCubesInWorld(World);
		if (SpecialCount < 5)
		{
			IfSpecial();
		}
	}
	
}



void ACube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACube, X);
	DOREPLIFETIME(ACube, SpecialCount);
	DOREPLIFETIME(ACube, Color);
}

// Called every frame
void ACube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(Aproject2Projectile::StaticClass())) {
			//UE_LOG(LogTemp, Warning, TEXT("Hit!!!"));
			StaticMeshComponent->SetWorldScale3D(FVector(StaticMeshComponent->GetComponentScale() * Y));
			HitCount++;


			AActor* OwnerActor = OtherActor->GetOwner();

			AController* Controller = OwnerActor->GetInstigatorController();
			if (Controller) {

				APlayerState* PlayerState = Controller->PlayerState;
				if (PlayerState) {

					// 更新玩家得分
					FString PlayerName = PlayerState->GetPlayerName();
					AMyPlayerState* MyPlayerState;
					MyPlayerState = Cast<AMyPlayerState>(PlayerState);
					MyPlayerState->AddPlayerScore(X);

					int32 score = MyPlayerState->MyPlayerScore;
					UE_LOG(LogTemp, Warning, TEXT("%s 's Score is %d"), *PlayerName, score);
				}
			}

			OtherActor->Destroy();

		}
	}
	if (HitCount > 1) {
		Destroy();
	}
}

void ACube::IfSpecial()
{
	int32 Min = 0;
	int32 Max = 9;
	int32 s = FMath::RandRange(Min,Max);
	if (s > 4) {
		X = X * 2;

		SetColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

void ACube::SetColor(FLinearColor NewColor)
{

	Color = NewColor;
	// 获取材质实例
	UMaterialInterface* Material = StaticMeshComponent->GetMaterial(0);
	if (Material == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Material found!"));
		return;
	}

	// 创建动态材质实例
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	if (DynamicMaterial == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create dynamic material instance!"));
		return;
	}

	StaticMeshComponent->SetMaterial(0, DynamicMaterial);

	// 设置材质实例的颜色参数
	DynamicMaterial->SetVectorParameterValue(FName("Color"), Color);
}



void ACube::OnRep_Color()
{
	SetColor(Color);
}

int32 ACube::CountCubesInWorld(UWorld* World)
{
	int32 SpecialCubeCount = 0;

	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid World!"));
		return SpecialCubeCount;
	}

	// 统计所有的特殊方块数量
	for (TActorIterator<ACube> It(World); It; ++It)
	{
		if (It->X == 20) {
			SpecialCubeCount++;
		}
	}

	return SpecialCubeCount;
}

