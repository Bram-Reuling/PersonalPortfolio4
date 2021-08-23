// Fill out your copyright notice in the Description page of Project Settings.


#include "PDPlatform.h"

#include "MultiplayerDemoUE5Character.h"

// Sets default values
APDPlatform::APDPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(
		TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0, 0, 0));
	}

	CollisionComponent->SetRelativeLocation(FVector(0, 0, 5));

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APDPlatform::BeginOverlap);
}

void APDPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Here we list the variables we want to replicate + a condition if wanted
	DOREPLIFETIME(APDPlatform, PlatformColor);
	DOREPLIFETIME(APDPlatform, PlatformCollisionType);
	DOREPLIFETIME(APDPlatform, Number);
}


// Called when the game starts or when spawned
void APDPlatform::BeginPlay()
{
	Super::BeginPlay();
	if (PlatformType == Timed_PassThrough)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APDPlatform::TimedPlatformLogic, TimeBetweenChange, true, 0.0f);	
	}
}

// Called every frame
void APDPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APDPlatform::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	Number++;
	UE_LOG(LogTemp, Warning, TEXT("Overlap Detected"));

	switch (PlatformCollisionType)
	{
		case RedPlayer:
			UE_LOG(LogTemp, Warning, TEXT("Is Red"));
			break;
		case BluePlayer:
			UE_LOG(LogTemp, Warning, TEXT("Is Blue"));
			break;
		case None:
			UE_LOG(LogTemp, Warning, TEXT("Is None"));
			break;
		default:
			break;
	}
	
	if (PlatformType == Static_PassThrough && PlatformCollisionType == None)
	{
		UE_LOG(LogTemp, Warning, TEXT("Has Static_PassThrough && None"));
		AMultiplayerDemoUE5Character* Player = Cast<AMultiplayerDemoUE5Character>(OtherActor);

		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast success!"));
			EPlayerCollisionType PlayerCollisionType = Player->GetCollisionType();

			switch (PlayerCollisionType)
			{
			case Red:
				PlatformCollisionType = RedPlayer;
				PlatformColor = FColor::Red;
				UE_LOG(LogTemp, Warning, TEXT("Red Player"));
				break;
			case Blue:
				PlatformCollisionType = BluePlayer;
				PlatformColor = FColor::Blue;
				UE_LOG(LogTemp, Warning, TEXT("Blue Player"));
				break;
			default:
				PlatformCollisionType = None;
				UE_LOG(LogTemp, Warning, TEXT("None"));
				break;
			}

			// Change the Collision Preset
			ChangePlatformCollision(PlatformCollisionType);
			ChangeColorOfPlatform();
		}
	}
	else if (PlatformType == Final)
	{
		//GetWorldTimerManager().SetTimer(TimerHandle, this, &APDPlatform::EndLevelLogic, TimeBetweenChange, false, 0.0f);
		EndLevelLogic(OtherActor);
	}
}

void APDPlatform::ChangeColorOfPlatform()
{
	UE_LOG(LogTemp, Warning, TEXT("Setting color"));
	UMaterialInstanceDynamic* MaterialInstanceDynamic = VisualMesh->CreateDynamicMaterialInstance(
		0, MaterialInterface, "Color");
	MaterialInstanceDynamic->SetVectorParameterValue("Color", PlatformColor);
}

void APDPlatform::OnRep_ChangePlatformColor()
{
	UE_LOG(LogTemp, Warning, TEXT("Setting color 2"));
	ChangeColorOfPlatform();
}

void APDPlatform::OnRep_ChangePlatformCollisionType()
{
	UE_LOG(LogTemp, Warning, TEXT("OnRep Type"));
	ChangePlatformCollision(PlatformCollisionType);
}

void APDPlatform::TimedPlatformLogic()
{
	switch (PlatformCollisionType)
	{
		case RedPlayer:
			PlatformCollisionType = BluePlayer;
			PlatformColor = FColor::Blue;
			UE_LOG(LogTemp, Warning, TEXT("Blue Player"));
			break;
		case BluePlayer:
			PlatformCollisionType = RedPlayer;
			PlatformColor = FColor::Red;
			UE_LOG(LogTemp, Warning, TEXT("Red Player"));
			break;
		case None:
			PlatformCollisionType = RedPlayer;
			PlatformColor = FColor::Red;
			UE_LOG(LogTemp, Warning, TEXT("Red Player"));
			break;
		default:
			break;
	}

	ChangePlatformCollision(PlatformCollisionType);
	ChangeColorOfPlatform();
}

void APDPlatform::OnRep_ChangeNumber()
{
	UE_LOG(LogTemp, Warning, TEXT("Changed number!"));
}
