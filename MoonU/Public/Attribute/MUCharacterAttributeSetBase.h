// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MUCharacterAttributeSetBase.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutOfHealthDelegate);

UCLASS()
class MOONU_API UMUCharacterAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public :
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, Damage);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, CurrentHp);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, MaxHp);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, AttackRange);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, DefendRange);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, AttackDamage);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, DefendRate);
	ATTRIBUTE_ACCESSORS(UMUCharacterAttributeSetBase, DropExperience);
	
public :
	UMUCharacterAttributeSetBase();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

#pragma region Hp Related Func
	virtual void HandleHPAttributeChange( const FGameplayAttribute& Attribute, float OldValue, float NewValue );

	virtual void HandleHPGameplayEffectCallback( const FGameplayEffectModCallbackData& Data );

	virtual void CheckDeath(const FGameplayEffectModCallbackData& Data );
	
#pragma endregion 

#pragma region Damage Related Func

	virtual bool HandlePreDamage( const FGameplayEffectModCallbackData& Data );
	
#pragma endregion
	
	//const에서 열외를 시키도록 만든다.
	mutable FOutOfHealthDelegate OnOutOfHealth;
	
protected :
	UPROPERTY(BlueprintReadOnly, Category = "Damage", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;
	
	UPROPERTY(BlueprintReadOnly, Category = "HP", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CurrentHp;

	UPROPERTY(BlueprintReadOnly, Category = "HP", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHp;

	UPROPERTY(BlueprintReadOnly, Category = "AttackDamage", meta= (AllowPrivateAccess = true))
	FGameplayAttributeData AttackDamage;

	UPROPERTY(BlueprintReadOnly, Category = "DefendRate", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DefendRate;
	
	UPROPERTY(BlueprintReadOnly, Category = "AttackRange", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "DefendRange", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DefendRange;

	UPROPERTY(BlueprintReadOnly, Category = "DropExperience", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DropExperience;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FGameplayTagContainer IgnoranceDamageTags;

	UPROPERTY( EditDefaultsOnly )
	FGameplayTagContainer DefenseTags;
	
	bool bOutOfHealth = false;
};
