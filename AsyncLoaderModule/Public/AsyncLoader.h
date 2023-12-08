// ©2023 JDSherbert. All rights reserved.

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>

#include <Runtime/Engine/Classes/Kismet/BlueprintFunctionLibrary.h>

#include "AsyncLoader.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAsyncLoadComplete, UObject*, LoadedObject);

/**
 * Async Load Tool Class
 * \n
 * : UBlueprintFunctionLibrary
 * \n \n
 * This class contains a set of static functions that makes asynchronous loading of UObjects more unified and easier to do.
 * Utilizes the internal streaming assets manager and throwaway lambda callbacks.
 * @since Unreal Engine 5.2
 * @author JDSherbert
 */
UCLASS()
class ASYNCLOADER_API UAsyncLoader final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
public:

    /**
    * Attempts to load an asset at a defined path asynchronously, and store it in a variable on completion. \n
    * EXAMPLE:
    * @code
    * void MyFunction()
    * { 
    *    TSoftObjectPtr<USomeObject> ObjectSoftPtr = SoftObjectPtrToYourObject;
    *    USomeObject* SomeLoadedObject = nullptr;
    *    UAsyncLoader::AsyncLoadObject<USomeObject>(ObjectSoftPtr, SomeLoadedObject);
    *    // Use the loaded object
    *    if (SomeLoadedObject != nullptr)
    *    {
    *       // Do something with the loaded object
    *    }
    * }
    * @endcode
    * 
    * @note This is naturally latent, so always assess the validity of the asynchronously loaded object before use.
    * @tparam T The class of UObject to asynchronously load. Should be automatically determined by the SoftPtr reference.
    * @param SoftPtr The Soft Pointer to load. This is normally a path reference to the asset's template location in the project.
    * @param Out_LoadedObject The reference to a variable that will be populated with the loaded object.
    * @since Unreal Engine 5.2
    * @author JDSherbert
    */
    template<class T = UObject>
    UFUNCTION(BlueprintCallable, Category = "Async Loader")
    static void AsyncLoadObject(TSoftObjectPtr<T> SoftPtr, T*& Out_LoadedObject);

    /**
    * Attempts to load an asset at a defined path asynchronously.
    * Will call the supplied function pointer on success, passing the loaded object pointer as a parameter.
    * Useful if you want to be notified when the load is completed. \n
    * EXAMPLE:
    * @code
    * void MyLoadCompleteCallback(UObject* LoadedObject)
    * {
    *     // Handle the loaded object
    *     if (LoadedObject != nullptr)
    *     {
    *         // Do something with the loaded object
    *     }
    * }
    *
    * void MyFunction()
    * {
    *     TSoftObjectPtr<UObject> ObjectSoftPtr = SoftObjectPtrToYourObject;
    *     UAsyncLoader::AsyncLoadObject(ObjectSoftPtr, &MyLoadCompleteCallback);
    * }
    * @endcode
    * 
    * @note This is naturally latent, so always assess the validity of the asynchronously loaded object before use.
    * @tparam T The class of UObject to asynchronously load. Should be automatically determined by the SoftPtr reference.
    * @param SoftPtr The Soft Pointer to load. This is normally a path reference to the asset's template location in the project.
    * @param Callback The function to call on a success, with the LoadedObject as a parameter.
    * @since Unreal Engine 5.2
    * @author JDSherbert
    */
    template<class T = UObject>
    UFUNCTION(BlueprintCallable, Category = "Async Loader")
    static void AsyncLoadObject(TSoftObjectPtr<T> SoftPtr, void(*Callback)(T* LoadedObject));

private:

    /**
    * Validates a soft pointer reference to ensure it is pointer to a valid memory address with the correct type.
    * @param SoftPtr The Soft Pointer to load. This is normally a path reference to the asset's template location in the project.
    * @returns bool - true if valid.
    * @since Unreal Engine 5.2
    * @author JDSherbert
    */
    template<class T = UObject>
    bool ValidateObject(TSoftObjectPtr<T> SoftPtr);
};
