// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "Interactable.h"
#include "BarrierBase.h"
#include "SnakeElementBase.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	LastMovementDirection = EMovementDirection::UP;
	MoveComplete = true;
	isFirstSetup = true;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(4);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);

		FTransform NewTransform(GetActorLocation() - NewLocation);

		if(SnakeElements.Num() > 0 && !isFirstSetup)
		{
			NewLocation = SnakeElements.Last()->lastPosition;
			NewTransform = FTransform(NewLocation);
		}

		const auto NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;

		const int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if(ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
		}
	}

	isFirstSetup = false;
}

void ASnakeBase::Move()
{
	if (!MoveComplete){return;}
	MoveComplete = false;
	FVector MovementVector(FVector::ZeroVector);

	
	switch (LastMovementDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	//AddActorWorldOffset(MovementVector);

	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1;i > 0;i--)
	{
		const auto CurrentElement = SnakeElements[i];
		const auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->lastPosition = CurrentElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	MoveComplete = true;
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if(IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;

		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		ABarrierBase* Barrier = Cast<ABarrierBase>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}else if(Barrier)
		{
			Destroy();
		}

	}
}

