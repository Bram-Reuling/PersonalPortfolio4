// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "PDPlatform.generated.h"

UENUM(BlueprintType)
enum EPlatformType { Static_PassThrough, Timed_PassThrough, Final };

UENUM(BlueprintType)
enum EPlatformCollisionType { RedPlayer, BluePlayer, None };

UCLASS()
class MULTIPLAYERDEMOUE5_API APDPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APDPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ChangePlatformCollision(EPlatformCollisionType Type);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                  AActor* OtherActor,
	                  UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex,
	                  bool bFromSweep,
	                  const FHitResult& SweepResult);
	void ChangeColorOfPlatform();

	UFUNCTION(BlueprintImplementableEvent)
	void EndLevelLogic(AActor* Actor);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UMaterialInterface* MaterialInterface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBoxComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TEnumAsByte<EPlatformType> PlatformType = Static_PassThrough;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ChangePlatformCollisionType,
		meta = (AllowPrivateAccess = true))
	TEnumAsByte<EPlatformCollisionType> PlatformCollisionType = None;

	UPROPERTY(ReplicatedUsing = OnRep_ChangePlatformColor)
	FLinearColor PlatformColor;

	UPROPERTY(ReplicatedUsing = OnRep_ChangeNumber)
	int Number = 0;

	UPROPERTY(EditAnywhere)
	float TimeBetweenChange = 1.0f;

	UFUNCTION()
	void OnRep_ChangePlatformColor();

	UFUNCTION()
	void OnRep_ChangePlatformCollisionType();

	FTimerHandle TimerHandle;

	UFUNCTION()
	void TimedPlatformLogic();

	UFUNCTION()
	void OnRep_ChangeNumber();
};
