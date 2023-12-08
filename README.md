![image](https://user-images.githubusercontent.com/43964243/235778441-9dfb45ab-befd-480b-bc30-5eab5dc2efef.png)

# Unreal Engine Async Load Tool

<!-- Header Start -->
<a href = "https://docs.unrealengine.com/5.3/en-US/"> <img height="40" img width="40" src="https://cdn.simpleicons.org/unrealengine/white"> </a> 
<a href = "https://learn.microsoft.com/en-us/cpp/c-language"> <img height="40" img width="40" src="https://cdn.simpleicons.org/c"> </a>
<a href = "https://learn.microsoft.com/en-us/cpp/cpp-language"> <img height="40" img width="40" src="https://cdn.simpleicons.org/c++"> </a>
<img align="right" alt="Stars Badge" src="https://img.shields.io/github/stars/jdsherbert/Unreal-Engine-Async-Load-Tool?label=%E2%AD%90"/>
<img align="right" alt="Forks Badge" src="https://img.shields.io/github/forks/jdsherbert/Unreal-Engine-Async-Load-Tool?label=%F0%9F%8D%B4"/>
<img align="right" alt="Watchers Badge" src="https://img.shields.io/github/watchers/jdsherbert/Unreal-Engine-Async-Load-Tool?label=%F0%9F%91%81%EF%B8%8F"/>
<img align="right" alt="Issues Badge" src="https://img.shields.io/github/issues/jdsherbert/Unreal-Engine-Async-Load-Tool?label=%E2%9A%A0%EF%B8%8F"/>
<img align="right" src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FJDSherbert%2FUnreal-Engine-Async-Load-Tool%2Fhit-counter%2FREADME&count_bg=%2379C83D&title_bg=%23555555&labelColor=0E1128&title=🔍&style=for-the-badge">
<!-- Header End --> 

-----------------------------------------------------------------------

<a href="https://docs.unrealengine.com/5.3/en-US/"> 
  <img align="left" alt="Unreal Engine Tool" src="https://img.shields.io/badge/Unreal%20Engine%20Template-black?style=for-the-badge&logo=unrealengine&logoColor=white&color=black&labelColor=black"> </a>
  
<a href="https://choosealicense.com/licenses/mit/"> 
  <img align="right" alt="License" src="https://img.shields.io/badge/License%20:%20MIT-black?style=for-the-badge&logo=mit&logoColor=white&color=black&labelColor=black"> </a>
  
<br></br>

-----------------------------------------------------------------------
## Overview
Compact Blueprint Function Library class that contains a set of static functions that makes asynchronous loading of UObjects more unified and easier to do.
Utilizes the internal streaming assets manager and throwaway lambda callbacks.
Note that this is naturally latent, so always assess the validity of the asynchronously loaded object before use.

These functions are also available in blueprint!

-----------------------------------------------------------------------

### Why Asynchronously Load Anything?
Loading game assets asynchronously in Unreal Engine offers several benefits:

- Reduced Loading Times: Loading assets asynchronously allows the game to load resources in the background while the game is running. This helps to reduce initial loading times and enables a smoother transition between different levels or sections of the game.
- Improved Responsiveness: Asynchronous loading helps prevent the main thread from being blocked, allowing other processes to continue unimpeded. This stops the game from freezing or becoming unresponsive while assets are being loaded - players can continue interacting with the game while resources are loaded in the background.
- Optimized Resource Usage: Loading assets asynchronously allows for better management of system resources. Resources can be loaded on-demand, ensuring that only the necessary assets are loaded when needed. This helps to optimize memory usage and can contribute to overall system stability.
- Dynamic Loading and Unloading: Asynchronous loading enables dynamic loading and unloading of assets during gameplay. This is particularly useful in open-world games or environments with large, sprawling levels. Assets can be loaded or unloaded based on the player's location or progression, helping to conserve resources.
- Streaming and Seamless Transitions: Asynchronous loading supports streaming of assets, allowing for seamless transitions between different parts of the game world. This is essential for maintaining a continuous and immersive experience without noticeable interruptions or loading screens.
- Parallel Processing: By loading assets asynchronously, the game engine can take advantage of parallel processing capabilities. This means that while one set of assets is being loaded, other game-related tasks can be performed simultaneously, maximizing the utilization of available hardware resources.
- Adaptability to Varying Hardware: Asynchronous loading provides a level of adaptability to varying hardware specifications. It allows the game to adjust its asset loading strategy based on the performance capabilities of the player's system, ensuring a more consistent experience across a range of hardware configurations.
- Support for Large and Diverse Game Worlds: Games with extensive and diverse environments benefit significantly from asynchronous loading. It enables developers to efficiently manage the loading and unloading of assets, supporting expansive game worlds without sacrificing performance or requiring excessive memory usage.

In summary, loading game assets asynchronously in Unreal Engine contributes to a more responsive, efficient, and immersive gaming experience, particularly in scenarios where large and dynamic game worlds are involved.

-----------------------------------------------------------------------
### Using the Tool

First, implement the this gameplay module into your project.

Then, there are two ways to load with the tool:
1. Without Callback (Pointer Only)
```cpp
    template<class T = UObject>
    UFUNCTION(BlueprintCallable, Category = "Async Loader")
    static void AsyncLoadObject(TSoftObjectPtr<T> SoftPtr, T*& Out_LoadedObject);
```
Attempts to load an asset at a defined path asynchronously, and store it in a variable on completion.
```cpp    
    * EXAMPLE:
    * void MyFunction()
    * { 
    *    TSoftObjectPtr<USomeObject> ObjectSoftPtr = SoftObjectPtrToYourObject;
    *    USomeObject* SomeLoadedObject = nullptr;
    *    UAsyncLoader::AsyncLoadObject<USomeObject>(ObjectSoftPtr, SomeLoadedObject);
    *    // Use the loaded object
    *    if (SomeLoadedObject != nullptr) // Always check for nullptrs on asyncloaded objects
    *    {
    *       // Do something with the loaded object
    *    }
    * }
```


2. With Callback
```cpp
    template<class T = UObject>
    UFUNCTION(BlueprintCallable, Category = "Async Loader")
    static void AsyncLoadObject(TSoftObjectPtr<T> SoftPtr, void(*Callback)(T* LoadedObject));
```
Attempts to load an asset at a defined path asynchronously.
Will call the supplied function pointer on success, passing the loaded object pointer as a parameter.
Useful if you want to be notified when the load is completed.
```cpp
  * EXAMPLE:
  * @code
  * void MyLoadCompleteCallback(UObject* LoadedObject)
  * {
  *     // Handle the loaded object
  *     if (LoadedObject != nullptr) // Always check for nullptrs on asyncloaded objects
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
```


-----------------------------------------------------------------------

