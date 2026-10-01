#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"

class URadialForceComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class UStaticMeshComponent;
class USoundBase;
class UAudioComponent;

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	ARogueExplosiveBarrel();
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> AudioComponent;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	TObjectPtr<USoundBase> BurningSound;
	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> BurningEffect;
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	void Explode();
private:
	FTimerHandle TimerHandle;
	bool bAlreadyExploded;
};
