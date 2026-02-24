// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/ABFountain.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "MyGASFountain.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEGAS_API AMyGASFountain : public AABFountain, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMyGASFountain();
	
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void PostInitializeComponents() override;
	
	virtual void RotationAction();
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<class URotatingMovementComponent> RotatingMovementComponent;
	
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<class UAbilitySystemComponent> ASC;
	
	UPROPERTY(EditAnywhere, Category=GAS)
	TArray<TSubclassOf<UGameplayAbility>> GameAbilities;
	
	UPROPERTY(EditAnywhere, Category=GAS)
	float RotationTimeInterval = 3.0f;
	
	FTimerHandle RotationActionHandle;
};
