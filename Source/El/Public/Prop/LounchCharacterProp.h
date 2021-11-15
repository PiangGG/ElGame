// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LounchCharacterProp.generated.h"

UCLASS()
class EL_API ALounchCharacterProp : public AActor
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:	
	// Sets default values for this actor's properties
	ALounchCharacterProp();
	
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Update(bool bProp,float Speed_Go,float Speed_Back,float DeltaTime);

	void LounchCaracter();
private:
	
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
	bool bOverlap = false;
	class AElCharacter *OverlapCharacter;
	bool bDoingProp = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	float LounchSize = 1.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector StartLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector TargetLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector EndLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=attribute)
	FVector MoveSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Speed)
	float UpdateSpeed_Go=1.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Speed)
	float UpdateSpeed_Back=1.0f;

	class UParticleSystemComponent*ParticleComp;
	
	class UParticleSystem* ParticleSystem;
};
