#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RoguePlayerController.generated.h"

class UInputAction;
class URogueInteractionComponent;

UCLASS()
class ACTIONROGUELIKE_API ARoguePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARoguePlayerController();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URogueInteractionComponent> InteractionComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Interact;

	void OnInteraction();
	virtual void SetupInputComponent() override;
};
