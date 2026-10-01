#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RoguePlayerController.generated.h"

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
};
