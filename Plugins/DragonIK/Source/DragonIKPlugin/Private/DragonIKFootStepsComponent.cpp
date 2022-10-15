// Fill out your copyright notice in the Description page of Project Settings.


#include "DragonIKFootStepsComponent.h"

// Sets default values for this component's properties
UDragonIKFootStepsComponent::UDragonIKFootStepsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;



	

}

/*
void UDragonIKFootStepsComponent::OnComponentDestroyed()
{
	// Don't forget to call parent function
	Super::OnComponentDestroyed();

	OnPlayerPickedUpItem.RemoveDynamic(this, &UDragonIKFootStepsComponent::ItemPickedUp);
}*/



// Called when the game starts
void UDragonIKFootStepsComponent::BeginPlay()
{
	Super::BeginPlay();

	OnCharacterFootStep.AddDynamic(this, &UDragonIKFootStepsComponent::CallFootSteps);

	/*
	if (OnCharacterFootStepItem.IsBound())
	{
		OnCharacterFootStepItem.Broadcast(pickedUpItem);
	}*/


}



void UDragonIKFootStepsComponent::SendInfoToDelegate(FName name,FTransform feet_transform_val,float height_difference_val)
{

	bone_name_input = name;

	foot_transform_input = feet_transform_val;

	height_difference_input = height_difference_val;

	allow_broadcast = true;

     


}

// Called every frame
void UDragonIKFootStepsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (allow_broadcast)
	{
		
		OnCharacterFootStep.Broadcast(bone_name_input, foot_transform_input, height_difference_input);

		allow_broadcast = false;

	}

	//OnPlayerPickedUpItem.AddDynamic(this, &UActionComponent::ItemPickedUp);


}

