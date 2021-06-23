// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OverlapProp.generated.h"

UCLASS()
class AOverlapProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOverlapProp();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Update(bool bProp,float Speed_Go,float Speed_Back,float DeltaTime);
	//virtual void 
protected:
	//跟组件
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Component)
	class USceneComponent* RootComp;
	//网格体
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Component)
	class UStaticMeshComponent* BaseMesh;
	//碰撞体
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Component)
	class UBoxComponent* BoxComp;
	
public:
	void SetPropDoing(bool bDoSomething);
private:
	bool bOverlap = false;
	class AElCharacter*OverlapCharacter;
	bool bDoingProp = false;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator StartRotator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator TargetRotator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FRotator RotatorSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector StartLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector TargetLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector MoveSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector StartScale3D;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector TargetScale3D;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector MoveScale3D;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Speed)
	float UpdateSpeed_Go=1.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Speed)
	float UpdateSpeed_Back=1.0f;
};




