// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MUCharacterBase.h"

#include "MotionWarpingComponent.h"
#include "Components/AbilityInitComponent.h"
#include "Components/MULevelUpComponent.h"
#include "Components/TimeWindComponent.h"
#include "Data/DataTable/MUData.h"
#include "Library/MUFunctionLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


// Sets default values
AMUCharacterBase::AMUCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimeWindComponent = CreateDefaultSubobject<UTimeWindComponent>(TEXT("TimeWinder"));
	AbilityInitComponent = CreateDefaultSubobject<UAbilityInitComponent>(TEXT("AbilityInitComponent"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpComponent"));
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliComponent"));
	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	LevelUpComponent = CreateDefaultSubobject<UMULevelUpComponent>(TEXT("LevelUpComponent"));
}

// Called when the game starts or when spawned
void AMUCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if ( IsValid(TimeWindComponent) == true)
	{
		TimeWindComponent->OnIntialize();	
	}
	
	LevelUpComponent->OnCharacterInitialized();
}

void AMUCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AbilityInitComponent->OnEndPlay(CharacterID);
	
	Super::EndPlay(EndPlayReason);
}

void AMUCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMUCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if ( IsValid(ASC) == true )
	{
		ASC->InitAbilityActorInfo(this, this);;
	}

	if ( IsValid(AbilityInitComponent) == true )
	{
		AbilityInitComponent->InitAbilities(CharacterID);	
	}

	FMUCharacterInfo CharacterInfo;
	
	if ( UMUFunctionLibrary::GetCharacterInfoData(this, CharacterID, CharacterInfo) == true)
	{
		for (auto NeedToReg : CharacterInfo.NeedToRegisterAttributeSet)
		{
			//Attribute에 대한 세팅 성공.
			UAttributeSet* AttributeSet = NewObject<UAttributeSet>(this, NeedToReg);
			ASC->AddSpawnedAttribute(AttributeSet);
		}
	}

	if ( IsValid(LevelUpComponent) == true)
	{
		LevelUpComponent->OnSetLevelEventCallback.AddUniqueDynamic(this, &AMUCharacterBase::OnLevelSetCallbackFunction);
	}
}

UMUComboActionData* AMUCharacterBase::GetComboActionData() const
{
	return ComboActionData;
}

bool AMUCharacterBase::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

bool AMUCharacterBase::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return ASC->HasAllMatchingGameplayTags(TagContainer);
}

bool AMUCharacterBase::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return ASC->HasAnyMatchingGameplayTags(TagContainer);
}

void AMUCharacterBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	ASC->GetOwnedGameplayTags(TagContainer);
}

UAbilitySystemComponent* AMUCharacterBase::GetAbilitySystemComponent() const
{
	return ASC;
}

FOnTimewindEnd& AMUCharacterBase::GetTimeWindEndEvent()
{
	return TimeWindComponent->GetTimeWindEndEvent();
}

const FVector AMUCharacterBase::GetDefendRange()
{
	return DefendExtent;
}

const FTransform AMUCharacterBase::GetDefendTransform()
{
	return GetDefendTransform_BP();
}

void AMUCharacterBase::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	if (IGenericTeamAgentInterface* GenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(GetController()))
	{
		GenericTeamAgentInterface->SetGenericTeamId(TeamID);
	}
}

ETeamAttitude::Type AMUCharacterBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const IGenericTeamAgentInterface* GenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(GetController()))
	{
		return GenericTeamAgentInterface->GetTeamAttitudeTowards(Other);
	}

	return ETeamAttitude::Neutral;
}

FGenericTeamId AMUCharacterBase::GetGenericTeamId() const
{
	if (const IGenericTeamAgentInterface* GenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(GetController()))
	{
		return GenericTeamAgentInterface->GetGenericTeamId();
	}

	return FGenericTeamId::NoTeam;
}

void AMUCharacterBase::LevelUp()
{
	if ( IsValid(LevelUpComponent) == true)
	{
		LevelUpComponent->LevelUp();
	}
}

void AMUCharacterBase::OnLevelSetCallbackFunction(int32 InLevel)
{
	if ( IsValid(ASC) == false)
	{
		return;
	}
	
	FMUCharacterInfo CharacterInfo;
	if ( UMUFunctionLibrary::GetCharacterInfoData(this, CharacterID, CharacterInfo) == false )
	{
		UE_LOG(LogTemp, Log, TEXT("Character Info Is Not Valid"));
		return;
	}

	TMap<int32, FMUAttributeInitValues>& AttributeByLevel = CharacterInfo.AttributeValueByLevel;

	if ( AttributeByLevel.Contains(InLevel) == false)
	{
		return;
	}

	FMUAttributeInitValues& AttributeInit = AttributeByLevel[InLevel];

	for (FMUAttributeValue& Initializer : AttributeInit.Attributes)
	{
		//데이터에 대한 InitValue Setting
		ASC->SetNumericAttributeBase( Initializer.InitAttribute,Initializer.InitializedValue );
	}
}

UMotionWarpingComponent* AMUCharacterBase::GetMotionWarpComponent()
{
	return MotionWarpingComponent;
}

void AMUCharacterBase::SetMotionWarp(const FName InName, EMotionWarpType InMotionWarpType, const float MotionWarpValue)
{
	
}

void AMUCharacterBase::ReleaseMotionWarp(const FName InName)
{
	MotionWarpingComponent->RemoveWarpTarget(InName);
}

