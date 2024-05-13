// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Item/MUCraftData.h"
#include "Data/Item/MUItemData.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "GameDataManager.generated.h"

/***********************************************************************************/
UCLASS(Blueprintable)
class MOONU_API UGameDataManager : public UObject
{
	GENERATED_BODY()

public :

	virtual void PostLoad() override;
	
	static UGameDataManager* Get();

	FItemDataRow GetItemDataRow(const FName& InNameId) const;

	FItemDataRow GetItemDataRow(const int32 InItemId);

	FItemDropTableRow GetItemDropTableRow(const FName& InNameId) const;
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemDropTable;
	
	UPROPERTY(Transient, BlueprintReadWrite)
	TMap<int32, FName> ItemTableMap;
};
