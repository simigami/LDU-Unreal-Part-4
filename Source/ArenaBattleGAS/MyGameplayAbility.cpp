// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayAbility.h"

#include "MyGameplayTagContainer.h"
#include "GameFramework/RotatingMovementComponent.h"

UMyGameplayAbility::UMyGameplayAbility()
{
	AbilityTags.AddTag(FOUNTAIN_ACTION_TAG);
	ActivationOwnedTags.AddTag(FOUNTAIN_STATE_TAG);
}

void UMyGameplayAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	
	AActor* Actor = ActorInfo->AvatarActor.Get();
	URotatingMovementComponent* Spec = Actor->GetComponentByClass<URotatingMovementComponent>();
	if (Spec)
	{
		Spec->Deactivate();
	}
}

void UMyGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	AActor* Actor = ActorInfo->AvatarActor.Get();
	URotatingMovementComponent* Spec = Actor->GetComponentByClass<URotatingMovementComponent>();
	if (Spec)
	{
		Spec->SetActive(true);
	}
}