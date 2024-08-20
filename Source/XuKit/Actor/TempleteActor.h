#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TempleteActor.generated.h"

UCLASS()
class ATempleteActor : public AActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;
};
