// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnforcementComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "Character/MUCharacterPlayer.h"
#include "Data/DataTable/MUData.h"
#include "Library/MUFunctionLibrary.h"
#include "Singleton/MUWidgetDelegateSubsystem.h"
#include "Abilities/MUAbilitySystemComponent.h"
#include "Components/Input/MUEnhancedInputComponent.h"
#include "Singleton/MUEnforcementSubsystem.h"

UEnforcementComponent::UEnforcementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UEnforcementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEnforcementComponent::EnforceAttribute(int32 InEnforcementID)
{
	FMUEnforcementData EnforcementData;

	if (UMUFunctionLibrary::GetEnforcementData(GetOwner(), InEnforcementID, EnforcementData) == false)
	{
		return;
	}

	//강화 옵션에 대한 인자 추가 완료.
	EnforcementIDs.Add(InEnforcementID);
	EnforcementAttribute(EnforcementData.EnforcementAttributeValue);
}

void UEnforcementComponent::EnforceSkill(ESkillSlotType SkillSlot, int32 InEnforcementID)
{
	FMUEnforcementData EnforcementData;

	if (UMUFunctionLibrary::GetEnforcementData(GetOwner(), InEnforcementID, EnforcementData) == false)
	{
		return;
	}
	
	// ASC에 Skill Ability 부여 + Input Binding이 필요한 경우에는 Input Binder 필요.
	OpenSkill(SkillSlot, EnforcementData.SkillID);
}

void UEnforcementComponent::EnforcementAttribute(FMUAttributeValue& AttributeValue)
{
	IAbilitySystemInterface* ASI = GetOwner<IAbilitySystemInterface>();

	if (ASI == nullptr)
	{
		return;
	}

	UAbilitySystemComponent* ASC = ASI->GetAbilitySystemComponent();

	if (IsValid(ASC) == false)
	{
		return;
	}

	//관계없는 Attribute가 들어왔을 경우에는 저촉의 위험성이 있음.
	if (ASC->HasAttributeSetForAttribute(AttributeValue.InitAttribute) == false )
	{
		return;
	}
	
	float CalculatedAttributeValue = ASC->GetNumericAttribute(AttributeValue.InitAttribute) + AttributeValue.InitializedValue;
	ASC->SetNumericAttributeBase(AttributeValue.InitAttribute, CalculatedAttributeValue);
}

void UEnforcementComponent::OpenSkill( ESkillSlotType SkillSlot, FName SkillID )
{
	FMUSkillData SkillData;
	if ( UMUFunctionLibrary::GetSkillData(GetOwner(), SkillID, SkillData) == false )
	{
		return;
	}

	// Input Binding이 필요한 경우에는 별도 세팅이 필요한 것은 사실임.
	FGameplayAbilitySpec AbilitySpec(SkillData.NeedToRegAbility);

	UMUAbilitySystemComponent* MUASC = UMUFunctionLibrary::GetAbilitySystemComponent( GetOwner() );

	if ( IsValid(MUASC) == true )
	{
		MUASC->AllocateSkill( SkillID, AbilitySpec );
	}

	SetupSkillInput( SkillID );

	AddSkillSlot( SkillSlot, SkillID );
}

void UEnforcementComponent::SetupSkillInput(FName SkillID)
{
	FMUSkillData SkillData;
	if ( UMUFunctionLibrary::GetSkillData(GetOwner(), SkillID, SkillData) == false )
	{
		return;
	}

	APawn* OwnerActor = GetOwner<APawn>();

	if ( IsValid(OwnerActor) == false )
	{
		return;
	}
	UMUEnhancedInputComponent* EnhancedInputComponent = Cast<UMUEnhancedInputComponent>(OwnerActor->InputComponent);

	if ( IsValid( EnhancedInputComponent ) == false )
	{
		return;
	}

	UInputConfig* InputConfig = UMUFunctionLibrary::GetInputConfigByOwner( GetOwner() );

	if ( IsValid(InputConfig) == false )
	{
		return;
	}
	
	const FMUSkillInput& SkillInput = SkillData.SkillInput;
	
	if ( SkillInput.ReleaseEvent != ETriggerEvent::None )
	{
		EnhancedInputComponent->BindActionByTag( InputConfig, SkillInput.InputTag, SkillInput.TriggerEvent, this, &UEnforcementComponent::CancelSkill );
	}

	if ( SkillInput.TriggerEvent != ETriggerEvent::None )
	{
		EnhancedInputComponent->BindActionByTag( InputConfig, SkillInput.InputTag, SkillInput.TriggerEvent, this, &UEnforcementComponent::TriggerInputSkill, SkillData.ApplySlotType );
	}
}


void UEnforcementComponent::CallSkillUpdatedEvent()
{
	UWorld* World = GetWorld();

	if ( IsValid(World) == false )
	{
		return;		
	}

	UGameInstance* GameInstance = World->GetGameInstance();

	if ( IsValid(GameInstance) == false	)
	{
		return;
	}

	UMUWidgetDelegateSubsystem* WidgetDelegateSubsystem = GameInstance->GetSubsystem<UMUWidgetDelegateSubsystem>();

	if ( IsValid( WidgetDelegateSubsystem ) == false )
	{
		return;	
	}

	if ( WidgetDelegateSubsystem->OnSkillUpdated.IsBound() == true )
	{
		WidgetDelegateSubsystem->OnSkillUpdated.Broadcast();
	} 
}

void UEnforcementComponent::TriggerInputSkill(ESkillSlotType SkillSlot)
{
	FName SkillID = GetSkillIDBySlot( SkillSlot );

	if ( SkillID == NAME_None )
	{
		return;
	}

	CastSkill( SkillID );
}

void UEnforcementComponent::CastSkill(FName SkillID)
{
	FMUSkillData SkillData;
	if ( UMUFunctionLibrary::GetSkillData( this, SkillID, SkillData ) == false )
	{
		return;
	}

	TriggerSkill( SkillID );
}

void UEnforcementComponent::TriggerSkill(FName SkillID)
{
	// 실질적인 GAS 트리거.
	UMUAbilitySystemComponent* MUASC = UMUFunctionLibrary::GetAbilitySystemComponent( GetOwner() );

	if ( IsValid(MUASC) == true )
	{
		MUASC->TryTriggerSkill( SkillID );
	}
}

void UEnforcementComponent::CancelSkill()
{
	UMUAbilitySystemComponent* MUASC = UMUFunctionLibrary::GetAbilitySystemComponent( GetOwner() );

	if ( IsValid(MUASC) == true )
	{
		
	}
}

void UEnforcementComponent::AddSkillSlot(ESkillSlotType SkillSlotType, FName SkillID)
{
	AllocatedSkillID.Add(SkillSlotType, SkillID);
	CallSkillUpdatedEvent();
}

void UEnforcementComponent::RemoveSkillSlot(ESkillSlotType SkillSlotType)
{
	AllocatedSkillID.Remove(SkillSlotType);
	CallSkillUpdatedEvent();
}

const FName UEnforcementComponent::GetSkillIDBySlot(ESkillSlotType SkillSlot)
{
	if ( AllocatedSkillID.Contains(SkillSlot) == false )
	{
		return NAME_None;
	}

	return AllocatedSkillID[SkillSlot];
}


