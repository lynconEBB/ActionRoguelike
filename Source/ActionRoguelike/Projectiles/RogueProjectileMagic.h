#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectPtr.h"
#include "RogueProjectileMagic.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectileMagic : public AActor
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditDefaultsOnly, Category="Components")
    TObjectPtr<USphereComponent> SphereComponent;
    UPROPERTY(EditDefaultsOnly, Category="Components")
    TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
    UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
    UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
    UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DmgTypeClass;
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> ExplosionSound;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	ARogueProjectileMagic();
	virtual void PostInitializeComponents() override;
};
