// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/ElTypes.h"
#include "GameFramework/Actor.h"
#include "AutomaticProp.generated.h"

UCLASS()
class AAutomaticProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAutomaticProp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Update(const bool &Dosomething,float DeltaTime);

	void Update_Go(float DeltaTime);
	
	void Update_Back(float DeltaTime);

	void ChangeGoOrBack();
public:	
	//跟组件
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Component)
	class USceneComponent* RootComp;
	//网格体
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Component)
	class UStaticMeshComponent* BaseMesh;
	//碰撞体
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Component)
	class UBoxComponent* BoxComp;

	bool bDosomething;
	/*
	 * transform
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator StartRotator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator EndRotator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator TargetRotator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	float RotatorSpeed = 1.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector StartLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector EndLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector TargetLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	float MoveSpeed = 1.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector StartScale3D;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector EndScale3D;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector TargetScale3D;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	float ScaleSpeed = 1.0f;

	EAutomaticPropState::State CurrentState;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	float TransfomTime = 2.0f;

	FTimerHandle TransfomTimeTimerHandle;

};

