// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(-90,0,0));
	CreateSnakeBase();
	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(IAMove, ETriggerEvent::Triggered, this, &APlayerPawnBase::Move);

}



void APlayerPawnBase::CreateSnakeBase()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::Move(const FInputActionValue& Value)
{
	FVector2D Axis2DValue = Value.Get<FVector2D>();

	if(IsValid(SnakeActor))
	{

		
		if (Axis2DValue.X > 0 && SnakeActor->LastMovementDirection != EMovementDirection::RIGHT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::LEFT;
		}else if (Axis2DValue.X < 0 && SnakeActor->LastMovementDirection != EMovementDirection::LEFT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::RIGHT;
		}

		if (Axis2DValue.Y > 0 && SnakeActor->LastMovementDirection != EMovementDirection::DOWN)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::UP;
		}
		else if (Axis2DValue.Y < 0 && SnakeActor->LastMovementDirection != EMovementDirection::UP)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::DOWN;
		}


	}

}

