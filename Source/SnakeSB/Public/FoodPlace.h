// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodPlace.generated.h"

class UBoxComponent;
class AApple;
class AFood;

UCLASS()
class SNAKESB_API AFoodPlace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodPlace();

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BoxSize")
	FVector BoxSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn objects")
	TArray<TSubclassOf<AFood>> ObjectsToSpawn;

	UPROPERTY()
	AFood* FoodObj;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	void SpawnFood();

};
