// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DragonIKPhysicsHolder.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Curves/CurveFloat.h"

#include "DragonIKPhysicsComponent.generated.h"

class ADragonIKPhysicsHolder;








USTRUCT(BlueprintType)
struct FDragonData_PhysicsParentRelationship
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (DisplayName = "Child Bone Name", PinHiddenByDefault))
		FName child_bone_name = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (DisplayName = "Parent Bone Name", PinHiddenByDefault))
		FName parent_bone_name = "None";

};







USTRUCT(BlueprintType)
struct FDragonData_PhysicsHandleMultiplier
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (DisplayName = "Bone Name", PinHiddenByDefault))
		FName bone_name = "None";

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkeletalControl, meta = (DisplayName = "Bone Handle Strength Multiplier", PinHiddenByDefault))
			float bone_strength = 1;

};




UCLASS( ClassGroup=(DragonIK), meta=(DisplayName = "Dragonik Physanim Component",BlueprintSpawnableComponent) )
class DRAGONIKPLUGIN_API UDragonIKPhysicsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	
	// Sets default values for this component's properties
	UDragonIKPhysicsComponent();

	TArray<FTransform> Raw_Animation_Transforms;

	USkeletalMeshComponent* owning_skeleton;

	


	ADragonIKPhysicsHolder* handler_holder;



	UPROPERTY(EditAnywhere, Category = CoreInput, meta = (DisplayName = "Common Root Physics Bone (Eg:- Pelvis bone for Mannequin)"))
		FName Custom_Root_Bone = "pelvis";

	

	UPROPERTY(EditAnywhere, Category = CoreInput, meta = (DisplayName = "Individual Bone Selection"))
		TArray<FName> individual_bone_selection;



	TArray<FTransform> control_bone_relative_transforms;


	
	
	//UPROPERTY(EditAnywhere, Category = CoreInput, meta = (DisplayName = "Common Root Physics Bone (Eg:- Pelvis bone for Mannequin)"))
		FName Root_Clamping_Bone = "pelvis";
















	float slight_delay_counter = 0;



	UPROPERTY(EditAnywhere, Category = CoreInput, meta = (DisplayName = "Influence Stopping Bones"))
		TArray<FName> Influence_Stopping_Bones;



	UPROPERTY(EditAnywhere, Category = CoreInput, meta = (DisplayName = "Override Handle Strength Multiplier (Per bone)"))
		TArray<FDragonData_PhysicsHandleMultiplier> Override_Handle_Strength_Multiplier;






		


	//UPROPERTY(EditAnywhere, Category = Input, meta = (DisplayName = "Parent_Bone_Map"))
	TArray<FName> Parent_Bone_Map;


	//UPROPERTY(EditAnywhere, Category = Input, meta = (DisplayName = "Last Second Parent_Bone_Map"))
		TArray<FName> Last_Second_Parent_Bone_Map;


	TArray<TArray<int>> bone_to_bone_map;


	/*
	* This value will only be affected after the first initialization or after each new "grab".
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreInput, meta = (DisplayName = "Linear Strength"))
		int Linear_Strength = 1000;


	/*
* This value will only be affected after the first initialization or after each new "grab".
*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreInput, meta = (DisplayName = "Angular Strength"))
		int Angular_Strength = 1000;


	/*
* This value will only be affected after the first initialization or after each new "grab".
*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreInput, meta = (DisplayName = "Linear Damp"))
		int Linear_Damp = 5;


	/*
* This value will only be affected after the first initialization or after each new "grab".
*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreInput, meta = (DisplayName = "Angular Damp"))
		int Angular_Damp = 5;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CoreInput, meta = (DisplayName = "Interpolation Speed"))
		int Interpolation_Speed = 10;









	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ParentChildCustomLinking, meta = (DisplayName = "(optional) Use custom Parent-Child body mapping ?"))
		bool parent_child_ragdoll_state = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ParentChildCustomLinking, meta = (DisplayName = "(optional) Child-Parent physics relationship", EditCondition = "parent_child_ragdoll_state"))
		TMap<FName, FName> Parent_Child_Connection_Array;







	/*
	* Let the component auto handle the physics blending whether the body is in a hit state or an non-hit state.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Use Auto Blending and Hit Logic ?"))
		bool use_auto_blending_logic = true;



	bool is_released = false;


	/*
	* An additional optional function that works in tandem with the auto blending logic
	* Let the component also turn off/on physics simulation whenever it is not hitting any physics object.
	* This will preserve performance, but can make physics turned off all the time if the onHit() doesnt register any hits from the mesh.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Modify physics simulation during gameplay for saving performance ?", EditCondition = "use_auto_blending_logic"))
		bool modify_physics_states = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Hit Enable Speed", EditCondition = "use_auto_blending_logic"))
		float Hit_Enable_Speed = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Hit Disable Speed", EditCondition = "use_auto_blending_logic"))
		float Hit_Disable_Speed = 1;



//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Modify physics simulation during gameplay for performance ?"))
//		bool modify_physics_states = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Delay in secs until blending starts going down ?", EditCondition = "use_auto_blending_logic"))
		float hit_delay_time = 1.0f;





	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Delay for switching ragdoll off after regrab"))
	//	float delay_until_ragdoll_off = 1;



	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Ragdoll exit speed ?", EditCondition = "use_auto_blending_logic"))
	//	float get_up_speed = 5;


	float temporary_disable_speed = 5;








	/*
	* This is the physics body alpha over time whenever the character tries to transition from ragdoll to physanim animations.
	* Useful for getup animations.
	*/
	UPROPERTY(EditAnywhere, Category = AlphaAndPhysicsManagement, meta = (DisplayName = "Ragdoll to Physanim alpha blend curve over time", PinHiddenByDefault))
		FRuntimeFloatCurve Physanim_Enter_Curve;











	float get_up_timer = 0;

	bool ragdoll_mode = false;

	bool ragdoll_lock = false;








	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Bodies_Physics_Blend"))
		TArray<float> Bodies_Physics_Blend;

	TArray<float> Extra_Bone_Delay_Array;


	TArray<bool> Bodies_Physics_Hit_Bools;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (DisplayName = "Grab_Handle_Tasks_Queue"))
	TArray<bool> Grab_Handle_Tasks_Queue;

	TArray<bool> Remap_Physics_States_Queue;

	TArray<bool> Physics_States;

	TArray<bool> Grab_Handle_Locks;

	bool component_grabbing_state = false;



	bool Grab_Tasks_Pending = false;

	bool Need_To_Remap_PhysicsStates = false;

	float largest_blend_value = 0;

	FString test_debug = "None";


	FTransform relative_mesh_transform;
	USceneComponent* mesh_parent_reference;
	//bool bring_mesh_back_in_place = false;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "First Time Initialization"))
	void FirstTimeInitialization(USkeletalMeshComponent* skeleton_input);


	void SetSkeletonInput(USkeletalMeshComponent* skeleton_input);
	void CreateAllHandles();

	//UFUNCTION(BlueprintCallable, Category = Input, meta = (DisplayName = "Grab all handles"))
	void GrabAllHandles();



	/*
	* This is for re-grabbing all the physics handles managed by the physanim component
	*/
	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Re-Grab all handles"))
		void ReGrabAllHandles(bool exit_ragdoll);



	//UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Execute Animated Ragdoll"))
	//	void ExecuteAnimatedRagdoll();


	void CalculateParentInfluenceBones();

	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Update Handle Transforms"))
	void ModifyAllHandleTransforms();

	//UFUNCTION()
	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "DragonIK PhysAnims onHitCallback"))
	void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Cache Simulation State (Call this after simulating physics)"))
	void CacheSimulationStates();


	FName GetLastSecondParentBone(FName ChildBoneIndex, FName ParentBoneIndex);

	bool BoneIsChildOf(FName ChildBoneIndex, FName ParentBoneIndex);

	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Release all handles"))
	void ReleaseAllHandles(bool go_ragdoll);


	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Update Physanim Data"))
	void UpdatePhysanimData(int LinearStrength, int AngularStrength, int LinearDamp, int AngularDamp);



	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Set Interpolation"))
		void SetInterpolation(int inter_value);



	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Override Bone Handle Transform"))
		void Control_Bone_Handle(FName bone_name, FTransform override_transform, bool enable);



	UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Modify & Reset Bone Settings"))
		void Modify_Reset_Bone_Info(TArray<FName> bone_list);




	void UpdateBodyBlends();



	//UFUNCTION(BlueprintCallable, Category = DragonIK, meta = (DisplayName = "Exit Ragdoll into Animation"))
		void Physanim_Safe_Exit_Ragdoll();





	TArray<FTransform> custom_override_transforms;	
	TArray<bool> custom_override_bool;



		
};
