// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ElCharacter.generated.h"

UCLASS()
class EL_API AElCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AElCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amount);

	void MoveRight(float amount);

	void RotateCamera(float amount);

	void ChangeCameraHeight(float amount);

	void CrouchEl();
	void UnCrouchEl();

	void InPower();
	void OutPower();
	bool bUsePower = false;
	
	FVector GetCameraLocation();

	void LeftOnClickLineTrance();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	/* COMPONENTS|组件 */
	//Spring Arm for holding camera 摄像机臂组件
	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	class USpringArmComponent* SpringArm;

	//Camera Component  摄像机组件
	UPROPERTY(EditDefaultsOnly, Category = "Base Character")
	class UCameraComponent *Camera;
	
	//角色生成的粒子
	class UParticleSystemComponent*ParticleComp;
	
	class UParticleSystem* ParticleSystem;
	
	bool ParticleSystemActive=false;
	//
	public:
	
	class UBatteryComponent *BatteryComp;
	//HUD
	TSharedPtr<class SElGameHUDWidget>GameHUDWidget;
	//class SElGameHUDWidget*GameHUDWidget;
	//
	void OverlapBaseprop(class ABaseprop* prop);
	class ABaseprop* CurrenOverlapBaseprop=nullptr;
	bool bOverlapBaseprop=false;

	void GameOver();
};
