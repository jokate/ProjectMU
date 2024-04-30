// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/TA/MUTA_DashAttackTrace.h"

#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AMUTA_DashAttackTrace::AMUTA_DashAttackTrace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AMUTA_DashAttackTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceStart();
}

void AMUTA_DashAttackTrace::TraceStart()
{
	ACharacter* Character = CastChecked<ACharacter>(SourceActor);
	const IGenericTeamAgentInterface* SourceActorTeam = CastChecked<IGenericTeamAgentInterface>(SourceActor);

	const auto* MeshComp = Character->GetMesh();

	if (!MeshComp)
	{
		return;
	}
	
	const FVector& CharacterLocation = Character->GetActorLocation();
	const FVector End = CharacterLocation + FVector::UpVector;
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitResults;
	ActorsToIgnore.Add(Character);

	UKismetSystemLibrary::SphereTraceMultiByProfile(this, CharacterLocation,
		End, 100.0f, TEXT("Weapon"), false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true,
		FLinearColor::Red, FLinearColor::Green, 1.0f);

	ProcessHitResult(HitResults);
}

