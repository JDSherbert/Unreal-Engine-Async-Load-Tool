// ©2023 JDSherbert. All rights reserved.

using UnrealBuildTool; 

public class Sherbert_AsyncLoader : ModuleRules
{
	public Sherbert_AsyncLoader(ReadOnlyTargetRules Target) : base(Target)
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