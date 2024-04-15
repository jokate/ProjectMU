// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_ClearFocus.h"

#include "AIController.h"

EBTNodeResult::Type UBTTask_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
   EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

   AAIController* Controller = OwnerComp.GetAIOwner();

   if (Controller == nullptr)
   {
      return EBTNodeResult::Failed;
   }

   Controller->ClearFocus(EAIFocusPriority::Gameplay);

   return EBTNodeResult::Succeeded;
}
