#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectPtr.h"
#include "RogueCharacter.generated.h"

class ARogueProjectileMagic;
struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;
class UNiagaraSystem;

UCLASS()
class ACTIONROGUELIKE_API ARogueCharacter : public ACharacter {
    GENERATED_BODY()

public:
    ARogueCharacter();

protected:
    UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
    TObjectPtr<UAnimMontage> AttackMontage;
    
    UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
    TSubclassOf<ARogueProjectileMagic> ProjectileClass;
    
    UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
    TObjectPtr<UNiagaraSystem> CastingEffect;
    
    UPROPERTY(VisibleAnywhere, Category="PrimaryAttack")
    FName MuzzleSocketName;
    
    UPROPERTY(EditDefaultsOnly, Category="Input")
    TObjectPtr<UInputAction> Input_Move;

    UPROPERTY(EditDefaultsOnly, Category="Input")
    TObjectPtr<UInputAction> Input_Look;
    
    UPROPERTY(EditDefaultsOnly, Category="Input")
    TObjectPtr<UInputAction> Input_PrimaryAttack;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UCameraComponent> CameraComponent;

    
    

    virtual void BeginPlay() override;
    
    void Move(const FInputActionValue& InValue);
    void Look(const FInputActionValue& InValue);
    void PrimaryAttack();
    
public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
