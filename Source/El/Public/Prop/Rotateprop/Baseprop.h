// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Baseprop.generated.h"

UCLASS()
class EL_API ABaseprop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseprop();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void UpdateInfoWidget(FVector Loaction);
public:
	
	virtual void DoSomethingStart();
	virtual void DoSomethingEnd();
	virtual void DoSomethinging(float speed);
	virtual void InPower(float Speed);
	virtual void OutPower(float Speed);
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
	
	class UPropWidgetComponent*WidgetComp;

 	TSharedPtr<class SElUserInfoWidget> InfoWidget;

	class UBatteryComponent* BatteryComp;
	
	class UParticleSystemComponent*ParticleComp;
	
	class UParticleSystem* ParticleSystem;
	
	bool bOverlap = false;

	class AElCharacter*OverlapCharacter;

	bool bDosomething = false;

	bool bUsePower;

	bool bInPower=false;
	
	bool ParticleSystemActive=false;

	bool bBaseState;
};
