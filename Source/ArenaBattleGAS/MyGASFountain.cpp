// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGASFountain.h"
#include "MyGameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

AMyGASFountain::AMyGASFountain()
{
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RMC"));
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	RotationTimeInterval = 3.0f;
}

class UAbilitySystemComponent* AMyGASFountain::GetAbilitySystemComponent() const
{
	return ASC;
}

void AMyGASFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	RotatingMovementComponent->bAutoActivate = false;
	RotatingMovementComponent->Deactivate();
	
	ASC->InitAbilityActorInfo(this, this);
	
	for (const auto& ab : GameAbilities)
	{
		FGameplayAbilitySpec GA(ab);
		ASC->GiveAbility(GA);
	}
}

void AMyGASFountain::RotationAction()
{
	// FGameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(UMyGameplayAbility::StaticClass());
	// if (Spec)
	// {
	// 	if (Spec->IsActive())
	// 	{
	// 		ASC->CancelAbilityHandle(Spec->Handle);
	// 	}
	// 	else
	// 	{
	// 		ASC->TryActivateAbility(Spec->Handle);
	// 	}
	// }
	
	FGameplayTagContainer ActionContainer(FOUNTAIN_ACTION_TAG);
	if (!ASC->HasMatchingGameplayTag(FOUNTAIN_STATE_TAG))
	{
		ASC->TryActivateAbilitiesByTag(ActionContainer);
	}
	else
	{
		ASC->CancelAbilities(&ActionContainer);
	}
}

void AMyGASFountain::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(
	RotationActionHandle, this, &AMyGASFountain::RotationAction, RotationTimeInterval, true, 0.0f
	);
}
