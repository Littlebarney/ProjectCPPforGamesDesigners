// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPforGamesDesigners/Public/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PackageCounterWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


//Called when the game starts
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay(); //Calls the Parent Class's Begin Play() function

	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Removes existing widget if a widget already exists
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, PackageCounterWidgetClass, false);

	for (UUserWidget* Widget : FoundWidgets)
	{
		if (Widget && Widget->IsInViewport())
		{
			Widget->RemoveFromParent();
		}
	}

	if (PackageCounterWidgetClass)
	{
		PackageCounterWidget = CreateWidget<UPackageCounterWidget>(GetWorld(),PackageCounterWidgetClass);
		if(PackageCounterWidget)
		{
			PackageCounterWidget->AddToViewport();
			PackageCounterWidget->UpdatePackageCount(PackagesInVan);
		}
	}
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	Score = 0;
	// Set this pawn to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the...
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character will point towards the way it's moving
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Other character movement settings
	GetCharacterMovement()->JumpZVelocity = 0;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 0;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // Camera follow distance
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm

	//Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	{
		// Set up Action Bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		{
			// Bind the move action to the input system
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

			// Bind the look action to the input system
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	//input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//add yaw and pitch input to controller

		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>(); 
 
	if (Controller != nullptr)
	{
		//find out which way is forward 
		const FRotator Rotation = Controller->GetControlRotation(); 
		const FRotator YawRotation(0, Rotation.Yaw, 0); 
 
		//get forward Vector 
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); 
 
		//get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); 
 
		//add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y); 
		AddMovementInput(RightDirection, MovementVector.X);

		//Vans Rotation
		FVector Direction = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);
		if (!Direction.IsNearlyZero())
		{
			FRotator NewRotation = Direction.Rotation();
			NewRotation.Pitch = 0.f;
			NewRotation.Roll = 0.f;

			//SetActorRotation(NewRotation);
		}

	}
	
}

void APlayerCharacter::PickupPackage()
{
	PackagesInVan++;
	UE_LOG(LogTemp, Log, TEXT("Packages in Van: %d"), PackagesInVan)

	if(PackageCounterWidget)
	{
		PackageCounterWidget->UpdatePackageCount(PackagesInVan);
	}
}

void APlayerCharacter::AddPoints(int32 Amount)
{
	Score += Amount;

	UE_LOG(LogTemp, Log, TEXT("Player score: %d"), Score);
}





