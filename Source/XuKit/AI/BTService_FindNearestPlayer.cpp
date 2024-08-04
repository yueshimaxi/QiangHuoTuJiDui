// copyright xuzhipeng


#include "BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	bool isPlayer= OwnerComp.GetAIOwner()->GetPawn()->ActorHasTag(FName("Player"));
	FName targetTag= isPlayer ?FName(TEXT("Enemy")) : FName(TEXT("Player"));
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), targetTag, FoundActors);
	if (FoundActors.Num() > 0)
	{
		AActor* NearestActor = FoundActors[0];
		float NearestDistance = TNumericLimits<float>::Max();
		for (int i = 0; i < FoundActors.Num(); i++)
		{
			float Distance = FVector::Dist(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), FoundActors[i]->GetActorLocation());
			if (Distance < NearestDistance)
			{
				NearestDistance = Distance;
				NearestActor = FoundActors[i];
			}
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetActor.SelectedKeyName, NearestActor);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TargetDistance.SelectedKeyName, NearestDistance);
	}
}
