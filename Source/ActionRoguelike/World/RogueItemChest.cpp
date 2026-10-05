#include "RogueItemChest.h"


ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	BaseMeshComponent->SetCollisionProfileName("Interaction");
	RootComponent = BaseMeshComponent;
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComponent->SetCollisionProfileName("NoCollision");
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentLidPitch = FMath::FInterpConstantTo(CurrentLidPitch, AnimationTargetPitch, DeltaTime, AnimationSpeed);
	LidMeshComponent->SetRelativeRotation(FRotator(CurrentLidPitch, 0.0f, 0.0f));
	
	if (FMath::IsNearlyEqual(CurrentLidPitch, AnimationTargetPitch))
	{
		AnimationDone();
		SetActorTickEnabled(false);
	}
}

void ARogueItemChest::Interact_Implementation()
{
	SetActorTickEnabled(true);
}