#pragma once

#include "CoreMinimal.h"
#include "Core/RogueInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor, public IRogueInteractionInterface
{
	GENERATED_BODY()

public:
	ARogueItemChest();
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float AnimationTargetPitch = 120.f;
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float AnimationSpeed = 50.f;

	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;	
	
	UFUNCTION(BlueprintImplementableEvent)
	void AnimationDone();	
	
private:	
	float CurrentLidPitch = 0.0f;
};
