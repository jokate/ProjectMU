// Fill out your copyright notice in the Description page of Project Settings.


#include "Indicator/MULinearSkillIndicator.h"


// Sets default values
AMULinearSkillIndicator::AMULinearSkillIndicator()
{
	IndicatorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Indicator Mesh");
}

void AMULinearSkillIndicator::CalculateIndicatorMesh()
{
	// 테스트 용 코드 / 차후 데이터 추가 후에 가공화 예정. -> Circular인 경우에는 별도 처리 필요.
	// -> Linear 인 경우에는 카메라가 잡아준 Location에 대해서 Direction을 구하는 방식으로 구현화 가능.
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if ( IsValid( PC ) == false )
	{
		return;
	}

	FVector WorldPos;
	FVector WorldDirection;
	PC->DeprojectMousePositionToWorld( WorldPos, WorldDirection );

	FVector GroundIntersection = FMath::LinePlaneIntersection(
		WorldPos,
		WorldPos + WorldDirection * 10000.0f,  // 충분히 먼 점
		FVector(0, 0, 0),                      // 지면 상의 한 점
		FVector::UpVector                      // 지면의 법선 (Z축)
	);

	//DrawDebugSphere( GetWorld(), WorldPos, 50, 50, FColor::White, true);
	//DrawDebugSphere( GetWorld(), GroundIntersection, 50, 50, FColor::Blue);

	APawn* OwnerPawn = PC->GetPawn();

	if ( IsValid( OwnerPawn ) == false )
	{
		return;
	}

	// 플레이어 위치에서 지면과의 교차점을 향하는 벡터 계산
	FVector SkillDirection = GroundIntersection - OwnerPawn->GetActorLocation();
	SkillDirection.Z = 0;
	SkillDirection.Normalize();
	
	// 목표 회전 계산
	FRotator TempTargetRotation = SkillDirection.Rotation();
	SetActorRotation(TempTargetRotation);

	TargetLocation = OwnerPawn->GetActorLocation() + SkillDirection * MaxAttackDistance;
	TargetLocation.Z = GroundIntersection.Z;
	
	TargetRotation = TempTargetRotation;
	
	DrawDebugSphere( GetWorld(), TargetLocation, 50, 50, FColor::Blue);
}

void AMULinearSkillIndicator::SetupIndicatorInfo(APlayerController* OwnerController, float AttackDistance,
	float InAOERadius)
{
	Super::SetupIndicatorInfo(OwnerController, AttackDistance, InAOERadius);

	if ( IsValid( IndicatorMeshComponent ) == true )
	{
			
	}
}
