// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DragonIKFootStepsComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCharacterFootStep,FName,bone_name,FTransform,foot_transform,float,height_difference);


UCLASS( ClassGroup=(DragonIK), meta=(BlueprintSpawnableComponent) )
//UCLASS()
class DRAGONIKPLUGIN_API UDragonIKFootStepsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDragonIKFootStepsComponent();



	UPROPERTY(BlueprintCallable, BlueprintAssignable)
		FCharacterFootStep OnCharacterFootStep;


	UFUNCTION(BlueprintImplementableEvent)
		void CallFootSteps(FName bone_name, FTransform foot_transform,float height_difference);


	FName bone_name_input = "None";
	FTransform foot_transform_input = FTransform::Identity;
	float height_difference_input = 0;

	bool allow_broadcast = false;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Foot Socket Array", PinHiddenByDefault))
		TArray<FName> foot_socket;





	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Foot Step Enter Height", PinHiddenByDefault))
		float foot_enter_height = 18;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Foot Step Exit Height", PinHiddenByDefault))
		float foot_exit_height = 20;




	void SendInfoToDelegate(FName name, FTransform feet_transform_val, float height_difference_val);


	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Foot Step Detection tolerance", PinHiddenByDefault))
		float foot_step_detection_tolerance = 0.5f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Approx Foot Height/Size", PinHiddenByDefault))
		float approx_foot_height = 10;
		*/


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//virtual void OnComponentDestroyed() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
