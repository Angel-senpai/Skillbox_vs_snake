// Fill out your copyright notice in the Description page of Project Settings.

#include "SnakeSB/Public/FoodPlace.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SnakeSB/Food.h"

// Sets default values
AFoodPlace::AFoodPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AFoodPlace::BeginPlay()
{
	Super::BeginPlay();
	SpawnFood();
}

// Called every frame
void AFoodPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodPlace::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CollisionMesh->SetBoxExtent(BoxSize);
}

void AFoodPlace::SpawnFood()
{
	if (ObjectsToSpawn.Num() < 0){return;}
	int32 random = FMath::RandRange(0, ObjectsToSpawn.Num() - 1);
	auto ActorToSpawn = ObjectsToSpawn[random];

	auto PlayerPawn = UGameplayStatics::GetPlayerPawn(nullptr, 0);

	const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(this->GetActorLocation(), CollisionMesh->GetScaledBoxExtent());;
	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, Location.ToString());

	
	const FTransform NewTransform(Location);
	FoodObj = GetWorld()->SpawnActor<AFood>(ActorToSpawn, NewTransform);

	if (IsValid(FoodObj))
	{
		FoodObj->OnEaten.AddDynamic(this, &AFoodPlace::SpawnFood);
	}
}


