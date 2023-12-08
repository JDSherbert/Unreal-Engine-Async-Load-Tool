// ©2023 JDSherbert. All rights reserved.

using UnrealBuildTool; 

public class AsyncLoaderModule : ModuleRules
{
	public AsyncLoaderModule(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange
		(
			new string[]
			{
				"Core", 
				"CoreUObject", 
				"Engine"
			}
		); 
	}
}