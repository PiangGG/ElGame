// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/GameOver/BaseGameOverActor.h"
#include "GameCompleteProp.generated.h"

/**
 * 
 */
UCLASS()
class EL_API AGameCompleteProp : public ABaseGameOverActor
{
	GENERATED_BODY()
	protected:
	
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
	public:
	AGameCompleteProp();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	class UStaticMeshComponent* BaseMesh2;
};
