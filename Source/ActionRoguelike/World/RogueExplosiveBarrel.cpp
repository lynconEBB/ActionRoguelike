#include "RogueExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueExplosiveBarrel::ARogueExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = true;
	bAlreadyExploded = false;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");
	RootComponent = StaticMeshComponent;
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	RadialForceComponent->ImpulseStrength = 150000.f;
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
}

float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	float Result =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (bAlreadyExploded || GetWorldTimerManager().TimerExists(TimerHandle))
		return Result;

	
	NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(BurningEffect, RootComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	AudioComponent = UGameplayStatics::SpawnSoundAttached(BurningSound, RootComponent);
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::Explode, 3.f);
	return Result;
}

void ARogueExplosiveBarrel::Explode()
{
	bAlreadyExploded = true;
	
	AudioComponent->Deactivate();
	NiagaraComponent->Deactivate();
	
	RadialForceComponent->FireImpulse();
	
	NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionEffect, RootComponent, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	AudioComponent = UGameplayStatics::SpawnSoundAttached(ExplosionSound, RootComponent);
}