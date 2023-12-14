// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Food.generated.h"

	/**
	 *
	 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFoodEatenDelegate);

UCLASS()
class SNAKESB_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AFood();

	UPROPERTY(BlueprintReadWrite)
	bool ChangeSpeed;
	UPROPERTY(BlueprintReadWrite, Category="Variables")
	float ChangeSpeedValue;

	/**
	 * 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnFoodEatenDelegate OnEaten;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
