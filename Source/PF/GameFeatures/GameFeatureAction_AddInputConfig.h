#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction_WorldActionBase.h"
#include "PF/Input/PFMappableConfigPair.h"
#include "GameFeatureAction_AddInputConfig.generated.h"


struct FComponentRequestHandle;
class APawn;

UCLASS()
class UGameFeatureAction_AddInputConfig : public UGameFeatureAction_WorldActionBase
{
	GENERATED_BODY()

public:
	/* UGameFeatureAction WorldActionBase's Interface */

	/* check world context, clearing active data */
	virtual void OnGameFeatureActivating(FGameFeatureActivatingContext& Context) override;
	virtual void OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context) override;

	/* attach the event handle to all pawn */
	virtual void AddToWorld(const FWorldContext& WorldContext, const FGameFeatureStateChangeContext& ChangeContext) override;

private:

	struct FPerContextData
	{
		TArray<TSharedPtr<FComponentRequestHandle>> ExtensionRequestHandles;
		TArray<TWeakObjectPtr<APawn>> PawnsAddedTo;
	};

	/* register handler from AddToWorld, call add or remove according to gameframeworkcomponentmanager event name */
	void HandlePawnExtension(AActor* Actor, FName EventName, FGameFeatureStateChangeContext ChangeContext);

	/* Add InputConfigs registered with gamefeature, and Pawn Caching in ContextData.PawnsAddedTo Array */
	void AddInputConfig(APawn* Pawn, FPerContextData& ActiveData);

	/* Called Reset, Remove all mappableconfig connected to local player */
	void RemoveInputConfig(APawn* Pawn, FPerContextData& ActiveData);

	/* Called Deactivate, Remove all config connected to pawn */
	void Reset(FPerContextData& ActiveData);

	TMap<FGameFeatureStateChangeContext, FPerContextData> ContextData;

	UPROPERTY(EditAnywhere)
	TArray<FPFMappableConfigPair> InputConfigs;

};
