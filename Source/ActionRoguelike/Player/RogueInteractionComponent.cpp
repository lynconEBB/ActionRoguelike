#include "RogueInteractionComponent.h"

#include "Engine/OverlapResult.h"


URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();

	TArray<FOverlapResult> Overlaps;
	ECollisionChannel CollisionChannel = ECC_Visibility;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	
	FVector LookDirection = PC->GetControlRotation().Vector();
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.0;
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
		
		float DotResult = FVector::DotProduct(OverlapDirection, LookDirection);
		FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
		DrawDebugString(GetWorld(),OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);
		
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
	}
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(50.0f), FColor::Green);
	}
}