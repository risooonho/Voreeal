#include "VoreealPrivatePCH.h"
#include "VoreealBasicVolumeActor.h"

#include "MessageLog.h"
#include "UObjectToken.h"
#include "MapErrors.h"

ABasicVolumeActor::ABasicVolumeActor(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BasicVolumeComponent = CreateDefaultSubobject<UBasicVolumeComponent>(TEXT("BasicVolumeComponent"));
	//BasicVolumeComponent->Mobility = EComponentMobility::Static;

	RootComponent = BasicVolumeComponent;
}

void ABasicVolumeActor::CheckForErrors()
{
	Super::CheckForErrors();

	FMessageLog MapCheck("MapCheck");

	if (!BasicVolumeComponent)
	{
		MapCheck.Warning()
			->AddToken(FUObjectToken::Create(this))
			->AddToken(FTextToken::Create(FText::FromString(TEXT("Basic volume actor has NULL BasicVolumeComponent property - please delete"))))
			->AddToken(FMapErrorToken::Create(TEXT("BasicVolumeComponentNull")));
	}
	else if (BasicVolumeComponent->GetVolume() == nullptr)
	{
		MapCheck.Warning()
			->AddToken(FUObjectToken::Create(this))
			->AddToken(FTextToken::Create(FText::FromString(TEXT("Basic volume actor has NULL BasicVolume property"))))
			->AddToken(FMapErrorToken::Create(TEXT("BasicVolumeNull")));
	}
}

bool ABasicVolumeActor::GetReferencedContentObjects(TArray<UObject*>& Objects) const
{
	Super::GetReferencedContentObjects(Objects);
	if (BasicVolumeComponent && BasicVolumeComponent->GetVolume())
	{
		Objects.Add(BasicVolumeComponent->GetVolume());
	}
	return true;
}

FString ABasicVolumeActor::GetDetailedInfoInternal() const
{
	return BasicVolumeComponent ? BasicVolumeComponent->GetDetailedInfoInternal() : TEXT("No_BasicVolumeComponent");
}

UBasicVolumeComponent* ABasicVolumeActor::GetBasicVolumeComponent() const
{
	return BasicVolumeComponent;
}
