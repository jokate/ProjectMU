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
#include "Indicator/MUIndicatorManageSubsystem.h"

UEnforcementComponent::UEnforcementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UEnforcementComponent::BeginPlay()
{
	Super::BeginPlay();
	InitializePlayerController();
}

void UEnforcementComponent::EnforceUnit(int32 InEnforcementID)
{
	FMUEnforcementData EnforcementData;

	if (UMUFunctionLibrary::GetEnforcementData(GetOwner(), InEnforcementID, EnforcementData) == false)
	{
		return;
	}

	//강화 옵션에 대한 인자 추가 완료.
	EnforcementIDs.Add(InEnforcementID);
	
	// 강화 선택 옵션에 따른 부분 체크.
	switch (EnforcementData.EnforcementType)
	{
	case Attribute:
		{
			EnforcementAttribute(EnforcementData.EnforcementAttributeValue);
		}
		break;

	case SkillOpen :
		{
			// ASC에 Skill Ability 부여 + Input Binding이 필요한 경우에는 Input Binder 필요.
			OpenSkill(EnforcementData.SkillID);
		}
		break;

	case SkillEnforcement:
		{
			UE_LOG(LogTemp, Log, TEXT("Not Implemented Functional Operation"));
		}
		break;

	default :
		{
			UE_LOG(LogTemp, Log, TEXT("Not Implemented Functional Operation"));
		}
	}
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

void UEnforcementComponent::OpenSkill(FName SkillID)
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

	AddSkillSlot( SkillData.ApplySlotType, SkillID );
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

void UEnforcementComponent::InitializePlayerController()
{
	AActor* OwningActor = GetOwner();
	
	if ( IsValid( OwningActor ) == false )
	{
		return;		
	}

	APlayerController* OwnerActorController = OwningActor->GetInstigatorController<APlayerController>();

	if ( IsValid( OwnerActorController ) == false )
	{
		return;
	}

	PlayerController = OwnerActorController;
}

void UEnforcementComponent::CastSkill(FName SkillID)
{
	FMUSkillData SkillData;
	if ( UMUFunctionLibrary::GetSkillData( this, SkillID, SkillData ) == false )
	{
		return;
	}

	if ( SkillData.bUseIndicator == true )
	{
		ReadySkill( SkillID );
		return;
	}

	TriggerSkill( SkillID );
}

void UEnforcementComponent::ReadySkill(FName SkillID)
{
	if ( ReadySkillID == SkillID )
	{
		return;
	}
	
	if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->DeactivateSkillIndicator( ReadySkillID );
		
		ReadySkillID = SkillID;
		
		Subsystem->ActivateSkillIndicator( ReadySkillID );
	}
}

void UEnforcementComponent::OnInputPressed()
{
	if ( ReadySkillID != NAME_None )
	{
		if (UMUIndicatorManageSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UMUIndicatorManageSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->DeactivateSkillIndicator( ReadySkillID );
		}
		
		TriggerSkill( ReadySkillID );
	}
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


