#include "RogueCharacter.h"
#include "Camera/CameraComponent.h"
#include "Projectiles/RogueProjectileMagic.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputTriggers.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

ARogueCharacter::ARogueCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComponent->SetupAttachment(SpringArmComponent);
	
	MuzzleSocketName = "Muzzle_01";
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARogueCharacter::Move);
    EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARogueCharacter::Look);
    EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ARogueCharacter::PrimaryAttack);
    EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARogueCharacter::Jump);
}

void ARogueCharacter::Move(const FInputActionValue& InValue)
{
    FVector2D InputValue = InValue.Get<FVector2D>();

    FRotator ControlRot = GetControlRotation();
    ControlRot.Pitch = 0.0f;
    FVector ForwardDirection = ControlRot.Vector();
    FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);

    AddMovementInput(ForwardDirection, InputValue.X);
    AddMovementInput(RightDirection, InputValue.Y);
}

void ARogueCharacter::Look(const FInputActionValue& InValue) 
{
    FVector2D InputValue = InValue.Get<FVector2D>();

    AddControllerPitchInput(InputValue.Y);
    AddControllerYawInput(InputValue.X);
}

void ARogueCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackMontage);

	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, 
		GetMesh(), 
		MuzzleSocketName, 
		FVector::ZeroVector,
		FRotator::ZeroRotator, 
		EAttachLocation::Type::SnapToTarget, 
		true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle,[this]()
	{
		FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
		FRotator SpawnRotation = GetControlRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		MoveIgnoreActorAdd(Projectile);
	},  AttackDelayTime, false);
}
