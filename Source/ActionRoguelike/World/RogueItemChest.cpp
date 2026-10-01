#include "RogueItemChest.h"


ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComponent;
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ARogueItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}