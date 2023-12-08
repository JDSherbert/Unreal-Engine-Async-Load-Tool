// ©2023 JDSherbert. All rights reserved.

#include "Sherbert_AsyncLoader/Public/AsyncLoader.h"

#include <Engine/Classes/Engine/AssetManager.h>
#include <Engine/Classes/Engine/StreamableManager.h>

template<class T>
void UAsyncLoader::AsyncLoadObject(TSoftObjectPtr<T> SoftPtr, T*& Out_LoadedObject)
{
	if (!ValidateObject(SoftPtr))
	{
		return;
	}

	FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
	StreamableManager.RequestAsyncLoad
	(SoftPtr.ToSoftObjectPath(), [SoftPtr, &Out_LoadedObject]()
		{
			Out_LoadedObject = Cast<T>(SoftPtr.Get());
		}
	);

	// Check if the object was already loaded synchronously
	if (StreamableManager.IsAsyncLoadComplete(SoftPtr.ToSoftObjectPath()))
	{
		Out_LoadedObject = Cast<T>(SoftPtr.Get());
	}
}

template<class T>
void UAsyncLoader::AsyncLoadObject(TSoftObjectPtr<T> SoftPtr, void(*Callback)(T* LoadedObject))
{
	if (!ValidateObject(SoftPtr))
	{
		return;
	}

	FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
	StreamableManager.RequestAsyncLoad
	(SoftPtr.ToSoftObjectPath(), [SoftPtr, Callback]()
		{
			T* LoadedObject = Cast<T>(SoftPtr.Get());
			if (Callback)
			{
				Callback(LoadedObject);
			}
		}
	);

	// Check if the object was already loaded synchronously
	if (StreamableManager.IsAsyncLoadComplete(SoftPtr.ToSoftObjectPath()))
	{
		if (Callback)
		{
			Callback(Cast<T>(SoftPtr.Get()));
		}
	}
}

template<class T>
bool UAsyncLoader::ValidateObject(TSoftObjectPtr<T> SoftPtr)
{
	return (SoftPtr != nullptr && TIsDerivedFrom<T, UObject>::IsDerived) ? true : false;
}
