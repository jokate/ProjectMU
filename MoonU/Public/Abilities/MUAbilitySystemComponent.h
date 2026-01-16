// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MUAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MOONU_API UMUAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMUAbilitySystemComponent();

public:
	
	virtual void AllocateSkill( FName SkillID, const FGameplayAbilitySpec& AbilitySpec );

	virtual void DeallocateSkill( FName SkillID );

	virtual FGameplayAbilitySpec* FindAbilitySpecBySkillID( FName SkillID );

	virtual void TryTriggerSkill( FName SkillID );

	virtual void TryCancelSkill( FName SkillID );
	void GiveAbility(const FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& InputTag);
	FGameplayAbilitySpec* GetAbilityByInputTag(const FGameplayTag& InputGameplayTag);

	// 아무래도 몽타주 어빌리티로 동작하는게 영 껄끄럽단 말이지..
	void AddActiveAbility(UGameplayAbility* GA)
	{
		ActiveAbilities.AddUnique(GA);
	}

	void RemoveActiveAbility( UGameplayAbility* TargetToRemove )
	{
		ActiveAbilities.Remove(TargetToRemove);
	}

	const TArray<TWeakObjectPtr<UGameplayAbility>>& GetCurrentActiveAbilities() const
	{
		return ActiveAbilities;
	}
	
protected :
	
	
	virtual void AddAbilitySpecWithTag(const FGameplayTag& InputGameplayTag, FGameplayAbilitySpecHandle& AbilitySpec);
	virtual void RemoveAbilitySpecWithTag(const FGameplayTag& InputGameplayTag)
	{
		InputAbilitySpecHandle.Remove(InputGameplayTag);
	}
	
public :
	UPROPERTY()
	TMap<FName, FGameplayAbilitySpecHandle> SkillAbilitySpec;

	// Local Client Only.
	UPROPERTY()
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> InputAbilitySpecHandle;

	UPROPERTY()
	TArray<TWeakObjectPtr<UGameplayAbility>> ActiveAbilities;
};